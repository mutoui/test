#include "fivephasewidget.h"
#include "content.h"

#include <QEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QtMath>

FivePhaseWidget::FivePhaseWidget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(280, 280);
    setMouseTracking(true);
}

QRectF FivePhaseWidget::nodeRect(int index) const
{
    const QRectF area = QRectF(rect()).adjusted(18, 18, -18, -18);
    const QPointF c = area.center();
    const qreal radius = qMin(area.width(), area.height()) * 0.34;
    // 木、火、土、金、水：左、上、中、右、下
    const QPointF offsets[] = {
        QPointF(-radius, 0),
        QPointF(0, -radius),
        QPointF(0, 0),
        QPointF(radius, 0),
        QPointF(0, radius),
    };
    const QPointF p = c + offsets[index];
    return QRectF(p.x() - 32, p.y() - 32, 64, 64);
}

int FivePhaseWidget::hitIndex(const QPoint &pos) const
{
    for (int i = 0; i < 5; ++i) {
        if (nodeRect(i).contains(pos))
            return i;
    }
    return -1;
}

void FivePhaseWidget::mouseMoveEvent(QMouseEvent *event)
{
    const int h = hitIndex(event->pos());
    if (h != m_hover) {
        m_hover = h;
        setCursor(h >= 0 ? Qt::PointingHandCursor : Qt::ArrowCursor);
        update();
    }
}

void FivePhaseWidget::leaveEvent(QEvent *)
{
    m_hover = -1;
    setCursor(Qt::ArrowCursor);
    update();
}

void FivePhaseWidget::mousePressEvent(QMouseEvent *event)
{
    const int i = hitIndex(event->pos());
    if (i < 0)
        return;
    m_selected = i;
    update();
    emit elementActivated(i);
}

void FivePhaseWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.fillRect(rect(), QColor(18, 22, 32));

    const auto &items = elementCatalog();

    auto drawArrow = [&](int from, int to, const QColor &color) {
        const QPointF a = nodeRect(from).center();
        const QPointF b = nodeRect(to).center();
        QLineF line(a, b);
        line.setLength(line.length() - 36);
        QLineF back(b, a);
        back.setLength(36);
        const QPointF start = back.p2();
        p.setPen(QPen(color, 2));
        p.drawLine(start, line.p2());
        QPolygonF head;
        QLineF dir(line.p2(), start);
        dir.setLength(10);
        const QPointF t = dir.p2();
        QLineF n = dir.normalVector();
        n.setLength(5);
        head << line.p2() << (t + n.p2() - n.p1()) << (t - n.p2() + n.p1());
        p.setBrush(color);
        p.setPen(Qt::NoPen);
        p.drawPolygon(head);
    };

    // 相生：木→火→土→金→水→木
    const int sheng[][2] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 0}};
    for (const auto &e : sheng)
        drawArrow(e[0], e[1], QColor(90, 200, 140, 160));
    // 相克：木→土→水→火→金→木
    const int ke[][2] = {{0, 2}, {2, 4}, {4, 1}, {1, 3}, {3, 0}};
    for (const auto &e : ke)
        drawArrow(e[0], e[1], QColor(220, 90, 90, 90));

    p.setPen(QColor(140, 155, 180));
    QFont hint = font();
    hint.setPixelSize(11);
    p.setFont(hint);
    p.drawText(QRect(8, height() - 22, width() - 16, 18), Qt::AlignCenter,
               QStringLiteral("绿矢相生 · 红矢相克  （点击五行）"));

    for (int i = 0; i < items.size(); ++i) {
        const QRectF r = nodeRect(i);
        const bool active = (i == m_selected) || (i == m_hover);
        p.setBrush(items[i].color);
        p.setPen(QPen(active ? Qt::white : items[i].color.darker(140), active ? 3 : 1));
        p.drawEllipse(r);
        p.setPen(i == 3 ? QColor(30, 34, 42) : QColor(255, 255, 255));
        QFont f = font();
        f.setPixelSize(20);
        f.setBold(true);
        p.setFont(f);
        p.drawText(r, Qt::AlignCenter, items[i].name);
    }
}
