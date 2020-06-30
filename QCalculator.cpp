#include "QCalculator.h"

QCalculator::QCalculator()
{

}

bool QCalculator::construct()
{
    //二阶构造函数
    my_ui = QCalculatorUI::NewInstance();          //如果ui构造成功
    if(my_ui != nullptr){                          //将ui和核心算法关联
        my_ui->setCalculator(&my_cal);
    }
    return (my_ui != nullptr);
}

QCalculator *QCalculator::NewInstance()
{
    //一阶构造函数
    QCalculator * ret = new QCalculator();
    if( (ret == nullptr) || ret->construct() == false){
        delete ret;
        ret = nullptr;
    }
    return ret;
}

void QCalculator::show()
{
    my_ui->show();
}

QCalculator::~QCalculator()
{
    delete my_ui;
}


