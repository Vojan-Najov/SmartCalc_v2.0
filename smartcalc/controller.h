#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QString>

#include "model.h"

class Controller
{
public:
    Controller(Model *model);

public:
    QString calc(QString expr);

private:
    Model *model;
};

#endif // CONTROLLER_H
