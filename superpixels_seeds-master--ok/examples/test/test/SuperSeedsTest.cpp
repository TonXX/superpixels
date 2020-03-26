#include <iostream>

#include "seeds_opencv.h"
#include<ctime>
using namespace std;
using namespace cv;

int main()
{
	clock_t start, end;
	start = clock();
	cv::Mat image = cv::imread( std::string( "2.png"), IMREAD_UNCHANGED);

  
    if ( !image.empty() )
    {
        cv::Mat labels;
        int count;
        seeds(image, 4, 4, 4, labels, count);
		cv::imwrite( std::string( "2-lables.png"), labels);
  
        cv::Mat contour;
        labelContourMask(labels, contour, false);
		cv::imwrite(std::string("2-contours.png"), contour);

        image.setTo(cv::Scalar(255, 255, 255), contour);
		cv::imwrite( std::string( "2-seg.png"), image);
		imshow("asasa",image);
    }
    else
    {
        cout << "Open image failed!" << endl;
    }
	end = clock();		//程序结束用时
	double endtime = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "Total time:" << endtime << endl;		//s为单位
	cout << "Total time:" << endtime * 1000 << "ms" << endl;	//ms为单位


	waitKey(0);
    return 0;

}