#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QDebug>
#include <list>
#include "iboolean.h"
#include "interval.h"
#include "box.h"
#include "repere.h"
#include "vector"
#include "math.h"

#include "arquivos.h"

#include "particula.h"

#include <QMainWindow>


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Init();

private:
    Ui::MainWindow *ui;
    repere *R;


signals:


private slots:
    void on_ButtonStart_clicked();
};



#endif // MAINWINDOW_H
