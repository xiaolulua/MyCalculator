#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

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

    //从堆空间申请内存创建主窗口
    //取消最大化最小化按钮
    QWidget * w = new QWidget(nullptr,Qt::WindowCloseButtonHint);

    //从堆空间申请内存创建文本框
    //设置文本框只读
    //设置文本右对齐
    QLineEdit * l = new QLineEdit(w);
    l->setReadOnly(true);
    l->setAlignment(Qt::AlignRight);

    l->move(10, 10);                        //文本框起始位置(10,10)
    l->resize(240, 30);                     //文本框长240,高30

    //一共需要20个按钮,可以使用对象指针数组来生成按钮
    QPushButton * b[20] = {nullptr};
    const char* btext[20]={"7", "8", "9", "+", "(",
                           "4", "5", "6", "-", ")",
                           "1", "2", "3", "*", "<-",
                           "0", ".", "=", "/", "C"};

    for(int i=0; i<4; i++){
        for(int j=0; j<5; j++){
            b[i*5 + j] = new QPushButton(w);
            b[i*5 + j]->resize(40, 40);     //按钮大小,按钮间隔10px
            b[i*5 + j]->move(10 + (10 + 40)*j, 50 + (10+40) *i);
            b[i*5 + j]->setText(btext[i*5 + j]);
        }
    }



    w->show();                               //显示主窗口
    w->setFixedSize(w->width(),w->height()); //设置主窗口固定大小

    int ret = a.exec();

    delete w;                               //释放主窗口

    return ret;
}
