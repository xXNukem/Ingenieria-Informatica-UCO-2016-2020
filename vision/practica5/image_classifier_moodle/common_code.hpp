/*! \file common_code.hpp
    \brief Useful for building a Bag of Visual Words model
    \authors Fundamentos de Sistemas Inteligentes en Vision
*/

#ifndef __COMMON_CODE_HPP__
#define __COMMON_CODE_HPP__

#include <string>
#include <opencv2/core.hpp>
#include <opencv2/ml.hpp>
using namespace cv;
using namespace std;

void basename(const std::string& path,
                     std::string& dirname,
                     std::string& filename,
                     std::string& ext);

/**\brief generate the corresponding filename of a sample in the dataset.*/
std::string compute_sample_filename(const std::string& basename, const std::string& cat, const int sample_index);

/**
 * \brief Load the dataset description.
 * It is expected one row per catergory with category name and num. of samples.
 * \arg[in] fname is the pathname of the file.
 * \arg[out] categories is a vector wth categories names.
 * \arg[out] samples_per_cat is a vector with the number of samples of each category.
 * \return retcode: 0->success, 1 couldn't open file, 2 wrong file forma.
 */
int load_dataset_information(const std::string& fname, std::vector<std::string>& categories, std::vector<int>& samples_per_cat);

/**
 * \brief Create a dataset to train and test.
 * \arg[in] samples_per_cat say the total samples per category.
 * \arg[in] ntrain says the number of train samples per cat.
 * \arg[in] ntest says the number of test samples per cat.
 * \arg[out] train_samples says the sample's index per cat will used to train.
 * \arg[out] test_samples says the sample's index per cat will used to test.
 */
void create_train_test_datasets (std::vector<int>& samples_per_cat, int ntrain, int ntest,
                                 std::vector< std::vector <int> >& train_samples, std::vector< std::vector<int> >& test_samples);

/**
 * @brief Compute the recognition rate from a confussion matrix.
 * @param[in] cmat is the CxC confussion matrix.
 * @param[out] mean is the recognition rate mean on classes C.
 * @param[out] dev is the recognition rate deviation on classes C.
 */
void compute_recognition_rate(const cv::Mat& cmat, double& mean, double& dev);

/**
  * @brief Compute a confusion matrix.
  * @param[in] n_categories is the number of differentes categories.
  * @param[in] true_labels is a vector with the true lables.
  * @param[in] predicted_labels is a vector with the predicted labels.
  * @return the confussion matrix.
  */
cv::Mat compute_confusion_matrix(int n_categories, const cv::Mat& true_labels, const cv::Mat& predicted_labels);


/**
 * @brief Extracts sparse SIFT descriptors given an image
 * @param[in] img Input image
 * @param[in] ndesc Maximum number of descriptors to be returned
 * @return The set of SIFT descriptors
 */ 

cv::Mat extractSIFTescriptors(const cv::Mat& img, const int ndesc);

cv::Mat extractSIFTDDENSEescriptors(const cv::Mat& img, const int ndesc,std::vector<int> siftScales);

cv::Mat extractSURFDescriptors(const cv::Mat& img, const int ndesc);

/**
 * @brief Computes a Bag of Visual Words descriptor
 * @param[in] dict the dictionary
 * @param[in] dict_size number of visual words
 * @param[in] img_descs the set of keypoint descriptors used to represent the image
 * @return the BoVW descriptor
 */
cv::Mat compute_bovw (const cv::Ptr<cv::ml::KNearest>& dict, const int dict_size, cv::Mat& img_descs, int kvecino, bool normalize=true);

#endif //__COMMON_CODE_HPP__
