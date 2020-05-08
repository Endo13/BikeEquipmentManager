# Target Definition

TARGET = BikeEquipmentManager
TEMPLATE = app


# Directories Definition

PROJECTDIR = ../../../..
DESTDIR = ${DELIVERY}/${BUILD_MKSPEC}/${BUILD_MODE}

DEFINES = _WIN32_PLATEFORM_ 
DEFINES +=_CRT_SECURE_NO_WARNINGS
DEFINES += WIN32_LEAN_AND_MEAN

QT       += core gui sql widgets

RESOURCES     = ressources/ressources.qrc
RC_FILE = BEM.rc

SOURCES += main.cpp\
        mainwindow.cpp \
    gearsdialog.cpp \
	gearsSqlModel.cpp \
	tableUtilities.cpp \
	gearsEdit.cpp \
    gearsview.cpp 

HEADERS  += mainwindow.h \
    gearsdialog.h \
	gearsSqlModel.h \
	tableUtilities.h \
	gearsEdit.h \
    gearsview.h 

FORMS    += mainwindow.ui \
    gearsdialog.ui \
    gearsview.ui 
	

	
include( $${QSMAKEPATH}/rules/standard_project.pri )