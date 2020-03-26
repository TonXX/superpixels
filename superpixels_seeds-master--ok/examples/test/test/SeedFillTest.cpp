#include <iostream>

#include "region_seed_fill.h"

using namespace std;
using namespace cv;

int main11()
{
    cv::Mat image = cv::imread( std::string("demo.jpg"), IMREAD_UNCHANGED);
    cv::Point2i pt(248, 71);
    cv::Mat fillImage;

    if ( !image.empty() )
    {
        RegionSeedFill rsf;
        rsf.ccaSeedFill(pt, image, fillImage);

		cv::imwrite(std::string("demo_result.jpg"), fillImage);
    }
	return 00;
}