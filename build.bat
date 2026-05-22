@echo off
setlocal

:: Handle clean argument
if "%~1"=="clean" (
    if exist build (
        rd /s /q build
    )
    exit /b 0
)

:: Configure project
echo Configuring project...
cmake -B build -DCMAKE_BUILD_TYPE=Debug

:: Compile project
echo Compiling...
cmake --build build --config Debug

echo Success! Executable at: build\Debug\OpenGLRenderer.exe
pause