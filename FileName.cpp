#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
//void predata(Mat src, int k);
void plus_learning_number(Mat preImg, int i);
Mat learning_number[10];
void study_num_data_recog();
Mat src(500, 1000, CV_8UC3, Scalar(255, 255, 255));
Point pt0ld;
void on_mouse(int event, int x, int y, int flags, void*);
void savethefile(Mat& savefile);
void loadthefile(Mat& savefile);
void clearthefile(Mat& savefile);
void runthefile(Mat& savefile);
void box(Mat& src);
void puttext(Mat& src);
void test_number_score(Mat savefile);
Mat resiz(Mat& img);

string name;
int main(void) {
    //
    //
    //for (int i = 0; i < 10; i++) {
    //    string data = "";
    //    data += (to_string(i) + "data.png");
    //    src = imread(data);
    //    predata(src, i);
    //}                 //데이터 파일을 받아서 전처리작업을 위한 반복문
    box(src);
    puttext(src);
    namedWindow("src");
    setMouseCallback("src", on_mouse);
    imshow("src", src);
    waitKey();
    return 0;
}
//void predata(Mat src, int k) {
//    Mat tmp;
//    src.copyTo(tmp);
//    Mat binaryimg;
//    cvtColor(tmp, binaryimg, COLOR_BGR2GRAY);
//    threshold(binaryimg, binaryimg, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
//    Mat labels, stats, centroids;
//    int cnt = connectedComponentsWithStats(binaryimg, labels, stats, centroids);
//    /*int num = 1;*/
//
//    for (int i = 0; i < 6; i++) {
//        for (int j = 0; j < 5; j++) { 
//            Mat tmp2 = tmp(Rect((i * 100), (j * 100), 100, 100));
//            resize(tmp2, tmp2, Size(300, 400));
//            ///*string numname;
//            //if (num < 10) {
//            //    numname += "0" + to_string(num);
//            //}
//            //else {
//            //    numname += "" + to_string(num);
//            //}
//            //string data = "./numberdata/" + to_string(k);
//            //imwrite(data + numname + "data.png", tmp2);
//            //이미지 저장
//            //num += 1;
//        }
//
//    }
//}
void box(Mat& src) {
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
void puttext(Mat& src) {
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
void on_mouse(int event, int x, int y, int flags, void*) {
    Rect areas(500, 0, 250, 100);
    Rect areal(500, 100, 250, 100);
    Rect areac(500, 200, 250, 100);
    Rect arear(500, 300, 250, 100);
    Rect areae(500, 400, 250, 100);
    Rect areacon(750, 0, 250, 100);
    Mat savefile;
    savefile = src(Rect(2, 2, 495, 490));

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
        break;

    case EVENT_MOUSEMOVE:
        if (flags & EVENT_FLAG_LBUTTON) {
            line(src(Rect(0, 0, 500, 500)), pt0ld, Point(x, y), Scalar(0, 0, 0), 8);
            imshow("src", src);
            pt0ld = Point(x, y);
        }
        if (flags & EVENT_FLAG_RBUTTON) {
            line(src(Rect(0, 0, 500, 500)), pt0ld, Point(x, y), Scalar(255, 255, 255), 9);
            imshow("src", src);
            pt0ld = Point(x, y);
        }
        break;

    }
    imshow("src", src);
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
    cout << "run" << endl;
    test_number_score(savefile);
}
void test_number_score(Mat savefile)
{
    Mat tmp, gray, bin;
    savefile.copyTo(tmp);
    cvtColor(tmp, gray, COLOR_BGR2GRAY);
    threshold(gray, bin, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
    resiz(bin);


    int identify_number_D[10] = { 0, };
    int index_num[2] = { 0,0 };
    int row = 40;
    int col = 30;
    const int rows = 10;
    const int cols = 3;
    int identify_number[rows][cols] = { 0 };
    Mat labels;
    for (int i = 0; i < 10; i++) {
        learning_number[i] = Mat::zeros(300, 400, CV_8UC1);
    }

    study_num_data_recog();

    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            Rect rec(x * col, y * row, col, row);
            // rec 객체가 이미지 경계를 벗어나지 않도록 체크
            if (rec.x >= 0 && rec.y >= 0 && rec.x + rec.width <= bin.cols && rec.y + rec.height <= bin.rows) {
                int cnt = connectedComponents(bin(rec), labels);
                for (int k = 0; k < 10; k++) {
                    if (learning_number[k].cols >= rec.x + rec.width && learning_number[k].rows >= rec.y + rec.height) {
                        int ex_cnt = connectedComponents(learning_number[k](rec), labels);
                        if (ex_cnt >= 2 && cnt >= 2) identify_number_D[k]++;
                        else if (ex_cnt >= 2 && cnt < 2) identify_number_D[k]--;
                        else if (ex_cnt < 2 && cnt >= 2) identify_number_D[k]++;
                    }
                }
            }
        }
    }

    int largest_index = -1;
    int second_largest_index = -1;
    int largest = INT_MIN;
    int second_largest = INT_MIN;

    for (int i = 0; i < 10; i++) {
        if (identify_number_D[i] > largest) {
            second_largest = largest;
            second_largest_index = largest_index;
            largest = identify_number_D[i];
            largest_index = i;
        }
        else if (identify_number_D[i] > second_largest) {
            second_largest = identify_number_D[i];
            second_largest_index = i;
        }
    }

    index_num[0] = largest_index;
    index_num[1] = second_largest_index;

    for (int i = 0; i < 10; i++) {
        cout << i << " 숫자에 대한 점수 : " << identify_number_D[i] << endl;
    }
    cout << "가장 유사한 숫자 2개(점수가 높은 순): " << index_num[0] << ", " << index_num[1] << endl << endl;

    identify_number[index_num[0]][2] = 1;
    if (index_num[0] - index_num[1] > 3) {
        identify_number[index_num[1]][2] = 1;
    }
}

