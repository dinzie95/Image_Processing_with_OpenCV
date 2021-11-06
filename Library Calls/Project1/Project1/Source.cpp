#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"

using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {

	//load image (colour image code=1)
	Mat img = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);

	if (!img.data) {
		cout << "Couldn't find image" << endl;
		return -1;
	}

	int height= img.rows;
	int width = img.cols;
	int widthstep= img.step;
	int channels = img.channels();

	Mat avgFilter = img.clone();
	Mat medianFilter = img.clone();
	Mat gaussianFilter = img.clone();
	Mat bThreshold = img.clone();
	Mat oThreashold= img.clone();
	Mat adThreshold= img.clone();
	Mat cannyedge = img.clone();
	Mat contours = img.clone();

	blur(img, avgFilter, Size(3, 3), Point(-1, -1), 4);

	medianBlur(img, medianFilter, 3);

	GaussianBlur(img, gaussianFilter, Size(3, 3), 4);

	threshold(medianFilter, bThreshold, 130, 255, CV_THRESH_BINARY);

	threshold(medianFilter, oThreashold, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);

	adaptiveThreshold(medianFilter, adThreshold, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 11, 2);

	Canny(medianFilter, cannyedge, 50, 100, 3,false);

	

	namedWindow("Image");
	imshow("Image", img);
	namedWindow("Average Filter");
	imshow("Average Filter", avgFilter);
	namedWindow("Median Filter");
	imshow("Median Filter", medianFilter);
	namedWindow("Gaussian Filter");
	imshow("Gaussian Filter", gaussianFilter);
	namedWindow("Binary Threshold");
	imshow("Binary Threshold", bThreshold);
	namedWindow("Otsu Threashold");
	imshow("Otsu Threshold", oThreashold);
	namedWindow("Adaptive Threshold");
	imshow("Adaptive Threshold", adThreshold);
	namedWindow("Canny edge");
	imshow("Canny edge", cannyedge);
	waitKey(0);
	return 0;
}