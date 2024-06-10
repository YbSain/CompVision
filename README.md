# 필기체 인식

## OpenCV를 활용해 필기체 숫자를 인식하는 프로그램임

https://www.youtube.com/watch?v=OvCnUivV7Qs

### 진행상황

     Mat src(500, 1000, CV_8UC3, Scalar(255, 255, 255));    //원본 윈도우
     Point pt0ld;			//마우스 좌표
     void on_mouse(int event, int x, int y, int flags, void*);    //마우스 이벤트
     void box(Mat& src);		//박스
     void puttext(Mat& src);		//박스 글씨
     int countcontours(const Mat& savefile);	//외곽선 갯수
     void find2contours(Mat& savefile);						//외곽선2개를 갖는 수를 구분하는 함수
     Mat grayy(const Mat& savefile);                        //그레이전환 및 이진화_inv
	 vector<vector<Point>> convertContoursToPoints(const Mat& savefile);	//외곽선을 검출해서 2차원 백터에 저장 -> 다른 함수에서 계산을 최대한 줄이기 																			위함
	 string name;											//savethefile과 loadthefile 두 함수에서 사용하기위해 전역변수로 사용

[마우스 이벤트](#마우스-이벤트)    
[박스](#박스)    
[박스 글씨](#박스-글씨)   
[저장](#저장)   
[불러오기](#불러오기)   
[Clear](#Clear)   
[이진화](#이진화)     
[외곽선 갯수](#외곽선-갯수)   
[외곽선의 2차원 행렬](#외곽선의2차원행렬)   
[실행(숫자검출)](#실행(숫자검출))

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
    
	 Rect areas(500, 0, 250, 100);      //save
	 Rect areal(500, 100, 250, 100);    //load
	 Rect areac(500, 200, 250, 100);    //clear
	 Rect arear(500, 300, 250, 100);    //run
	 Rect areae(500, 400, 250, 100);    //exit
	 Rect areacon(750, 0, 250, 100);    //contour
	 Mat savefile;
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
_반복적으로 쓰인것은 생략_   
 [목차로 돌아가기](#진행상황)   
## 저장
 	 cout << "save" << endl;
	 cout << "파일이름 입력(.jpg포함): ";
	 cin >> name;
	 imwrite(name, savefile);
저장은 비교적 간단하게 사용했다
[목차로 돌아가기](#진행상황)   
## 불러오기
	 cout << "load" << endl;
 load_image:		//파일이름이 없을경우 다시 물어보기
	 cout << "불러올 파일 이름 입력(.jpg포함) : ";
	 cin >> name;
	 savefile = imread(name);
	 if (savefile.empty())
	 {
		 cerr << "Image Loaded Failed!" << endl;
		 goto load_image;		//load_image로 돌아가서 다시 시작
	 }
	 Mat roi = src(Rect(2, 2, 495, 490));	//원본이미지 src에서 검은선을 제외하고 위에서 선언한 savefile만큼의 Rect범위를roi로 앝은복사
	 savefile.copyTo(roi);		//원본이미지에서 roi즉 savefile 만큼의 범위에 맞게 불러오기가 된다.
[목차로 돌아가기](#진행상황)   
## Clear

	 cout << "clear" << endl;
	 savefile = (500, 500, CV_8UC3, Scalar(255, 255, 255));		//savefile을 500, 500만큼의 하얀 3채널 이미지로 초기화시킴
	 rectangle(src, Point(0, 0), Point(500, 500), Scalar(0, 0, 0), 2);	//기존src에서 (0, 0) 에서 (500, 500) 만큼의 Rect범위의 검은 line이 지워져서 																			다시 메꿔줌
[목차로 돌아가기](#진행상황)   
## 이진화

	 Mat gray;
	 cvtColor(savefile, gray, COLOR_BGR2GRAY);
	 threshold(gray, gray, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
	 morphologyEx(gray, gray, MORPH_CLOSE, Mat(15, 15, CV_8UC1), Point(-1, -1));
	 return gray;

  이진화를 INV로 진행시켜 외곽선 검출 할 때에 부작용이 없게하고, 모폴로지 연산을 통해서 오차율을 줄이고자 함     
 [목차로 돌아가기](#진행상황)   
## 외곽선 갯수

     int countcontours(const Mat& savefile)
     {
	 	 Mat binaryImage = grayy(savefile);		//위에서 만든 이진화 함수를 사용
	     vector<vector<Point>> contours;
	     findContours(binaryImage, contours, RETR_LIST, CHAIN_APPROX_NONE);
     
	     return contours.size();
     }

외곽선 갯수를 받기위해서 함수를 int로 만들었고 그에대한 2차원백터 생성후, findContours를 써주었다.    
return값, 외곽선 갯수    
 [목차로 돌아가기](#진행상황)     

## 외곽선의 2차원행렬

![image](https://github.com/YbSain/CompVision/assets/108385276/56a0bcbb-73fb-4a26-94f2-a1d574091bab)

push_back과 1차원행렬을 이용해서 2차원행렬값에 대입한 뒤, return 해주었다.

[목차로 돌아가기](#진행상황)     
## 실행(숫자검출)
	 int numContours = countcontours(savefile);					//run
	 cout << "run" << endl;
	 if (numContours == 3) {		//외곽선을 3개 갖는 숫자는 8밖에 없기떄문에 8로 지정함
		 cout << "8" << endl;
	 }
	 if (numContours == 2) {
		 find2contours(savefile);	//외곽선 2개 검출된것중, 0, 6, 9를 출력함 (4도 추후 나올 예정)
	 }
 	 if (numContours == 1) {
		 cout << "1, 2, 3, 4, 5, 7" << endl;	//외곽선 1개 검출될때 실행
	 }

[목차로 돌아가기](#진행상황)    
## 2개짜리 외곽선 0, 6, 9 검출

![image](https://github.com/YbSain/CompVision/assets/108385276/e98d3ffc-57d1-4adb-82c1-ecf99c177f1f)

위 사진과 같이 __points__ 로 2차원행렬로 외곽선을 받아옴    
### 변수들의 각자 역할
	 int count = 0;						//0을 기준으로 count++ count--를 한뒤에 그 값에 해당함에 따라 6과 9를 출력하기 위함(출력 후 0으로 초기화)
  	 int largestIndex, smallIndex;		//둘다 0으로 초기화 한뒤, 몇번때 외곽선일때 최댓값과 최솟값을 갖는지 그 값을 받기 위함
	 double largestArea, smallArea(numeric_limits<double>::infinity();	//largestArea는 0.0으로 smallArea는 한계값으로 받아서 넓이를 받기 위함
  	 double area = 0.0;					//검출된 외곽선의 넓이를 구함
### 넓이와 최댓값, 최솟값 구하기
![image](https://github.com/YbSain/CompVision/assets/108385276/66f23f04-6514-4baf-a9e6-08fd9c0908b9)
위 반복문을 사용해서 최댓값과 최솟값을 지정(함수자체가 외곽선 2개일때 실행되기때문에 두개의 값이 같게 나오지않음-변수는 있을지도)   
### 구해진 최솟값과, 최댓값의 비율로 0 뽑아내기
![image](https://github.com/YbSain/CompVision/assets/108385276/3e3729bd-fe61-4c6d-bba4-4b1d5f4780a6)
글씨를 8픽셀로 적용했고 6과 9과다르게 0의 외곽선은 서로 큰 차이를 보기 힘들기 때문에 비율을 0.7이상일 경우 0으로 지정했다.   
### 무게중심을 구한 뒤, 바운딩 박스의 중점과  높이 차이를 비교하여 중점보다 높을경우 9, 낮을경우 6을 출력
![image](https://github.com/YbSain/CompVision/assets/108385276/d7a0e3a5-17e8-4a8f-9f94-2750c02f6ef2)
중간에 있는boundingBoy와 circle, rectange imshow는 추후 지울예정
__이곳에서 무게중심과 중점 기준으로 x좌표를 비교해서 왼쪽일경우 4로 지정까지 해서 구분지을 예정__

[목차로 돌아가기](#진행상황)     
