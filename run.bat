@echo off
title Launch Game and Controller

:: Start the Python hand controller in a separate background window
start "Hand Controller" python hand_controller.py

:: Small delay to let the camera initialize (optional, 2 seconds)
timeout /t 2 /nobreak >nul

:: Start the C++ game executable
start "" main.exe

exit