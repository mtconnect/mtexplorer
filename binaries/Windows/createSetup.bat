rem @echo off
set PWD=%1
set OUT_PWD=%2
set QTDIR=%3
set QTIFW=%4
if "%QTIFW%" == "" (
    echo "Usage: createSetup <source location> <build output location> <QT installation location> <QT Installer Framework location"
    goto done
)

rem convert unix path tod dos path
cd "%OUT_PWD%"
set OUT_PWD=%CD%
cd "%PWD%"
set PWD=%CD%
cd "%QTDIR%"
set QTDIR=%CD%
cd "%QTIFW%"
set QTIFW=%CD%

echo Source Location = %PWD%
echo Build Location = %OUT_PWD%
echo QT Installation location = %QTDIR%

rem clean up old data
cd %PWD%\binaries\Windows
del /F MTExlorerSetup.exe
del /F /S /Q packages\org.mtconnect\data\*
rmdir /S /Q packages\org.mtconnect\data
mkdir packages\org.mtconnect\data


copy %OUT_PWD%\release\MTExplorer.exe packages\org.mtconnect\data
call %QTDIR%\bin\qtenv2.bat 
@echo on
cd %PWD%\binaries\Windows\packages\org.mtconnect\data
%QTDIR%/bin/windeployqt.exe MTExplorer.exe
cd %PWD%\binaries\Windows
%QTIFW%\bin\binarycreator.exe --offline-only -c config/config.xml -p packages MTExplorerSetup.exe

:done

