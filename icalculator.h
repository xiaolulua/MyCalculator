#ifndef ICALCULATOR_H
#define ICALCULATOR_H

//实现用户界面与业务逻辑分离用到的纯虚类
//用纯虚类实现接口

#include <QString>

class ICalculator{
public:
    virtual bool expersion(const QString &exp) = 0;
    virtual QString result(void) = 0;
};

#endif // ICALCULATOR_H
