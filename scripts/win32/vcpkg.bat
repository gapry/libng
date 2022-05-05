@REM

%~d0

cd %~dp0

set dir_vcpkg=..\..\externals\vcpkg

git clone https://github.com/microsoft/vcpkg.git %dir_vcpkg%

call externals\vcpkg\bootstrap-vcpkg.bat

%dir_vcpkg%\vcpkg install fmt:x64-windows --recurse
%dir_vcpkg%\vcpkg install eastl:x64-windows --recurse
%dir_vcpkg%\vcpkg install glew:x64-windows --recurse

@pause
