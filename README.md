# libng

**libng** is the Cross Platform Networking Game Engine.

## Development Environment 

#### Windows
- Install the following tools
  - [CMake](https://cmake.org/download/)
  - [git](https://git-scm.com/downloads)
  - [Visual Studio Community 2022](https://visualstudio.microsoft.com/)
  - [Make for Windows - GnuWin32](http://gnuwin32.sourceforge.net/packages/make.htm)
- [vcpkg](https://vcpkg.io/en/index.html)
  ```
  .\scripts\win32\vcpkg.bat 
  ```
- Generate the Visual Studio Project
  ```
  .\vs2022.bat
  ```
- Open the Visual Studio Solution
  ```
  .\build\libng-x64-windows\libng.sln 
  ```

#### [Manjaro Linux](https://manjaro.org/)
- Install the following tools
  ```
  $ sudo pacman -S cmake git tig vim
  ```
- [vcpkg](https://vcpkg.io/en/index.html)
  ```
  $ make vcpkg
  ```
- Execution
  ```
  $ make clean; make fmt; make build; make execute
  ```
- Unit Test
  ```
  $ make clean; make fmt; make build; make tests
  ```

#### OS Independent: [Visual Studio Code](https://code.visualstudio.com/)
- Install the following tools
  - [C/C++ for Visual Studio Code](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
  - [Vim](https://marketplace.visualstudio.com/items?itemName=vscodevim.vim)
- Execution: `Ctrl + Shift + B`
- Unit Test: `Ctrl + Shift + B`
- Debug: Set Breakpoint and Press `F5`

## License
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
