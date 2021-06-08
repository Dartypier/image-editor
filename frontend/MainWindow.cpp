#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    pendingSaveModifications(false)
{
    ui->setupUi(this);
    ui->graphicsView->hide();
    ui->statusbar->hide();
    ui->statusbar->addPermanentWidget(&imageName);
    ui->statusbar->addPermanentWidget(&imageSize);
    activeImage.reset();

    zoomList << 1.0 << 1.5 << 2.2 << 3.3 << 4.7 << 6.8;
    zoomList << 10 << 15 << 22 << 33 << 47 << 68;
    zoomList << 100 << 150 << 220 << 330 << 470 << 680;
    zoomList << 1000 << 1500 << 2200 << 3300 << 4700 << 6800;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString imagePath = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));

    if(!imagePath.isEmpty()){
        activeImage.reset(new Image(imagePath));

        qDebug() << activeImage->getFilename();


        scene.clear();
        pixmapItem = scene.addPixmap(QPixmap::fromImage(activeImage->getQImage()));
        scene.setSceneRect(0,0, activeImage->getW(), activeImage->getH());
        ui->graphicsView->setScene(&scene);




        if(ui->graphicsView->isHidden())
            ui->graphicsView->show();

        ui->graphicsView->fitInView(pixmapItem, Qt::KeepAspectRatio);
        updateStatusBar();
        ui->statusbar->show();
    }
}

void MainWindow::zoomUpdate(bool increment)
{
    double zoom = ui->graphicsView->transform().m11() *100;

    if(increment) {
        for(double z: zoomList) {
            if ((z-z/10) > zoom) {
                zoom = z;
                break;
            }
        }
    }

    else{

        for(int i=zoomList.count()-1; i>0; i--){
            double zoomIt = zoomList[i];

            if((zoomIt+zoomIt/10) < zoom) {
                zoom = zoomIt;
                break;
            }
            qDebug() <<"inside zoom out " << zoom;
        }
    }

    ui->graphicsView->setTransform(QTransform::fromScale(zoom/100, zoom/100));
}

void MainWindow::updateStatusBar()
{
    if(activeImage.get()!=nullptr){
        imageName.setText(activeImage->getFilename());
        imageSize.setText(QString("%1x%2")
                          .arg(activeImage->getH())
                          .arg(activeImage->getW()));
    }
}

void MainWindow::on_actionSave_as_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this,
        "",
        activeImage->getFilename(),
        tr("Images (*.jpg *.png *.bmp)"));

    if(!filename.isEmpty()){
        activeImage->save(filename);
        activeImage->setPath(filename);
        updateStatusBar();
    }

    pendingSaveModifications = false;
}

//void MainWindow::resizeEvent(QResizeEvent *event)
//{
//    if(!ui->graphicsView->isHidden())
//        ui->graphicsView->fitInView(pixmapItem, Qt::KeepAspectRatio);
//    QWidget::resizeEvent(event);
//}

void MainWindow::on_actionZoom_Adapt_triggered()
{
    if(!ui->graphicsView->isHidden())
        ui->graphicsView->fitInView(pixmapItem, Qt::KeepAspectRatio);
}

void MainWindow::on_actionZoomInc_triggered()
{
    zoomUpdate(true);
    qDebug() << "Zoom In";
}

void MainWindow::on_actionZoomDec_triggered()
{
    zoomUpdate(false);
    qDebug() << "Zoom out";
}

void MainWindow::on_actionRotate_Clockwise_triggered()
{
    std::shared_ptr<ICommand> c1(new rotateClockwiseCommand(*activeImage));
    commandManager.execute(c1);
    qDebug() << "rotate clockwise";
    activeImage->updateBuffer();
    pixmapItem->setPixmap(QPixmap::fromImage(activeImage->getQImage()));
    scene.setSceneRect(0,0, activeImage->getW(), activeImage->getH());
    on_actionZoom_Adapt_triggered();
    updateStatusBar();

    pendingSaveModifications = true;
}

void MainWindow::on_actionRotate_anticlockwise_triggered()
{
    std::shared_ptr<ICommand> c1(new rotateAntiClockwiseCommand(*activeImage));
    commandManager.execute(c1);
    qDebug() << "rotate clockwise";
    activeImage->updateBuffer();
    pixmapItem->setPixmap(QPixmap::fromImage(activeImage->getQImage()));
    scene.setSceneRect(0,0, activeImage->getW(), activeImage->getH());
    on_actionZoom_Adapt_triggered();
    updateStatusBar();

    pendingSaveModifications = true;
}

