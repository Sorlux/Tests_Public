#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main(int argc, char** argv )
{

    cv::Mat image; 
    image = cv::imread("C:/Users/ldomi/OneDrive/Pictures/car.jpg", cv::IMREAD_COLOR);
    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }

    cv::Mat erode, dilate, elementKernel;


    cv::erode(image,erode, elementKernel, cv::Point(-1,-1),1);
    cv::dilate(erode,dilate,elementKernel,cv::Point(-1,-1),1);
    cv::imshow("Image", image);
    cv::imshow("Erode",erode);
    cv::imshow("Dilate", dilate);

    cv::waitKey(0); //Waits for the user to press a key
    return 0;
}
