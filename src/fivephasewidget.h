#pragma once

#include <QWidget>

class FivePhaseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FivePhaseWidget(QWidget *parent = nullptr);

signals:
    void elementActivated(int index);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    int hitIndex(const QPoint &pos) const;
    QRectF nodeRect(int index) const;

    int m_hover = -1;
    int m_selected = 0;
};