void MainWindow::on_actionFlip_x_triggered()
{
    std::shared_ptr<ICommand> c1(new flipXCommand(*activeImage));
    commandManager.execute(c1);
    qDebug() << "rotate clockwise";
    activeImage->updateBuffer();
    pixmapItem->setPixmap(QPixmap::fromImage(activeImage->getQImage()));

    pendingSaveModifications = true;
}

void MainWindow::on_actionFlip_y_triggered()
{
    std::shared_ptr<ICommand> c1(new flipYCommand(*activeImage));
    commandManager.execute(c1);
    qDebug() << "rotate clockwise";
    activeImage->updateBuffer();
    pixmapItem->setPixmap(QPixmap::fromImage(activeImage->getQImage()));

    pendingSaveModifications = true;
}

void MainWindow::on_actionUndo_triggered()
{
    commandManager.undo();
    activeImage->updateBuffer();
    pixmapItem->setPixmap(QPixmap::fromImage(activeImage->getQImage()));
    updateStatusBar();

    pendingSaveModifications = true;
}

void MainWindow::on_actionRedo_triggered()
{
    commandManager.redo();
    activeImage->updateBuffer();
    pixmapItem->setPixmap(QPixmap::fromImage(activeImage->getQImage()));
    updateStatusBar();

    pendingSaveModifications = true;
}

void MainWindow::on_actionGrayscale_triggered()
{
    std::shared_ptr<ICommand> c1(new grayScaleCommand(*activeImage));
    commandManager.execute(c1);
    qDebug() << "grayscale";
    activeImage->updateBuffer();
    pixmapItem->setPixmap(QPixmap::fromImage(activeImage->getQImage()));

    pendingSaveModifications = true;
}

void MainWindow::on_actionBlur_triggered()
{
    std::shared_ptr<ICommand> c1(new blurCommand(*activeImage));
    commandManager.execute(c1);
    qDebug() << "blur";
    activeImage->updateBuffer();
    pixmapItem->setPixmap(QPixmap::fromImage(activeImage->getQImage()));

    pendingSaveModifications = true;
}

void MainWindow::on_actionSharpen_triggered()
{
    std::shared_ptr<ICommand> c1(new sharpenCommand(*activeImage));
    commandManager.execute(c1);
    qDebug() << "sharpen";
    activeImage->updateBuffer();
    pixmapItem->setPixmap(QPixmap::fromImage(activeImage->getQImage()));

    pendingSaveModifications = true;
}

void MainWindow::on_actionEmboss_triggered()
{
    std::shared_ptr<ICommand> c1(new embossCommand(*activeImage));
    commandManager.execute(c1);
    qDebug() << "emboss";
    activeImage->updateBuffer();
    pixmapItem->setPixmap(QPixmap::fromImage(activeImage->getQImage()));

    pendingSaveModifications = true;
}

void MainWindow::on_actionEdge_detect_triggered()
{
    std::shared_ptr<ICommand> c1(new edgeDetectCommand(*activeImage));
    commandManager.execute(c1);
    qDebug() << "edgedetect";
    activeImage->updateBuffer();
    pixmapItem->setPixmap(QPixmap::fromImage(activeImage->getQImage()));

    pendingSaveModifications = true;
}

void MainWindow::closeEvent(QCloseEvent *event){

    if(pendingSaveModifications){

        QString title = APP_NAME;
        QString message = "<p>Any modifications not saved will be lost. Are you "
                          "sure to close Image Editor?</p>";

        int status = QMessageBox::question(this, title, message, QMessageBox::Ok, QMessageBox::Cancel);

        if(status == QMessageBox::Ok)
            event->accept();
        else
            event->ignore();
    }
    else{
        event->accept();
    }
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionSave_triggered()
{
    activeImage->save(activeImage->getPath());
}

void MainWindow::on_actionAbout_Image_Editor_triggered()
{
    QString title = APP_NAME;
    QString msg = QString("<h2>%1</h2>")
            .arg(title);
    msg += QString("<p>"
        "Uni Project for <i>Programmazione</i> class teached by Marco Bertini.</p>"
        "<p>The Project aims to be a simple image editor with the use of filters and convolution matrixes.</p>"
        "<p>Powered by C++ and Qt5.</p>");
    msg += QString("<p><b>Author: </b> <a href =%1>Jacopo Zecchi</a></p>")
            .arg("https://github.com/Dartypier");
    msg += QString("<p><b>Version: </b>%1")
            .arg(APP_VERSION);
    msg += QString("<p><div>Icons made by <a href=%1 title=%2>Freepik</a> from <a href=%3 title=%4>www.flaticon.com</a></div></p>")
            .arg("https://www.freepik.com")
            .arg("Freepik")
            .arg("https://www.flaticon.com/")
            .arg("Flaticon");

    QMessageBox::about(this, title, msg);
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this);
}
