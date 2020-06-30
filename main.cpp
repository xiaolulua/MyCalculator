#include <QApplication>
#include "QCalculator.h"

#if 0
这是我写的地一个QtGui应用程序 : 计算器
对算数表达式进行解析,通过逆波兰式计算的出结果
此次我没有用到Qt Creator,纯手工布局
关于界面设计:
    主窗口 : QWidget
    按  钮 : QPusheButton
    文本框 : QLineEdit

#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    int ret = -1;

    //从堆空间申请内存创建主窗口
    QCalculator * cal = QCalculator::NewInstance();

    if(cal != nullptr){
        cal->show();
        ret = a.exec();
        delete cal;      //释放主窗口
    }

    return ret;
}
