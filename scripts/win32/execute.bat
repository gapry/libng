:: @echo off
:: cls
:: nmake /S /NOLOGO default

set compiler=libng_compiler_app
set target=libng_game

.\build\libng\compiler\app\%compiler%.exe
.\build\game\%target%.exe