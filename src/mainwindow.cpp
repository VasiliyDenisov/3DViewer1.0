#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(geometry().width(), geometry().height());
    glWidget = new GLWidget(ui->openGLWidget);
    glWidget->setFixedSize(1350, 1000);

    connect(ui->background_color_btn,SIGNAL(clicked()),this,SLOT(change_background_color()));
    connect(ui->load_from_file_btn,SIGNAL(clicked()),this,SLOT(load_file()));
    connect(ui->screenshot_btn,SIGNAL(clicked()),this,SLOT(take_screenshot()));
    connect(ui->record_btn,SIGNAL(clicked()),this,SLOT(create_gif()));
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::load_file()
{
    QString path = QFileDialog::getOpenFileName(this, "Load a file", QDir::currentPath());
    QFileInfo fileInfo(path);
    if (!path.isEmpty()) {
        if (fileInfo.suffix() != "obj") {
            QMessageBox::warning(this, "Warning!", "Invalid file extension. Expected '.obj'");
        } else {
            glWidget->modelPath = path;
            QString filename = fileInfo.fileName();
            ui->Filename_Label->setText(filename);
        }
    }
}

void MainWindow::change_background_color()
{
    QColor bg = glWidget->get_background();
    QColor new_bg = QColorDialog::getColor(bg, this, tr("Background Color:"));
    if (new_bg.isValid()) {
      glWidget->set_background(new_bg);
      glWidget->update();
    }
}

void MainWindow::take_screenshot()
{
    QString filename = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString filter = "JPEG Files (*.jpg);;BMP Files (*.bmp);;All Files (*)";
    QString filepath = QFileDialog::getSaveFileName(this, "Enter the name of screenshot", filename, filter);
    if (!filepath.isEmpty()){
      QString extension = "jpg";
        extension = QFileInfo(filepath).suffix().toLower();
        extension = extension.isEmpty() ? "jpg" : extension;
        if (!(extension == "jpeg" || extension == "jpg" || extension == "bmp")) {
            QMessageBox::warning(this, "Warning!", "Invalid file extension. Expected JPG or BMP");
        }
        QPixmap pixmap (glWidget->size());
        QRect renderRect(QPoint(0, 0), glWidget->size());
        pixmap.fill(Qt::white);
        glWidget->render(&pixmap, QPoint(), renderRect);
        pixmap.save(filepath + "." + extension, extension.toUtf8().constData());
    }
}

void MainWindow::create_gif()
{
    QString filename = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString filter = "GIF files (*.gif);;All Files (*)";
    QString filepath = QFileDialog::getSaveFileName(this, "Enter the name of screenshot", filename, filter);
    if (!filepath.isEmpty()){
        QGifImage gif(QSize(640, 480));
        gif.setDefaultDelay(100);
        for (QVector<QImage>::Iterator screen = gif.begin(); screen != gif.end();
             ++screen) {
            gif.addFrame(*screen);
        }
        gif.save(filename);
        gif.clear();
        count = 0.0;
    }
}
