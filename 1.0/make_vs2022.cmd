@echo off
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars32.bat"
msbuild %~dp0\project\PRegEx.sln /p:Configuration=Release /p:Platform=Win32
echo.
pause
