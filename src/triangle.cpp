#include "triangle.h"
#include <QDebug>
#include <QtQuick/qquickwindow.h>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLContext>

Triangle::Triangle():m_num(0), m_renderer(nullptr)
{
	connect(this, &QQuickItem::windowChanged, this, &Triangle::handleWindowChanged);
}

void Triangle::setNum(qreal num)
{
	if (num == m_num)
		return;
	m_num = num;
	emit numChanged();
	if (window())
		window()->update();
}

void Triangle::handleWindowChanged(QQuickWindow *win)
{
	//qDebug() << "function called: handleWindowChanged";
	if (win) {
		connect(win, &QQuickWindow::beforeSynchronizing, this, &Triangle::sync, Qt::DirectConnection);
		connect(win, &QQuickWindow::sceneGraphInvalidated, this, &Triangle::cleanup, Qt::DirectConnection);
		//! [1]
				// If we allow QML to do the clearing, they would clear what we paint
				// and nothing would show.
		//! [3]
		win->setClearBeforeRendering(false);
	}
}

void Triangle::sync()
{
	//qDebug() << "function called: sync";
	if (!m_renderer) {
		m_renderer = new TrangleRenderer();
		connect(window(), &QQuickWindow::beforeRendering, m_renderer, &TrangleRenderer::paint, Qt::DirectConnection);
	}
	m_renderer->setViewportSize(window()->size() * window()->devicePixelRatio());
	m_renderer->setNum(m_num);
	m_renderer->setWindow(window());
}

void Triangle::cleanup()
{
	qDebug() << "function called: cleanup";
	if (m_renderer) {
		delete m_renderer;
		m_renderer = nullptr;
	}
}

TrangleRenderer::~TrangleRenderer()
{
	delete m_program;
	m_program = nullptr;
}

void TrangleRenderer::paint()
{
	//qDebug() << "function called: paint";
	if (!m_program) {
		initializeOpenGLFunctions();

		m_program = new QOpenGLShaderProgram();
		m_program->addCacheableShaderFromSourceCode(QOpenGLShader::Vertex,
			"attribute highp vec4 vertices;"
			"varying highp vec2 coords;"
			"void main() {"
			"    gl_Position = vertices;"
			"    coords = vertices.xy;"
			"}");
		m_program->addCacheableShaderFromSourceCode(QOpenGLShader::Fragment,
			"uniform lowp float t;"
			"varying highp vec2 coords;"
			"void main() {"
			"    lowp float i = 1. - (pow(abs(coords.x), 4.) + pow(abs(coords.y), 4.));"
			"    i = smoothstep(t - 0.8, t + 0.8, i);"
			"    i = floor(i * 20.) / 20.;"
			"    gl_FragColor = vec4(coords * .5 + .5, i, i);"
			"}");

		m_program->bindAttributeLocation("vertices", 0);
		m_program->link();

	}
	//! [4] //! [5]
	m_program->bind();

	m_program->enableAttributeArray(0);

	float values[] = {
		-1, -1,
		1, -1,
		-1, 1,
		1, 1
	};
	m_program->setAttributeArray(0, GL_FLOAT, values, 2);
	m_program->setUniformValue("t", (float)m_num);

	glViewport(0, 0, m_viewportSize.width(), m_viewportSize.height());

	glDisable(GL_DEPTH_TEST);

	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	m_program->disableAttributeArray(0);
	m_program->release();

	// Not strictly needed for this example, but generally useful for when
	// mixing with raw OpenGL.
	m_window->resetOpenGLState();
}
