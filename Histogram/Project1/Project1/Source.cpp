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

	//convert 10*10 pixel to white
	img.at<uchar>(10, 10) = 255;

	//New window
	//Scalar=colour of the empty window. Here 0 is black
	//1 in CV_8UC1 mean one channel
	Mat gray(height, width,CV_8UC1,Scalar(0));
	// result same size width image window in black color

	//convert image from BGR to GRAY
	//print a gray image of the img window in gray window
	cvtColor(img, gray, COLOR_BGR2GRAY);

	//Copy image
	Mat copy(height, width, CV_8UC3, Scalar(0, 0, 0));

	//read pixel by pixel and copy
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			//Vec3b for 3 channel images
			copy.at<Vec3b>(y, x) = img.at<Vec3b>(y, x);
		}
	}

	//Histogram 
	
	//Stp 1: Print count of pixels for each intensity values of grayscale image

	//allocate memory location for intensity values
	int hist[256];
	//initialize to zero
	for (int a = 0; a < 256; a++) {
		hist[a] = 0;
	}
	 
	//count 1 by 1 pixel for each intensity value
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			hist[(int)gray.at<uchar>(y, x)] = hist[(int)gray.at<uchar>(y, x)]+1;
			
		}
	}

	//print counts for each intensity value
	for (int y = 0; y < 256; y++) {
		printf("Intensity %d: %d\n", y, hist[y]);
	}

	//create image to display histogram
	int hist_w = 512;
	int hist_h = 400;
	//set line width for histogram
	int bin_w = cvRound((double)hist_w / 256);

	//window for histogram with white BG
	Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(255));

	//Find the maximum no of pixels from the histogram array
	int max = hist[0];
	for (int i = 0; i < 256; i++) {
		if (max < hist[i]) {
			max = hist[i];
		}
	}

	//Normalize the histogram between 0 and histogram height
	for (int i = 0; i < 256; i++) {
		hist[i] = ((double)hist[i] / max) * histImage.rows; //given equation

	}

	//Draw the lines of the histogram
	for (int i = 0; i < 256; i++) {

		line(histImage, Point(bin_w * i, hist_h), Point(bin_w * i, hist_h - hist[i]), Scalar(0), 1, 8, 0); //line colour is black Scalar=0
	}


	namedWindow("Image");
	imshow("Image", img);
	namedWindow("Gray");
	imshow("Gray", gray);
	namedWindow("Copy");
	imshow("Copy", copy);
	namedWindow("Histogram");
	imshow("Histogram", histImage);
	waitKey(0);
	return 0;
}