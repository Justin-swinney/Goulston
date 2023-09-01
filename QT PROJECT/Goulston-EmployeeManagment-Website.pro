QT       += core gui webenginewidgets


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += resources.qrc


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv/build/x64/vc16/lib/ -lopencv_world480
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv/build/x64/vc16/lib/ -lopencv_world480d

INCLUDEPATH += $$PWD/../opencv/sources/include/opencv2
DEPENDPATH += $$PWD/../opencv/sources/include/opencv2
INCLUDEPATH += C:/Users/Justi/Desktop/Goulston-Project/opencv/build/include
LIBS += -LC:/Users/Justi/Desktop/Goulston-Project/opencv/build/x64/vc16/bin/ -lopencv_world480
