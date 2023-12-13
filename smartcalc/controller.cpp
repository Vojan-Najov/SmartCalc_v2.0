#include "controller.h"
#include <vector>

Controller::Controller(Model *model)
    : model(model)
{

}

QString Controller::calc(QString expr)
{
    return model->calculateExpression(std::move(expr));
}

const QStringList &Controller::getFuncNames(void)
{
    return model->getFuncNames();
}


std::vector<std::pair<double, double>> Controller::getPlot(const QString &funcname,
                                                           double emin, double emax,
                                                           double dmin, double dmax) {
    return model->getPlot(funcname, emin, emax, dmin, dmax);
}
