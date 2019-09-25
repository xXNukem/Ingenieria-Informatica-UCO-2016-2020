#include <iostream>
#include <exception>
#include <string>

//Includes para OpenCV, Descomentar según los módulo utilizados.
#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/videoio/videoio.hpp>
using namespace std;
using namespace cv;

const cv::String keys =
    "{help h usage ? |      | print this message   }"
    "{t  |<none> |umbral deteccion}"
    "{s |<none>|radio de opeaciones morfologicas}"
    "{@entrada  | | input video}"
    "{@salida | |output video}"
    ;

int main(int argc, char* const* argv)
{
	int retCode = EXIT_SUCCESS;

	try {

		cv::CommandLineParser parser(argc, argv, keys);
		parser.about("Application name v1.0.0");
		if (parser.has("help"))
		{
			parser.printMessage();
			return 0;
		}

		int umbral = parser.get<int>("t");
		int radioMorf = parser.get<int>("s");
		String video = parser.get<String>(0);
		String videoSalida = parser.get<String>(1);

		if (!parser.check())
		{
			parser.printErrors();
			return 0;
		}

		/*Programa principal ...*/

		if (umbral < 0 || radioMorf < 0)
		{
			cout << "Los parametros t y s tienen que ser mayores que 0" << endl;
			exit(-1);
		}

		VideoCapture videoEntrada;
		videoEntrada.open(video);

		if (!videoEntrada.isOpened())
		{
			cout << "No se puede abrir el video" << endl;
			exit(-1);
		}

		Mat frame, preFrame, frameDif, elementoEstructural, umbralizado, final,
		    Canales;

		int cont = 0;

		videoEntrada >> preFrame; //Guardamos frame previo
		VideoWriter videoS(videoSalida, CV_FOURCC('M', 'J', 'P', 'G'), 10, Size(preFrame.size().width,
		                   preFrame.size().height)); //Inicializacion para guardar el video

		while (true)
		{
			videoEntrada >> frame;//Guardamos cada frame del video

			if (frame.empty()) //Salimos del bucle en cuanto el video acabe
			{
				break;
			}
			Mat opening, closing;
			//Bara de deslizacion
			createTrackbar("UMBRAL", "VIDEO", &umbral, 255);


			//Frame-PreFrame=frameDif
			absdiff(frame, preFrame, frameDif);
			umbralizado = frameDif > umbral;//Obtencion de la mascara umbralizada

			Mat canalesRGB[3];
			split(umbralizado, canalesRGB);
			Canales = canalesRGB[0] | canalesRGB[1] | canalesRGB[2];



			//Transformaciones morfologicas
			elementoEstructural = getStructuringElement(MORPH_ELLIPSE, Size(radioMorf * 2 + 1,
			                      radioMorf * 2 + 1),
			                      Point(radioMorf,
			                            radioMorf));
			morphologyEx(Canales, opening, MORPH_OPEN, elementoEstructural);
			morphologyEx(opening, closing, MORPH_CLOSE, elementoEstructural);
			Mat morfologia, transformada;
			morfologia = closing;

			cvtColor(morfologia, transformada, CV_GRAY2RGB);//Devolvemos las imagenes a color
			final = frame & transformada;//resultado final

			imshow("VIDEO", frame);//Video original

			preFrame = frame.clone();
			videoS.write(transformada);//Guardamos el video con todas las transformaciones

			imshow("DETECCION", final);//Video con movimiento capturado
			//waitKey(30);//Salimos del bucle al pulsar una tecla

			char key = (char) waitKey(30);

			if (key == 27)
			{
				break;
			}
			else if (key == 32)
			{
				string save = "img" + to_string(cont) + ".png";
				imwrite(save, morfologia);
			}
			cont++;

		}
		videoEntrada.release();
		videoS.release(); //fin del guardado del video
	}
	catch (std::exception& e)
	{
		std::cerr << "Capturada excepcion: " << e.what() << std::endl;
		retCode = EXIT_FAILURE;
	}
	return retCode;
}
