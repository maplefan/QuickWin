#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef RECTPAINT_H
#define RECTPAINT_H

#include <QRectF>
#include <QPen>

class RectPaint : public QRectF
{
public:
	RectPaint();
	RectPaint(const QPointF &topLeft, const QPointF &bottomRight, const QPen &pen, const QBrush &brush);
	RectPaint(const QRectF &rect);
	~RectPaint();

	void setPen(const QPen &pen);
	const QPen& getPen() const;

	void setBrush(const QBrush &brush);
	const QBrush& getBrush() const;

private:
	QPen _pen;
	QBrush _brush;
};

#endif // RECTPAINT_H
