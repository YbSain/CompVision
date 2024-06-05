# 필기체 인식

## OpenCV를 활용해 필기체 숫자를 인식하는 프로그램임

https://www.youtube.com/watch?v=OvCnUivV7Qs

### 진행상황

     Mat src(500, 1000, CV_8UC3, Scalar(255, 255, 255));    //원본 윈도우
     Point pt0ld;                                            //마우스 좌표
     void on_mouse(int event, int x, int y, int flags, void*);    //마우스 이벤트
     void box(Mat& src);                                    //박스
     void puttext(Mat& src);                                //박스 글씨
     int countcontours(const Mat& savefile);                //외곽선 갯수
     Mat grayy(const Mat& savefile);                        //그레이전환 및 이진화_inv

[마우스 이벤트](#마우스-이벤트)
[박스](#박스)
[박스 글씨](#박스-글씨)
[외곽선 갯수](#외곽선-갯수)
[이진화](#이진화)

## 메인함수

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

메인 함수는 위의 함수들만 호출시킴
 [목차로 돌아가기](#진행상황)
## 마우스 이벤트
    
	 Rect areas(500, 0, 250, 100);        //save
	 Rect areal(500, 100, 250, 100);       //load
	 Rect areac(500, 200, 250, 100);    //clear
	 Rect arear(500, 300, 250, 100);    //run
	 Rect areae(500, 400, 250, 100);    //exit
	 Rect areacon(750, 0, 250, 100);    //contour
	 Mat savefile;
	 string name;
	 savefile = src(Rect(0, 0, 500, 500));
     
일단 마우스 이벤트로 save, load, clear, run, exit, contour 칸을 누를때 효과를 봐야 하기 때문에 Rect로 구간을 다 정해둠.

     case EVENT_MOUSEMOVE:
	     if (flags & EVENT_FLAG_LBUTTON) {
		     line(src(Rect(0, 0, 500, 500)), pt0ld, Point(x, y), Scalar(0, 0, 0), 8);
		     imshow("src", src);
		     pt0ld = Point(x, y);
	     }
	     break;

**flags & EVENT_FLAG_LBUTTON**을 사용해서 line을 src에서 0, 0, 500, 500부분만 칠해지게 하고 그 영상을 얕은 복사를 해서 그대로 반영시킨다.

추가로 마지막에 pt0ld에 마지막으로 마우스이벤트가 받은Point(x, y) 위치에 두는 이유는 line을 떼었다가 다시 그릴때 해당 위치부터 시작하게 하기 위함
 [목차로 돌아가기](#진행상황)
## 박스

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

박스는 (500, 0)좌표마다 일일이 가로선을 그어주고 세로선을 하나씩 그어 현재 모양이 나오게 line을 활용함
 [목차로 돌아가기](#진행상황)
## 박스 글씨 

     Mat save;
     save = src(Rect(500, 0, 250, 100));
     const String texts = "Save";
     int fontFace = FONT_HERSHEY_SIMPLEX;
     double fontScale = 2.0;
     int thickness = 2;
     
     Size sizeImgS = save.size();
     Size sizeTextS = getTextSize(texts, fontFace, fontScale, thickness, 0);
     Point saveorg((sizeImgS.width - sizeTextS.width) / 2, (sizeImgS.height + sizeTextS.height) / 2);
     
     
     putText(save, texts, saveorg, fontFace, fontScale, Scalar(0, 0, 0), thickness);

**Mat save**로 src에서 가져올 해당 이미지를 지정하고, "Save" 문자열을 넣기위해 const String을 사용했으며 미리 상수값 폰트, 실수값 폰트스케일, 굵기를 지정해주었다.

**Size**형태로 이미지와 문자의 크기를 받고, 길이를 적절히 계산하여 이미지 칸 내부 중앙좌표에 위치 할 수 있게 하였다.
 [목차로 돌아가기](#진행상황)
## 외곽선 갯수

     int countcontours(const Mat& savefile)
     {
	     vector<vector<Point>> contours;
	     findContours(grayy(savefile), contours, RETR_LIST, CHAIN_APPROX_NONE);
     
	     return contours.size();
     }

외곽선 갯수를 받기위해서 함수를 int로 만들었고 그에대한 2차원백터 생성후, findContours를 써주었다.
return값, 외곽선 갯수
 [목차로 돌아가기](#진행상황)
## 이진화

	 Mat gray;
	 cvtColor(savefile, gray, COLOR_BGR2GRAY);
	 threshold(gray, gray, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
 
	 Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	 erode(gray, gray, element);
	 dilate(gray, gray, element);

	 return gray;

  이진화를 INV로 진행시켜 외곽선 검출 할 때에 부작용이 없게하고, 모폴로지 연산을 통해서 오차율을 줄이고자 함
 [목차로 돌아가기](#진행상황)
