#include<opencv2/opencv.hpp>
#include<iostream>
#include<random>
using namespace std;
using namespace cv;


Mat src(500, 1000, CV_8UC3, Scalar(255, 255, 255));
Point pt0ld;
Scalar getRandomColor();
void on_mouse(int event, int x, int y, int flags, void*);
void savethefile(Mat& savefile);
void loadthefile(Mat& savefile);
void clearthefile(Mat& savefile);
void runthefile(Mat& savefile);
void box(Mat& src);
void puttext(Mat& src);
int countcontours(const Mat& savefile);
void find2contours(Mat& savefile);
vector<vector<Point>> convertContoursToPoints(const Mat& savefile);
Mat grayy(const Mat& savefile);
string name;
Point centroid;
Point medianPoint;

int main(void)
{

	box(src);
	puttext(src);
	namedWindow("src");
	setMouseCallback("src", on_mouse);
	imshow("src", src);
	waitKey();
	return 0;
}
Scalar getRandomColor() {
	// C++11 표준 랜덤 장치와 분포 설정
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, 255); // 0부터 255까지의 랜덤 값 생성

	// 랜덤한 BGR 색상 생성
	int b = dis(gen);
	int g = dis(gen);
	int r = dis(gen);

	return Scalar(b, g, r); // BGR 순서
}
void on_mouse(int event, int x, int y, int flags, void*)
{
	Rect areas(500, 0, 250, 100);
	Rect areal(500, 100, 250, 100);
	Rect areac(500, 200, 250, 100);
	Rect arear(500, 300, 250, 100);
	Rect areae(500, 400, 250, 100);
	Rect areacon(750, 0, 250, 100);
	Mat savefile;
	savefile = src(Rect(2, 2, 495, 490));
	static Scalar ranc = Scalar(255, 255, 255);
	static Point pt0ld = Point(-1, -1);
	switch (event) {
	case EVENT_LBUTTONDOWN:
		pt0ld = Point(x, y);
		if (areas.contains(pt0ld)) {						//save
			savethefile(savefile);
		}
		if (areal.contains(pt0ld)) {						//load
			loadthefile(savefile);
		}
		if (areac.contains(pt0ld))
		{						//clear
			clearthefile(savefile);
		}
		if (arear.contains(pt0ld)) {
			runthefile(savefile);
		}
		if (areae.contains(pt0ld)) {						//exit
			cout << "exit" << endl;
			exit(1);
		}
		if (areacon.contains(pt0ld)) {
			int numContours = countcontours(savefile);
			cout << "외곽선의 갯수: " << numContours << endl;
		}
		break;
	case EVENT_MOUSEMOVE:
		if (flags & EVENT_FLAG_LBUTTON) {
			line(src(Rect(0, 0, 500, 500)), pt0ld, Point(x, y), Scalar(0, 0, 0), 8);
			imshow("src", src);
		}
		if ((flags & EVENT_FLAG_RBUTTON) && (flags & EVENT_FLAG_CTRLKEY)) {
			line(src(Rect(0, 0, 500, 500)), pt0ld, Point(x, y), Scalar(255, 255, 255), 8);
			imshow("src", src);
		}
		else if (flags & EVENT_FLAG_RBUTTON) {
			line(src(Rect(0, 0, 500, 500)), pt0ld, Point(x, y), ranc, 9);
			imshow("src", src);
		}
		pt0ld = Point(x, y);
		break;
	case EVENT_FLAG_RBUTTON:
		ranc = getRandomColor();
		break;
	case EVENT_LBUTTONUP:
	case EVENT_RBUTTONUP:
		pt0ld = Point(-1, -1); // 마우스 버튼을 떼면 초기화
		break;
	}
	imshow("src", src);
}

