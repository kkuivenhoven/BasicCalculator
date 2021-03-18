#include "mycustomwidget.h"

// https://www.programmersought.com/article/64106095402/
// https://falsinsoft.blogspot.com/2014/06/qt-get-click-event-from-button-inside.html
// https://www.bogotobogo.com/Qt/Qt5_GridLayout.php
// http://faculty.cs.niu.edu/~hutchins/csci241/eval.htm
// https://www.programmingnotes.org/4737/c-multi-digit-decimal-negative-number-infix-to-postfix-conversion-evaluation/
// https://stackoverflow.com/questions/12643009/regular-expression-for-floating-point-numbers
// https://www.mathopenref.com/calcinstructions.html

MyCustomWidget::MyCustomWidget(QWidget *parent) : QWidget(parent) {
    // QWidget *window = new QWidget();
    _basicCalc = new QWidget();

    _lineEdit = new QLineEdit();
    _lineEdit->setDisabled(true);

    // QGridLayout *gridLayout = new QGridLayout();
    _gridLayout = new QGridLayout();
    QPushButton *oneButton = new QPushButton("1");
    QPushButton *twoButton = new QPushButton("2");
    QPushButton *threeButton = new QPushButton("3");
    QPushButton *plusButton = new QPushButton("+");

    QPushButton *fourButton = new QPushButton("4");
    QPushButton *fiveButton = new QPushButton("5");
    QPushButton *sixButton = new QPushButton("6");
    QPushButton *minusButton = new QPushButton("-");

    QPushButton *sevenButton = new QPushButton("7");
    QPushButton *eightButton = new QPushButton("8");
    QPushButton *nineButton = new QPushButton("9");
    QPushButton *divideButton = new QPushButton("/");

    QPushButton *leftParenButton = new QPushButton("(");
    QPushButton *rightParenButton = new QPushButton(")");
    QPushButton *zeroButton = new QPushButton("0");
    QPushButton *multiplyButton = new QPushButton("*");

    QPushButton *clearButton = new QPushButton("Clear");
    QPushButton *decimalButton = new QPushButton(".");
    QPushButton *equalButton = new QPushButton("=");
    QPushButton *scientificButton = new QPushButton("Sci");

    _gridLayout->addWidget(_lineEdit,0,0,1,4);

    _gridLayout->addWidget(oneButton,1,0,1,1);
    _gridLayout->addWidget(twoButton,1,1,1,1);
    _gridLayout->addWidget(threeButton,1,2,1,1);
    _gridLayout->addWidget(plusButton,1,3,1,1);
    QObject::connect(oneButton, SIGNAL(clicked(bool)), this, SLOT(oneButtonClicked()));
    QObject::connect(twoButton, SIGNAL(clicked(bool)), this, SLOT(twoButtonClicked()));
    QObject::connect(threeButton, SIGNAL(clicked(bool)), this, SLOT(threeButtonClicked()));
    QObject::connect(plusButton, SIGNAL(clicked(bool)), this, SLOT(plusButtonClicked()));

    // addWidget(*Widget, row, column, rowspan, colspan)
    _gridLayout->addWidget(fourButton,2,0,1,1);
    _gridLayout->addWidget(fiveButton,2,1,1,1);
    _gridLayout->addWidget(sixButton,2,2,1,1);
    _gridLayout->addWidget(minusButton,2,3,1,1);
    QObject::connect(fourButton, SIGNAL(clicked(bool)), this, SLOT(fourButtonClicked()));
    QObject::connect(fiveButton, SIGNAL(clicked(bool)), this, SLOT(fiveButtonClicked()));
    QObject::connect(sixButton, SIGNAL(clicked(bool)), this, SLOT(sixButtonClicked()));
    QObject::connect(minusButton, SIGNAL(clicked(bool)), this, SLOT(minusButtonClicked()));

    _gridLayout->addWidget(sevenButton,3,0,1,1);
    _gridLayout->addWidget(eightButton,3,1,1,1);
    _gridLayout->addWidget(nineButton,3,2,1,1);
    _gridLayout->addWidget(divideButton,3,3,1,1);
    QObject::connect(sevenButton, SIGNAL(clicked(bool)), this, SLOT(sevenButtonClicked()));
    QObject::connect(eightButton, SIGNAL(clicked(bool)), this, SLOT(eightButtonClicked()));
    QObject::connect(nineButton, SIGNAL(clicked(bool)), this, SLOT(nineButtonClicked()));
    QObject::connect(divideButton, SIGNAL(clicked(bool)), this, SLOT(divideButtonClicked()));

    _gridLayout->addWidget(leftParenButton,4,0,1,1);
    _gridLayout->addWidget(rightParenButton,4,1,1,1);
    _gridLayout->addWidget(zeroButton,4,2,1,1);
    _gridLayout->addWidget(multiplyButton,4,3,1,1);
    QObject::connect(leftParenButton, SIGNAL(clicked(bool)), this, SLOT(leftParenBtnClicked()));
    QObject::connect(rightParenButton, SIGNAL(clicked(bool)), this, SLOT(rightParenBtnClicked()));
    QObject::connect(zeroButton, SIGNAL(clicked(bool)), this, SLOT(zeroButtonClicked()));
    QObject::connect(multiplyButton, SIGNAL(clicked(bool)), this, SLOT(multiplyButtonClicked()));

    _gridLayout->addWidget(clearButton,5,0,1,1);
    _gridLayout->addWidget(decimalButton,5,1,1,1);
    _gridLayout->addWidget(scientificButton,5,2,1,1);
    _gridLayout->addWidget(equalButton,5,3,1,1);
    QObject::connect(clearButton, SIGNAL(clicked(bool)), this, SLOT(clearButtonClicked()));
    QObject::connect(decimalButton, SIGNAL(clicked(bool)), this, SLOT(decimalButtonClicked()));
    QObject::connect(scientificButton, SIGNAL(clicked(bool)), this, SLOT(scientificButtonClicked()));
    QObject::connect(equalButton, SIGNAL(clicked(bool)), this, SLOT(equalButtonClicked()));

    // window->setLayout(gridLayout);
    // window->show();
    _basicCalc->setLayout(_gridLayout);
    _basicCalc->show();
}

