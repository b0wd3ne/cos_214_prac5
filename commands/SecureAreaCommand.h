#ifndef CAMPUSGUARD_COMMANDS_SECURE_AREA_COMMAND_H
#define CAMPUSGUARD_COMMANDS_SECURE_AREA_COMMAND_H

#include <string>

#include "Command.h"
#include "../common/Types.h"

class AccessControlCentre;

// Locks/restricts/opens an area. Remembers the area's previous access mode
// so undo() can put it back exactly as it was - this is the command with
// genuinely meaningful undo, since re-running execute() would not be
// enough to know what to revert to.
class SecureAreaCommand : public Command {
 public:
  SecureAreaCommand(AccessControlCentre& access, std::string areaName,
                     AccessMode newMode);

  void execute() override;
  void undo() override;
  std::string describe() const override;

 private:
  AccessControlCentre& access_;  // receiver (non-owning)
  std::string areaName_;
  AccessMode newMode_;
  AccessMode previousMode_ = AccessMode::Open;
  bool executed_ = false;
};

#endif  // CAMPUSGUARD_COMMANDS_SECURE_AREA_COMMAND_H
