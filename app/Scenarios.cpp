#include "Scenarios.h"

#include <iostream>
#include <memory>

#include "CampusGuardSystem.h"
#include "../commands/DispatchUnitCommand.h"
#include "../commands/EvacuationOrderCommand.h"
#include "../commands/IssueAlertCommand.h"
#include "../commands/SecureAreaCommand.h"
#include "../common/Exceptions.h"
#include "../common/Logger.h"

namespace {
void section(const std::string& title) {
  std::cout << "\n=== " << title << " ===" << std::endl;
}
}  // namespace

namespace Scenarios {

void runChemistryLabFire(CampusGuardSystem& system) {
  section("Story 1: Chemistry lab fire");

  Incident& fire = system.registry().create(
      "Fire in the chemistry lab", IncidentType::Fire, Severity::Critical,
      "Science Block");
  fire.verify();

  section("Dispatch security (Command -> Mediator fan-out)");
  system.console().execute(std::unique_ptr<Command>(
      new DispatchUnitCommand(system.security(), fire)));

  section("Lock the building (Composite recursion into both labs)");
  system.console().execute(std::unique_ptr<Command>(
      new SecureAreaCommand(system.access(), "Science Block",
                             AccessMode::Locked)));

  section("Alert (Adapter: reaches AppPush and the legacy pager)");
  system.console().execute(std::unique_ptr<Command>(new IssueAlertCommand(
      system.comms(), "Science Block", fire.severity(),
      "Fire reported, area locked")));

  section("Failure case: illegal transition");
  try {
    fire.resolve();  // Dispatched cannot jump straight to Resolved
  } catch (const InvalidTransitionException& e) {
    Logger::log(std::string("[SCENARIO] Caught expected error: ") + e.what());
  }

  section("Undo the alert, then the lock (LIFO)");
  system.console().undoLast();
  system.console().undoLast();

  section("Legal path to a terminal state");
  fire.contain();
  fire.resolve();
  Logger::log("[SCENARIO] Incident #" + std::to_string(fire.id()) +
              " final state: " + fire.stateName());
}

void runLibraryMedicalEmergency(CampusGuardSystem& system) {
  section("Story 2: Library medical emergency");

  Incident& medical = system.registry().create(
      "Student collapsed in the reading room", IncidentType::Medical,
      Severity::Medium, "Library");

  // The Facade's dispatch hook needs to know which Incident it's acting on,
  // since CampusGuardFacade::evacuateBuilding() only takes an id + area
  // name, not an Incident reference.
  system.setActiveIncident(&medical);

  section("facade.evacuateBuilding(): verify + dispatch + restrict + alert");
  system.facade().evacuateBuilding(medical.id(), "Library");
  Logger::log("[SCENARIO] Incident #" + std::to_string(medical.id()) +
              " state after facade call: " + medical.stateName());

  section("Failure case: unit already unavailable");
  Incident& secondCall = system.registry().create(
      "Second caller, same building", IncidentType::Medical, Severity::Low,
      "Library");
  try {
    // Medical was already dispatched by the facade call above and has not
    // been freed up again, so this must fail.
    system.console().execute(std::unique_ptr<Command>(
        new DispatchUnitCommand(system.medical(), secondCall)));
  } catch (const UnitUnavailableException& e) {
    Logger::log(std::string("[SCENARIO] Caught expected error: ") + e.what());
  }

  section("Failure case: legacy channel fails, AppPush still delivers");
  // "Library Annex" has no registered legacy zone code, so the adapter's
  // gateway call fails; CommunicationsCentre catches it internally, logs
  // it, and still delivers via AppPush - a failure handled sensibly rather
  // than silently ignored.
  system.comms().broadcastAlert("Library Annex", Severity::Low,
                                 "Test page to an unregistered zone");

  section("Stand down");
  system.facade().standDown("Library");
  Logger::log("[SCENARIO] Building access after stand-down: " +
              std::to_string((int)system.access().areaAccess("Library")));
}

}  // namespace Scenarios
