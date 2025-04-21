#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

class ZoomCarte : public QGraphicsView {
    Q_OBJECT
public:
    ZoomCarte();
    ~ZoomCarte() {};
    //virtual ~ZoomCarte() = default; // Ensure a virtual destructor for proper cleanup
};

#endif // FENETREPRINCIPALE_H