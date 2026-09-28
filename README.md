# CampusGuard — COS 214 Practical 5

CampusGuard is an emergency-response coordination platform for a university
campus, built in C++11 to demonstrate six GoF design patterns working
together as one application: **Command, Mediator, Adapter, Facade, State,
and Composite**.

## Team

| Person | Focus | Patterns |
|---|---|---|
| A | Operator and Incident (`incident/`, `commands/`, `common/`) | Command, State |
| B | Coordination and Integration (`response/`, `app/`) | Mediator |
| C | Campus, Comms and Ops (`campus/`, `comms/`, `external/`, `facade/`) | Composite, Adapter, Facade |

## Run it (Docker — used for the assessed demo)

```bash
docker compose up --build
```

This builds the image (Ubuntu 22.04 + `build-essential`, `gdb`, `valgrind`)
and runs the two end-to-end demo stories back to back.

### GDB / Valgrind inside Docker

```bash
docker compose run --rm tools bash
# inside the container:
gdb ./campusguard
valgrind --leak-check=full --show-leak-kinds=all ./campusguard
```

## Run it locally (without Docker)

Requires a C++11 compiler and GNU Make.

```bash
make          # build
make run      # build (if needed) and run
make clean    # remove build artifacts
```

## What you'll see

Two stories run one after another, each showing several patterns
collaborating in a single flow:

1. **Chemistry lab fire** — Command, Mediator, Composite, State, Adapter.
   A raw sequence of operator Commands: dispatch security, lock the
   building (locking cascades into every zone inside it), alert (delivered
   through both the modern app-push channel and, via the Adapter, a
   simulated legacy pager). Includes an illegal state-transition failure
   case and a full undo.
2. **Library medical emergency** — all six patterns in one flow. Driven
   through `CampusGuardFacade`, which coordinates incident verification,
   dispatch, building access, and alerts in one call. Includes a
   unit-already-dispatched failure case and a partial-comms-failure case
   (the legacy channel fails for an unregistered zone; the app-push
   channel still delivers).

## Project layout

```
app/          composition root (CampusGuardSystem) + the two Scenarios + main()
incident/     Incident, IncidentState (State pattern)
commands/     Command, 4 concrete commands, OperatorConsole (Command pattern)
response/     ResponseComponent, DispatchCoordinator, SecurityTeam,
              MedicalTeam, FacilitiesCrew (Mediator pattern)
campus/       CampusArea, Building, Zone, AccessControlCentre (Composite)
comms/        NotificationChannel, AppPushChannel, LegacyPagerAdapter,
              CommunicationsCentre (Adapter pattern)
external/     LegacyPagerGateway — simulated third-party legacy code
facade/       CampusGuardFacade
common/       shared Types, Exceptions, Logger
```

## Branching

- `main` is always buildable.
- Work on `feature/<area>-<short-name>` branches and open a pull request.
- Every PR needs at least one review from a teammate before merging.
