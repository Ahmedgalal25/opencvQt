#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QFileDialog>
#include <opencv2/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv_modules.hpp>
#include <opencv2/opencv.hpp>
#include<opencv2/objdetect.hpp>
#include "opencv2/imgproc.hpp"
#include <QDebug>
using namespace cv;
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void getImage();
    void on_verticalSlider_valueChanged(int value);
    void on_actionEdge_detection_triggered();
    void on_actionThresholding_triggered();
    void on_actionface_Detection_triggered();
    //void detectAndDraw( Mat& img, CascadeClassifier& cascade, double scale);
};

#endif // MAINWINDOW_H
