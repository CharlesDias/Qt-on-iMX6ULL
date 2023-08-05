#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <gpiod.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnOn_clicked();

    void on_btnOff_clicked();

private:
    Ui::MainWindow *ui;

    struct gpiod_line* getGpioLine(QString bank, int gpio);

    struct gpiod_line* m_outputLine;
};
#endif // MAINWINDOW_H
