#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

Mat src(500, 750, CV_8UC3, Scalar(255, 255, 255));
Point pt0ld;
void on_mouse(int event, int x, int y, int flags, void*);
void detect(Mat& savefile);
void box(Mat& src);
void puttext(Mat& src);

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

void on_mouse(int event, int x, int y, int flags, void*)
{
	Rect areas(500, 0, 250, 100);
	Rect areal(500, 100, 250, 100);
	Rect areac(500, 200, 250, 100);
	Rect arear(500, 300, 250, 100);
	Rect areae(500, 400, 250, 100);
	Mat savefile;
	string name;
	savefile = src(Rect(0, 0, 500, 500));

	switch (event) {
	case EVENT_LBUTTONDOWN:
		pt0ld = Point(x, y);
		if (areas.contains(pt0ld)) {						//save
			cout << "save" << endl;
			cout << "파일이름 입력(.jpg포함): ";
			cin >> name;
			imwrite(name, savefile);
		}
		if (areal.contains(pt0ld)) {						//load
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
			Mat roi = src(Rect(0, 0, 500, 500));
			savefile.copyTo(roi);
		}
		if (areac.contains(pt0ld))
		{						//clear
			cout << "clear" << endl;
			savefile = (500, 500, CV_8UC3, Scalar(255, 255, 255));
			rectangle(src, Point(0, 0), Point(500, 500), Scalar(0, 0, 0), 2);
		}
		if (arear.contains(pt0ld)) {						//run
			cout << "run" << endl;
			detect(savefile);
		}
		if (areae.contains(pt0ld)) {						//exit
			cout << "exit" << endl;
			exit(1);
		}
		break;

	case EVENT_MOUSEMOVE:
		if (flags & EVENT_FLAG_LBUTTON) {
			line(src(Rect(0, 0, 500, 500)), pt0ld, Point(x, y), Scalar(0, 0, 0), 8);
			imshow("src", src);
			pt0ld = Point(x, y);
		}
		break;

	case EVENT_RBUTTONDOWN:
		return;
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

	line(src, Point(0, 0), Point(0, src.rows - 1), Scalar(0, 0, 0), 2);
	line(src, Point(0, 0), Point(src.cols - 1, 0), Scalar(0, 0, 0), 2);
	line(src, Point(0, src.rows - 1), Point(src.cols - 1, src.rows - 1), Scalar(0, 0, 0), 2);
	line(src, Point(src.cols - 1, 0), Point(src.cols - 1, src.rows - 1), Scalar(0, 0, 0), 2);
}
void puttext(Mat& src)
{
	Mat save, load, clear, run, exit;
	save = src(Rect(500, 0, 250, 100));
	load = src(Rect(500, 100, 250, 100));
	clear = src(Rect(500, 200, 250, 100));
	run = src(Rect(500, 300, 250, 100));
	exit = src(Rect(500, 400, 250, 100));
	const String texts = "Save";
	const String textl = "Load";
	const String textc = "Clear";
	const String textr = "Run";
	const String texte = "Exit";
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

	putText(save, texts, saveorg, fontFace, fontScale, Scalar(0, 0, 0), thickness);
	putText(load, textl, loadorg, fontFace, fontScale, Scalar(0, 0, 0), thickness);
	putText(clear, textc, clearorg, fontFace, fontScale, Scalar(0, 0, 0), thickness);
	putText(run, textr, runorg, fontFace, fontScale, Scalar(0, 0, 0), thickness);
	putText(exit, texte, exitorg, fontFace, fontScale, Scalar(0, 0, 0), thickness);


}
void detect(Mat& savefile)
{
	vector<vector<Point>> contours;
	Mat gray;
	int cX, cY;
	cvtColor(savefile, gray, COLOR_BGR2GRAY);
	threshold(gray, gray, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);

	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));

	erode(gray, gray, element);
	dilate(gray, gray, element);

	//레이블링 ------------------------------------------------------------
	Mat labels, stats, centroids;
	int c = connectedComponentsWithStats(gray, labels, stats, centroids);
	int* cc = stats.ptr<int>(1);
	Rect c1(cc[0] - 1, cc[1] - 1, cc[2] + 3, cc[3] + 3);
	c1 &= Rect(0, 0, gray.cols, gray.rows);
	findContours(gray(c1), contours, RETR_LIST, CHAIN_APPROX_NONE);


	int c1c;
	c1c = connectedComponents(gray(c1), labels);
	Mat contoursImage(savefile.size(), CV_8UC3, Scalar(0, 0, 0));
	drawContours(contoursImage, contours, -1, Scalar(0, 255, 0), 2);
	imshow("contours", contoursImage);
	imshow("gray", gray(c1));
	if (c1c == 3) {
		cout << " 8 " << endl;
	}
}