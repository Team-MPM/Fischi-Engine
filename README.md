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
