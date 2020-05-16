SETLOCAL
SET PWD=%CD%
SET WORKSPACE=%~dp0

rem Script options

IF "%1"=="" (
    SET "MSVC_COMNTOOLS=%VS140COMNTOOLS%"
) ELSE IF "%1"=="2015" (
    SET "MSVC_COMNTOOLS=%VS140COMNTOOLS%"
) 
IF NOT EXIST "%MSVC_COMNTOOLS%" (
    ECHO Visual Studio common tools path not resolved.
    GOTO:eof
)
rem Common tools variables
SET SYSTEM32=%SystemRoot%\System32

rem Building environment
set QTDIR=C:\Qt\Qt5.9.6\5.9.6\msvc2015
set QMAKESPEC=
SET PATH=%SYSTEM32%
SET PATH=%QTDIR%\bin;%PATH%

CALL "%MSVC_COMNTOOLS%\..\..\VC\vcvarsall.bat" x86
rem qmake processing

CD /D %WORKSPACE%
lupdate -pro BikeEquipmentManager.pro -ts BikeEquipmentManager_en.ts BikeEquipmentManager_fr.ts
lrelease BikeEquipmentManager_en.ts BikeEquipmentManager_fr.ts
qmake -tp vc -r





