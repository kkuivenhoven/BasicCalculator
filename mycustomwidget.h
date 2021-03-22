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
#include <QDebug>

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
    int _height;
    int _width;
    int _sciHeight;
    int _sciWidth;
    bool _firstSciCallOccurred;

    QWidget *_basicCalcWindow;
    QWidget *_scientificCalc;
    QGridLayout *_gridLayout;

    QPushButton *_basicCalcButton;
    QPushButton *_scientificButton;
    QPushButton *_sineButton;
    QPushButton *_cosineButton;
    QPushButton *_tangentButton;
    QPushButton *_squareRoot;

    QPushButton *_arcSinButton;
    QPushButton *_arcCosButton;
    QPushButton *_arcTanButton;
    QPushButton *_powButton;
    // https://stackoverflow.com/questions/20382050/how-to-insert-specific-symbols-in-qt-widgets
    // const QChar _squareRootSymbol(0x221A);

    QSize _calcSize;

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

    void returnToBasicCalcClicked();
    void scientificButtonClicked();
    void sineButtonClicked();
    void cosineButtonClicked();
    void tangentButtonClicked();
    void squareRootButtonClicked();

    void arcSineButtonClicked();
    void arcCosineButtonClicked();
    void arcTangentButtonClicked();
    void powButtonClicked();
};

#endif // MYCUSTOMWIDGET_H
