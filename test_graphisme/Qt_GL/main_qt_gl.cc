#include <QApplication>
#include "glwidget.h"

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  GLWidget w;
  w.show();

     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);       // efface l'écran

  return a.exec();
}
