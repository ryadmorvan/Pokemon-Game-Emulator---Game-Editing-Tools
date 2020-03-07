@echo off
Setlocal enabledelayedexpansion

Set "Pattern= "
Set "Replace="

For %%a in (*.png) Do (
    Set "File=%%~a"
    Ren "%%a" "!File:%Pattern%=%Replace%!"
)

Pause&Exit