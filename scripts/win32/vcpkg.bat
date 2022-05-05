@REM

%~d0

cd %~dp0

set dir_vcpkg=..\..\externals\vcpkg

git clone https://github.com/microsoft/vcpkg.git %dir_vcpkg%

call %dir_vcpkg%\bootstrap-vcpkg.bat

%dir_vcpkg%\vcpkg install fmt   --recurse
%dir_vcpkg%\vcpkg install eastl --recurse
%dir_vcpkg%\vcpkg install glew  --recurse
%dir_vcpkg%\vcpkg install imgui --recurse

@pause