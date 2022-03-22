#include "smiley.h"
#include <QPainter>

Smiley::Smiley(QWidget *parent)
    : QWidget(parent)
{
}

QSize Smiley::sizeHint() const {
    return QSize(200,200);
}

void Smiley::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPoint center = rect().center();
    int size = qMin(width(), height());
    
    // enter your code here
    // draw round face with center in 'center' and diameter of 'size'
    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::black);
    painter.setPen(pen);
    painter.setBrush(Qt::yellow);
    // Bad approach because the eyes and smile do not depend on the center (mismatch when resizing!)
    // painter.drawEllipse(center, center.x() - size, center.y() -size);
    painter.drawEllipse(center, size/2, size/2);

    // draw eyes
    int eyeHeight = center.y() - size/4;
    QPoint leftEye(center.x()-size/8, eyeHeight);
    QPoint rightEye(center.x()+size/8, eyeHeight);

    paintEye(&painter, leftEye, size/8);
    paintEye(&painter, rightEye, size/8);

    // draw smile

    int smileHeight = center.y()-size/8;
    paintSmile(&painter, QRect(center.x()-size/3, smileHeight, 2*size/3, size/2));

}

void Smiley::paintEye(QPainter *painter, const QPoint &pt, int size) {
    // enter your code here
    // paint an ellipse with center in pt, height of size and width of size/2
    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::red);
    painter->setPen(pen);
    painter->setBrush(Qt::white);
    painter->drawEllipse(pt, size/2, size);
}

void Smiley::paintSmile(QPainter *painter, const QRect &r) {
    // enter your code here
    // draw an arc inside the area of r
    painter->drawArc(r, 0, -180 * 16);
}
