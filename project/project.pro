TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


# 添加头文件的路径
INCLUDEPATH += C:\opencv452\include
INCLUDEPATH += C:\opencv452\include\opencv2

# 添加库文件的路径
LIBS += C:\opencv452\x64\mingw\lib\libopencv_*.a

SOURCES += \
        main.cpp

HEADERS += \
    cvui.h
