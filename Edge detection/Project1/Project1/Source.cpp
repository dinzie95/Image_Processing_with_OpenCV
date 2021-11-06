#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"

using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {

	//load image (colour image code=1)
	Mat img = imread(argv[1],1);

	if (!img.data) {
		cout << "Couldn't find image" << endl;
		return -1;
	}

	int height= img.rows;
	int width = img.cols;
	int widthstep= img.step;
	int channels = img.channels();

	printf("Height : %d, Width : %d, Steps : %d, Channels : %d\n", height, width, widthstep, channels);

	Mat gr(height, width, CV_8UC1, Scalar(0));

	


	namedWindow("Image");
	imshow("Image", img);
	namedWindow("Gray");
	imshow("Gray", gray);
	namedWindow("Hist 1");
	imshow("Hist 1", histImage);
	namedWindow("New Image");
	imshow("New Image", new_image);
	namedWindow("Hist 2");
	imshow("Hist 2", histImageN);
	waitKey(0);
	return 0;
}