@echo off

pushd ..
Engine\Build\premake5.exe --file=Build.lua vs2022
popd
pause