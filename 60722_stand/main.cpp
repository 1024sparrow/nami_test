#include <QApplication>
#include <QString>
#include <iostream>

#include "gameplay.h"

void showHelp();

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    bool ifStartDemo = false;
    bool ifShowHelp = false;
    if (argc > 1)
    {
        if (argc == 2)
        {
            QString command = argv[1];
            if (QString::compare(command, "--help", Qt::CaseSensitive) == 0)
                ifShowHelp = true;
            else if (QString::compare(command, "-h", Qt::CaseSensitive) == 0)
                ifShowHelp = true;
            else if (QString::compare(command, "--demo", Qt::CaseSensitive) == 0)
                ifStartDemo = true;
            else if (QString::compare(command, "-d", Qt::CaseSensitive) == 0)
                ifStartDemo = true;
        }
        else
            ifShowHelp = true;
    }
    if (ifShowHelp)
    {
        showHelp();
        return 0;
    }
    else
    {

        Gameplay *gp = new Gameplay(ifStartDemo);
        gp->showMaximized();

        return app.exec();
    }
    return 0;
}

void showHelp()
{
    std::cout<<"speedometer imitator\n";
    std::cout<<"this is a stupid application that support just one key.\n";
    std::cout<<"-h, --help\tshow this message\n";
    std::cout<<"-d, --demo\tshow demo at start\n";
}
