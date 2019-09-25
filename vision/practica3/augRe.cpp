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
  "{cols  |<none> |columnas}"
  "{rows |<none>|filas}"
  "{size  | <none>|  tamaño}"
  "{f |1| 1 para coordenadas,2 para imagen}"
  "{@intrinsics |<none>  |parametros intrinsecos}"
  "{@video  |<none>| input video}"
  "{@imagen  | | input imagen}"
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

    int cols = parser.get<int>("cols");
    int rows = parser.get<int>("rows");
    int size = parser.get<int>("size");
    int flag = parser.get<int>("f");
    String intrinsics = parser.get<String>(0);
    String video = parser.get<String>(1);
    String imagen = parser.get<string>(2);

    if (!parser.check())
    {
      parser.printErrors();
      return 0;
    }

    /*Programa principal ...*/

    VideoCapture videoEntrada;
    videoEntrada.open(video);

    if (!videoEntrada.isOpened())
    {
      cout << "No se puede abrir el video" << endl;
      exit(-1);
    }
    Mat frame, img_grey, tvec, rvec;
    bool find, encontrado;
    Size patternsize(cols, rows);
    vector<Point2f> esquinas;
    vector<Point3f> puntos;
    vector<Point3f> sentido_lineas;
    vector<Point2f> inputQuad(4), outputQuad(4);
    Mat img = imread(imagen);
    Mat lambda(3, 3, CV_32FC1);
    lambda = Mat::zeros(img.rows, img.cols,
                        img.type());//inicilaizamos lamba a la imagen que queremos proyectar

    //Lectura de la calibracion de la camara
    Mat cameraMatrix, distCoeffs;
    string filename = intrinsics;
    FileStorage fs(filename, FileStorage::READ);
    fs["camera_matrix"] >> cameraMatrix;
    fs["distortion_coefficients"] >> distCoeffs;
    fs.release();

    //sacamiento del sistema de referencias de la camara
    vector<Point3f> obj;
    for (int i = 0; i < rows; i++)
    {

      for (int j = 0; j < cols; j++)
      {
        obj.push_back(Point3d(j * size, i * size, 0.0f));
      }

    }


    while (true)
    {
      videoEntrada >> frame;//Guardamos cada frame del video

      if (frame.empty())
      {
        break;
      }

      //comprobamos si hemos encontrado el tablero
      bool found = findChessboardCorners(frame, patternsize, esquinas,
                                         CV_CALIB_CB_ADAPTIVE_THRESH + CV_CALIB_CB_FILTER_QUADS);

      if (found)
      {

        cvtColor(frame, img_grey, CV_BGR2GRAY); //Pasamos los frames a blanco y negro
        cornerSubPix(img_grey, esquinas, Size(11, 11), Size(-1, -1),
                     TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));//guardamos en el vector de esquinas
        //drawChessboardCorners(frame, patternsize, esquinas, found);//Dibuja las lineas

        //1ºSistema de referencias, 2ºVector de esquinas,3ºy4º parametros intrinsecos, 5º vector de rotacion, 6ºvector de translacion
        solvePnP(obj, esquinas, cameraMatrix, distCoeffs, rvec, tvec);

        if (flag == 1)
        {
          //Ejes de coordenadas que se van a dibujar;
          sentido_lineas.push_back(Point3f(0, 0, 0));
          sentido_lineas.push_back(Point3f(size, 0, 0));
          sentido_lineas.push_back(Point3f(0, size, 0));
          sentido_lineas.push_back(Point3f(0, 0, -size));

          //1ºSentido de las lineas,2ºMatriz de rotacion, 3ºMatriz de traslacion, 4º y 5º Parametros intrinsecos,6ºVector de esquinas
          projectPoints(sentido_lineas, rvec, tvec, cameraMatrix, distCoeffs, esquinas);

          //dibujamiento de las lineas
          line(frame, esquinas[0], esquinas[1], CV_RGB(255, 0, 0), 2, 8, 0);
          line(frame, esquinas[0], esquinas[2], CV_RGB(0, 255, 0), 2, 8, 0);
          line(frame, esquinas[0], esquinas[3], CV_RGB(0, 0, 255), 2, 8, 0);
        }
        if (flag == 2)
        {
          if (img.rows > 0)
          {
            //Cogemos las esquinas de la imagen que queremos proyectar para tener puntos de referencia
            inputQuad[0] = Point2f(0, 0);
            inputQuad[1] = Point2f(img.cols - 1, 0);
            inputQuad[2] = Point2f(0, img.rows - 1);
            inputQuad[3] = Point2f(img.cols - 1, img.rows - 1);

            //Esquinas del tablero

            outputQuad[0] = esquinas[0];
            outputQuad[1] = esquinas[cols - 1];
            outputQuad[2] = esquinas[(cols * rows) - cols];
            outputQuad[3] = esquinas[(cols * rows) - 1];

            //Obtenemos la perspectiva entre las dos imagenes, la capturada y la que queremos proyectar
            lambda = getPerspectiveTransform(inputQuad, outputQuad);
            //Dibuja la imagen en la captura
            warpPerspective(img, frame, lambda, frame.size(), INTER_LINEAR, BORDER_TRANSPARENT, 0);
          }
        }


      }
      imshow("VIDEO", frame);
      waitKey(1);

    }


  }
  catch (std::exception& e)
  {
    std::cerr << "Capturada excepcion: " << e.what() << std::endl;
    retCode = EXIT_FAILURE;
  }
  return retCode;
}