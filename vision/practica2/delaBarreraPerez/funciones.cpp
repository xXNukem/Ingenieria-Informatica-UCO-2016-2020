#include "funciones.hpp"

cv::Mat createBoxFilter(int r)
{
	//Tamaño del filtro: T=2r+1
	cv::Mat boxFilter;
	float valor=(float)1/((2*r+1)*(2*r+1));
		boxFilter=Mat(2*r+1,2*r+1,CV_32FC1,cv::Scalar(valor));

	return boxFilter;
}

cv::Mat createGaussianFilter(int r)
{

    cv::Mat gaussianFilter((2*r+1),(2*r+1),CV_32FC1,Scalar(0)); //matriz del tamaño calculado con la formula de la practica
    double sigma = 1.0; //çel parametro Sigma la ponemos a 1
    double s = 2.0 * sigma * sigma;

    double XY;
    double sum = 0.0;


    //Obtenemos la matriz del filtro
    for (int x = -r; x <= r; x++)
    {
        for(int y = -r; y <= r; y++)
        {
            XY = (x*x) + (y*y);
            gaussianFilter.at<float>(x+r,y+r) = (exp(-(XY*XY)/s))/(M_PI * s);//Aplicamos la formula del filtro gausiano para meter los datos en la matriz del filtro
            sum += gaussianFilter.at<float>(x+r,y+r);//Vamos acumulando todo para luego hacer una normalizacion
        }
    }

    // normalizar the Kernel dividiendo entre el valor acumulado mientras se crea el filtro
    for(int i = 0; i < 2*r+1; ++i)
    {
        for(int j = 0; j < 2*r+1; ++j)
        {
            gaussianFilter.at<float>(i,j) /= sum;
        }
    }

    return gaussianFilter;
}

void convolve(const cv::Mat& in, const cv::Mat& filter, cv::Mat& out)
{

     int mm, jj, ii,nn;
     float pixel;
     int a=0,b=0;
     int radio=((filter.rows-1)/2);
    for (int i = 0; i < in.rows-filter.rows; ++i) // Filas
    {
        for (int j = 0; j < in.cols-filter.cols; ++j) // Columnas
        {

            // Variable acumuladora
            pixel=0;
            
            for (int m = i; m < i+filter.rows; ++m) // Filas del filter
            {
               
                for (int n = j; n<j+ filter.cols; ++n) // Columnas del filter
                {

                	pixel+=in.at<float>(m,n)*filter.at<float>(a,b);
                	b++;

                                           
                }

                a++;
               b=0;
            }
            a=b=0;
            out.at<float>(i+radio,j+radio)   = pixel;
        }
	}

}	

