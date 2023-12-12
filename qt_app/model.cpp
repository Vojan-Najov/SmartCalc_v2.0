#include "model.h"

#include <QString>
#include <QStringList>

Model::Model()
{

}

QString Model::calculateExpression(QString expr)
{
   if (!expr.contains("=")) {
       sc.CalculateExpression(expr.toLatin1());
       if (sc.Error()) {
           return sc.ErrorMessage().c_str();
       }
       return QString::number(sc.Result(),'g', 6);
   }

   QStringList strlist = expr.split("=");
   if (strlist.size() > 2) {
       return "Error: no more than one assignment character is expected";
   }
   QString lhs = strlist.front().trimmed();
   QString rhs = strlist.back();
   strlist = lhs.split(" ", Qt::SkipEmptyParts);
   if (strlist.front() != "var" && strlist.front() != "func") {
       return QString("Error: unlnown keyword ") + strlist.front();
   }
   if (!strlist.back()[0].isLetter() && strlist.back()[0].unicode() > 127) {
       return QString("Error: '") + strlist.back() + QString("' incorrect name of ") + strlist.front();
   }
   if (strlist.front() == "var") {
        sc.SetVariable(strlist.back().toLatin1(), rhs.toLatin1());
        if (sc.Error()) {
            return sc.ErrorMessage().c_str();
        }
        sc.CalculateExpression(strlist.back().toLatin1());
        return QString::number(sc.Result(),'g', 6);
   }
   if (strlist.front() == "func") {
        sc.SetFunction(strlist.back().toLatin1(), rhs.toLatin1());
        if (sc.Error()) {
            return sc.ErrorMessage().c_str();
        }
        return QString("func ") + lhs.back() + QString(" defined");
   }
   return "TODO";
}
