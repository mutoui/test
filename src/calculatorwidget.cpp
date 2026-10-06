#include "calculatorwidget.h"

#include <QGridLayout>
#include <QKeyEvent>
#include <QLineEdit>
#include <QPushButton>
#include <cmath>

namespace {

QPushButton *makeButton(const QString &text, const QString &objectName, bool accent = false)
{
    auto *button = new QPushButton(text);
    button->setObjectName(objectName);
    button->setMinimumSize(64, 52);
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button->setCursor(Qt::PointingHandCursor);
    button->setFocusPolicy(Qt::NoFocus);
    if (accent)
        button->setProperty("accent", true);
    return button;
}

QString formatNumber(double value)
{
    if (!std::isfinite(value))
        return QStringLiteral("错误");
    QString text = QString::number(value, 'g', 12);
    return text;
}

} // namespace

CalculatorWidget::CalculatorWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(QStringLiteral("计算器"));
    setMinimumSize(320, 460);
    resize(360, 520);

    setStyleSheet(QStringLiteral(R"(
        CalculatorWidget { background: #121620; }
        QLineEdit {
            background: transparent;
            border: none;
            color: #e6ebf5;
            font-size: 36px;
            font-weight: 600;
            padding: 12px 8px;
        }
        QPushButton {
            background: #2a3244;
            color: #e6ebf5;
            border: none;
            border-radius: 10px;
            font-size: 20px;
        }
        QPushButton:hover { background: #3a445c; }
        QPushButton:pressed { background: #1e2533; }
        QPushButton[accent="true"] {
            background: #3d6dff;
            color: white;
        }
        QPushButton[accent="true"]:hover { background: #5b84ff; }
    )"));

    m_display = new QLineEdit(QStringLiteral("0"));
    m_display->setReadOnly(true);
    m_display->setAlignment(Qt::AlignRight);
    m_display->setMaxLength(16);

    auto *layout = new QGridLayout(this);
    layout->setContentsMargins(16, 16, 16, 16);
    layout->setSpacing(8);
    layout->addWidget(m_display, 0, 0, 1, 4);

    struct Cell { const char *text; const char *name; int row; int col; bool accent; };
    const Cell cells[] = {
        {"AC", "clear", 1, 0, false},
        {"⌫", "back", 1, 1, false},
        {"%", "percent", 1, 2, false},
        {"÷", "div", 1, 3, true},
        {"7", "n7", 2, 0, false},
        {"8", "n8", 2, 1, false},
        {"9", "n9", 2, 2, false},
        {"×", "mul", 2, 3, true},
        {"4", "n4", 3, 0, false},
        {"5", "n5", 3, 1, false},
        {"6", "n6", 3, 2, false},
        {"-", "sub", 3, 3, true},
        {"1", "n1", 4, 0, false},
        {"2", "n2", 4, 1, false},
        {"3", "n3", 4, 2, false},
        {"+", "add", 4, 3, true},
        {"±", "neg", 5, 0, false},
        {"0", "n0", 5, 1, false},
        {".", "dot", 5, 2, false},
        {"=", "eq", 5, 3, true},
    };

    for (const auto &cell : cells) {
        auto *button = makeButton(QString::fromUtf8(cell.text), QString::fromLatin1(cell.name), cell.accent);
        layout->addWidget(button, cell.row, cell.col);
        const QString text = button->text();
        if (text.size() == 1 && text[0].isDigit())
            connect(button, &QPushButton::clicked, this, &CalculatorWidget::digitClicked);
        else if (text == QStringLiteral(".") )
            connect(button, &QPushButton::clicked, this, &CalculatorWidget::decimalClicked);
        else if (text == QStringLiteral("AC"))
            connect(button, &QPushButton::clicked, this, &CalculatorWidget::clearClicked);
        else if (text == QStringLiteral("⌫"))
            connect(button, &QPushButton::clicked, this, &CalculatorWidget::backspaceClicked);
        else if (text == QStringLiteral("%"))
            connect(button, &QPushButton::clicked, this, &CalculatorWidget::percentClicked);
        else if (text == QStringLiteral("±"))
            connect(button, &QPushButton::clicked, this, &CalculatorWidget::negateClicked);
        else if (text == QStringLiteral("="))
            connect(button, &QPushButton::clicked, this, &CalculatorWidget::equalClicked);
        else
            connect(button, &QPushButton::clicked, this, &CalculatorWidget::operatorClicked);
    }

    for (int i = 1; i <= 5; ++i)
        layout->setRowStretch(i, 1);
}

void CalculatorWidget::digitClicked()
{
    const auto *button = qobject_cast<QPushButton *>(sender());
    if (!button)
        return;
    const QString digit = button->text();
    if (m_waitingForOperand) {
        m_display->setText(digit);
        m_waitingForOperand = false;
        return;
    }
    if (m_display->text() == QStringLiteral("0"))
        m_display->setText(digit);
    else
        m_display->setText(m_display->text() + digit);
}

void CalculatorWidget::operatorClicked()
{
    const auto *button = qobject_cast<QPushButton *>(sender());
    if (!button)
        return;
    const double operand = m_display->text().toDouble();
    if (!m_pendingOperator.isEmpty()) {
        if (!calculate(operand, m_pendingOperator)) {
            m_display->setText(QStringLiteral("错误"));
            m_waitingForOperand = true;
            m_pendingOperator.clear();
            return;
        }
        m_display->setText(formatNumber(m_left));
    } else {
        m_left = operand;
    }
    m_pendingOperator = button->text();
    m_waitingForOperand = true;
}

void CalculatorWidget::equalClicked()
{
    const double operand = m_display->text().toDouble();
    if (m_pendingOperator.isEmpty())
        return;
    if (!calculate(operand, m_pendingOperator))
        m_display->setText(QStringLiteral("错误"));
    else
        m_display->setText(formatNumber(m_left));
    m_pendingOperator.clear();
    m_waitingForOperand = true;
}

void CalculatorWidget::clearClicked()
{
    m_left = 0.0;
    m_pendingOperator.clear();
    m_waitingForOperand = true;
    m_display->setText(QStringLiteral("0"));
}

void CalculatorWidget::backspaceClicked()
{
    if (m_waitingForOperand)
        return;
    QString text = m_display->text();
    text.chop(1);
    if (text.isEmpty() || text == QStringLiteral("-")) {
        m_display->setText(QStringLiteral("0"));
        m_waitingForOperand = true;
        return;
    }
    m_display->setText(text);
}

void CalculatorWidget::decimalClicked()
{
    if (m_waitingForOperand) {
        m_display->setText(QStringLiteral("0."));
        m_waitingForOperand = false;
        return;
    }
    if (!m_display->text().contains(QLatin1Char('.')))
        m_display->setText(m_display->text() + QLatin1Char('.'));
}

void CalculatorWidget::negateClicked()
{
    const double value = m_display->text().toDouble();
    if (value == 0.0)
        return;
    m_display->setText(formatNumber(-value));
    m_waitingForOperand = false;
}

void CalculatorWidget::percentClicked()
{
    const double value = m_display->text().toDouble() / 100.0;
    m_display->setText(formatNumber(value));
    m_waitingForOperand = true;
}

bool CalculatorWidget::calculate(double right, const QString &op)
{
    if (op == QStringLiteral("+"))
        m_left += right;
    else if (op == QStringLiteral("-"))
        m_left -= right;
    else if (op == QStringLiteral("×"))
        m_left *= right;
    else if (op == QStringLiteral("÷")) {
        if (right == 0.0)
            return false;
        m_left /= right;
    }
    return std::isfinite(m_left);
}

void CalculatorWidget::keyPressEvent(QKeyEvent *event)
{
    const int key = event->key();
    if (key >= Qt::Key_0 && key <= Qt::Key_9) {
        if (m_waitingForOperand) {
            m_display->setText(QString::number(key - Qt::Key_0));
            m_waitingForOperand = false;
        } else if (m_display->text() == QStringLiteral("0")) {
            m_display->setText(QString::number(key - Qt::Key_0));
        } else {
            m_display->setText(m_display->text() + QString::number(key - Qt::Key_0));
        }
        return;
    }

    switch (key) {
    case Qt::Key_Plus:
        if (auto *b = findChild<QPushButton *>(QStringLiteral("add")))
            b->click();
        break;
    case Qt::Key_Minus:
        if (auto *b = findChild<QPushButton *>(QStringLiteral("sub")))
            b->click();
        break;
    case Qt::Key_Asterisk:
        if (auto *b = findChild<QPushButton *>(QStringLiteral("mul")))
            b->click();
        break;
    case Qt::Key_Slash:
        if (auto *b = findChild<QPushButton *>(QStringLiteral("div")))
            b->click();
        break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
    case Qt::Key_Equal:
        equalClicked();
        break;
    case Qt::Key_Period:
        decimalClicked();
        break;
    case Qt::Key_Backspace:
        backspaceClicked();
        break;
    case Qt::Key_Escape:
        clearClicked();
        break;
    default:
        QWidget::keyPressEvent(event);
        break;
    }
}
