@echo off
echo 🔨 Compiling Simple Class Example...

g++ -std=c++17 -I./include -o calculator.exe main.cpp src/Calculator.cpp

if %errorlevel% == 0 (
    echo ✅ Compilation successful!
    echo.
    echo Run: calculator.exe
) else (
    echo ❌ Compilation failed!
)
pause