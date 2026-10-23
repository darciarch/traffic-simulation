# Traffic Simulation

A simple object-oriented traffic simulation written in C++17. Vehicles (PKW, Fahrrad) move along roads (`Weg`), change direction at intersections (`Kreuzung`), and PKWs refuel at gas stations. The simulation is visualized graphically by the Java-based `SimuServer.jar`.

## Structure

| File | Description |
|---|---|
| `Simulationsobjekt` | Base class of all simulation objects |
| `Fahrzeug`, `PKW`, `Fahrrad` | Vehicle hierarchy (speed, fuel consumption, tank) |
| `Weg`, `Tempolimit` | Roads and speed limits (Innerorts, Landstrasse, Autobahn) |
| `Kreuzung` | Intersections connecting roads, gas station |
| `Verhalten` (`Fahren`, `Parken`) | A vehicle's behavior on a road |
| `Fahrausnahme` (`Losfahren`, `Streckenende`) | Exceptions for simulation events |
| `vertagt_liste`, `vertagt_aktion` | List with deferred updates |
| `SimuClient`, `SimuClientSocket` | Communication with the graphics server (Boost.Asio) |
| `Main.cpp` | Example scenarios as `vAufgabe_*` functions |

## Requirements

- `g++` with C++17 support
- Boost (Asio, Thread)
- Java (for the graphics server `SimuServer.jar`)

## Build and Run

```sh
make        # build and run
make run    # run only
make clean  # remove the binary
```

The scenario to run is selected in the `main()` function in `Main.cpp` (default: `vAufgabe_7`, a road network with graphical output). The graphics server is started automatically by the program.
