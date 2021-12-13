#include "mainwindow.h"
#include <QApplication>
#include <QWindow>
#include <cstring>


static void handleVisibleChanged(){
    if (!QGuiApplication::inputMethod()->isVisible())
        return;
    for(QWindow * w: QGuiApplication::allWindows()){
        if(std::strcmp(w->metaObject()->className(), "QtVirtualKeyboard::InputView") == 0){
            if(QObject *keyboard = w->findChild<QObject *>("keyboard")){
                QRect r = w->geometry();
                r.moveTop(keyboard->property("y").toDouble());
                r.setTop(170);
                r.setBottom(480);
                w->setMask(r);
                return;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    QApplication a(argc, argv);
    QObject::connect(QGuiApplication::inputMethod(), &QInputMethod::visibleChanged, &handleVisibleChanged);
    MainWindow w;
    w.show();

    return a.exec();
}
