SET DEST_DIR=.\Delivery\win-msvc2015-x86-QT5.9.6\
SET QTDIR=C:\Qt\Qt5.9.6\5.9.6\msvc2015

xcopy /y %QTDIR%\bin\Qt5Widgetsd.dll %DEST_DIR%\debug
xcopy /y %QTDIR%\bin\Qt5Sqld.dll %DEST_DIR%\debug
xcopy /y %QTDIR%\bin\Qt5Cored.dll %DEST_DIR%\debug
xcopy /y %QTDIR%\bin\Qt5Guid.dll %DEST_DIR%\debug
xcopy /y .\Sources\records\*.* %DEST_DIR%\debug\records\

xcopy /y %QTDIR%\bin\Qt5Widgets.dll %DEST_DIR%\release
xcopy /y %QTDIR%\bin\Qt5Sql.dll %DEST_DIR%\release
xcopy /y %QTDIR%\bin\Qt5Core.dll %DEST_DIR%\release
xcopy /y %QTDIR%\bin\Qt5Gui.dll %DEST_DIR%\release
xcopy /y .\Sources\records\*.* %DEST_DIR%\release\records\
