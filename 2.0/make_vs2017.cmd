@echo off
del "%~dp0\xtras\Release\PRegEx.x32" 2>nul
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars32.bat"
msbuild "%~dp0\project\PRegEx.sln" /p:Configuration=Release /p:Platform=Win32
echo.
pause
