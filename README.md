# libng

**libng** is the Cross Platform Networking Game Engine.

## Development Environment 

#### Windows
- Install the following tools
  - [CMake](https://cmake.org/download/)
  - [git](https://git-scm.com/downloads)
  - [Visual Studio Community 2022](https://visualstudio.microsoft.com/)
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
  $ sudo pacman -S cmake git
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

## License
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)