Mat resiz(Mat& img) {
    Mat tmp;
    img.copyTo(tmp);

    vector<vector<Point>> contours;
    findContours(tmp, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    if (contours.empty()) {
        cerr << "No contour found!" << endl;
        return Mat();
    }

    double maxArea = 0;
    int maxContourIdx = -1;
    for (int i = 0; i < contours.size(); i++) {
        double area = contourArea(contours[i]);
        if (area > maxArea) {
            maxArea = area;
            maxContourIdx = i;
        }
    }

    if (maxContourIdx >= 0) {
        Rect boundingR = boundingRect(contours[maxContourIdx]);
        Mat roi = img(boundingR).clone();
        Mat resized_roi;
        resize(roi, resized_roi, Size(300, 400));
        return resized_roi;
    }
    else {
        cerr << "Failed to find the largest contour!" << endl;
        return Mat();
    }
}

void plus_learning_number(Mat preImg, int i) {
    int row = 40;
    int col = 30;
    Mat labels;
    Mat tmp;
    preImg.copyTo(tmp);
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            Rect rec(x * col, y * row, col, row);
            int cnt = connectedComponents(preImg(rec), labels);
            if (cnt >= 2) learning_number[i](rec) += 1;
        }
    }
}
void study_num_data_recog() {
    for (int i = 0; i < 10; i++) {
        learning_number[i] = Mat::zeros(400, 300, CV_8UC1);
        string fileName = "./numberdata/";
        fileName += to_string(i);
        for (int j = 1; j <= 50; j++) { //데이터 수가 늘어난다면 60이 위치한 값을 변경 
            string number_name = "";
            if (j < 10) number_name += ("0" + to_string(j));
            else number_name += ("" + to_string(j));
            number_name += "data.png";
            string final_path = fileName + number_name;
            Mat img = imread(final_path);
            Mat gray, resized_gray;
            cvtColor(img, gray, COLOR_BGR2GRAY);
            threshold(gray, gray, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
            resized_gray = resiz(gray);
            if (img.empty()) { cout << "image is empty pls check filename : " << final_path; }
            plus_learning_number(gray, i);
        }
    }
    for (int i = 0; i < 10; i++) {  //데이터셋이 충분하지 않아 25 이상이면 정답으로 처리 
        threshold(learning_number[i], learning_number[i], 15, 255, THRESH_BINARY);
    }
}
