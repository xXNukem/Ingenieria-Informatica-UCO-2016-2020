#include "funciones.hpp"

vector<float> acumular_histograma(const cv::Mat& img, int tam, const cv::Mat& mask, bool existeMask)
{
    std::vector<float> h(255,0);
    std::vector<float> h_prima(255,0); //vector donde esta el histograma acumulado

     //calculo del istograma

            if(existeMask==false)
            {
                  for(int i=0;i<img.rows;i++)
                  {
                    for(int j=0;j<img.cols;j++)
                    {
                      h[img.at<uchar>(i,j)]++;
                    }
                  }
            }
            if(existeMask==true)//Parte que estaba mal en la primera entrega. Corregido: Calcular el historgrama segun los puntos activos de la mascara
            {
              for(int i=0;i<img.rows;i++)
                  {
                    for(int j=0;j<img.cols;j++)
                    {
                      if(mask.at<uchar>(i,j)==255)
                      h[img.at<uchar>(i,j)]++;
                    }
                  }
            }
          //acumulamos el histograma
          h_prima[0]=h[0];
          for(int i=0;i<h.size();i++)
          {
            h_prima[i]=h[i]+h_prima[i-1];
          }

    return h_prima;
}

vector<float> normalizar_histograma(vector<float> h_prima, int tam)
{
  for(int i=0;i<h_prima.size();i++)
  {
    h_prima[i] = ((double)h_prima[i] * (255.0 / (tam))); //formula de la wikipedia para ecualizar el histograma
  }

  return h_prima;
}

vector<float> calculate_histogram(const cv::Mat& img, int bins, const cv::Mat& mask, bool normalized, bool accumulated)
{
  std::vector<float> h(255,0);
  std::vector<float> h_prima(255,0); //vector donde esta el histograma acumulado
  int tam=0;
  bool existeMask=false;
  if(mask.empty())
  {
      tam=img.rows*img.cols;
      if(accumulated)
      h_prima=acumular_histograma(img,tam,mask,existeMask);
      if(normalized)
      h_prima=normalizar_histograma(h_prima, tam);
  }
  else
  {
    //parte que esta mal en la primera entrega
    //Corregido: calcular el tamaño segun los puntos activos en la mascara
      for(int i=0;i<mask.rows;i++)
      {
        for(int j=0;j<mask.cols;j++)
        {
          if(mask.at<uchar>(i,j)==255)
          tam++;
        }
      }
    
      existeMask=true;

      if(accumulated)
      h_prima=acumular_histograma(img,tam,mask,existeMask);
      if(normalized)
      h_prima=normalizar_histograma(h_prima, tam);
  }

  return h_prima;
}

Mat ecualizar_histograma(std::vector<float> const & h_prima, const cv::Mat& img,int r, const cv::Mat& mask)
{
  cv::Mat imagenEcualizada=img.clone(); //imagen ecualizada clonada de la original para devolverla
  Mat ventana(2*r+1,2*r+1,CV_8UC1);
  std::vector<float>h_ecualizado(255,0);
  cv::Mat ventanaMask (r*2+1,r*2+1,CV_8UC1);

  if(r!=0) //Si el radio es distinto de cero tengo que calcular el histograma del tamaño de la ventana 
  {
      for(int i=0;i<img.rows-(2*r+1);i++)
      {
          for(int j=0;j<img.cols-(2*r+1);j++)
          {
              if(mask.empty())
              {
                ventana=img(Rect(j,i,(2*r+1),(2*r+1)));//la funcion de recortar la ventana funciona primero con las columnas y luego con las filas
                h_ecualizado=calculate_histogram(ventana,256,mask,true,true);
                imagenEcualizada.at<uchar>(i+r,j+r)=(h_ecualizado[imagenEcualizada.at<uchar>(i+r,j+r)]);
              }
              else
              {
                  if(mask.at<uchar>(i+r,j+r)==255)
                  {
                    ventana=img(Rect(j,i,(2*r+1),(2*r+1)));
                    ventanaMask=mask(Rect(j,i,r*2+1,r*2+1));
                    h_ecualizado=calculate_histogram(ventana,256,ventanaMask,true,true);
                    imagenEcualizada.at<uchar>(i+r,j+r)=(h_ecualizado[imagenEcualizada.at<uchar>(i+r,j+r)]);
                  }
              }
          }
      }
  }
  else //si el radio vale 0 ecualizo todo entero
  {
        //ecualizacion de la imagen
      if(mask.empty())
      {
          for(int i=0;i<img.rows;i++)
          {
              for (int j = 0; j < img.cols; ++j)
              {
                imagenEcualizada.at<uchar>(i,j)=h_prima[img.at<uchar>(i,j)];
              }
          }
      }
      else
      {
          for(int i=0;i<img.rows;i++)
          {
              for (int j = 0; j < img.cols; ++j)
              {
                  if(mask.at<uchar>(i,j)==255)
                  imagenEcualizada.at<uchar>(i,j)=h_prima[img.at<uchar>(i,j)];
              }
          }
      }
  }

  return imagenEcualizada;
}
