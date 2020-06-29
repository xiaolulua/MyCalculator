#include "QCalculatorUI.h"

//解决半成品对象问题,使用二阶构造法
//二阶构造法要么得到完整的对象,要么得到空指针,是不可能得到半成品对象的
QCalculatorUI::QCalculatorUI(void) : QWidget(nullptr,Qt::WindowCloseButtonHint)
{
    //取消最大化最小化按钮
    //对象中的成员获取空间
}

QCalculatorUI *QCalculatorUI::NewInstance(void)
{
    QCalculatorUI * ret = new QCalculatorUI();  //此处调用私有构造函数
    if( (ret == nullptr) || ret->construct() == false){
                                                //如果资源申请失败就释放资源
        delete ret;                             //delete NULL 是安全的
        ret = nullptr;
    }
    return ret;
}

bool QCalculatorUI::construct(void)
{
    //二阶构造函数
    //该函数用于对象初始化时,对象中的对象成员指针向堆上的内存申请空间初始化对象成员指针
    bool ret = true;

    //从堆空间申请内存创建文本框
    //设置文本框只读
    //设置文本右对齐
    my_edit = new QLineEdit(this);
    if(my_edit != nullptr){                           //内存申请成功
        my_edit->setReadOnly(true);
        my_edit->setAlignment(Qt::AlignRight);
        my_edit->move(10, 10);                        //文本框起始位置(10,10)
        my_edit->resize(240, 30);                     //文本框长240,高30
    }else{
        ret = false;
    }

    //一共需要20个按钮,可以使用对象指针数组来生成按钮
    const char* btext[20]={"7", "8", "9", "+", "(",
                           "4", "5", "6", "-", ")",
                           "1", "2", "3", "*", "<-",
                           "0", ".", "=", "/", "C"
                          };

    for(int i=0; (i<4) && ret; i++){
        for(int j=0; (j<5) && ret; j++){
            my_buttons[i*5 + j] = new QPushButton(this);
            if( my_buttons[i*5 + j] != nullptr ){
                my_buttons[i*5 + j]->resize(40, 40);     //按钮大小,按钮间隔10px
                my_buttons[i*5 + j]->move(10 + (10 + 40)*j, 50 + (10+40) *i);
                my_buttons[i*5 + j]->setText(btext[i*5 + j]);
            }else{
                ret = false;
            }
        }
    }

    return ret;
}

void QCalculatorUI::show(void)
{
    QWidget::show();                               //调用父类函数,显示主窗口
    setFixedSize(width(),height());                //设置主窗口固定大小,只有在show()之后,调用height()和weight()获得的结果才是准确的
}

QCalculatorUI::~QCalculatorUI(void){

}
