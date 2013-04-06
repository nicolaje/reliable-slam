#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QDebug>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

    void Init();

private:
    Ui::MainWindow *ui;

signals:


private slots:
    void on_ButtonStart_clicked();
};



#endif // MAINWINDOW_H
