######################################################################
# Automatically generated by qmake (3.1) Sun Jun 5 21:01:24 2022
######################################################################

TEMPLATE = app
TARGET = P10
INCLUDEPATH += .

# The following define makes your compiler warn you if you use any
# feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += general/ChampsForces.h \
           general/constantes.h \
           general/Dessinable.h \
           general/ex_vecteur.h \
           general/Integrateur.h \
           general/Objetcompose.h \
           general/ObjetMobile.h \
           general/obstacle.h \
           general/SupportADessin.h \
           general/Systeme.h \
           Qt_GL/glsphere.h \
           Qt_GL/glwidget.h \
           Qt_GL/vertex_shader.h \
           Qt_GL/vue_opengl_syst.h \
           text/text_viewer.h
SOURCES += general/ChampsForces.cc \
           general/constantes.cc \
           general/ex_vecteur.cc \
           general/exerciceP9a.cc \
           general/Integrateur.cc \
           general/Objetcompose.cc \
           general/ObjetMobile.cc \
           general/obstacle.cc \
           general/Systeme.cc \
           general/testBalle.cc \
           general/testChocs.cc \
           general/testChocs2.cc \
           general/testChocs2pendules.cc \
           general/testChocsballeballe.cc \
           general/testChocsballeplan.cc \
           general/testChocsbriquependules.cc \
           general/testIntegrateur1.cc \
           general/testIntegrateur2.cc \
           general/testIntegrateurN.cc \
           general/testObstacle.cc \
           general/testPendule.cc \
           general/testVecteur.cc \
           Qt_GL/glsphere.cc \
           Qt_GL/glwidget.cc \
           Qt_GL/main_qt_gl.cc \
           Qt_GL/vue_opengl_syst.cc \
           text/main_text.cc \
           text/text_viewer.cc
RESOURCES += Qt_GL/resource.qrc
