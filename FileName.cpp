#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
Mat predata(Mat src);

int main(void) {
	Mat src = imread("1data.png", IMREAD_GRAYSCALE);
	for (int i = 0; i < 10; i++) {
		string data = "";
		data += (to_string(i) + "data.png");
		src = imread("data.png");

	}
	predata(src, i)
	return 0;
}
Mat predata(Mat src) {
	Mat tmp;
	src.copyTo(tmp);
	Mat binaryimg;
	threshold(tmp, binaryimg, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
	Mat labels, stats, centroids;
	int cnt = connectedComponentsWithStats(tmp, labels, stats, centroids);
	
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 5; j++) {
			Mat tmp2 = tmp(Rect((i * 100), (j * 100), 100, 100));
			resize(tmp2, tmp2, Size(300, 400));

		}
	}

}