void box(Mat& src)
{
	line(src, Point(500, 0), Point(500, src.rows - 1), Scalar(0, 0, 0), 2);
	line(src, Point(500, 100), Point(src.cols - 1, 100), Scalar(0, 0, 0), 2);
	line(src, Point(500, 200), Point(src.cols - 1, 200), Scalar(0, 0, 0), 2);
	line(src, Point(500, 300), Point(src.cols - 1, 300), Scalar(0, 0, 0), 2);
	line(src, Point(500, 400), Point(src.cols - 1, 400), Scalar(0, 0, 0), 2);

	line(src, Point(750, 0), Point(750, src.rows - 1), Scalar(0, 0, 0), 2);

	line(src, Point(0, 0), Point(0, src.rows - 1), Scalar(0, 0, 0), 2);
	line(src, Point(0, 0), Point(src.cols - 1, 0), Scalar(0, 0, 0), 2);
	line(src, Point(0, src.rows - 1), Point(src.cols - 1, src.rows - 1), Scalar(0, 0, 0), 2);
	line(src, Point(src.cols - 1, 0), Point(src.cols - 1, src.rows - 1), Scalar(0, 0, 0), 2);
}
void puttext(Mat& src)
{
	Mat save, load, clear, run, exit, contour;
	save = src(Rect(500, 0, 250, 100));
	load = src(Rect(500, 100, 250, 100));
	clear = src(Rect(500, 200, 250, 100));
	run = src(Rect(500, 300, 250, 100));
	exit = src(Rect(500, 400, 250, 100));
	contour = src(Rect(750, 0, 250, 100));

	const String texts = "Save";
	const String textl = "Load";
	const String textc = "Clear";
	const String textr = "Run";
	const String texte = "Exit";
	const String textcon = "Contour";
	const String texth = "hist";
	int fontFace = FONT_HERSHEY_SIMPLEX;
	double fontScale = 2.0;
	int thickness = 2;

	Size sizeImgS = save.size();
	Size sizeTextS = getTextSize(texts, fontFace, fontScale, thickness, 0);
	Point saveorg((sizeImgS.width - sizeTextS.width) / 2, (sizeImgS.height + sizeTextS.height) / 2);

	Size sizeImgL = load.size();
	Size sizeTextL = getTextSize(textl, fontFace, fontScale, thickness, 0);
	Point loadorg((sizeImgL.width - sizeTextL.width) / 2, (sizeImgL.height + sizeTextL.height) / 2);

	Size sizeImgC = clear.size();
	Size sizeTextC = getTextSize(textc, fontFace, fontScale, thickness, 0);
	Point clearorg((sizeImgC.width - sizeTextC.width) / 2, (sizeImgC.height + sizeTextC.height) / 2);

	Size sizeImgR = run.size();
	Size sizeTextR = getTextSize(textr, fontFace, fontScale, thickness, 0);
	Point runorg((sizeImgR.width - sizeTextR.width) / 2, (sizeImgR.height + sizeTextR.height) / 2);

	Size sizeImgE = exit.size();
	Size sizeTextE = getTextSize(texte, fontFace, fontScale, thickness, 0);
	Point exitorg((sizeImgE.width - sizeTextE.width) / 2, (sizeImgE.height + sizeTextE.height) / 2);

	Size sizeImgCon = contour.size();
	Size sizeTextcon = getTextSize(textcon, fontFace, fontScale, thickness, 0);
	Point contorg((sizeImgCon.width - sizeTextcon.width) / 2, (sizeImgCon.height + sizeTextcon.height) / 2);

	putText(save, texts, saveorg, fontFace, fontScale, Scalar(0, 0, 0), thickness);
	putText(load, textl, loadorg, fontFace, fontScale, Scalar(0, 0, 0), thickness);
	putText(clear, textc, clearorg, fontFace, fontScale, Scalar(0, 0, 0), thickness);
	putText(run, textr, runorg, fontFace, fontScale, Scalar(0, 0, 0), thickness);
	putText(exit, texte, exitorg, fontFace, fontScale, Scalar(0, 0, 0), thickness);
	putText(contour, textcon, contorg, fontFace, fontScale, Scalar(0, 0, 0), thickness);
}
int countcontours(const Mat& savefile)
{
	Mat binaryImage = grayy(savefile);
	vector<vector<Point>> contours;
	findContours(binaryImage, contours, RETR_LIST, CHAIN_APPROX_NONE);
	return contours.size();
}
Mat grayy(const Mat& savefile)
{
	Mat gray;
	cvtColor(savefile, gray, COLOR_BGR2GRAY);
	threshold(gray, gray, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);

	morphologyEx(gray, gray, MORPH_CLOSE, Mat(15, 15, CV_8UC1), Point(-1, -1));

	// imshow("gray", gray); // 주석 처리: gray 이미지를 표시하지 않음
	return gray; // 그레이스케일 이미지 반환
}
void savethefile(Mat& savefile)
{
	cout << "save" << endl;
	cout << "파일이름 입력(.jpg포함): ";
	cin >> name;
	imwrite(name, savefile);
}
void loadthefile(Mat& savefile)
{
	cout << "load" << endl;
load_image:
	cout << "불러올 파일 이름 입력(.jpg포함) : ";
	cin >> name;
	savefile = imread(name);
	if (savefile.empty())
	{
		cerr << "Image Loaded Failed!" << endl;
		goto load_image;
	}
	Mat roi = src(Rect(2, 2, 495, 490));
	savefile.copyTo(roi);
}
void clearthefile(Mat& savefile)
{
	cout << "clear" << endl;
	savefile = (500, 500, CV_8UC3, Scalar(255, 255, 255));
	rectangle(src, Point(0, 0), Point(500, 500), Scalar(0, 0, 0), 2);
}
void runthefile(Mat& savefile)
{
	int numContours = countcontours(savefile);					//run
	cout << "run" << endl;
	if (numContours == 3) {
		cout << "8" << endl;
	}
	if (numContours == 2) {
		find2contours(savefile);
	}
	if (numContours == 1) {
		cout << "1, 2, 3, 4, 5, 7" << endl;
	}
}
void find2contours(Mat& savefile)
{
	Mat tmp;
	savefile.copyTo(tmp);
	vector<vector<Point>> points = convertContoursToPoints(tmp);
	int count = 0;
	int largestIndex = 0;
	int smallIndex = 0;
	double largestArea = 0.0;
	double smallArea = numeric_limits<double>::infinity();
	double area = 0.0;

	for (int i = 0; i < points.size(); i++) {
		Rect bB = boundingRect(points[i]);
		double area = bB.width * bB.height;
		if (area > largestArea) {
			largestArea = area;
			largestIndex = i;
		}
		if (area < smallArea) {
			smallArea = area;
			smallIndex = i;
		}
	}
	double ratio = smallArea / largestArea;
	if (ratio > 0.7) {
		cout << "0" << endl;
		return;
	}
	Moments momento = moments(points[largestIndex]);
	double cX = momento.m10 / momento.m00;
	double cY = momento.m01 / momento.m00;
	centroid = Point(static_cast<int>(cX), static_cast<int>(cY));
	for (int i = 0; i < points.size(); i++) {
		Rect boundingBox = boundingRect(points[largestIndex]);
		Rect innerboundingBox = boundingRect(points[smallIndex]);
		if (static_cast<int>(cY) < static_cast<int>(boundingBox.y + boundingBox.height / 2)) {
			count++;
		}
		else if (static_cast<int>(cY) > static_cast<int>(boundingBox.y + boundingBox.height / 2)) {
			count--;
		}
		circle(tmp, centroid, 5, Scalar(255, 0, 255), -1);
		rectangle(tmp, boundingBox, Scalar(0, 255, 0), 2);
		rectangle(tmp, innerboundingBox, Scalar(0, 255, 255), 2);
	}
	if (count > 0) {
		cout << "9" << endl;
		count = 0;
	}
	else if (count < 0) {
		cout << "6" << endl;
		count = 0;
	}
	imshow("tmp", tmp);
}
vector<vector<Point>> convertContoursToPoints(const Mat& savefile) {
	vector<vector<Point>> points, contours;
	Mat grayImage = grayy(savefile);
	findContours(grayImage, contours, RETR_LIST, CHAIN_APPROX_NONE);
	for (int i = 0; i < contours.size(); ++i) {
		vector<Point> contourPoints;
		for (int j = 0; j < contours[i].size(); ++j) {
			contourPoints.push_back(contours[i][j]);
		}
		points.push_back(contourPoints);
	}

	return points;
}
