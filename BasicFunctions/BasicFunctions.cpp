#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

Mat grayscale(Mat img) {
    Mat gray_img;
    cvtColor(img, gray_img, COLOR_BGR2GRAY);
    return gray_img;
}

int main() {

	string path = "Resources/cards.jpg";
	Mat img = imread(path);
    Mat gray_img;
    gray_img = grayscale(img);
    

    // Create a window
    namedWindow("Config", 1);
    int desiredWidth = 640;
    int desiredheight = 480;

    resizeWindow("Config", desiredWidth, desiredheight);
    

    //median
    int iSliderValue1 = 0;
    createTrackbar("Median Blur", "Config", &iSliderValue1, 100);

    //Create trackbar to change blur
    int iSliderValue2 = 0;
    
    createTrackbar("Guassian Blur", "Config", &iSliderValue2, 100);

    //create trackbar for canny filter
    int iSliderValue3 =0;
    createTrackbar("Low thresh", "Config", &iSliderValue3, 255);

    int iSliderValue4 = 0;
    createTrackbar("High thresh", "Config", &iSliderValue4, 255);

    int iSliderValue5 = 0;
    createTrackbar("Dilate", "Config", &iSliderValue5, 1);

    int iSliderValue6 = 0;
    createTrackbar("Erode", "Config", &iSliderValue6, 1);

    int iSliderValue7 = 0;
    createTrackbar("Kernel", "Config", &iSliderValue7, 100);

    int iSliderValue8 = 0;
    createTrackbar("Fill", "Config", &iSliderValue8, 1);

    

    while (true) 
    {
        
        Mat res_img = gray_img.clone();
        //make sure guas kernel always odd
        if (iSliderValue2 % 2 == 0) {
            iSliderValue2 = iSliderValue2 + 1;
        }
        if (iSliderValue1 % 2 == 0) {
            iSliderValue1 = iSliderValue1 + 1;
        }
        if (iSliderValue7 % 2 == 0) {
            iSliderValue7 = iSliderValue7 + 1;
        }

        //create vector to hold the values
        vector<int> configs = { iSliderValue1,//0
                                iSliderValue2,//1
                                iSliderValue3,//2
                                iSliderValue4,//3
                                iSliderValue5,//4
                                iSliderValue6,//5
                                iSliderValue7,//6
                                iSliderValue8 //7
                                };
        for (int i : configs) {
            cout << i << ' ';
        }
        cout << endl;

        GaussianBlur(res_img, res_img, Size(configs[1], configs[1]), 0, 0);
        medianBlur(res_img, res_img, configs[0]);
        Canny(res_img, res_img, configs[2], configs[3]);

        Mat kernel = getStructuringElement(MORPH_RECT, Size(configs[6], configs[6]));
        if (configs[4] == 1) {
            dilate(res_img, res_img, kernel);
        }
        if (configs[5] == 1) {
            erode(res_img, res_img, kernel);
        }
        if (configs[7] == 1) {

            floodFill(res_img, cv::Point(0, 0), Scalar(255));
            //Mat floodfill_inv;
            //bitwise_not(res_img, floodfill_inv);
            //res_img = floodfill_inv;


        }
        
        imshow("Result", res_img);
 
        // Wait until user press some key for 50ms
        int iKey = waitKey(50);

        //if user press 'ESC' key
        if (iKey == 27)
        {
            break;
        }
    }

    return 0;
}