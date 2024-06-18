# Fischi-Engine

## Building


### Windows (Visual Studio/Rider)
- run: .\dependencies\premake\windows\premake5.exe vs2022
- open .sln file in vs/rider
- ready to go

### Windows NMake
- run: .\dependencies\premake\windows\premake5.exe gmake2
- build: nmake config=debug all
- executables found in bin

### WSL

- compile script: `wsl gcc scripts/wsl.c -o scripts/wsl`
- and run it: `wsl scripts/wsl`

### WSL - Raw
- dependencies: make, gcc, buildessential
- run: `wsl ./dependencies/premake/linux/premake5 gmake2`
- build: `wsl make config=debug all`
- executable in bin directory: ` wsl ./bin/Debug-linux-x86_64/Sandbox`

### Linux

- build: just use make, you know the drill

### Linux via SSH

- build: just use make
- for X11
  - Install XServer on Windows
  - use `ssh -X user@host`
  - run `export DISPLAY=0`
  - run the executable
- for wayland
  - install weston on linux box
  - start weston as headless: `weston --backend=headless-backend.so`
  - set env var: `export WAYLAND_DISPLAY=wayland-0`
  - run the executable