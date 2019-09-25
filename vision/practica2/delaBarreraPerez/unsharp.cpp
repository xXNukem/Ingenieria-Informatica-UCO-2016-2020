#include <iostream>
#include <exception>
#include <string>

//Includes para OpenCV, Descomentar según los módulo utilizados.
#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/calib3d/calib3d.hpp>
#include "funciones.hpp"

using namespace std;
using namespace cv;

const cv::String keys =
    "{help h usage ? |      | print this message   }"
    "{@img1  |<none> |imagen entrada}"
    "{@img2 |<none>|imagen salida}"
    "{r            | 1|  tamaño del filtro}"
    "{g |1.0  |ganancia}"
    "{f  |0| flag}"
    
    ;

int main (int argc, char* const* argv)
{
  int retCode=EXIT_SUCCESS;
  
  try {    

      cv::CommandLineParser parser(argc, argv, keys);
      parser.about("Application name v1.0.0");
      if (parser.has("help"))
      {
          parser.printMessage();
          return 0;
      }
      
      cv::String img1 = parser.get<cv::String>(0);
      cv::String img2 = parser.get<cv::String>(1);
      float r = parser.get<float>("r");
      float g = parser.get<float>("g");
      int f =parser.get<int>("f");

      if (!parser.check())
      {
          parser.printErrors();
          return 0;
      }

    /*Ahora toca que tu rellenes con lo que hay que hacer ...*/


      //Comprobamos que los parametros esten introducidos conrrectamente
      if(r>1)
      {
        std::cout<<"Valor de 'r' debe ser menor que 1"<<std::endl;
        exit(1);
      }
      if(g<0.0 || g>10.0)
      {
        std::cout<<"Valor de 'g' debe estar entre 0.0 y 10.0"<<std::endl;
        exit(1);
      }

      //leemos la imagen pasada por argumento como img1
      cv::Mat imagenEntrada=cv::imread(img1, cv::IMREAD_GRAYSCALE); //leemos la imagen siempre en monocromo;

      int min;

        if(imagenEntrada.cols>imagenEntrada.rows)
        {
          min=imagenEntrada.rows;
        }
        else
        {
          min=imagenEntrada.cols;
        }

        int radio=(min/2)*r;


      imagenEntrada.convertTo(imagenEntrada, CV_32FC1,1.0/255.0);
      //La imagen de salida la ponemos todo a 0 para que se queden a 0 las partes sin procesar
      cv::Mat imagenSalida=Mat::zeros(imagenEntrada.rows,imagenEntrada.cols,CV_32FC1);
      //Mostramos por pantalla la imagen de entrada
      cv::Mat boxFilter;
      cv::namedWindow("imagenOriginal");
      cv::imshow("imagenOriginal",imagenEntrada);

      //llamamos a la funcion para crear el box filter
      if(f==0)
      {
        boxFilter=createBoxFilter(radio);
      }
      else if(f==1)
      {
        boxFilter=createGaussianFilter(radio);
      }
      else
      {
        std::cout<<"Parametro F incorreto"<<std::endl;
        exit(1);
      }

      //llamamos a la convolucion
      convolve(imagenEntrada,boxFilter,imagenSalida);
      
        //aplicamos la ganancia con la formula
        imagenSalida=(g+1)*imagenEntrada-g*imagenSalida;
      //imagenSalida.convertTo(imagenSalida, CV_32FC1,255.0);
      cv::namedWindow("imagenProcesada");
      cv::imshow("imagenProcesada",imagenSalida);
      //Convertimos la imagen para que no se guarde todo negro
      imagenSalida.convertTo(imagenSalida, CV_32FC1,255.0);
      imwrite(img2.c_str(), imagenSalida); //guardamos la imagen con el nombr de la cadena img2

	    cv::waitKey(0);
    
  }
  catch (std::exception& e)
  {
    std::cerr << "Capturada excepcion: " << e.what() << std::endl;
    retCode = EXIT_FAILURE;
  }
  return retCode;
}