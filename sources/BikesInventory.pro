# Target Definition

TARGET = BikesInventory
TEMPLATE = app


# Directories Definition

PROJECTDIR = ../../../..
DESTDIR = ${DELIVERY}/${BUILD_MKSPEC}/${BUILD_MODE}

DEFINES = _WIN32_PLATEFORM_ 
DEFINES +=_CRT_SECURE_NO_WARNINGS
DEFINES += WIN32_LEAN_AND_MEAN

QT       += core gui sql widgets



SOURCES += main.cpp\
        mainwindow.cpp \
    gearsdialog.cpp \
    gearsview.cpp 

HEADERS  += mainwindow.h \
    gearsdialog.h \
    gearsview.h 

FORMS    += mainwindow.ui \
    gearsdialog.ui \
    gearsview.ui 
	
libraries.files = C:\Qt\Qt5.9.6\5.9.6\msvc2015/bin/Qt5Widgetsd.dll \
				  C:\Qt\Qt5.9.6\5.9.6\msvc2015/bin/Qt5Sqld.dll \
				  C:\Qt\Qt5.9.6\5.9.6\msvc2015/bin/Qt5Cored.dll \
				  C:\Qt\Qt5.9.6\5.9.6\msvc2015/bin/Qt5Guid.dll \
				                     
libraries.CONFIG += no_check_exist
libraries.path = $${DESTDIR}

INSTALLS += config \
            libraries	
	
include( $${QSMAKEPATH}/rules/standard_project.pri )