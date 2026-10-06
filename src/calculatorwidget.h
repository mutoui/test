#pragma once

#include <QWidget>

class QLineEdit;

class CalculatorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CalculatorWidget(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    void digitClicked();
    void operatorClicked();
    void equalClicked();
    void clearClicked();
    void backspaceClicked();
    void decimalClicked();
    void negateClicked();
    void percentClicked();

    bool calculate(double right, const QString &op);

    QLineEdit *m_display = nullptr;
    QString m_pendingOperator;
    double m_left = 0.0;
    bool m_waitingForOperand = true;
};
