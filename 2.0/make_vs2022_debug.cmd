@echo off
del "%~dp0\xtras\Debug\PRegEx.x32" 2>nul
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars32.bat"
msbuild "%~dp0\project\PRegEx.sln" /p:Configuration=Debug /p:Platform=Win32
echo.
pause
