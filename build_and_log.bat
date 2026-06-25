@echo off
echo ==========================================
echo    CleanQuake Build and Log Generator
echo ==========================================
echo.

:: Step 1: Force a clean build so the linker runs on all files again
echo [1/4] Cleaning previous build...
cmake --build build --target clean

:: Step 2: Build the project and redirect stdout and stderr to a file
echo.
echo [2/4] Building project and capturing output...
echo       (This may take a minute. Please wait, no text will print here...)
cmake --build build > build_log.txt 2>&1

:: Step 3: Filter the log for dead code and warnings
echo.
echo [3/4] Filtering log for warnings and discarded functions...
powershell -Command "Select-String -Path build_log.txt -Pattern 'unreachable code|unreferenced|Discarded' | Select-String -NotMatch 'SDL2|LIBCMT|msvcrt|OLDNAMES|uuid\.lib|ws2_32\.lib|winmm\.lib|kernel32\.lib' | Out-File -FilePath clean_warnings_log.txt -Encoding utf8"

:: Step 4: Finish and open the log
echo.
echo [4/4] Build and filter complete! 
echo       Outputs successfully saved to build_log.txt and clean_warnings_log.txt
echo.

:: Automatically open both the raw log and the clean warnings log in VS Code
code build_log.txt clean_warnings_log.txt

pause