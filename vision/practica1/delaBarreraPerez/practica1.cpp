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
    "{@mask  |<none |mascara}"
    "{r            | 0|  introducir radio}"
    
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
      cv::String mask = parser.get<cv::String>(2);
      int R = parser.get<int>("r");

      if (!parser.check())
      {
          parser.printErrors();
          return 0;
      }

    /*Ahora toca que tu rellenes con lo que hay que hacer ...*/

      std::vector<float> h_prima(255,0); //vector donde esta el histograma procesado
      cv::Mat imagen; //imagen de entrada
      cv::Mat imagenEcualizada; //imagen ecualizada
      cv::Mat mascara;
      mascara= cv::imread(mask, cv::IMREAD_GRAYSCALE);


	    // leer la imagen
	    imagen = cv::imread(img1, cv::IMREAD_GRAYSCALE);//la imagen se pasa a tonos de gris
      imagenEcualizada= imagen.clone();

        if(imagen.rows==0)
        {
          std::cout<<"Introduce una imagen valida con formato png como primer argumento "<<std::endl;
          exit(1);
        }
	    // mostrar la imagen original
	    cv::namedWindow("imagenOriginal");
	    cv::imshow("imagenOriginal",imagen);


	       //obtenemos el histograma y lo devolvemos acumulado y normalizado
        h_prima=calculate_histogram(imagen,256,mascara,true,true);

        //llamamos a la funcion para ecualizar histograma y devolvemos la imagen 
        imagenEcualizada=ecualizar_histograma(h_prima, imagen,R,mascara);

        //Mostramos la imagen ecualizada y la guardamos con el nombre del segundo argumento
        cv::namedWindow("imagenEcualizada");
        cv::imshow("imagenEcualizada",imagenEcualizada);
        imwrite(img2.c_str(), imagenEcualizada); //guardamos la imagen con el nombr de la cadena img2

	    cv::waitKey(0);
    
  }
  catch (std::exception& e)
  {
    std::cerr << "Capturada excepcion: " << e.what() << std::endl;
    retCode = EXIT_FAILURE;
  }
  return retCode;
}
