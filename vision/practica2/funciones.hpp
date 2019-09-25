#ifndef FUNCIONES_HPP_
#define FUNCIONES_HPP_

#include <iostream>
#include <exception>
#include <string>

//Includes para OpenCV, Descomentar según los módulo utilizados.
#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/calib3d/calib3d.hpp>

using namespace std;
using namespace cv;

cv::Mat createBoxFilter(int r);
void convolve(const cv::Mat& in, const cv::Mat& filter, cv::Mat& out);
cv::Mat createGaussianFilter(int r);

#endif