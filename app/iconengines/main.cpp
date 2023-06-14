#include "startmenu.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //a.setQuitOnLastWindowClosed(0);

    StartMenu st;
    st.show();
    return a.exec();
}
