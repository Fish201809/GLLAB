#include <QGuiApplication>
#include <QtQuick/QQuickView>

#include "triangle.h"

int main(int argc, char *argv[])
{
	//QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QGuiApplication app(argc, argv);

	qmlRegisterType<Triangle>("OpenGLUnderQML", 1, 0, "Triangle");

	QQuickView view;
	view.setResizeMode(QQuickView::SizeRootObjectToView);
	view.setSource(QUrl(QStringLiteral("qrc:/main.qml")));
	view.show();

	return app.exec();
}