#ifndef QCALCULATORUI_H
#define QCALCULATORUI_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

#include "icalculator.h"

class QCalculatorUI : public QWidget
{
    Q_OBJECT           //必须要在类声明的开始处使用Q_OBJECT,只有QObject的子类才可以使用自定义信号和槽
public:
    static QCalculatorUI * NewInstance(void);
    void show(void);
    void setCalculator(ICalculator * cal);
    ICalculator * getCalculator(void);
    ~QCalculatorUI(void);
private slots:
    void onButtonClicked(void);

private:
    //使用二阶构造,则构造函数不能再为公有
    //顶层窗口不需要父类
    QCalculatorUI(void);
    bool construct(void);

    QLineEdit * my_edit;
    QPushButton * my_buttons[20];
    ICalculator * my_cal;

};

#endif // QCALCULATORUI_H
