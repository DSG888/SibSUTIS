@echo off
if defined MY_VAR echo "it is defined"
if "%MY_VAR%"=="97" (set MY_VAR) else (echo "my variable MY_VAR is not defined (не определена)")