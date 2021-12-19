REM Build process for Spell checker prototype
@echo off
cl /Zi /MDd /IC:\dev_lib\SDL2-2.0.3\include *.c /link /NODEFAULT
