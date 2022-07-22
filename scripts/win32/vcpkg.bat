@REM

%~d0

cd %~dp0

set dir_vcpkg=..\..\externals\vcpkg

:: git clone https://github.com/microsoft/vcpkg.git %dir_vcpkg%
git submodule update --remote

call %dir_vcpkg%\bootstrap-vcpkg.bat

%dir_vcpkg%\vcpkg install fmt:x86-windows           --recurse
%dir_vcpkg%\vcpkg install eastl:x86-windows         --recurse
%dir_vcpkg%\vcpkg install glew:x86-windows          --recurse
%dir_vcpkg%\vcpkg install imgui:x86-windows         --recurse
%dir_vcpkg%\vcpkg install nlohmann-json:x86-windows --recurse
%dir_vcpkg%\vcpkg install libpng:x86-windows        --recurse

%dir_vcpkg%\vcpkg install fmt:x64-windows           --recurse
%dir_vcpkg%\vcpkg install eastl:x64-windows         --recurse
%dir_vcpkg%\vcpkg install glew:x64-windows          --recurse
%dir_vcpkg%\vcpkg install imgui:x64-windows         --recurse
%dir_vcpkg%\vcpkg install nlohmann-json:x64-windows --recurse
%dir_vcpkg%\vcpkg install libpng:x64-windows        --recurse

@pause