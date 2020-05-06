@ECHO OFF
SETLOCAL

SET PWD=%CD%
SET WORKSPACE=%~dp0

rem Script options


SET "MSVC_VERSION=2015"
SET "MSVC_COMNTOOLS=%VS140COMNTOOLS%"



rem Common tools variables

SET SYSTEM32=%SystemRoot%\System32

rem Building environment
set QTDIR=C:\Qt\Qt5.9.6\5.9.6\msvc2015
set QMAKESPEC=
SET PATH=%SYSTEM32%
SET PATH=%QTDIR%\bin;%PATH%

CALL "%MSVC_COMNTOOLS%\..\..\VC\vcvarsall.bat" x86


CD /D %WORKSPACE%

ECHO %WORKSPACE%

CALL sources\_project.bat 2015


msbuild sources\BikesInventory.vcxproj /p:configuration=debug
msbuild sources\BikesInventory.vcxproj /p:configuration=release



