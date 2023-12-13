#include "controller.h"

Controller::Controller(Model *model)
    : model(model)
{

}

QString Controller::calc(QString expr)
{
    return model->calculateExpression(std::move(expr));
}
