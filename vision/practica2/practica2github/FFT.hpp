#ifndef __FFT_HPP__FSIV
#define __FFT_HPP__FSIV

#include <opencv2/core/core.hpp>

using namespace cv;

enum COMPLEX_NUMBER { COMPLEX, REAL };
enum ESPACIO_COLOR { HSV, RGB, CIE, YCrCb, HLS };

namespace FSIV
{

	class FFT
	{
	public:
		/** 
		* @brief Default constructor
		* @param picture Picture to be transformed
		* **/
		FFT(const Mat &picture = cv::Mat(), const ESPACIO_COLOR &espacio = HSV);
		
		/** @brief Copy Constructor
		*  @param f FFT to be copied
		* **/
		FFT(const FFT &f);
		/**
		* @brief Set up a picture to be transformed
		* @param picture Picture to be transformed
		* **/
		void setPicture(const Mat &picture = cv::Mat());
		
		/**
		* @brief Do transformation
		* **/
		void doFFT();
		
		/**
		* @brief Do inverse FFT
		* **/
		void inverseFFT();
		
		/**
		* @brief Show picture's fft
		* **/
		void show() const;
		
		/**
		* @brief Return fft's copy
		* **/
		Mat getFFT() const;
		
		/**
		* @brief Return picture
		* **/
		Mat getPicture() const;
		
		/**
		* @brief Set a FFT picture **/
		void setFFT(const Mat &fft = cv::Mat());
		
		/**
		* @brief Set a frequency pixel
		* **/
		void setFrequency(const unsigned int &fil, const unsigned int &col, const enum COMPLEX_NUMBER &part, const float &frequency);
		
		/**
		* @brief Get a frequency pixel
		* **/
		float getFrequency(const unsigned int &fil, const unsigned int &col, const enum COMPLEX_NUMBER &part) const;
		
		/**
		* @brief Return fft's rows
		* **/
		unsigned int getRows() const;
		
		/**
		* @brief Return fft's cols
		* **/
		unsigned int getCols() const;
		
		/** @brief Establece el espacio de color de la clase
		* **/
		void setEspacioColor(const enum ESPACIO_COLOR &espacio);
		
		/** @brief Obtiene el espacio de color de la clase **/
		enum ESPACIO_COLOR getEspacioColor() const;
		
		/**
		* @brief Libera la imagen y la transformada de fourier **/
		void release();
		
		/** @brief Aplica el filtro butterworth sobre el espectro (cambia el espectro) **/
		void butterworth(const double &cutOfFrequency, const unsigned int &orden);
		
		/** Sobrecarga del constructor = **/
		FFT& operator=(const FFT & f);

		bool operator==(const FFT & f);
		
		bool operator!=(const FFT & f);
		
	private:
		Mat _picture;
		Mat _fft;
		enum ESPACIO_COLOR _espacio;
		
		void convertirEspacioColor(Mat &picture, const enum ESPACIO_COLOR &espacio);
		unsigned int getIluminacion(const enum ESPACIO_COLOR &espacio) const;
	};
}
#endif
