#define _USE_MATH_DEFINES

#include <iostream>

#include <cmath>

#include <vector>



using namespace std;







vector<vector<double>> createFilter(int row, int column, double sigmaIn)

    {

        vector<vector<double>> filter;



        for (int i = 0; i < row; i++)

        {

            vector<double> col;

            for (int j = 0; j < column; j++)

            {

                col.push_back(-1);

            }

            filter.push_back(col);

        }



        float coordSum = 0;

        float constant = 2.0 * sigmaIn * sigmaIn;



        // Sum is for normalization

        float sum = 0.0;



        for (int x = - row/2; x <= row/2; x++)

        {

            for (int y = -column/2; y <= column/2; y++)

            {

                coordSum = (x*x + y*y);

                filter[x + row/2][y + column/2] = (exp(-(coordSum) / constant)) / (M_PI * constant);

                sum += filter[x + row/2][y + column/2];

            }

        }



        // Normalize the Filter

        for (int i = 0; i < row; i++)

            for (int j = 0; j < column; j++)

                filter[i][j] /= sum;



        return filter;



    }

    vector<vector<int>> useFilter(vector<vector<int>> img_in, vector<vector<double>> filterIn)

    {

        int size = (int)filterIn.size()/2;

        vector<vector<int>> filteredImg=img_in;

        for (int i = size; i < img_in.size() - size; i++)

        {

            for (int j = size; j < img_in[i].size() - size; j++)

            {

                double sum = 0;



                for (int x = 0; x < filterIn.size(); x++)

                    for (int y = 0; y < filterIn.size(); y++)

                    {

                        sum += filterIn[x][y] * (double)(img_in[i + x - size][j + y - size]);

                    }



                filteredImg[i-size][j-size] = sum;

            }



        }

        return filteredImg;

    }

    vector<vector<int>> sobel(vector<vector<int>> gFiltered){

        double x1[] = {-1.0, 0, 1.0};

        double x2[] = {-2.0, 0, 2.0};

        double x3[] = {-1.0, 0, 1.0};



        vector<vector<double>> xFilter(3);

        xFilter[0].assign(x1, x1+3);

        xFilter[1].assign(x2, x2+3);

        xFilter[2].assign(x3, x3+3);

        //Sobel Y Filter

        double y1[] = {1.0, 2.0, 1.0};

        double y2[] = {0, 0, 0};

        double y3[] = {-1.0, -2.0, -1.0};



        vector<vector<double>> yFilter(3);

        yFilter[0].assign(y1, y1+3);

        yFilter[1].assign(y2, y2+3);

        yFilter[2].assign(y3, y3+3);



        //Limit Size

        int size = (int)xFilter.size()/2;



        //Mat gFiltered;

        //Mat filteredImg = Mat(gFiltered.rows - 2*size, gFiltered.cols - 2*size, CV_8UC1);

        vector<vector<int>> filteredImg=gFiltered;

        //Mat angles = Mat(gFiltered.rows - 2*size, gFiltered.cols - 2*size, CV_32FC1); //AngleMap

        //vector<vector<int>> angles=gFiltered;

        vector<vector<int>> angles=gFiltered;

        //vector<vector<int>> angles;



        for (int i = size; i < gFiltered.size() - size; i++)

        {

            for (int j = size; j < gFiltered[i].size() - size; j++)

            {

                double sumx = 0;

                double sumy = 0;



                for (int x = 0; x < xFilter.size(); x++)

                    for (int y = 0; y < xFilter.size(); y++)

                    {

                        sumx += xFilter[x][y] * (double)(gFiltered[i + x - size][j + y - size]); //Sobel_X Filter Value

                        sumy += yFilter[x][y] * (double)(gFiltered[i + x - size][j + y - size]); //Sobel_Y Filter Value

                    }

                double sumxsq = sumx*sumx;

                double sumysq = sumy*sumy;



                double sq2 = sqrt(sumxsq + sumysq);



                if(sq2 > 4096) //Unsigned Char Fix

                    sq2 =4096;

                filteredImg[i-size][j-size] = sq2;



                if(sumx==0) //Arctan Fix

                    angles[i-size][j-size] = 90;

                else

                    angles[i-size][j-size] = atan(sumy/sumx);

            }

        }



        return filteredImg;

    }

    vector<vector<int>> anglesMap(vector<vector<int>> gFiltered){

        double x1[] = {-1.0, 0, 1.0};

        double x2[] = {-2.0, 0, 2.0};

        double x3[] = {-1.0, 0, 1.0};



        vector<vector<double>> xFilter(3);

        xFilter[0].assign(x1, x1+3);

        xFilter[1].assign(x2, x2+3);

        xFilter[2].assign(x3, x3+3);

        //Sobel Y Filter

        double y1[] = {1.0, 2.0, 1.0};

        double y2[] = {0, 0, 0};

        double y3[] = {-1.0, -2.0, -1.0};



        vector<vector<double>> yFilter(3);

        yFilter[0].assign(y1, y1+3);

        yFilter[1].assign(y2, y2+3);

        yFilter[2].assign(y3, y3+3);



        //Limit Size

        int size = (int)xFilter.size()/2;



        //Mat gFiltered;

        //Mat filteredImg = Mat(gFiltered.rows - 2*size, gFiltered.cols - 2*size, CV_8UC1);

        vector<vector<int>> filteredImg=gFiltered;

        //Mat angles = Mat(gFiltered.rows - 2*size, gFiltered.cols - 2*size, CV_32FC1); //AngleMap

        vector<vector<int>> angles=gFiltered;

        //angles2(angles.begin(),angles.end());

        //angles=gFiltered;

        //vector<vector<float>> angles3=angles2;



        for (int i = size; i < gFiltered.size() - size; i++)

        {

            for (int j = size; j < gFiltered[i].size() - size; j++)

            {

                double sumx = 0;

                double sumy = 0;



                for (int x = 0; x < xFilter.size(); x++)

                    for (int y = 0; y < xFilter.size(); y++)

                    {

                        sumx += xFilter[x][y] * (double)(gFiltered[i + x - size][j + y - size]); //Sobel_X Filter Value

                        sumy += yFilter[x][y] * (double)(gFiltered[i + x - size][j + y - size]); //Sobel_Y Filter Value

                    }

                double sumxsq = sumx*sumx;

                double sumysq = sumy*sumy;



                double sq2 = sqrt(sumxsq + sumysq);



                if(sq2 > 4096) //Unsigned Char Fix

                    sq2 =4096;

                filteredImg[i-size][j-size] = sq2;



                if(sumx==0) //Arctan Fix

                    angles[i-size][j-size] = 90;

                else

                    angles[i-size][j-size] = atan(sumy/sumx);

            }

        }



        return angles;

    }

    vector<vector<int>> nonMaxSupp(vector<vector<int>> sFiltered,vector<vector<int>> angles2)

   {

       //Mat nonMaxSupped = Mat(sFiltered.rows-2, sFiltered.cols-2, CV_8UC1);

       vector<vector<int>> nonMaxSupped=sFiltered;

       vector<vector<int>> angles=angles2;

          for (int i=1; i< sFiltered.size() - 1; i++) {

              for (int j=1; j<sFiltered[i].size() - 1; j++) {

                  float Tangent = angles[i][j];



                  nonMaxSupped[i-1][j-1] = sFiltered[i][j];

                  //Horizontal Edge

                  if (((-22.5 < Tangent) && (Tangent <= 22.5)) || ((157.5 < Tangent) && (Tangent <= -157.5)))

                  {

                      if ((sFiltered[i][j] < sFiltered[i][j+1]) || (sFiltered[i][j] < sFiltered[i][j-1]))

                          nonMaxSupped[i-1][j-1] = 0;

                  }

                  //Vertical Edge

                  if (((-112.5 < Tangent) && (Tangent <= -67.5)) || ((67.5 < Tangent) && (Tangent <= 112.5)))

                  {

                      if ((sFiltered[i][j] < sFiltered[i+1][j]) || (sFiltered[i][j] < sFiltered[i-1][j]))

                          nonMaxSupped[i-1][j-1] = 0;

                  }



                  //-45 Degree Edge

                  if (((-67.5 < Tangent) && (Tangent <= -22.5)) || ((112.5 < Tangent) && (Tangent <= 157.5)))

                  {

                      if ((sFiltered[i][j] < sFiltered[i-1][j+1]) || (sFiltered[i][j] < sFiltered[i+1][j-1]))

                          nonMaxSupped[i-1][j-1] = 0;

                  }



                  //45 Degree Edge

                  if (((-157.5 < Tangent) && (Tangent <= -112.5)) || ((22.5 < Tangent) && (Tangent <= 67.5)))

                  {

                      if ((sFiltered[i][j] < sFiltered[i+1][j+1]) || (sFiltered[i][j]< sFiltered[i-1][j-1]))

                          nonMaxSupped[i-1][j-1] = 0;

                  }

              }

          }

       return nonMaxSupped;

   }

   vector<vector<int>> threshold(vector<vector<int>> imgin,int low, int high)

   {

       if(low > 4096)

           low = 1;

       if(high > 4096)

           high = 1;



       vector<vector<int>> EdgeMat=imgin;

       //Mat EdgeMat = Mat(imgin.rows, imgin.cols, imgin.type());



       for (int i=0; i<imgin.size(); i++)

       {

           for (int j = 0; j<imgin[i].size(); j++)

           {

               EdgeMat[i][j] = imgin[i][j];

               if(EdgeMat[i][j] > high)

                   EdgeMat[i][j] = 1;

               else if(EdgeMat[i][j] < low)

                   EdgeMat[i][j] = 0;

               else

               {

                   bool anyHigh = false;

                   bool anyBetween = false;

                   for (int x=i-1; x < i+2; x++)

                   {

                       for (int y = j-1; y<j+2; y++)

                       {

                           if(x <= 0 || y <= 0 || x > EdgeMat.size() || y > EdgeMat[x].size()) //Out of bounds

                               continue;

                           else

                           {

                               if(EdgeMat[x][y] > high)

                               {

                                   EdgeMat[i][j] = 1;

                                   anyHigh = true;

                                   break;

                               }

                               else if(EdgeMat[x][y] >= low)

                                   anyBetween = true;

                           }

                       }

                       if(anyHigh)

                           break;

                   }

                   if(!anyHigh && anyBetween)

                       for (int x=i-2; x < i+3; x++)

                       {

                           for (int y = j-1; y<j+3; y++)

                           {

                               if(x < 0 || y < 0 || x > EdgeMat.size() || y > EdgeMat[x].size()) //Out of bounds

                                   continue;

                               else

                               {

                                   if(EdgeMat[x][y] > high)

                                   {

                                       EdgeMat[i][j] = 1;

                                       anyHigh = true;

                                       break;

                                   }

                               }

                           }

                           if(anyHigh)

                               break;

                       }

                   if(!anyHigh)

                       EdgeMat[i][j] = 0;

               }

           }

       }

       return EdgeMat;

   }

vector<vector<int>> canny(vector<vector<int>> img_in,int low, int high){

	vector<vector<double>> filter=createFilter(3,3,1);

	vector<vector<int>> gFiltered=useFilter(img_in,filter);

	vector<vector<int>> sFiltered=sobel(gFiltered);

	vector<vector<int>> angles=anglesMap(gFiltered);

	vector<vector<int>> non=nonMaxSupp(sFiltered,angles);

	vector<vector<int>> thres=threshold(non,low,high);

	return thres;

}


