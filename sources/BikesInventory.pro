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
		Equipments\gearsdialog.cpp \
		Equipments\gearsSqlModel.cpp \
		Equipments\gearsEdit.cpp \
		Equipments\gearsview.cpp \		
		Bikes\bikedialog.cpp \
		Bikes\bikesview.cpp \
		Bikes\bikesSqlModel.cpp \
		Bikes\bikesEdit.cpp \
		Common\tableUtilities.cpp

HEADERS  += mainwindow.h \
			Equipments\gearsdialog.h \
			Equipments\gearsSqlModel.h \
			Equipments\gearsview.h \
			Equipments\gearsEdit.h \			
			Bikes\bikedialog.h \
			Bikes\bikesSqlModel.h \
			Bikes\bikesview.h \
			Bikes\bikesEdit.h \
			Common\tableUtilities.h 

FORMS    += mainwindow.ui \			
			Bikes\bikedialog.ui \
			Bikes\bikesview.ui \
			Equipments\gearsdialog.ui \
			Equipments\gearsview.ui 
	

	
include( $${QSMAKEPATH}/rules/standard_project.pri )