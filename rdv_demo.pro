QT += widgets

HEADERS += \
    mainwindow.h \
    commandtab.h \
    optionsdialog.h

SOURCES += \
    mainwindow.cpp \
    main.cpp \
    commandtab.cpp \
    optionsdialog.cpp

RESOURCES += \
    mainwindow.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/x64/ -lbase
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/x64/ -lbased

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/x64/ -lcpknife
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/x64/ -lcpknifed

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/x64/ -lrdv
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/x64/ -lrdvd

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/x64/ -lvdr
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/x64/ -lvdrd

INCLUDEPATH += $$PWD/include/base
INCLUDEPATH += $$PWD/include/vdr
INCLUDEPATH += $$PWD/include/rdv

DEPENDPATH += $$PWD/lib/x64
