@cls

@REM #change current directory to this file

@%~d0

@cd %~dp0

set build_arch=x64
set build_os=windows
set build_project=libng
set build_dir=%build_project%-%build_arch%-%build_os%

cmake -DBUILD_GAME=ON -G "Visual Studio 17 2022" -B build\%build_dir% .

@pause