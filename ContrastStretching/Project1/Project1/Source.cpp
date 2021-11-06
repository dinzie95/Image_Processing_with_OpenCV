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

	

	//New window
	//Scalar=colour of the empty window. Here 0 is black
	//1 in CV_8UC1 mean one channel
	Mat gray(height, width,CV_8UC1,Scalar(0));
	// result same size width image window in black color

	//convert image from BGR to GRAY
	//print a gray image of the img window in gray window
	cvtColor(img, gray, COLOR_BGR2GRAY);

	//Histogram 

	//Stp 1: Print count of pixels for each intensity values of grayscale (low contrast) image

	//allocate memory location for intensity values
	int hist[256];
	//initialize to zero
	for (int a = 0; a < 256; a++) {
		hist[a] = 0;
	}

	//count 1 by 1 pixel for each intensity value
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			hist[(int)gray.at<uchar>(y, x)] = hist[(int)gray.at<uchar>(y, x)] + 1;

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

	Mat new_image = gray.clone();
	
	int v;
	int output;

	//changing the intensities to strech contrast

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			v = (int)gray.at<uchar>(y, x);

			if (v >= 0 && v <= 105) {
				output = int((5 / 105) * v);
			}
			else if (v > 105 && v <= 240) {
				output = int(((245/ 135) * (v - 105)) + 5);
			}
			else if (v > 240 && v <= 255) {
				output = int(((5 / 15) * (v - 240))) + 250;
			}

			new_image.at<uchar>(y, x) = (uchar)output;
		}
	}
	//Histogram 

	//Stp 1: Print count of pixels for each intensity values of grayscale (low contrast) image

	//allocate memory location for intensity values
	int histN[256];
	//initialize to zero
	for (int a = 0; a < 256; a++) {
		histN[a] = 0;
	}

	//count 1 by 1 pixel for each intensity value
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			histN[(int)new_image.at<uchar>(y, x)] = histN[(int)new_image.at<uchar>(y, x)] + 1;

		}
	}

	//print counts for each intensity value
	for (int y = 0; y < 256; y++) {
		printf("Intensity %d: %d\n", y, histN[y]);
	}

	//create image to display histogram
	int hist_wN = 512;
	int hist_hN = 400;
	//set line width for histogram
	int bin_wN = cvRound((double)hist_wN / 256);

	//window for histogram with white BG
	Mat histImageN(hist_hN, hist_wN, CV_8UC1, Scalar(255));

	//Find the maximum no of pixels from the histogram array
	int maxN = histN[0];
	for (int i = 0; i < 256; i++) {
		if (maxN < histN[i]) {
			maxN = histN[i];
		}
	}

	//Normalize the histogram between 0 and histogram height
	for (int i = 0; i < 256; i++) {
		histN[i] = ((double)histN[i] / maxN) * histImageN.rows; //given equation

	}

	//Draw the lines of the histogram
	for (int i = 0; i < 256; i++) {

		line(histImageN,Point(bin_wN * i, hist_hN), Point(bin_wN * i, hist_hN - histN[i]), Scalar(0), 1, 8, 0); //line colour is black Scalar=0
	}

	


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