#include <iostream>

#include "CampusGuardSystem.h"
#include "Scenarios.h"

// Entry point. Runs both required end-to-end stories against one wired-up
// CampusGuardSystem, back to back, so a tutor sees one coherent
// application rather than six isolated pattern demos. This is what
// `docker compose up --build` launches for the assessed demonstration.
int main() {
  std::cout << "CampusGuard - COS 214 Practical 5" << std::endl;

  CampusGuardSystem system;

  Scenarios::runChemistryLabFire(system);
  Scenarios::runLibraryMedicalEmergency(system);

  std::cout << "\nCampusGuard run complete." << std::endl;
  return 0;
}
