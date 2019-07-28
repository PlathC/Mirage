@echo off
set /p validatorPath="Please enter glslValidator.exe path :"
%validatorPath% -V shader.vert
%validatorPath% -V shader.frag
pause