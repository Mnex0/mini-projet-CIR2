#include "FenetrePrincipale.h"

FenetrePrincipale::FenetrePrincipale(Carte carte) : carte(carte)
{
	int largeur = 200, hauteur = 200;
	// initialisation carte
	zoomArea = new ZoomCarte;
	zoomArea->setMinimumSize(largeur, hauteur);

	// initialisation fenetre principale
	this->setWindowTitle("Mini Projet");
	this->setWindowIcon(QIcon(":/images/icone.png"));
	this->setGeometry(0, 0, largeur, hauteur);
	this->setStyleSheet("background-color: #FFFFFF;");

	// creation widget principal
	QWidget *widget_general;

	widget_general = new QWidget;
	QHBoxLayout *qbl_general = new QHBoxLayout;
	widget_general->setLayout(qbl_general);
	this->setCentralWidget(widget_general);

	largeur = 600;
	hauteur = 400;
	setMinimumSize(largeur, hauteur);

	qbl_general->addWidget(creerGroupBoxInfos());

	qbl_general->addWidget(zoomArea);
	barre_statut = statusBar();

	BDD bdd = BDD("tcp://localhost:3306", "carte", "isen", "isen29");
	bdd.ajouterContour();
	bdd.ajouterWaypoints();
	bdd.ajouterVilles();
	bdd.ajouterRoutes();
	this->dessinerVilles();
	// this->dessinerRoutes();
	// this->afficherCarte();
}

QGroupBox *FenetrePrincipale::creerGroupBoxInfos()
{
	QGroupBox *groupBox = new QGroupBox("Choisir ville départ");
	QVBoxLayout *layout = new QVBoxLayout;

	QLabel *label = new QLabel("détails");
	layout->addWidget(label);

	groupBox->setLayout(layout);
	return groupBox;
}

ZoomCarte::ZoomCarte()
{
	// Initialisation de la vue
	this->setRenderHint(QPainter::Antialiasing);
	this->setRenderHint(QPainter::TextAntialiasing);
	this->setRenderHint(QPainter::SmoothPixmapTransform);
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setDragMode(QGraphicsView::ScrollHandDrag);
	this->setMouseTracking(true);
}

Minicarte::Minicarte()
{
	// initialisation minicarte à gauche
	this->setRenderHint(QPainter::Antialiasing);
	this->setRenderHint(QPainter::TextAntialiasing);
	this->setRenderHint(QPainter::SmoothPixmapTransform);
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setDragMode(QGraphicsView::ScrollHandDrag);
	this->setMouseTracking(true);
}

void FenetrePrincipale::affiche_pos_scene(QPointF p)
{
	// Afficher position souris dans la barre_status
	QString pos = QString("Position : %1, %2").arg(p.x()).arg(p.y());
	barre_statut->showMessage(pos);
}

FenetrePrincipale::~FenetrePrincipale()
{
	delete zoomArea;
	delete minimap;
	delete barre_statut;
}

void FenetrePrincipale::dessinerContour()
{
}

void FenetrePrincipale::dessinerVilles()
{
	// QPen pen(Qt::blue, 2);
	QPainter painter(this->zoomArea);
	painter.setPen(Qt::green);
	float X = 0, Y = 0;
	QGraphicsEllipseItem *point = nullptr;
	vector<waypoint> &waypoints = this->carte.getWaypoints();
	for (auto &wayP : waypoints)
	{
		X = (47 - wayP.getLat()) * 100;
		Y = (0 - wayP.getLon()) * 100;
		cout << X << Y << endl;
		point = new QGraphicsEllipseItem(Y, X, 1, 1);
	}
}

void FenetrePrincipale::dessinerRoutes()
{
	QGraphicsLineItem *line = nullptr;
	float X1{0}, Y1{0}, X2{0}, Y2{0};
	for (auto &route : carte.getRoutes())
	{
		X1 = route.getWaypointFin().getLon();
		Y1 = route.getWaypointFin().getLat();
		X2 = route.getWaypointFin().getLon();
		Y2 = route.getWaypointFin().getLat();
		line = new QGraphicsLineItem(X1, Y1, X2, Y2);
		
	}
}

void FenetrePrincipale::afficherCarte()
{
	// affichage
}
