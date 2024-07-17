@echo off

REM Define file names
set CppFile=keyloggerdetector1.cpp
set PyFile=block.py

REM Compile the C++ file (Assuming MinGW is installed)
g++ %CppFile% -o keyloggerdetector1.exe

 
start keyloggerdetector1.exe
  

REM Execute the Python file after the keylogger terminates
python %PyFile%

REM Pause to view output before the window closes (optional)
pause
