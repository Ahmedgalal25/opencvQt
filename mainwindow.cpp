#include "mainwindow.h"
#include "ui_mainwindow.h"

void detectAndDraw( Mat& img, CascadeClassifier& cascade, double scale);
int sliderValue=255;
cv::Mat g_src;
bool threFlag=false;
cv::Mat gray;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //QString path="";

    connect(ui->Browsebtn, SIGNAL(released()),this,SLOT(getImage()));
     ui->imageViewer->setScaledContents(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::getImage()
{   //view the path of the opened image
    QString filename = QFileDialog::getOpenFileName(this,tr("Open image"),"/home/galal/Pictures",tr("Images Files(*.png *.jpg)"));
    QString path =  filename;
    ui->pathLabel->setText(path);
     //view image
    cv::Mat img=cv::imread(path.toStdString(),CV_LOAD_IMAGE_ANYCOLOR);
    g_src=img;
    QImage image=  QImage( img.data,img.cols, img.rows,static_cast<int>(img.step),QImage::Format_RGB888 );
    ui->imageViewer->setPixmap(QPixmap::fromImage(image.rgbSwapped()));
    ui->imageViewer->show();
    //cv::Mat img;
        //cv::threshold(src,img,128,255,CV_THRESH_BINARY);


        //show cv::mat image bu open cv on new dialog
        //imshow("",img);
        //show Qimage on Qlabel



    //cv::Mat src_gray;
    //cv::Mat imgg;
        /*
        //cv::cvtColor( src, src_gray, CV_RGB2GRAY );
        //cv::threshold(src_gray,img,60,255,CV_THRESH_BINARY);
        //Mat img;

        //cvCvtColor( &src, &img, CV_RGB2GRAY );
        //cvThreshold(&src_gray,&img, thresh, maxValue, CV_THRESH_BINARY);
        // convert from cv::Mat to Qimage
        */


}

void MainWindow::on_verticalSlider_valueChanged(int value)
{

    if(threFlag==true){
        cv::Mat imgg=gray;
        cv::Mat img;
        cv::threshold(gray,img,value,255,CV_THRESH_BINARY);
         QImage image=  QImage( img.data,img.cols, img.rows,static_cast<int>(img.step),QImage::Format_Alpha8 );

         //show cv::mat image bu open cv on new dialog
         //imshow("",img);
         //show Qimage on Qlabel
         ui->imageViewer->setPixmap(QPixmap::fromImage(image));
         ui->imageViewer->show();
    }


}

void MainWindow::on_actionEdge_detection_triggered()
{
        //cv::namedWindow( "Original image", CV_WINDOW_AUTOSIZE );
        //cv::imshow( "Original image", g_src );

        cv::Mat gray, edge, img;
        cv::cvtColor(g_src, gray, CV_BGR2GRAY);

        cv::Canny( gray, edge, 50, 150, 3);

        edge.convertTo(img, CV_8U);
        QImage image=  QImage( img.data,img.cols, img.rows,static_cast<int>(img.step),QImage::Format_Alpha8 );

        //show cv::mat image bu open cv on new dialog
        //imshow("",img);
        //show Qimage on Qlabel
        ui->imageViewer->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_actionThresholding_triggered()
{
    threFlag=true;
    cv::cvtColor(g_src, gray, CV_BGR2GRAY);

}
void detectAndDraw( Mat& img, CascadeClassifier& cascade, double scale){
    //vector<cv::Rect> objects;
    //cascade.load( "../../haarcascade_frontalcatface.xml");
    vector<Rect> faces;
    Mat gray;
    cvtColor( img, gray,CV_RGB2GRAY );
    //cascade.detectMultiScale(gray,faces,1.1,3,3,cv::Size(45,80));
    cascade.detectMultiScale( gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );
    for ( size_t i = 0; i < faces.size(); i++ )
    {
    Rect r = faces[i];
    Scalar color = Scalar(255, 0, 0);
    rectangle( img, cvPoint(cvRound(r.x*scale), cvRound(r.y*scale)), cvPoint(cvRound((r.x +
    r.width-1)*scale), cvRound((r.y + r.height-1)*scale)), color, 3, 8, 0);
    }
    namedWindow("Face Detection",CV_WINDOW_NORMAL);
    resizeWindow("Face Detection",600,600);
    imshow( "Face Detection", img );

}

void MainWindow::on_actionface_Detection_triggered()
{
    Mat img=g_src;
    CascadeClassifier cascade;
    cascade.load( "/home/galal/opencv/opencv-3.0.0-alpha/data/haarcascades/haarcascade_frontalface_alt.xml" ) ;
    //cv::cascascade.load( "../../haarcascade_frontalcatface.xml" ) ;
    detectAndDraw(img,cascade,1);
}
