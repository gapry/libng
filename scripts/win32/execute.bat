:: @echo off
:: cls
:: nmake /S /NOLOGO default

set compiler=libng_shader_compiler
set target=libng_game

.\build\libng\shader\compiler\%compiler%.exe
.\build\game\%target%.exe