void MyCustomWidget::leftParenBtnClicked() {
    _concatenateNumbersOperations("(");
}

void MyCustomWidget::rightParenBtnClicked() {
    _concatenateNumbersOperations(")");
}

void MyCustomWidget::plusButtonClicked() {
    _concatenateNumbersOperations("+");
}

void MyCustomWidget::minusButtonClicked() {
    _concatenateNumbersOperations("-");
}

void MyCustomWidget::divideButtonClicked() {
    _concatenateNumbersOperations("/");
}

void MyCustomWidget::multiplyButtonClicked() {
    _concatenateNumbersOperations("*");
}

void MyCustomWidget::decimalButtonClicked() {
    QString number = "";
    if(_stack.empty()) {
        _addMultipleDigits("0");
        number.append(".");
        _concatenateNumbersOperations(number);
        return;
    }
    QString currentText = _lineEdit->text();
    while((_stack.top() != "+") && (_stack.top() != "-")
          && (_stack.top() != "*") && (_stack.top() != "/")
          && (_stack.top() != ")") && (_stack.top() != "(")) {
        // number += _stack.pop();
        QString popped = _stack.pop();
        qDebug() << (" decimal popped: " + popped);
        number += popped;
        // currentText.remove((currentText.length() - number.length()), 1);
        if(_stack.empty()) {
            break;
        }
    }
    currentText.remove((currentText.length() - number.length()), number.length());
    // qDebug() << (" decimal number: " + number);
    // QRegExp detectOperator("([+-/*]{1})");
    // int opPos = currentText.indexOf(detectOperator, 0);
    // qDebug() << (" currentText : " + currentText);
    // currentText.remove(opPos+1, (currentText.length()-(opPos+1)));
    // qDebug() << (" currentText : " + currentText);
    if(number != "") {
        number += ".";
        _stack.push(number);
        currentText.append(number);
        _lineEdit->setText(currentText);
    }
}

