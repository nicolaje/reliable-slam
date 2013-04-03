#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "ibex.h"
#include "sivia.h"

double epsilon;

MainWindow::MainWindow(QWidget *parent) :  QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

void MainWindow::Init() {
    epsilon=ui->EpsilonSpinBox->value();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_ButtonStart_clicked()
{

    Init();

    // Build the frame
    double xmin=-10;
    double xmax=10;
    double ymin=-10;
    double ymax=10;

    Frame* frame = new Frame(this,ui->graphicsView,xmin,xmax,ymin,ymax);

    // run SIVIA
    Sivia sivia(*frame,epsilon);
}
