#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QLabel>
#include <QCloseEvent>
#include "../backend/Image.h"
#include "../backend/CommandPattern/Commands.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionZoom_Adapt_triggered();

    void on_actionZoomInc_triggered();

    void on_actionZoomDec_triggered();

    void on_actionRotate_Clockwise_triggered();

    void on_actionRotate_anticlockwise_triggered();

    void on_actionFlip_x_triggered();

    void on_actionFlip_y_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionGrayscale_triggered();

    void on_actionBlur_triggered();

    void on_actionSharpen_triggered();

    void on_actionEmboss_triggered();

    void on_actionEdge_detect_triggered();

    void on_actionExit_triggered();

    void on_actionSave_as_triggered();

    void on_actionAbout_Image_Editor_triggered();

    void on_actionAbout_Qt_triggered();

    void on_actionContrast_triggered();

    void on_actionBrightness_triggered();

    void on_actionColormask_triggered();

    void on_actionScale_triggered();

protected slots:
//    void resizeEvent(QResizeEvent *event) override;
    void zoomUpdate(bool increment);

private:
    Ui::MainWindow *ui;
    QGraphicsPixmapItem* pixmapItem;
    QGraphicsScene scene;

    std::unique_ptr<Image> activeImage;
    CommandManager commandManager;

    bool pendingSaveModifications;

    QList<double> zoomList;

    QLabel imageName;
    QLabel imageSize;

protected:
    void closeEvent(QCloseEvent *event) override;
    void updateStatusBar();
};

#endif // MAINWINDOW_H
