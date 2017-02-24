@echo off
if exist *.bob set BOB=1
if exist *.bac set BAC=1
if exist *.bak set BAK=1 

copy *.bob bob\
if defined BAK copy ?3.bak bak\bak3
if "%BAC%"=="1" copy *1.bac  bac\

rar a  arch.rar *.bas *.bac *.bob

if ERRORLEVEL 1 (echo "Something's gone wrong!") else (del *.bak *.bob *.bac)
