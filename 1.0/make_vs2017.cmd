@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars32.bat"
msbuild %~dp0\project\PRegEx.sln /p:Configuration=Release /p:Platform=Win32
echo.
pause
