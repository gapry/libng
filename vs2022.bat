@cls

@REM #change current directory to this file

@%~d0

@cd %~dp0

set editor="Visual Studio 17 2022"

set build_arch=x64
set build_os=windows
set build_project=libng

set build_dir=build\%build_project%-%build_arch%-%build_os%

set build_components=-DBUILD_GAME=ON

cmake %build_components% -G %editor% -B %build_dir% .

@pause