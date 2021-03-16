#ifndef MYCUSTOMWIDGET_H
#define MYCUSTOMWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QObject>
#include <QSignalMapper>
#include <QPushButton>
#include <QStringList>
#include <QLineEdit>
#include <QScreen>
#include <QMessageBox>
#include <QStack>
#include <QRegExp>
#include <QtMath>
#include <QChar>

class MyCustomWidget : public QWidget
{
    Q_OBJECT

    QLineEdit *_lineEdit;
    QStack<QString> _stack;
    QStack<QString> _evalStack;
    QStringList _convertToPostFix(QStringList expression);
    // int _evaluatePostFix(QString expression);
    // int _evaluatePostFix(QStringList expression);
    float _evaluatePostFix(QStringList expression);
    void _concatenateNumbersOperations(QString operationOrNumber);
    void _addMultipleDigits(QString numOp);

public:
    MyCustomWidget(QWidget *parent = 0);

private slots:
    void plusButtonClicked();
    void minusButtonClicked();
    void divideButtonClicked();
    void multiplyButtonClicked();
    void equalButtonClicked();
    void leftParenBtnClicked();
    void rightParenBtnClicked();
    void clearButtonClicked();
    void decimalButtonClicked();

    void oneButtonClicked();
    void twoButtonClicked();
    void threeButtonClicked();
    void fourButtonClicked();
    void fiveButtonClicked();
    void sixButtonClicked();
    void sevenButtonClicked();
    void eightButtonClicked();
    void nineButtonClicked();
    void zeroButtonClicked();
};

#endif // MYCUSTOMWIDGET_H
