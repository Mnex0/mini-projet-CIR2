
#include <QApplication>
#include <QMessageBox>
#include "FenetrePrincipale.h"


int main(int argc, char * argv[]) {
    QApplication app(argc, argv);
	
	Carte carte;
	FenetrePrincipale mw (carte);
	mw.show();

	mw.dessinerContour();
	mw.dessinerVilles();
	mw.dessinerRoutes();

	return app.exec();
}