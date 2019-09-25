/*! \file common_code.cpp
    \brief Useful for building a Bag of Visual Words model
    \authors Fundamentos de Sistemas Inteligentes en Vision
*/

#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "common_code.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>

void basename(const std::string& path,
                     std::string& dirname,
                     std::string& filename,
                     std::string& ext)
{
    dirname="";
    filename=path;
    ext="";

    auto pos = path.rfind("/");

    if (pos != std::string::npos)
    {
      dirname=path.substr(0, pos);
      filename=path.substr(pos+1);
    }

    pos = filename.rfind(".");

    if (pos != std::string::npos)
    {
      ext = filename.substr(pos+1);
      filename = filename.substr(0,pos);
    }
    return;
}

std::string compute_sample_filename(const std::string& basename, const std::string& cat, const int sample_index)
{
    std::ostringstream filename;
    filename << basename << "/101_ObjectCategories/" << cat << "/image_" << std::setfill('0') << std::setw(4) << sample_index << ".jpg";
    return filename.str();
}

int load_dataset_information(const std::string& fname, std::vector<std::string>& categories, std::vector<int>& samples_per_cat)
{
   int retCode = 0;
   std::ifstream in (fname);

   if (!in)
       retCode = 1;
   else
   {
       while((in) && (retCode==0) )
       {
           std::string catName;
           int nsamples;
           in >> catName >> nsamples;
           if (!in)
           {
               if (! in.eof())
                retCode = 2;
           }
           else
           {
               categories.push_back(catName);
               samples_per_cat.push_back(nsamples);
           }
       }
   }
   return retCode;
}

void random_sampling (int total, int ntrain, int ntest,
                      std::vector< int >& train_samples,
                      std::vector< int >& test_samples)
{
    assert(ntrain<total);
    train_samples.resize(0);
    test_samples.resize(0);
    std::vector<bool> sampled(total, false);
    while (ntrain>0)
    {
        int s = int(double(total) * rand()/(RAND_MAX+1.0));
        int i=0;
        while(sampled[i] && i<sampled.size()) ++i; //the first unsampled.
        int c=0;
        while (c<s) //count s unsampled.
        {
            while (sampled[++i]); //advance to next unsampled.
            ++c;
        }
        assert(!sampled[i]);
        train_samples.push_back(i+1);
        sampled[i]=true;
        --total;
        --ntrain;
    }
    if (ntest>=total)
    {
        for (size_t i=0 ; i<sampled.size(); ++i)
            if (!sampled[i])
                test_samples.push_back(i+1);
    }
    else
    {
        while (ntest>0)
        {
            int s = int(double(total) * rand()/(RAND_MAX+1.0));
            int i=0;
            while(sampled[i] && i<sampled.size()) ++i; //the first unsampled.
            int c=0;
            while (c<s) //count s unsampled.
            {
                while (sampled[++i]); //advance to next unsampled.
                ++c;
            }
            test_samples.push_back(i+1);
            sampled[i]=true;
            --total;
            --ntest;
        }
    }
}

void create_train_test_datasets (std::vector<int>& samples_per_cat, int ntrain_samples, int ntest_samples,
                                 std::vector< std::vector <int> >& train_samples, std::vector< std::vector<int> >& test_samples)
{
    train_samples.resize(0);
    test_samples.resize(0);
    for (size_t i=0;i<samples_per_cat.size(); ++i)
    {
        std::vector<int> train;
        std::vector<int> test;
        random_sampling (samples_per_cat[i], ntrain_samples, ntest_samples, train, test);
        train_samples.push_back(train);
        test_samples.push_back(test);
    }
}

cv::Mat compute_confusion_matrix(int n_categories, const cv::Mat& true_labels, const cv::Mat& predicted_labels)
{
    CV_Assert(true_labels.rows == predicted_labels.rows);
    CV_Assert(true_labels.type()==CV_32FC1);
    CV_Assert(predicted_labels.type()==CV_32FC1);
    cv::Mat confussion_mat = cv::Mat::zeros(n_categories, n_categories, CV_32F);
    for (int i = 0; i < true_labels.rows; ++i)
    {
        confussion_mat.at<float>(true_labels.at<float>(i), predicted_labels.at<float>(i)) += 1.0;
    }
    return confussion_mat;
}

void compute_recognition_rate(const cv::Mat& cmat, double& mean, double& dev)
{
    CV_Assert(cmat.rows == cmat.cols && cmat.rows>1);
    CV_Assert(cmat.depth()==CV_32F);

    mean = 0.0;
    dev = 0.0;
    for (int c=0; c<cmat.rows; ++c)
    {
        const double class_Rate = cmat.at<float>(c,c)/cv::sum(cmat.row(c))[0];
        mean += class_Rate;
        dev += class_Rate*class_Rate;
    }
    mean /= double(cmat.rows);
    dev = sqrt(dev/double(cmat.rows) - mean*mean);
}

cv::Mat extractSIFTescriptors(const cv::Mat& img, const int ndesc)
{
    cv::Ptr<cv::xfeatures2d::SIFT> sift = cv::xfeatures2d::SIFT::create(ndesc);
    std::vector<cv::KeyPoint> kps;
    cv::Mat descs;
    sift->detectAndCompute(img, cv::noArray(), kps, descs);
    return descs;
}

cv::Mat extractSIFTDDENSEescriptors(const cv::Mat& img, const int ndesc,std::vector<int> siftScales)
{
  /*
    cv::Ptr<cv::xfeatures2d::SIFT> sift = cv::xfeatures2d::SIFT::create(ndesc);
    std::vector<cv::KeyPoint> kps;
    cv::Mat descs;
    sift->detectAndCompute(img, cv::noArray(), kps, descs);
    return descs;
  */
    cv::Ptr<cv::xfeatures2d::SIFT> sift = cv::xfeatures2d::SIFT::create(ndesc);
    std::vector<cv::KeyPoint> kps;

    vector<KeyPoint> keypoints; // keypoint storage
    Mat descriptors; // descriptor storage

    for(int i=0;i<siftScales.size();i++)
    {
      for (int y=siftScales[i]; y<img.rows-siftScales[i]; y+=siftScales[i])
      {
        for (int x=siftScales[i]; x<img.cols-siftScales[i]; x+=siftScales[i])
        {

            // x,y,radius
            keypoints.push_back(KeyPoint(float(x), float(y), float(siftScales[i])));
        }
      }
    }

    // compute descriptors

    sift->compute(img, keypoints, descriptors);

    return descriptors;
}

cv::Mat extractSURFDescriptors(const cv::Mat& img, const int ndesc)
{
    cv::Ptr<cv::xfeatures2d::SURF> surf = cv::xfeatures2d::SURF::create(ndesc);
    std::vector<cv::KeyPoint> kps;
    cv::Mat descs;
    surf->detectAndCompute(img, cv::noArray(), kps, descs);
    return descs;
}

cv::Mat
compute_bovw (const cv::Ptr<cv::ml::KNearest>& dict, const int dict_size, cv::Mat& img_descs, int kvecino, bool normalize)
{
    cv::Mat bovw = cv::Mat::zeros(1, dict_size, CV_32F);
    cv::Mat vwords;
    CV_Assert(img_descs.type()==CV_32F);
    dict->findNearest(img_descs, kvecino, vwords);
    CV_Assert(vwords.depth()==CV_32F);
    for (int i=0;i<img_descs.rows;++i)
        bovw.at<float>(vwords.at<float>(i))++;
    if (normalize)
        bovw /= float(img_descs.rows);
    return bovw;
}