void MyCustomWidget::oneButtonClicked() {
    _addMultipleDigits("1");
}

void MyCustomWidget::twoButtonClicked() {
    _addMultipleDigits("2");
}

void MyCustomWidget::threeButtonClicked() {
    _addMultipleDigits("3");
}

void MyCustomWidget::fourButtonClicked() {
    _addMultipleDigits("4");
}

void MyCustomWidget::fiveButtonClicked() {
    _addMultipleDigits("5");
}

void MyCustomWidget::sixButtonClicked() {
    _addMultipleDigits("6");
}

void MyCustomWidget::sevenButtonClicked() {
    _addMultipleDigits("7");
}

void MyCustomWidget::eightButtonClicked() {
    _addMultipleDigits("8");
}

void MyCustomWidget::nineButtonClicked() {
    _addMultipleDigits("9");
}

void MyCustomWidget::zeroButtonClicked() {
    _addMultipleDigits("0");
}

void MyCustomWidget::_addMultipleDigits(QString numOp) {
    QString number = "";
    if(_stack.empty()) {
        _concatenateNumbersOperations(numOp);
        return;
    }
    QString currentText = _lineEdit->text();
    while((_stack.top() != "+") && (_stack.top() != "-")
          && (_stack.top() != "*") && (_stack.top() != "/")
          && (_stack.top() != ")") && (_stack.top() != "(")) {
        number += _stack.pop();
        if(_stack.empty()) {
            break;
        }
    }

    currentText.remove((currentText.length() - number.length()), number.length());

    QRegExp rx("([\.]{1}[0-9]+)");
    if(rx.exactMatch(number)) {
        std::reverse(number.begin(), number.end());
    }
    if(number == "") {
        _concatenateNumbersOperations(numOp);
    }
    if(number != "") {
        number += numOp;
        _stack.push(number);
        currentText.append(number);
        _lineEdit->setText(currentText);
    }
}

void MyCustomWidget::_concatenateNumbersOperations(QString operationOrNumber) {
    _stack.push(operationOrNumber);
    QString currentText = _lineEdit->text();
    currentText.append(operationOrNumber);
    _lineEdit->setText(currentText);
}

void MyCustomWidget::clearButtonClicked() {
    while(!_stack.empty()) {
        _stack.pop();
    }
    QString emptyString = "";
    _lineEdit->setText(emptyString);
}

void MyCustomWidget::equalButtonClicked() {
    QString displayThis;
    QStringList numbersOperands;
    while(!_stack.isEmpty()) {
        QString tmp = _stack.pop();
        displayThis.append(tmp);
        numbersOperands << tmp;
    }

    std::reverse(displayThis.begin(), displayThis.end());
    QStringList postFix = _convertToPostFix(numbersOperands);

    if(postFix.at(0) == "ERROR") {
        _lineEdit->setText("ERROR");
    } else {
        float finalResult = _evaluatePostFix(postFix);
        _lineEdit->setText(QString::number(finalResult));
    }
}

