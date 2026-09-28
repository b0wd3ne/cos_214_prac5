#ifndef CAMPUSGUARD_APP_SCENARIOS_H
#define CAMPUSGUARD_APP_SCENARIOS_H

class CampusGuardSystem;

// The two end-to-end demo stories required by Task 3 of the practical.
// Each takes the fully-wired system and drives it the way an operator
// would - through Commands and the Facade, never by reaching into the
// subsystems directly - so the output is a trace of one coherent
// incident, not six isolated pattern demonstrations.
namespace Scenarios {

// Story 1: "Chemistry lab fire" - Command, Mediator, Composite, State,
// Adapter. Runs raw Commands through the OperatorConsole (no Facade), to
// show the low-level building blocks working on their own.
void runChemistryLabFire(CampusGuardSystem& system);

// Story 2: "Library medical emergency" - all six patterns in one flow:
// Facade, Command, Mediator, State, Composite, Adapter. Runs through
// CampusGuardFacade for the high-level workflow, then drops back to raw
// Commands to demonstrate a couple of additional failure cases.
void runLibraryMedicalEmergency(CampusGuardSystem& system);

}  // namespace Scenarios

#endif  // CAMPUSGUARD_APP_SCENARIOS_H
