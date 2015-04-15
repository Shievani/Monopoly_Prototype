#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <ctime> //includes time from computer
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

public slots:
    void on_rollButton_clicked(); /*slot created when Roll button is pressed, basically takes signal from the action of clicking
                                    roll button and this function on_rollButton_clicked contains all that should happen when button
                                    is clicked*/


private slots:
    void on_YesButton_clicked();

    void on_NoButton_clicked();

private:
    Ui::MainWindow *ui;

    void setResponseButtonsState(bool);
    void updateTurn();

    int rolldice1;
    int rolldice2;
    int turn=0;

};



#endif // MAINWINDOW_H
