QT += core gui opengl

TARGET = texture-mapping

TEMPLATE = app

SOURCES += main.cpp\
           glwidget.cpp \
    form.cpp \
    mainwidget.cpp

HEADERS += glwidget.h \
    form.h \
    mainwidget.h

OTHER_FILES += fragmentShader.fsh\
               vertexShader.vsh

RESOURCES += resources.qrc

FORMS += \
    form.ui \
    mainwidget.ui
