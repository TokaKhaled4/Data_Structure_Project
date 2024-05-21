#include "demoqt.h"
#include <QtWidgets/QApplication>
#include<iostream>

#include "frequencywindow.h" 

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   
    demoqt w;
    w.setWindowTitle("Word Counter");
    w.show();
    return a.exec();
}
