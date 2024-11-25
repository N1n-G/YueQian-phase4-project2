
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#define CVUI_IMPLEMENTATION
#include "cvui.h"

#include <unistd.h>

// 添加OpenCV的头文件
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
    // 实例化一个摄像头
    VideoCapture *cap = new VideoCapture;

    int deviceID = 0; // 0 = open default camera  0 默认 摄像头
    int apiID = cv::CAP_ANY; // 0 = autodetect default API  0 自动 监测  摄像头采集的 格式

    // 打开摄像头
    cap->open(deviceID, apiID);

    // 判断摄像头是否打开
    if (!cap->isOpened())
    {
        cerr << "ERROR! Unable to open camera\n";
        return 0;
    }
    cout << "Start grabbing" << endl << "Press 'Enter' to terminate" << endl;


    // 定义一个 人脸检测器
    CascadeClassifier cascade ;

    //  加载检测器
    if(!cascade.load("C:/opencv452/etc/haarcascades/haarcascade_frontalface_alt.xml"))
    {
            cerr << "ERROR: Could not load classifier cascade" << endl;
            return -1;
    }


    while (1)
    {
        // 定义一个mat类用于存储数据帧
        Mat frame;

        // 读取采集的数据 放入 数据帧中
        cap->read(frame);

        if (frame.empty()) {
            cerr << "ERROR! blank frame grabbed\n";
            return 0;
        }


/*------------------------------------------------------------------------------------------*/

        // 水平翻转画面，1表示水平翻转，-1是水平和垂直翻转，0是垂直翻转
        flip(frame, frame, 1);


#if 0
detectMultiScale函数的参数包括：
    frame：输入图像，即你想要在其中检测对象的图像。
    faces：一个向量(动态数组)，用于存储检测到的面部矩形框的位置。
    1.1：每次图像尺寸减小的比例。这个值越大，检测速度越快，但可能会错过一些小对象。
    3：每个候选矩形应该保留的邻近矩形的最小数量。这个值越大，检测的精度越高，但可能会增加误检率。
    0：操作标志。默认值为0。
    Size(100, 100)：检测窗口的最小尺寸。
    Size(300, 300)：检测窗口的最大尺寸。
#endif

        // 构造一个数组，用于存储检测到的人脸位置的数据（矩形）
        std::vector <Rect> faces;

        // 检测人脸并存储结果
        cascade.detectMultiScale( frame, faces,1.1, 3, 0,Size(100, 100) , Size(300,300) );

        if(faces.size() > 0)
        {
            cout << " face succeed: now have " << faces.size() <<  " face. " << endl;


#if 0
          CV_EXPORTS_W void rectangle(InputOutputArray img, Point pt1, Point pt2,
                                        const Scalar& color, int thickness = 1,
                                        int lineType = LINE_8, int shift = 0);


          img：输入/输出图像，即你想要在其上绘制矩形的图像。
          pt1：矩形的第一个角点(起点左上角)。
          pt2：矩形的第二个角点（终点右下角）。
          color：矩形边框的颜色。颜色由BGR（蓝、绿、红）值组成，例如Scalar(255, 0, 0)表示蓝色。
          thickness：矩形边框的厚度。默认值为1，表示绘制一个单像素宽的边框。如果值为负数，例如FILLED，则绘制一个填充的矩形。
          lineType：线条的类型。默认值为LINE_8，表示8连通的线条。其他可能的值包括LINE_4（4连通的线条）和LINE_AA（抗锯齿的线条）。
          shift：坐标点的小数位数。默认值为0。
#endif

            // 从前面检测到的人脸数据中获得人脸出现的起始坐标
            int x = faces.at(0).x;
            int y = faces.at(0).y;
            // 人脸的宽度和高度
            int w = faces.at(0).width;
            int h = faces.at(0).height ;

            // 绘制矩形框标记人脸
            rectangle(frame, Point(x , y ),Point(x+w , y+h) , cv::Scalar(0, 255, 0), 2, cv::LINE_8, 0);


        }
        else{
            cout << "face err.." << endl ;
        }


/*------------------------------------------------------------------------------------------*/

        // 显示翻转后的画面
        imshow("Live", frame);

        // 等待按键，若按下 'enter' 则退出循环
        if (waitKey(5) == 13)
            break;
    }
    return 0;
}
