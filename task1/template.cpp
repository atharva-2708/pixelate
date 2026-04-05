#include <iostream>
#include <opencv2/opencv.hpp>
#include "convolution.hpp"  

using namespace std;
using namespace cv;

int main()
{
    // The two kernels — do not change these
    cv::Mat K1 = (cv::Mat_<double>(3, 3) <<
         1,  2,  1,
         0,  0,  0,
        -1, -2, -1
    );

    cv::Mat K2 = (cv::Mat_<double>(3, 3) <<
         1,  0, -1,
         2,  0, -2,
         1,  0, -1
    ); 

      
    
    // Convolve with original 'full' kernel
    std::string input_path = "./assets/hogwarts.png";
    cv::Mat input = cv::imread(input_path, cv::IMREAD_COLOR); 
     cv::Mat output;

     auto start = std::chrono::high_resolution_clock::now();
    filter2D(input, output, -1, K1);              // Convolve with original 'full' kernel
    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Regular convolution took " << duration.count() << " microseconds.\n";

    // Making All Windows resizable
    cv::namedWindow("Output", cv::WINDOW_NORMAL); 

    cv::Mat gaussian_v = (Mat_<double>(3, 1) << 1.0,  0.0,  -1.0);
    cv::Mat gaussian_h = (Mat_<double>(1, 3) <<  1.0,  2.0,  1.0);

    // Making All Windows resizable
    cv::namedWindow("Output", cv::WINDOW_NORMAL); //ithe output print kela first
    cv::imshow("Output", output);

    cv::waitKey(0); // Wait for key press before moving to the next image


    // Declare matrix to store intermediate image
    cv::Mat intermediate;

    // Now to actually convolve
    intermediate = convolve(input, gaussian_v);         // Convolve Vertically
    output = convolve(intermediate, gaussian_h);        // Convolve Horizontally

    ///////////////////////////


   
    cv::namedWindow("Output of Horizontal Convolution", cv::WINDOW_NORMAL);
    cv::imshow("Output of Horizontal Convolution", output);
    cv::waitKey(0);
    

    
    cv::Mat img = cv::imread("./assets/hogwarts.png", cv::IMREAD_GRAYSCALE);
    if (img.empty()) {
        cerr << "Could not load image at ./assets/hogwarts.png\n";
        return -1;
    }

    cv::Mat img_f;
    img.convertTo(img_f, CV_64FC1);

    

    // TODO: apply K1 and K2 to img_f with as few multiplications per pixel as possible.
    // Print the number of multiplications your approach uses per pixel.

    return 0;
}
