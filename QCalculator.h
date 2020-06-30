#ifndef QCALCULATOR_H
#define QCALCULATOR_H
//此类将ui和业务逻辑联系在一起

#include "QCalculatorUI.h"
#include "QCalculatorDec.h"

class QCalculator
{
public:
    static QCalculator * NewInstance(void);
    void show(void);
    ~QCalculator(void);

protected:
    QCalculatorUI * my_ui; //若有一个成员变量使用二阶构造来构造,使用该成员变量的类也应使用二阶构造
    QCalculatorDec my_cal;
    QCalculator(void);
    bool construct(void);

};

#endif // QCALCULATOR_H
