#ifndef __UNSHARP_MASK__
#define __UNSHARP_MASK__

#include <opencv2/core/core.hpp>
#include <cassert>

using namespace std;
using namespace cv;

namespace FSIV
{
  enum fourierTransform { SPATIAL_DOMAIN, FREQUENCY_DOMAIN };

  class UnsharpMask
  {
  public:
    /** 
	  * @brief Default Constructor
	  * @param cutoff Cutoff frequency, default 0.5
	  * @param orderButterWorth Order ButterWorth filter, default 2
	  * @param gain, Gain enhancement, default 1
    **/
    inline UnsharpMask(double cutoff = 0.5, unsigned short int orderButterWorth = 2, double gain = 1)
    {
      this->setCutOffFrequency(cutoff);
      this->setOrderButterworth(orderButterWorth);
      this->setGain(gain);
    }

    /** @brief Sets cutoff frequency
	   * @param cutoff Cutoff frequency
    **/
    inline void setCutOffFrequency(double cutoff)
    {
      assert((cutoff >= 0) && (cutoff <= 1));

      _cutoffFrequency = cutoff;
    }

    /** @brief Sets order Butterworth filter 
	   * @param order Order butterworth filter
    **/
    inline void setOrderButterworth(unsigned short int order)
    {
      assert((order >= 1) && (order <= 10));

      _orderButterworth = order;
    }

    /** @brief Sets gain enhancement
	   * @param gain Gain enhancement
    **/
    inline void setGain(double gain)
    {
      assert((gain >= 0) && (gain <= 5));

      _gain = gain;
    }

    /** @brief Returns cutoff frequency saved **/
    inline double getCutOffFrequency() const
    {
      return _cutoffFrequency;
    }

    /** @brief Returns butterworth order **/
    inline unsigned short int getOrderButterworth() const
    {
      return _orderButterworth;
    }

    /** @brief Returns gain enhancement **/
    inline double getGain() const
    {
      return _gain;
    }
    
    /** @brief Unsharp picture **/
	 Mat unshark(const Mat &picture, const Mat &mascara = Mat());
    
private:
	double _cutoffFrequency; //!<Cutoff frequency
	unsigned short int _orderButterworth; //!< Order Butterworth filter
	double _gain; //!< Gain enhancement
  };
}

#endif
