#include "openglwindow.h"
#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);

	GlDrawWidget w;
	//    w.setWindowFlag(Qt::FramelessWindowHint);
	//    w.setAttribute(Qt::WA_TranslucentBackground);
	QPushButton ptn(&w);
	QObject::connect(&ptn, &QPushButton::clicked, [&] {
		static double rate = 1.0;
		w.drawRect(w.rect().adjusted(rate, rate, -rate, -rate));
		rate += 4;
	});
	w.show();

	return a.exec();
}
