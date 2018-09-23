
#ifndef TRIANGLE_H
#define TRIANGLE_H


#include <QtQuick/QQuickItem>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLFunctions>


class TrangleRenderer : public QObject, protected QOpenGLFunctions
{
	Q_OBJECT
public:
	TrangleRenderer() : m_num(0), m_program(0) { }
	~TrangleRenderer();

	void setNum(qreal num) { m_num = num; }
	void setViewportSize(const QSize &size) { m_viewportSize = size; }
	void setWindow(QQuickWindow *window) { m_window = window; }

public slots:
	void paint();

private:
	QSize m_viewportSize;
	qreal m_num;
	QOpenGLShaderProgram *m_program;
	QQuickWindow *m_window;
};

class Triangle :public QQuickItem {
	Q_OBJECT
	Q_PROPERTY(qreal num READ num WRITE setNum NOTIFY numChanged)
public:
	Triangle();

	qreal num() const { return m_num; }
	void setNum(qreal num);

signals:
	void numChanged();



private slots:
	void handleWindowChanged(QQuickWindow *win);


public slots:
	void sync();
	void cleanup();

private:
	qreal m_num;
	TrangleRenderer *m_renderer;
};

#endif 
