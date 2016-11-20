import sys
from cx_Freeze import setup, Executable

exe = Executable(
        script = "PasswordGenerator.py",
        icon = "PasswordGenerator.ico",
        targetName = "PasswordGenerator.exe",
        )
includefiles = ["PasswordGenerator.ico"]

setup(
    name = "PasswordGenerator",
    version = "0.1",
    description = "PasswordGenerator",
    author = "IV522",
    options = {'build_exe': {'include_files':includefiles}},
    executables = [exe]
)
