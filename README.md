# Desert Travel Simulator
**Object-Oriented Programming (POO) 2024/2025 - DEIS/ISEC**

## Authors
* Pedro (from comments)
* Tiago (from comments)

## Description

This is a C++ console application that simulates the management of caravans in a desert. The simulation is turn-based (using "instantes" or instants) and takes place on a grid-based map containing desert, mountains, and cities.

The user interacts via text commands to manage their caravans, trade goods in cities, combat barbarians, and discover items. A key feature is a custom `Buffer` class, which draws the game state to an in-memory character buffer before printing to the console to prevent flickering.

## Components

The system is a single executable, `SimDeserto`. The core logic is built around C++ classes:
* **Deserto:** The main simulation engine, manages the map, time, and all entities.
* **Caravana:** Base class for caravans, with derived types:
    * `CaravanaComercio` (Commerce Caravan)
    * `CaravanaMilitar` (Military Caravan)
    * `CaravanaSecreta` (Secret Caravan)
* **Barbaro:** AI-controlled barbarian caravans.
* **Cidade:** City entities where trading occurs.
* **Item:** Discoverable items on the map.
* **Buffer:** Custom text buffer for console rendering.

## Technologies

* **C++** (C++17)
* **CMake** (for build automation)
* **C++ Standard Library** (`vector`, `map`, `string`, `memory`, etc.)
* **Doxygen** (for documentation)

## Directory Structure

* `src/`: C++ source files (`.cpp`).
* `include/`: C++ header files (`.h`).
* `config/`: Simulation configuration files (e.g., `exemplo.txt`) and command scripts (e.g., `combates.txt`).
* `documentacao/`: Contains the project assignment PDF and Doxygen-generated documentation.
* `cmake-build-debug/`: Default CMake build output directory (ignored by .gitignore).

## How to Compile and Run

### Prerequisites

1.  A C++17 compliant compiler (e.g., GCC, Clang, MSVC).
2.  CMake (version 3.26 or higher).

### 1. Compile the Project

Use the standard CMake workflow. From the project root directory:

```bash

mkdir cmake-build-debug
cd cmake-build-debug
cmake ..
cmake --build .

````

### 2. Run the Simulation

1.  Run the executable created in the build directory:
    ```bash
    ./cmake-build-debug/SimDeserto
    ```

2.  The simulation starts in **Phase 1**. You must first load a configuration file:
    ```
    config exemplo
    ```

3.  The simulation is now in **Phase 2**. You can run commands to interact with the world or advance time.
    * To execute a pre-written script of commands:
        ```
        exec combates
        ```
    * To advance the simulation by one "instant":
        ```
        prox
        ```
    * To move a caravan:
        ```
        move 1 D
        ```

## Commands

All commands are defined in the project assignment PDF.

### Phase 1: Configuration
* `config <filename>`: Loads the map and parameters from a config file (e.g., `config exemplo`).
* `sair`: Exits the program.

### Phase 2: Simulation
* `exec <filename>`: Executes a script of commands from a file in the `config/` directory.
* `prox <n>`: Advances the simulation by `n` instants (or 1 if `n` is omitted).
* `comprac <C> <T>`: Buy a caravan of type `T` (C, M, or S) at city `C`.
* `precos`: Lists the purchase and sale prices of merchandise.
* `cidade <C>`: Lists the contents of city `C`.
* `caravana <N>`: Shows detailed information for caravan `N`.
* `compra <N> <M>`: Buy `M` tons of merchandise for caravan `N` (must be in a city).
* `vende <N>`: Sell all merchandise from caravan `N` (must be in a city).
* `move <N> <X>`: Move caravan `N` one position in direction `X` (e.g., C, B, E, D, CE, CD, BE, BD).
* `auto <N>`: Sets caravan `N` to autonomous behavior mode.
* `stop <N>`: Stops autonomous behavior for caravan `N`.
* `barbaro <l> <c>`: Creates a new barbarian caravan at coordinates (l, c).
* `areia <l> <c> <r>`: Creates a sandstorm at (l, c) with radius `r`.
* `moedas <N>`: Adds (or removes if negative) `N` coins from the player.
* `tripul <N> <T>`: Buy `T` crew members for caravan `N` (must be in a city).
* `saves <name>`: Saves the current visual state of the buffer to memory with a given name.
* `loads <name>`: Displays a previously saved buffer state (does not restore game state).
* `lists`: Lists all saved buffer states in memory.
* `dels <name>`: Deletes a saved buffer state from memory.
* `terminar`: Ends the simulation and returns to Phase 1.
