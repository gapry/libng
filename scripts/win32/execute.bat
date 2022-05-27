:: @echo off
:: cls
:: nmake /S /NOLOGO default

set compiler=libng_compiler
set target=libng_game

.\build\libng\compiler\%compiler%.exe
.\build\game\%target%.exe