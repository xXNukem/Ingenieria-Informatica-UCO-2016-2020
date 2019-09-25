#include <opencv2/core/core.hpp>
#include <cassert>
#include <vector>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "FFT.hpp"
#include <iostream>
#include <cmath>
using namespace std;
using namespace cv;

namespace FSIV
{

	FFT::FFT(const Mat &picture, const ESPACIO_COLOR &espacio)
	{
		this->setPicture(picture);
		this->setEspacioColor(espacio);
	}

	FFT::FFT(const FFT &f)
	{
		Mat tmp = f.getPicture();
		enum ESPACIO_COLOR espacio;
		
		espacio = f.getEspacioColor();
		this->setPicture(tmp);
		this->setFFT(f.getFFT());
		this->setEspacioColor(espacio);
	}

	void FFT::setPicture(const Mat &picture)
	{
		_picture = picture.clone();
	}

	void FFT::doFFT()
	{
		assert(!_picture.empty());
		Mat picture = this->getPicture();
		Mat fft;
		
		if(picture.channels() == 1)
		{
			picture.convertTo(fft, CV_32F);
		}
		else
		{
			Mat iluminacion;
			vector<Mat> canalesIluminacion;
			enum ESPACIO_COLOR espacio;
			unsigned int canalLuz;
			
			espacio = this->getEspacioColor();
			this->convertirEspacioColor(picture, espacio);

			split(picture, canalesIluminacion);
			canalLuz = this->getIluminacion(espacio);
			iluminacion = canalesIluminacion[canalLuz].clone();
			iluminacion.convertTo(fft, CV_32F);
		}
		dft(fft, fft, cv::DFT_COMPLEX_OUTPUT);
		
		this->setFFT(fft);
	}

	void FFT::inverseFFT()
	{
		assert(!_fft.empty());
		
		Mat fft = this->getFFT();
		
		dft(fft, fft, cv::DFT_INVERSE|cv::DFT_REAL_OUTPUT|DFT_SCALE);
		fft.convertTo(fft, CV_8U);

		if(_picture.channels() != 1)
		{
			Mat imagen = this->getPicture();
			enum ESPACIO_COLOR espacio = this->getEspacioColor();
			unsigned int canalLuz = this->getIluminacion(espacio);
			vector<Mat> canales;
			
			this->convertirEspacioColor(imagen, espacio);
			split(imagen, canales);
			
			canales[canalLuz] = fft.clone();
			merge(canales, imagen);
			this->convertirEspacioColor(imagen, RGB);
			fft = imagen.clone();
		}
		this->setPicture(fft);
	}

	void FFT::show() const
	{
		assert(!_fft.empty());
		
		Mat fft = this->getFFT();
		
		int cx = fft.cols/2;
		int cy = fft.rows/2;

		Mat q0(fft, Rect(0, 0, cx, cy));   // Top-Left
		Mat q1(fft, Rect(cx, 0, cx, cy));  // Top-Right
		Mat q2(fft, Rect(0, cy, cx, cy));  // Bottom-Left
		Mat q3(fft, Rect(cx, cy, cx, cy)); // Bottom-Right

		Mat tmp; 
		q0.copyTo(tmp);
		q3.copyTo(q0);
		tmp.copyTo(q3);

		q1.copyTo(tmp);
		q2.copyTo(q1);
		tmp.copyTo(q2);
		
		vector<Mat> planes;
		
		split(fft, planes);
		
		magnitude(planes[0], planes[1], planes[0]);
		planes[0] += Scalar::all(1);
		log(planes[0], planes[0]);
		normalize(planes[0], planes[0], 0, 1, CV_MINMAX);
		fft.convertTo(fft, CV_8U);
		
		imshow("Espectro", planes[0]);
	}

	Mat FFT::getFFT() const
	{
		return _fft.clone();
	}

	Mat FFT::getPicture() const
	{
		return _picture.clone();
	}

	void FFT::setFFT(const Mat &fft)
	{
		_fft = fft.clone();
	}

	void FFT::setFrequency(const unsigned int &fil, const unsigned int &col, const enum COMPLEX_NUMBER &part, const float &frequency)
	{
		assert(fil < this->getRows());
		assert(col < this->getCols());
		
		if(part == REAL)
		{
			_fft.at<float>(fil, col, 0) = frequency;
		}
		else
		{
			vector<Mat> canales;
			split(_fft, canales);
			
			canales[1].at<float>(fil, col) = frequency;
			
			merge(canales, _fft);
		}
	}

