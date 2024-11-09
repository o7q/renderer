@echo off
mkdir build 2> nul
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
copy "renderer.exe" "../renderer.exe"
pause