:: @echo off
:: cls

set compiler=libng_compiler_app
set editor=libng_editor_app
set target=libng_game

.\build\libng\compiler\app\%compiler%.exe
.\build\libng\editor\app\%editor%.exe
.\build\game\%target%.exe