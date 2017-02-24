@echo off
set SPISOK=
for %%i in (*) do set SPISOK=!SPISOK!  %%i
echo %SPISOK%
for %%i in (*.txt) do  attrib +R %%i