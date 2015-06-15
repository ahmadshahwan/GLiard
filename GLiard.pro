TEMPLATE = app
TARGET   = GLiardo
CONFIG  *=  warn_on release arv qglviewer glut

LIBS += -lglut
LIBS += -lGLU

ARV = glove
SOURCES  = Ball.cpp Engine.cpp MathStructs.cpp Stick.cpp BitmapText.cpp GLiardo.cpp PhysicalObject.cpp Table.cpp Color.cpp GLLayer.cpp Pocket.cpp
OBJECTS_DIR = .obj

