#include "view.h"
#include "model.h"
#include "controller.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QLocale::setDefault(QLocale::c());

    QApplication app(argc, argv);

    Model model{};
    Controller controller{model};
    View view{controller};

    view.show();

    return app.exec();
}
