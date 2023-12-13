#ifndef MODEL_H
#define MODEL_H

#include <QString>

#include "smartcalc.h"

class Model
{
public:
    Model();

public:
    QString calculateExpression(QString expr);

private:
    s21::Smartcalc sc;
};

#endif // MODEL_H
