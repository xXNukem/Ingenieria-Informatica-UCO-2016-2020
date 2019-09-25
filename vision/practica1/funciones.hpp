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

vector<float> acumular_histograma(const cv::Mat& img, int tam, const cv::Mat& mask, bool existeMask);
vector<float> normalizar_histograma(vector<float> h_prima, int tam);

vector<float> calculate_histogram(const cv::Mat& img, int bins=256, const cv::Mat& mask=cv::Mat(), bool normalized=false, bool accumulated=false);
Mat ecualizar_histograma(std::vector<float> const & h_prima, const cv::Mat& img,int r, const cv::Mat& mask=cv::Mat());

#endif