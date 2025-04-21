
#include <QGroupBox>
#include <QLayout>
#include <QGraphicsView>
#include <QLabel>
#include <QMainWindow>
#include <QStatusBar>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QApplication>
#include <QGraphicsEllipseItem>


#include "model/BDD.h"
#include "Minicarte.h"
#include "ZoomCarte.h"

class FenetrePrincipale : public QMainWindow {
	Q_OBJECT
	public:
		FenetrePrincipale(Carte carte);
		~FenetrePrincipale();
		void dessinerContour();
		void dessinerVilles();
		void dessinerRoutes();
		void afficherCarte();
	private:
		QGroupBox * creerGroupBoxInfos();
	private slots:
		void affiche_pos_scene( QPointF p);
	private:
		QWidget * widget_general;
		ZoomCarte *zoomArea;
		Minicarte *minimap;
		QStatusBar *barre_statut;

		Carte &carte;
		int hauteur;
		int largeur;
		
};
