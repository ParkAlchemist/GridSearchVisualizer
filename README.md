# GridSearchVisualizer updated 12.12.2025

An interactive desktop application that visualizes pathfinding algorithms on a 2D grid using Qt (QMake + C++).

Repository: https://github.com/ParkAlchemist/GridSearchVisualizer

Table of Contents
- [Overview](#overview)
- [Features (what's actually in this program)](#features-whats-actually-in-this-program)
- [Requirements](#requirements)
- [Build & Run](#build--run)
- [Usage](#usage)
- [Files of interest](#files-of-interest)
- [Maybe someday (roadmap)](#maybe-someday-roadmap)
- [Troubleshooting](#troubleshooting)
- [License](#license)
- [Contact](#contact)

## Overview
GridSearchVisualizer is a Qt-based visualizer for studying and demonstrating graph search / pathfinding algorithms on a rectangular grid. The UI provides an interactive canvas and controls to run and step through searches so you can observe frontier expansion and final path recovery.

## Features
- Interactive Qt GUI (mainwindow.ui, mainwindow.cpp)
- Grid canvas and drawing code (customview.*)
- Implemented search algorithms:
  - A* (searchastar.*)
  - Dijkstra (searchdijkstra.*)
  - Greedy Best-First Search (searchgbfs.*)
  - Breadth-First Search (searchbfs.*)
  - Depth-First Search (searchdfs.*)
- Grid / node representation and utilities (gridgraph.*, squarenode.*)
- Helper utilities in helperfunctions.*
- Project files for building with qmake (src/GridSearchVisualizer.pro, src/PathFinder.pro)
- Prebuilt Windows installer in repo root: GSVInstaller.exe

## Requirements
- Qt 5.x or Qt 6.x (Qt Widgets)
- A C++17-capable compiler (g++, clang, MSVC)
- QMake (used by the provided .pro files)
- Optional: Qt Creator for building and running from an IDE

Tested platforms depend on your Qt build and toolchain; the project includes a Windows installer in the repository.

## Build & Run

1. Clone the repository
```bash
git clone https://github.com/ParkAlchemist/GridSearchVisualizer.git
cd GridSearchVisualizer/src
```

2. Build with qmake + make (Linux/macOS)
```bash
qmake
make
# run the produced binary, e.g.:
./GridSearchVisualizer
```

Windows
- You can open `src/GridSearchVisualizer.pro` in Qt Creator, configure a kit, Build and Run.
- There is also a prebuilt installer in the repo root: `GSVInstaller.exe`.

Notes
- If your system provides multiple qmake executables (Qt5 vs Qt6), use the appropriate one (e.g., `qmake-qt6` or the full path to the qmake inside your Qt installation).
- Out-of-source builds are supported by creating a build directory and invoking qmake from there:
```bash
mkdir build && cd build
qmake ../GridSearchVisualizer.pro
make
```

## Usage
Typical interactions provided by the application:
- Place the Start and Goal nodes on the grid.
- Draw or erase obstacles on the grid.
- Select one of the available algorithms (A*, Dijkstra, Greedy Best-First, BFS, DFS).
- Start the search visualization and watch the frontier expansion and visited sets.
- Step through the algorithm or run at adjustable speed (controls are provided in the UI).
- Reset the grid or algorithm state to try different scenarios.

UI labels and exact control names are those in the shipped `mainwindow.ui` — run the built application to see the precise widget layout and control names.

## Files of interest
- src/main.cpp — application entrypoint
- src/mainwindow.ui / src/mainwindow.* — main GUI and logic
- src/customview.* — grid drawing and input handling
- src/gridgraph.* / src/squarenode.* — grid and node data structures
- src/search*.cpp / src/search*.h — implementations for A*, Dijkstra, GBFS, BFS, DFS
- src/GridSearchVisualizer.pro — main qmake project file
- GSVInstaller.exe — prebuilt Windows installer (in repository root)

## Maybe someday (roadmap)
(Informal — things that could be added in the future; not promises.)
- Export animated visualizations (frames → video)
- Additional search variants (Jump Point Search, bidirectional search)
- Weighted / hex grids and configurable movement costs
- UI improvements: presets, map import/export, keyboard shortcuts
- Unit tests for algorithm correctness and edge cases

## Troubleshooting
- qmake / Qt not found:
  - Ensure Qt and its development tools are installed and qmake is on PATH, or use the full path to qmake from your Qt installation.
- Build errors related to includes or libraries:
  - Verify your kit (compiler + Qt) in Qt Creator or your local toolchain supports the Qt version you intend to use.
- If the installer is not desired, remove or ignore `GSVInstaller.exe` — build from source using qmake / Qt Creator.

## License
Specify your preferred license here (if none provided in repo). Example:

```
MIT License
Copyright (c) 2025 ParkAlchemist
```

## Contact
- Repo: https://github.com/ParkAlchemist/GridSearchVisualizer
- Issues: https://github.com/ParkAlchemist/GridSearchVisualizer/issues
- Author: ParkAlchemist
