/*
 * @Description: 色块识别和追踪
 * @Author: lifuguan
 * @Date: 2019-10-03 15:21:38
 * @LastEditTime: 2019-11-20 23:02:23
 * @LastEditors: Please set LastEditors
 */
#include <iostream>
#include <string>
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

using namespace cv;

static const std::string IMAGE_TOPIC = "/usb_cam/image_raw";

std::vector<std::vector<int>> position = {{160, 100}, {320, 100}, {480, 100}, {160, 260}, {320, 260}, {480, 260}, {160, 420}, {320, 420}, {480, 420}};

//设置颜色区间
//red
Scalar u_range[3] = {Scalar(0, 160, 50), Scalar(10, 255, 255)};
//green
Scalar d_range[3] = {Scalar(25, 43, 46), Scalar(95, 255, 255)};
//blue
Scalar l_range[3] = {Scalar(98, 102, 20), Scalar(130, 255, 255)};

// 获取图像的160, 420回调函数
void imageCallback(const sensor_msgs::ImageConstPtr &msg);

int main(int argc, char **argv)
{
    ros::init(argc, argv, "cubot_cv_node");
    ros::NodeHandle nh;
    image_transport::ImageTransport it(nh);
    image_transport::Subscriber sub = it.subscribe(IMAGE_TOPIC, 10, imageCallback);
    namedWindow("OPENCV_WINDOW");

    ros::Rate loop(10);
    while (nh.ok())
    {
        ros::spinOnce();
        loop.sleep();
    }

    return 0;
}

void imageCallback(const sensor_msgs::ImageConstPtr &msg)
{
    Mat frame_hsv, frame;
    try
    {
        frame = cv_bridge::toCvShare(msg, "bgr8")->image;
    }
    catch (cv_bridge::Exception &e)
    {
        ROS_ERROR("%s", e.what());
        return;
    }
    // 图像格式切换
    cvtColor(frame, frame_hsv, CV_BGR2HSV);

    Mat red_frame, blue_frame, green_frame;

    inRange(frame_hsv, u_range[0], u_range[1], red_frame);
    inRange(frame_hsv, d_range[0], d_range[1], blue_frame);
    inRange(frame_hsv, l_range[0], l_range[1], green_frame);

    std::cout << red_frame.at<Vec3b>(160, 100) << std::endl;
    for (int i = 0; i < 9; i++)
    {
        if (red_frame.at<Vec3b>(position[i][0], position[i][1])[0] != 0)
        {
            putText(frame, std::to_string(i + 1), Point(position[i][0], position[i][1]), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 2);
        }
    }

    imshow("OPENCV_WINDOW", frame);
    imshow("red", red_frame);

    waitKey(30);
}