QStringList MyCustomWidget::_convertToPostFix(QStringList numberOperands) {
    QStringList postFix;
    QStack<QString> stackPostFix;
    int leftParenCount = 0;
    int rightParenCount = 0;
    for(int i = (numberOperands.length()-1); i >= 0; i--) {
        QRegExp rx("([0-9]*[\.]{0,1}[0-9]*)");
        QString numOp = numberOperands.at(i);
        if(rx.exactMatch(numOp)) {
            postFix.append(numOp);
        }
        if(numOp == "("){
            stackPostFix.push(numOp);
            leftParenCount += 1;
        }
        if(numOp == ")"){
            while((!stackPostFix.empty()) && (stackPostFix.top() != "(")) {
                QString poppedValue = stackPostFix.pop(); // pop the stack
                postFix.append(poppedValue);
            }
            if(stackPostFix.top() == "(") {
                stackPostFix.pop();
                rightParenCount += 1;
            }
        }
        // if((numOp == "+") || (numOp == "-") || (numOp == "/") || (numOp == "*")) {
        if((numOp == "+") || (numOp == "-") || (numOp == "/") || (numOp == "*") || (numOp == "sin")
                || (numOp == "cos") || (numOp == "tan") || (numOp == "√")) {
            if((stackPostFix.empty()) || (stackPostFix.top() == "(")) {
                stackPostFix.push(numOp);
            }
            else {
                while((!stackPostFix.empty()) && (stackPostFix.top() != "(")
                   && (stackPostFix.top() < "*") && (stackPostFix.top() < "\\")) {
                      QString poppedValue = stackPostFix.pop();
                      postFix.append(poppedValue);
                }
                stackPostFix.push(numOp);
            }
        }
    }
    while(!stackPostFix.empty()) {
        QString poppedValue = stackPostFix.pop();
        postFix.append(poppedValue);
    }

    if(leftParenCount != rightParenCount) {
       QStringList error;
       error << "ERROR";
       return error;
    }
    if(leftParenCount == rightParenCount) {
        return postFix;
    }
}

float MyCustomWidget::_evaluatePostFix(QStringList expression) {
    QStack<float> evalStack;
    for(int i = 0; i < expression.length(); i++) {
        QRegExp rx("([0-9]*[\.]{0,1}[0-9]*)");
        QString numOp = expression[i];
        if(rx.exactMatch(numOp)) {
            evalStack.push(numOp.toFloat());
        }
        if((numOp == "+") || (numOp == "-") || (numOp == "/") || (numOp == "*")) {
            float A = evalStack.pop();
            float B = evalStack.pop();
            float result;
            if(numOp == "+") {
                result = (B + A);
            }
            if(numOp == "-") {
                result = (B - A);
            }
            if(numOp == "/") {
                result = (B/A);
            }
            if(numOp == "*") {
                result = (B*A);
            }
            evalStack.push(result);
        }
        if((numOp == "sin") || (numOp == "cos") || (numOp == "tan") || (numOp == "√")) {
            float result;
            float A = evalStack.pop();
            if(numOp == "sin") {
                result = (qSin(A));
            }
            if(numOp == "cos") {
                result = (qCos(A));
            }
            if(numOp == "tan") {
                result = (qTan(A));
            }
            if(numOp == "√") {
                result = (qSqrt(A));
            }
            evalStack.push(result);
        }
    }
    float finalResult = evalStack.pop();
    return finalResult;
}

void MyCustomWidget::scientificButtonClicked() {
    QPushButton *sineButton = new QPushButton("sin");
    QPushButton *cosineButton = new QPushButton("cos");
    QPushButton *tangentButton = new QPushButton("tan");
    QPushButton *squareRoot = new QPushButton("√");

    _gridLayout->addWidget(sineButton,6,0,1,1);
    _gridLayout->addWidget(cosineButton,6,1,1,1);
    _gridLayout->addWidget(tangentButton,6,2,1,1);
    _gridLayout->addWidget(squareRoot,6,3,1,1);
    QObject::connect(sineButton, SIGNAL(clicked(bool)), this, SLOT(sineButtonClicked()));
    QObject::connect(cosineButton, SIGNAL(clicked(bool)), this, SLOT(cosineButtonClicked()));
    QObject::connect(tangentButton, SIGNAL(clicked(bool)), this, SLOT(tangentButtonClicked()));
    QObject::connect(squareRoot, SIGNAL(clicked(bool)), this, SLOT(squareRootButtonClicked()));
}

void MyCustomWidget::sineButtonClicked() {
    _concatenateNumbersOperations("sin");
    _concatenateNumbersOperations("(");
}

void MyCustomWidget::cosineButtonClicked() {
    _concatenateNumbersOperations("cos");
    _concatenateNumbersOperations("(");
}

void MyCustomWidget::tangentButtonClicked() {
    _concatenateNumbersOperations("tan");
    _concatenateNumbersOperations("(");
}

void MyCustomWidget::squareRootButtonClicked() {
    _concatenateNumbersOperations("√");
    _concatenateNumbersOperations("(");
}