#include "QCalculatorDec.h"
#include <QDebug>

bool QCalculatorDec::isDigitalOrDot(QChar c)
{
    return ( (('0' <= c) && (c <= '9')) || c == '.');
}

bool QCalculatorDec::isSymbol(QChar c)
{
    return isOperator(c) || (c == '(' || c == ')');
}

bool QCalculatorDec::isSign(QChar c)
{
    return (c == '+') || (c == '-');
}

bool QCalculatorDec::isNumber(QString s)
{
    bool ret = false;
    s.toDouble(&ret);
    return ret;
}

bool QCalculatorDec::isOperator(QString s)
{
    return ( (s == "+") || (s == "-") || (s == "*") || (s == "/"));
}

bool QCalculatorDec::isLeft(QString s)
{
    return (s == "(");
}

bool QCalculatorDec::isRight(QString s)
{
    return (s == ")");
}

int QCalculatorDec::priority(QString s)
{
    int ret = 0;

    if( (s == "+") || (s == "-")){
        ret = 1;
    }
    if( (s == "*") || (s == "/")){
        ret = 2;
    }

    return ret;
}

bool QCalculatorDec::match(QQueue<QString> &exp)
{
    //括号匹配算法,检查表达式是否合法(核心算法2)
    bool ret = true;

    QStack<QString> stack;
    for ( int i=0;i<exp.length();i++){
        if( isLeft(exp[i]) ){                               //左括号入栈
            stack.push(exp[i]);
        }else if ( isRight(exp[i]) ){
            if( !stack.isEmpty() && isLeft(stack.top()) ){  //如果当前字符为右括号,判断栈是否不为空且栈顶是否为左括号
                stack.pop();                                //左括号出栈
            }else{
                ret = false;                                //栈顶为右括号,则右括号重复
                break;
            }
        }
    }

    return ret && stack.isEmpty();                          //队列空,栈不为空,则括号不匹配
}

QString QCalculatorDec::calculate(QQueue<QString> &exp)
{
    QString ret = "Error";
    QStack<QString> stack;

    while (!exp.isEmpty()) {
        QString e = exp.dequeue();
        if(isNumber(e)){
            stack.push(e);
        }else if(isOperator(e)){
            QString right = !stack.isEmpty() ? stack.pop() : "";
            QString left = !stack.isEmpty() ? stack.pop() : "";
            QString result=calculate(left,e,right);
            if(result != "Error"){
                stack.push(result);
            }else {
                break;
            }
        }
    }

    if(exp.isEmpty() && (stack.size() == 1) && isNumber(stack.top())){
        ret = stack.pop();
    }

    return ret;
}

QString QCalculatorDec::calculate(QString left, QString op, QString right)
{
    QString ret = "Error";

    if(isNumber(left) && isNumber(right)){
        double ldob = left.toDouble();
        double rdob = right.toDouble();

        if(op == "+"){
            ret.sprintf("%f",ldob + rdob);
        }else if(op == "-"){
            ret.sprintf("%f",ldob - rdob);
        }else if(op == "*"){
            ret.sprintf("%f",ldob - rdob);
        }else if(op == "/"){
            //除法要判断double类型的除零操作
            const double p=0.000000000000001;

            if( (-p<rdob) && (rdob<p)){
                ret = "Error";
            }else {
                ret.sprintf("%f",ldob/rdob);
            }
        }else {
            ret = "Error";
        }
    }

    return ret;
}

bool QCalculatorDec::transform(QQueue<QString> &exp, QQueue<QString> &out)
{
    //中缀转后缀表达式(核心算法3)
    bool ret = match(exp);
    QStack<QString> stack;

    while(ret && !exp.isEmpty()){                         //只有括号匹配且表达式队列不为空,才可以转换为后缀表达式
        QString e = exp.dequeue();
        if(isNumber(e)){
            out.enqueue(e);
        }else if(isOperator(e)){                          //对栈和队列操作前应该先判断是否为空,这样可以减少很多bug
            while (!stack.isEmpty() && priority(e) <= priority(stack.top())) {
                out.enqueue(stack.pop());
            }
            stack.push(e);
        }else if(isLeft(e)){
            stack.push(e);
        }else if(isRight(e)){
            while(!stack.isEmpty() && !isLeft(stack.top())){
                out.enqueue(stack.pop());
            }
            if(!stack.isEmpty()){
                stack.pop();
            }
        }else{
            ret = false;
        }
    }

    while(!stack.isEmpty()){
        out.enqueue(stack.pop());
    }
    if(!ret){
        out.clear();                                    //转换失败则清空
    }

    return ret;
}

QQueue<QString> QCalculatorDec::split(const QString &exp)
{
    //分离数字与符号(核心算法1)
    QQueue<QString> ret;
    QString num = "";
    QString pre = "";

    for(int i=0; i<exp.length(); i++){
        if( isDigitalOrDot(exp[i]) ){
            num += exp[i];
            pre = exp[i];
        }else if( isSymbol(exp[i]) ){
            if( !num.isEmpty() ){                        //分离出表达式中的数字
                ret.enqueue(num);
                num.clear();
            }

            if( isSign(exp[i]) && ( pre == "" || pre == "(" || isOperator(pre) )){
                num += exp[i];                           //分离出表达式中数字的正负号
            }else{
                ret.enqueue(exp[i]);                     //分离出表达式的运算符和括号
            }
            pre = exp[i];
        }

    }

    if( !num.isEmpty() ){
        ret.enqueue(num);
    }

    return ret;
}

QCalculatorDec::QCalculatorDec(void)
{
    my_exp = "";
    my_result = "";
}

QCalculatorDec::~QCalculatorDec(void)
{

}

bool QCalculatorDec::expersion(const QString &exp)
{
    bool ret = false;

    my_exp = exp;
    QQueue<QString> spExp=split(exp);
    QQueue<QString> postExp;
    if (transform(spExp,postExp)){
        my_result = calculate(postExp);
        ret = (my_result != "Error");
    }else{
        my_result = "Error";
    }

    return ret;
}

QString QCalculatorDec::expression(void)
{
    return my_exp;
}

QString QCalculatorDec::result(void)
{
    return my_result;
}
