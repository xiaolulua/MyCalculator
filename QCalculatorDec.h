#ifndef QCALCULATORDEC_H
#define QCALCULATORDEC_H

#include <QString>
#include <QStack>
#include <QQueue>

#include "icalculator.h"

class QCalculatorDec : public ICalculator
{
public:
    QCalculatorDec();
    ~QCalculatorDec();
    bool expersion(const QString &exp);
    QString expression(void);
    QString result(void);

protected:
    QString my_exp;
    QString my_result;

    //QString 中的每个字符为 QChar
    bool isDigitalOrDot(QChar c);
    bool isSymbol(QChar c);
    bool isSign(QChar c);
    bool isNumber(QString s);
    bool isOperator(QString s);
    bool isLeft(QString s);
    bool isRight(QString s);

    int priority(QString s);
    bool match(QQueue<QString> & exp);
    QString calculate(QQueue<QString> & exp);
    QString calculate(QString left,QString op,QString right);
    bool transform(QQueue<QString> & exp,QQueue<QString> &out);

    QQueue<QString> split(const QString &exp);
};

#endif // QCALCULATORDEC_H
