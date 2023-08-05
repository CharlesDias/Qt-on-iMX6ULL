#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* SODIMM_55 is equal to bank gpiochip1 and line 0*/
    m_outputLine = getGpioLine("gpiochip1", 0);

    /* Configure the GPIO line as output. */
    gpiod_line_request_output(m_outputLine, "gpioRelay", GPIOD_LINE_ACTIVE_STATE_HIGH);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnOn_clicked()
{
    gpiod_line_set_value(m_outputLine, 0);
}


void MainWindow::on_btnOff_clicked()
{
    gpiod_line_set_value(m_outputLine, 1);
}

struct gpiod_line* MainWindow::getGpioLine(QString bank, int gpio)
{
    struct gpiod_chip *chip;
    QByteArray byteArray = bank.toLocal8Bit();

    /* Open the GPIO bank. */
    chip = gpiod_chip_open_by_name(byteArray.data());
    if (chip == NULL)
    {
        return NULL;
    }

    /* Open the GPIO line. */
    return gpiod_chip_get_line(chip, gpio);
}
