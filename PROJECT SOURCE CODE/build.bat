@echo off
echo ========================================================
echo   RESTAURANT ORDER & BILLING SYSTEM (CPP07)
echo   Enrollment: IU2541230417
echo ========================================================
echo.
echo Compiling source files with g++...
g++ -std=c++17 -Wall -Wextra -o Project.exe main.cpp MenuItem.cpp FoodItem.cpp BeverageItem.cpp Customer.cpp Order.cpp Bill.cpp FileManager.cpp Restaurant.cpp

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo [ERROR] Compilation failed! Please verify MinGW / g++ installation.
    pause
    exit /b %ERRORLEVEL%
)

echo.
echo [SUCCESS] Compilation successful! Generated Project.exe.
echo Launching Restaurant Order & Billing System...
echo ========================================================
echo.
Project.exe
pause
