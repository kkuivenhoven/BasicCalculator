#include "mycustomwidget.h"

// https://www.programmersought.com/article/64106095402/
// https://falsinsoft.blogspot.com/2014/06/qt-get-click-event-from-button-inside.html
// https://www.bogotobogo.com/Qt/Qt5_GridLayout.php
// http://faculty.cs.niu.edu/~hutchins/csci241/eval.htm
// https://www.programmingnotes.org/4737/c-multi-digit-decimal-negative-number-infix-to-postfix-conversion-evaluation/
// https://stackoverflow.com/questions/12643009/regular-expression-for-floating-point-numbers
// https://www.mathopenref.com/calcinstructions.html

MyCustomWidget::MyCustomWidget(QWidget *parent) : QWidget(parent) {
    _basicCalcWindow = new QWidget();

    _lineEdit = new QLineEdit();
    _lineEdit->setDisabled(true);

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
    // QPushButton *scientificButton = new QPushButton("Sci");
    _scientificButton = new QPushButton("Sci");

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
    _gridLayout->addWidget(_scientificButton,5,2,1,1);
    _gridLayout->addWidget(equalButton,5,3,1,1);
    QObject::connect(clearButton, SIGNAL(clicked(bool)), this, SLOT(clearButtonClicked()));
    QObject::connect(decimalButton, SIGNAL(clicked(bool)), this, SLOT(decimalButtonClicked()));
    QObject::connect(_scientificButton, SIGNAL(clicked(bool)), this, SLOT(scientificButtonClicked()));
    QObject::connect(equalButton, SIGNAL(clicked(bool)), this, SLOT(equalButtonClicked()));

    _basicCalcWindow->setLayout(_gridLayout);
    _basicCalcWindow->show();

    _height = _basicCalcWindow->height();
    _width = _basicCalcWindow->width();
    _basicCalcWindow->setMinimumHeight(_height);
    _basicCalcWindow->setMinimumWidth(_width);
    _basicCalcWindow->setMaximumHeight(_height + 122);
    _basicCalcWindow->setMaximumWidth(_width);
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
        number += popped;
        // currentText.remove((currentText.length() - number.length()), 1);
        if(_stack.empty()) {
            break;
        }
    }
    currentText.remove((currentText.length() - number.length()), number.length());

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
          && (_stack.top() != ")") && (_stack.top() != "(")
          && (_stack.top() != "^") && (_stack.top() != "e^")) {
        number += _stack.pop();
        if(_stack.empty()) {
            break;
        }
    }

    currentText.remove((currentText.length() - number.length()), number.length());

    QRegExp rx("([\.]{1}[0-9]+)");
    if((rx.exactMatch(number)) || (number.contains("^"))) {
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

    if(!postFix.empty()) {
        if(postFix.at(0) == "ERROR") {
            _lineEdit->setText("ERROR");
        } else {
            float finalResult = _evaluatePostFix(postFix);
            _lineEdit->setText(QString::number(finalResult));
        }
    } else {
        _lineEdit->setText(" postFix empty");
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
        if(numOp == "π") {
            postFix.append("3.14159");
        }
        if(numOp == "e") {
            postFix.append("2.718");
        }
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
        if((numOp == "+") || (numOp == "-") || (numOp == "/") || (numOp == "*") || (numOp == "sin")
                || (numOp == "cos") || (numOp == "tan") || (numOp == "√") || (numOp == "sin-1") ||
                (numOp == "cos-1") || (numOp == "tan-1") || (numOp == "^") || (numOp == "e^")
                || (numOp == "loge") || (numOp == "π")) {
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
        if((numOp == "sin") || (numOp == "cos") || (numOp == "tan") || (numOp == "√") ||
                (numOp == "sin-1") || (numOp == "cos-1") || (numOp == "tan-1") ||
                (numOp == "^") || (numOp == "e^") || (numOp == "loge")) {
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
            if(numOp == "sin-1") {
                result = (qAsin(A));
            }
            if(numOp == "cos-1") {
                result = (qAcos(A));
            }
            if(numOp == "tan-1") {
                result = (qAtan(A));
            }
            if(numOp == "^") {
                float B = evalStack.pop();
                result = (qPow(B, A));
            }
            if(numOp == "e^") {
                result = (qExp(A));
            }
            if(numOp == "loge") {
                result = (qLn(A));
            }
            evalStack.push(result);
        }
    }
    float finalResult = evalStack.pop();
    return finalResult;
}

// https://en.wikipedia.org/wiki/List_of_Unicode_characters

void MyCustomWidget::scientificButtonClicked() {
    QString inverse = QChar(0x207b);
    QString one = QChar(0xb9);
    QString e = QChar(0x2091);
    QString x = QChar(0x02E3);

    _sineButton = new QPushButton("sin");
    _cosineButton = new QPushButton("cos");
    _tangentButton = new QPushButton("tan");
    _squareRoot = new QPushButton("√");
    _arcSinButton = new QPushButton("sin" + inverse + one);
    _arcCosButton = new QPushButton("cos" + inverse + one);
    _arcTanButton = new QPushButton("tan" + inverse + one);
    _powButton = new QPushButton("^");
    _eRaisedToXButton = new QPushButton("e" + x);
    _logBaseEButton = new QPushButton("log" + e);
    _piButton = new QPushButton("π");
    _eByItselfButton = new QPushButton("e");

    _gridLayout->addWidget(_sineButton,6,0,1,1);
    _gridLayout->addWidget(_cosineButton,6,1,1,1);
    _gridLayout->addWidget(_tangentButton,6,2,1,1);
    _gridLayout->addWidget(_squareRoot,6,3,1,1);
    QObject::connect(_sineButton, SIGNAL(clicked(bool)), this, SLOT(sineButtonClicked()));
    QObject::connect(_cosineButton, SIGNAL(clicked(bool)), this, SLOT(cosineButtonClicked()));
    QObject::connect(_tangentButton, SIGNAL(clicked(bool)), this, SLOT(tangentButtonClicked()));
    QObject::connect(_squareRoot, SIGNAL(clicked(bool)), this, SLOT(squareRootButtonClicked()));

    _gridLayout->addWidget(_arcSinButton, 7, 0, 1, 1);
    _gridLayout->addWidget(_arcCosButton, 7, 1, 1, 1);
    _gridLayout->addWidget(_arcTanButton, 7, 2, 1, 1);
    _gridLayout->addWidget(_powButton, 7, 3, 1, 1);

    QObject::connect(_arcSinButton, SIGNAL(clicked(bool)), this, SLOT(arcSineButtonClicked()));
    QObject::connect(_arcCosButton, SIGNAL(clicked(bool)), this, SLOT(arcCosineButtonClicked()));
    QObject::connect(_arcTanButton, SIGNAL(clicked(bool)), this, SLOT(arcTangentButtonClicked()));
    QObject::connect(_powButton, SIGNAL(clicked(bool)), this, SLOT(powButtonClicked()));

    _gridLayout->addWidget(_eRaisedToXButton, 8, 0, 1, 1);
    _gridLayout->addWidget(_logBaseEButton, 8, 1, 1, 1);
    _gridLayout->addWidget(_piButton, 8, 2, 1, 1);
    _gridLayout->addWidget(_eByItselfButton, 8, 3, 1, 1);
    QObject::connect(_eRaisedToXButton, SIGNAL(clicked(bool)), this, SLOT(eRaisedToXButtonClicked()));
    QObject::connect(_logBaseEButton, SIGNAL(clicked(bool)), this, SLOT(logBaseEButtonClicked()));
    QObject::connect(_piButton, SIGNAL(clicked(bool)), this, SLOT(piButtonClicked()));
    QObject::connect(_eByItselfButton, SIGNAL(clicked(bool)), this, SLOT(eByItselfButtonClicked()));

    _gridLayout->removeWidget(_scientificButton);
    delete _scientificButton;

    _basicCalcButton = new QPushButton("Basic");
    _gridLayout->addWidget(_basicCalcButton,5,2,1,1);
    QObject::connect(_basicCalcButton, SIGNAL(clicked(bool)), this, SLOT(returnToBasicCalcClicked()));

    _basicCalcWindow->resize(_width, (_height + 122));
    // _basicCalcWindow->resize(500, 500);
    // if(_firstSciCallOccurred == false) {
        // _firstSciCallOccurred = true;
        // _sciHeight = (_height + 122);
        // _basicCalcWindow->setFixedHeight(_sciHeight);
        // _sciWidth = _basicCalcWindow->width();
        // _sciHeight = _basicCalcWindow->height();
        // _sciWidth = _basicCalcWindow->width();
        // _basicCalcWindow->setFixedWidth(_sciWidth);
    // }
    // if(_firstSciCallOccurred == true) {
        // _basicCalcWindow->setFixedHeight(_height);
        // _basicCalcWindow->setFixedHeight(_sciHeight);
        // _basicCalcWindow->setFixedWidth(_sciWidth);
        // _basicCalcWindow->setFixedWidth(_sciWidth);
    // }
}

void MyCustomWidget::returnToBasicCalcClicked() {
    _gridLayout->removeWidget(_sineButton);
    _gridLayout->removeWidget(_cosineButton);
    _gridLayout->removeWidget(_tangentButton);
    _gridLayout->removeWidget(_squareRoot);
    _gridLayout->removeWidget(_basicCalcButton);
    _gridLayout->removeWidget(_arcCosButton);
    _gridLayout->removeWidget(_arcSinButton);
    _gridLayout->removeWidget(_arcTanButton);
    _gridLayout->removeWidget(_powButton);
    _gridLayout->removeWidget(_eRaisedToXButton);
    _gridLayout->removeWidget(_logBaseEButton);
    _gridLayout->removeWidget(_piButton);
    _gridLayout->removeWidget(_eByItselfButton);

    delete _sineButton;
    delete _cosineButton;
    delete _tangentButton;
    delete _squareRoot;
    delete _basicCalcButton;
    delete _arcCosButton;
    delete _arcSinButton;
    delete _arcTanButton;
    delete _powButton;
    delete _eRaisedToXButton;
    delete _logBaseEButton;
    delete _piButton;
    delete _eByItselfButton;

    _scientificButton = new QPushButton("Sci");
    QObject::connect(_scientificButton, SIGNAL(clicked(bool)), this, SLOT(scientificButtonClicked()));
    _gridLayout->addWidget(_scientificButton,5,2,1,1);

    _basicCalcWindow->resize(_width, _height);
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

void MyCustomWidget::arcSineButtonClicked() {
    _concatenateNumbersOperations("sin-1");
    _concatenateNumbersOperations("(");
}

void MyCustomWidget::arcCosineButtonClicked() {
    _concatenateNumbersOperations("cos-1");
    _concatenateNumbersOperations("(");
}

void MyCustomWidget::arcTangentButtonClicked() {
    _concatenateNumbersOperations("tan-1");
    _concatenateNumbersOperations("(");
}

void MyCustomWidget::powButtonClicked() {
    _concatenateNumbersOperations("^");
}

void MyCustomWidget::eRaisedToXButtonClicked() {
    _concatenateNumbersOperations("e^");
}

void MyCustomWidget::logBaseEButtonClicked() {
    _concatenateNumbersOperations("loge");
    _concatenateNumbersOperations("(");
}

void MyCustomWidget::piButtonClicked() {
    _concatenateNumbersOperations("π");
}

void MyCustomWidget::eByItselfButtonClicked() {
    _concatenateNumbersOperations("e");
}
