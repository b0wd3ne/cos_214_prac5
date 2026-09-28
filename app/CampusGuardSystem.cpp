#include "CampusGuardSystem.h"

#include "../campus/Building.h"
#include "../campus/Zone.h"
#include "../commands/DispatchUnitCommand.h"
#include "../common/Logger.h"
#include "../external/LegacyPagerGateway.h"

std::unique_ptr<CampusArea> CampusGuardSystem::buildCampusTree() {
  // Campus (root Building)
  //   |-- Science Block (Building)
  //   |     |-- Chemistry Lab (Zone)
  //   |     `-- Physics Lab (Zone)
  //   `-- Library (Building, no sub-zones)
  //
  // Demonstrates real Composite recursion: locking "Science Block" cascades
  // into both labs, while "Library" is unaffected.
  std::unique_ptr<CampusArea> campus(new Building("Campus"));

  std::unique_ptr<CampusArea> scienceBlock(new Building("Science Block"));
  scienceBlock->add(std::unique_ptr<CampusArea>(new Zone("Chemistry Lab")));
  scienceBlock->add(std::unique_ptr<CampusArea>(new Zone("Physics Lab")));
  campus->add(std::move(scienceBlock));

  campus->add(std::unique_ptr<CampusArea>(new Building("Library")));

  return campus;
}

CampusGuardSystem::CampusGuardSystem()
    : mediator_(),
      security_("Campus Security", &mediator_),
      medical_("Medical Team", &mediator_),
      facilities_("Facilities Crew", &mediator_),
      campusRoot_(buildCampusTree()),
      access_(campusRoot_.get(), &mediator_),
      comms_(&mediator_),
      appPush_(),
      legacyPager_(new LegacyPagerAdapter(
          std::unique_ptr<LegacyPagerGateway>(new LegacyPagerGateway()))),
      registry_(),
      console_(),
      facade_(new CampusGuardFacade(campusRoot_.get(), &access_, &comms_)) {
  // ---- Adapter: give the legacy pager zone codes for our real areas ----
  legacyPager_->registerZoneCode("Science Block", "Z-SCI");
  legacyPager_->registerZoneCode("Library", "Z-LIB");

  // ---- CommunicationsCentre gets both channels: modern + adapted legacy --
  comms_.addChannel(&appPush_);
  comms_.addChannel(legacyPager_.get());

  // ---- Mediator: wire the routing table -----------------------------
  // When any colleague reports a unit is on scene, both AccessControlCentre
  // and CommunicationsCentre are notified (they log what they observed;
  // Scenarios then issues the real SecureAreaCommand/IssueAlertCommand,
  // which is the visible "one command triggers coordinated behaviour"
  // sequence the practical asks for).
  mediator_.registerComponent(ResponseEvent::Type::UnitOnScene, &access_);
  mediator_.registerComponent(ResponseEvent::Type::UnitOnScene, &comms_);
  mediator_.registerComponent(ResponseEvent::Type::AreaSecured, &comms_);

  // ---- Facade: wire its hooks back into real Commands -----------------
  facade_->setVerifyIncidentHook([this](int incidentId) {
    Incident* incident = registry_.find(incidentId);
    if (incident != nullptr) {
      incident->verify();
    }
  });
  facade_->setDispatchHook(
      [this](const std::string& unitType, const std::string& areaName) {
        dispatchByUnitType(unitType, areaName);
      });
}

void CampusGuardSystem::dispatchByUnitType(const std::string& unitType,
                                            const std::string& areaName) {
  if (activeIncident_ == nullptr) {
    Logger::log(
        "[SYSTEM] dispatchByUnitType called with no active incident set - "
        "ignoring dispatch of " +
        unitType + " to " + areaName);
    return;
  }

  ResponseComponent* unit = nullptr;
  if (unitType == "Security") {
    unit = &security_;
  } else if (unitType == "Medical") {
    unit = &medical_;
  } else if (unitType == "Facilities") {
    unit = &facilities_;
  } else {
    Logger::log("[SYSTEM] Unknown unit type requested: " + unitType);
    return;
  }

  console_.execute(std::unique_ptr<Command>(
      new DispatchUnitCommand(*unit, *activeIncident_)));
}
