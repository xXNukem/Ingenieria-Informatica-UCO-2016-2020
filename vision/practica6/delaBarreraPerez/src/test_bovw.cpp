/*!
  Esto es un esqueleto de programa para usar en las prácticas
  de Visión Artificial.

  Se supone que se utilizará OpenCV.

  Para compilar, puedes ejecutar:
    g++ -Wall -o esqueleto esqueleto.cc `pkg-config opencv --cflags --libs`

*/

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <tclap/CmdLine.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/ml/ml.hpp>
#include "common_code.hpp"
#define IMG_WIDTH 300
//#include <opencv2/calib3d/calib3d.hpp>
using namespace cv;
using namespace std;

int main(int argc, char* const* argv)
{

	TCLAP::CmdLine cmd("Train and test a BoVW model", ' ', "0.0");

	TCLAP::ValueArg<string> imgInput("", "img", "imagen de entrada", false, "", "pathname");
	cmd.add(imgInput);

	TCLAP::ValueArg<string> videoInput("", "video", "video de entrada", false, "", "pathname");
	cmd.add(videoInput);

	TCLAP::ValueArg<string> classifier("", "classifier", "clasificador", false, "classifier.yml",
	                                   "pathname");
	cmd.add(classifier);

	TCLAP::ValueArg<string> dict("", "dict", "diccionario", false, "dictionary.yml", "pathname");
	cmd.add(dict);

	TCLAP::ValueArg<string> configFile("", "config_file", "fichero de configuracion", false,
	                                   "../data/02_ObjectCategories_conf.txt", "pathname");
	cmd.add(configFile);

	cmd.parse(argc, argv);

	int modo;

	Mat img;
	VideoCapture videoEntrada;
	if (videoInput.getValue() == "" && imgInput.getValue() != "") //Es una imagen
	{
		img = cv::imread(imgInput.getValue(), cv::IMREAD_GRAYSCALE);
		modo = 1;
	}
	else if (videoInput.getValue() != "" && imgInput.getValue() == "") //Es un video
	{
		videoEntrada.open(videoInput.getValue());
		if (!videoEntrada.isOpened())
		{
			cout << "No se puede abrir el video" << endl;
			exit(-1);
		}
		modo = 2;
	}

	std::vector<std::string> categories;
	std::vector<int> samples_per_cat;

	//Cargar el fichero de configuracion
	int retCode;
	if ((retCode = load_dataset_information(configFile.getValue(), categories, samples_per_cat)) != 0)
	{
		std::cerr << "Error: could not load dataset information from '"
		          << configFile.getValue()
		          << "' (" << retCode << ")." << std::endl;
		exit(-1);
	}

	std::cout << "Found " << categories.size() << " categories: ";
	if (categories.size() < 2)
	{
		std::cerr << "Error: at least two categories are needed." << std::endl;
		return -1;
	}

	for (size_t i = 0; i < categories.size(); ++i)
		std::cout << categories[i] << ' ';
	std::cout << std::endl;

	//--------------------------------

	//Leer el diccionario y el clasificador
	FileStorage dictFile;
	FileStorage classFile;
	int keywords, ndesc, descriptor, classi, kmeans;
	//Dictionary
	cv::Ptr<cv::ml::KNearest> dictionary_ptr = cv::ml::KNearest::create();
	//Classifier
	cv::Ptr<cv::ml::StatModel> classifier_ptr;

	//Load the dictionary model
	dictFile.open(dict.getValue(), cv::FileStorage::READ);
	dictionary_ptr->read(dictFile.root());

	//Load the type of descriptor used, the ndesc value, and number of keywords
	descriptor = dictFile["descriptor"];
	ndesc = dictFile["ndesc"];
	keywords = dictFile["keywords"];
	classi = dictFile["classifier"];
	kmeans = dictFile["kmeans"];
	dictFile.release();

	if (classi == 1)
	{
		cv::Ptr<cv::ml::KNearest> knn = cv::ml::KNearest::create();
		//Load the classifier model
		knn = cv::Algorithm::load<cv::ml::KNearest> (classifier.getValue());
		classifier_ptr = knn;
		if (classifier_ptr.empty())
		{
			std::cout << "Error: the classifier could not be loaded" << std::endl;
			exit(-1);
		}
	}
	else if (classi == 2)
	{
		cv::Ptr<cv::ml::SVM> SVMClassifier = cv::ml::SVM::create();
		SVMClassifier = cv::Algorithm::load<cv::ml::SVM> (classifier.getValue());
		classifier_ptr = SVMClassifier;
		if (classifier_ptr.empty())
		{
			std::cout << "Error: the classifier could not be loaded" << std::endl;
			exit(-1);
		}
	}

	Mat test_bovw;
	//-------------------

	int sift_type = 0;

	std::vector<int> siftScales{ 9, 13 }; // 5 , 9


	if (modo == 1)//Modo prediccion de foto
	{
		Mat train_descs;
		if (img.empty())
		{
			std::cerr << "Error: could not read image '" << imgInput.getValue() << "'." << std::endl;
			exit(-1);
		}
		else
		{
			// Fix size
			resize(img, img, cv::Size(IMG_WIDTH, round(IMG_WIDTH * img.rows / img.cols)));

			cv::Mat descs;
			if (descriptor == 1)
			{
				descs = extractSIFTDDENSEescriptors(img, ndesc, siftScales);
			}
			else if (descriptor == 2)
			{
				descs = extractSURFDescriptors(img, ndesc);
			}
			else if (descriptor == 3)
			{
				descs = extractSIFTescriptors(img, ndesc);
			}
			else
			{
				exit(-1);
			}
			cv::Mat bovw = compute_bovw(dictionary_ptr, keywords, descs, kmeans);

			if (train_descs.empty())
				train_descs = bovw;
			else
			{
				cv::Mat dst;
				cv::vconcat(train_descs, bovw, dst);
				train_descs = dst;
			}
		}

		std::clog << "\tClassifying test images." << std::endl;
		cv::Mat predicted_labels;

		//Consigue la categoria y la guarda en predicted labels
		classifier_ptr->predict(train_descs, predicted_labels);

		CV_Assert(predicted_labels.depth() == CV_32F);
		CV_Assert(predicted_labels.rows == train_descs.rows);

		cout << "La foto es: ";
		cout << categories[ int (cv::sum(predicted_labels) [0])] << " " << endl;
	}
	if (modo == 2) //modo prediccion de video
	{
		Mat frame, img;

		while (true)
		{
			Mat train_descs;
			videoEntrada >> frame;

			if (frame.empty())
			{
				cout << "Error de video" << endl;
				exit(-1);
			}

			resize(frame, frame, cv::Size(IMG_WIDTH, round(IMG_WIDTH * frame.rows / frame.cols)));
			cv::Mat descs;
			if (descriptor == 1)
			{
				descs = extractSIFTDDENSEescriptors(frame, ndesc, siftScales);
			}
			else if (descriptor == 2)
			{
				descs = extractSURFDescriptors(frame, ndesc);
			}
			else if (descriptor == 3)
			{
				descs = extractSIFTescriptors(frame, ndesc);
			}
			else
			{
				exit(-1);
			}
			cv::Mat bovw = compute_bovw(dictionary_ptr, keywords, descs, kmeans);

			if (train_descs.empty())
				train_descs = bovw;
			else
			{
				cv::Mat dst;
				cv::vconcat(train_descs, bovw, dst);
				train_descs = dst;
			}

			cv::Mat predicted_labels;

			//Consigue la categoria y la guarda en predicted labels
			classifier_ptr->predict(train_descs, predicted_labels);

			CV_Assert(predicted_labels.depth() == CV_32F);
			CV_Assert(predicted_labels.rows == train_descs.rows);

			//cout << categories[ int (cv::sum(predicted_labels) [0])] << " " << endl;

			namedWindow("ADIVINACION", WINDOW_AUTOSIZE);
			putText(frame, categories[ int (cv::sum(predicted_labels) [0])], Point2f(100, 100),
			        FONT_HERSHEY_PLAIN, 2,  Scalar(0, 0, 255,
			                                       255), 2);
			imshow("ADIVINACION", frame);

			waitKey(1);
		}
	}
}

