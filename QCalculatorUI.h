#ifndef QCALCULATORUI_H
#define QCALCULATORUI_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class QCalculatorUI : public QWidget
{
    Q_OBJECT
public:
    static QCalculatorUI * NewInstance(void);
    void show(void);
    ~QCalculatorUI(void);

private:
    //使用二阶构造,则构造函数不能再为公有
    //顶层窗口不需要父类
    QCalculatorUI(void);
    bool construct(void);

    QLineEdit * my_edit;
    QPushButton * my_buttons[20];

};

#endif // QCALCULATORUI_H
