QT          += core gui widgets

TEMPLATE    = app
CONFIG      += c++17

TARGET      = 3D-programmering

SOURCES += main.cpp \
    Window/mainwindow.cpp \
    Window/renderwindow.cpp \
    Shaders\shader.cpp \
    Objects\Base\visualobject.cpp \
    Objects/axis.cpp \
    Objects/plane.cpp \
    camera.cpp \
    Scenes/mainscene.cpp \
    Scenes/Base/basescene.cpp \
    Objects/sphere.cpp \
    Scenes/housescene.cpp \
    Objects/planexy.cpp \
    Blueprints/player.cpp \
    Objects/beziercurve.cpp \
    Scenes/bezierscene.cpp \
    Scenes/lightscene.cpp \
    Objects/basecube.cpp \
    Objects/baselight.cpp \
    Scenes/oblig3scene.cpp \
    Managers/filemanager.cpp \
    Managers/shadermanager.cpp \
    Managers/scenemanager.cpp \
    Objects/object.cpp \
    Objects/billboard.cpp \
    Scenes/helpscene.cpp \
    Objects/trigger.cpp

HEADERS += \
    Window/mainwindow.h \
    Window/renderwindow.h \
    Shaders\shader.h \
    Objects\Base\visualobject.h \
    Objects/allobjects.h \
    Objects/axis.h \
    Objects/plane.h \
    Math/vector2d.h \
    Math\vector3d.h \
    Math\vector4d.h \
    Math\matrix4x4.h \
    components/basecomponent.h \
    components/materialcomponent.h \
    components/transformcomponent.h \
    vertex.h \
    camera.h \
    Scenes/Base/basescene.h \
    Scenes/mainscene.h \
    Objects/sphere.h \
    Scenes/housescene.h \
    Objects/planexy.h \
    Blueprints/player.h \
    transform.h \
    Objects/beziercurve.h \
    Math/jbamath.h \
    Scenes/bezierscene.h \
    Scenes/lightscene.h \
    Objects/basecube.h \
    Objects/baselight.h \
    Scenes/oblig3scene.h \
    Managers/filemanager.h \
    Managers/shadermanager.h \
    external/PerlinNoise.hpp \
    Managers/scenemanager.h \
    Scenes/allscenes.h \
    Objects/object.h \
    Objects/billboard.h \
    Scenes/helpscene.h \
    Objects/trigger.h

FORMS += \
    Window/mainwindow.ui

DISTFILES += \
    Shaders\plainfragment.frag \
    Shaders\plainvertex.vert \
    Data/Objects/cube.txt \
    Data/Objects/simpletriangle.txt \
    Data/Objects/sphere.txt \
    Data/Objects/plane.txt \
    Data/Objects/tetrahedron.txt \
    Data/Objects/axis.txt \
    Data/Objects/textures/test.jpg \
    Data/Objects/cube_cornerPivot.txt \
    Shaders/texturevertex.vert \
    Shaders/texturefragment.frag \
    Data/Textures/container.png \
    Data/Textures/crate.bmp \
    Shaders/light.frag \
    Shaders/phong.frag \
    Shaders/phong.vert \
    Shaders/Lights/directional.frag \
    Shaders/Lights/directional.vert \
    Shaders/Lights/point.frag \
    Shaders/Lights/point.vert \
    Shaders/billboardvertex.vert \
    Shaders/billboardfragment.frag