	float FFT::getFrequency(const unsigned int &fil, const unsigned int &col, const enum COMPLEX_NUMBER &part) const
	{
		assert(fil < this->getRows());
		assert(col < this->getCols());
		
		if(part == REAL)
		{
			return _fft.at<float>(fil, col);
		}
		else
		{
			Mat fft = this->getFFT();
			vector<Mat> canales;
			
			split(fft, canales);
			assert(canales.size() == 2);
			
			return canales[1].at<float>(fil, col);
		}
	}

	unsigned int FFT::getRows() const
	{
		return static_cast<unsigned int>(_fft.rows);
	}

	unsigned int FFT::getCols() const
	{
		return static_cast<unsigned int>(_fft.cols);
	}

	void FFT::release()
	{
		_fft.release();
		_picture.release();
	}

	FFT& FFT::operator=(const FFT & f)
	{
		this->setPicture(f.getPicture());
		this->setFFT(f.getFFT());
		return *this;
	}

	bool FFT::operator==(const FFT & f)
	{
		bool resultado;
		Mat fftA = this->getFFT();
		Mat fftB = f.getFFT();
		
		resultado = true;
		
		if((this->getRows() != f.getRows()) || (this->getCols() != f.getCols()))
		{
			resultado = false;
		}
		else
		{
			for(unsigned int i = 0; i < this->getRows(); i++)
			{
				for(unsigned int j = 0; j < this->getCols(); j++)
				{
					float complexA;
					float complexB;
					float realA;
					float realB;
				
					complexA = this->getFrequency(i, j, COMPLEX);
					complexB = f.getFrequency(i, j, COMPLEX);
					realA = this->getFrequency(i, j, REAL);
					realB = f.getFrequency(i, j, REAL);
					
					if((complexA != complexB) || (realA != realB))
					{
						resultado = false;
						break;
					}
				}
			}
		}
		return resultado;
	}

	bool FFT::operator!=(const FFT & f)
	{
		return !(*this == f);
	}

	unsigned int FFT::getIluminacion(const enum ESPACIO_COLOR &espacio) const
	{
		if((espacio == HSV) || (espacio == HLS))
		{
			return 2;
		}
		else if(espacio == CIE)
		{
			return 1;
		}
		else if(espacio == YCrCb)
		{
			return 0;
		}
		else
		{
			cerr << "Error al tratar de sacar la iluminacion: Espacio de color irreconocible" << endl;
			exit(0);
		}
	}

	void FFT::convertirEspacioColor(Mat &picture, const enum ESPACIO_COLOR &espacio)
	{
		if(espacio == RGB) //Restauracion
		{
			if(this->getEspacioColor() == HSV)
			{
				cvtColor(picture, picture, CV_HSV2BGR);
			}
			else if(this->getEspacioColor() == CIE)
			{
				cvtColor(picture, picture, CV_XYZ2BGR);
			}
			else if(this->getEspacioColor() == YCrCb)
			{
				cvtColor(picture, picture, CV_YCrCb2BGR);
			}
			else if(this->getEspacioColor() == HLS)
			{
				cvtColor(picture, picture, CV_HLS2BGR);
			}
			else
			{
				cerr << "Error al restaurar el espacio de color de la imagen ? to BGR" << endl;
			}
		}
		else if(espacio == HSV)
		{
			cvtColor(picture, picture, CV_BGR2HSV);
		}
		else if(espacio == CIE)
		{
			cvtColor(picture, picture, CV_BGR2XYZ);
		}
		else if(espacio == YCrCb)
		{
			cvtColor(picture, picture, CV_BGR2YCrCb);
		}
		else if(espacio == HLS)
		{
			cvtColor(picture, picture, CV_BGR2HLS);
		}
		else
		{
			cerr << "Error al convertir el espacio de color BGR to ?" << endl;
			exit(0);
		}
	}

	void FFT::setEspacioColor(const enum ESPACIO_COLOR &espacio)
	{
		assert(espacio != RGB);
		_espacio = espacio;
	}

	enum ESPACIO_COLOR FFT::getEspacioColor() const
	{
		return _espacio;
	}

	void FFT::butterworth(const double &cutOfFrequency, const unsigned int &orden)
	{
		assert(!_fft.empty());
		assert((cutOfFrequency >= 0) && (cutOfFrequency <= 1));
		
		for(unsigned int i = 0; i < this->getRows(); i++)
		{
			for(unsigned int j = 0; i < this->getCols(); j++)
			{
				float real;
				float compleja;
				
				real = this->getFrequency(i, j, REAL);
				compleja = this->getFrequency(i, j, COMPLEX);
				
				real /= cutOfFrequency;
				compleja /= cutOfFrequency;
				
				real = pow(real, 2*orden);
				compleja = pow(compleja, 2*orden);
				
				this->setFrequency(i, j, REAL, real);
				this->setFrequency(i, j, COMPLEX, compleja);
			}
		}
	}
}