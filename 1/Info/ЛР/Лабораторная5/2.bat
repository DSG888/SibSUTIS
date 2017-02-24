@echo off
set LIST=
for %%i in (*.txt) do set LIST=!LIST! %%i
echo %LIST%