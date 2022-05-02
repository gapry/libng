@echo off
cls

IF EXIST build rmdir build /q /s
IF EXIST *.cso DEL *.cso
IF EXIST *.obj DEL *.obj
IF EXIST *.exe DEL *.exe
IF EXIST *.ilk DEL *.ilk
IF EXIST *.pdb DEL *.pdb