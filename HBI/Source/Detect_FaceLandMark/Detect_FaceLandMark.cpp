//////////////////////////////////////////////////////////////////////////
//
// 이 화일은 함수 등록시 자동으로 생성된 프로젝트입니다.
//
// 사용자가 임으로 만든 경우, Project의 Setting...의 설정이 필요하므로,
//
// 이는 도움말의 '함수 작성법'을 참조 바랍니다.
//
//////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "MFCTestDialog.h"
#include "Detect_FaceLandMark.h"
#include "\dlib-19.4\dlib-19.4\dlib\image_processing\frontal_face_detector.h"
#include "\dlib-19.4\dlib-19.4\dlib\image_processing\render_face_detections.h"
#include "\dlib-19.4\dlib-19.4\dlib\image_processing.h"
#include "\dlib-19.4\dlib-19.4\dlib\gui_widgets.h"
#include "\dlib-19.4\dlib-19.4\dlib\image_io.h"
using namespace dlib;

// DLL을 만들기 위한 부분
static AFX_EXTENSION_MODULE MFC_EXT_DLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	TRACE0("USERIMAGETRANSFORM.DLL Initializing!\n");
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(MFC_EXT_DLL, hInstance))
			return 0;

		new CDynLinkLibrary(MFC_EXT_DLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("USERIMAGETRANSFORM.DLL Terminating!\n");
		// Terminate the library before destructors are called
		AfxTermExtensionModule(MFC_EXT_DLL);
	}

	return 1;   // ok
}

// 함수의 정의 부분
int CDECL Detect_FaceLandMark(KScRgbImage2d* sourceImg,KScRgbImage2d* destImg,int* facestyles)
{
// 전처리 /////////////////////////////////////////////////////////////////////


// 입력 버퍼의 자료 형태 검사.
	if (sourceImg->GetId() != KS_RGB_IMAGE_2D)
	{
		::MessageBox(NULL, "Input buffer type not suitable.",
			"convertRGBToUnit8", MB_OK);
		return FALSE;
	}

	// 출력 버퍼의 자료 형태 검사.
	if (destImg->GetId() != KS_RGB_IMAGE_2D)
	{
		::MessageBox(NULL, "Output buffer type not suitable.",
			"convertRGBToGray", MB_OK);
		return FALSE;
	}

	// 입력 버퍼의 할당 여부 검사.
	int dx = sourceImg->GetMainXSize();
	int dy = sourceImg->GetMainYSize();
	if (!dx || !dy)
	{
		::MessageBox(NULL, "Input buffer not allocated.",
			"convertRGBToGray", MB_OK);
		return FALSE;
	}

	// ROI 설정 ///////////////////////////////////////////////////////////////
	// 입력 버퍼에 ROI가 설정이 되어 있을 경우,
	if (sourceImg->IsRoi())
	{
		// 생략

		// ROI가 설정되면 나머지 처리는 ROI가 없는 경우와 동일하다.
	}
	// 입력 버퍼에 ROI가 설정이 안되어 있을 경우.
	else
	{
		// 입력 버퍼를 기준으로 실제 처리 영역 설정.
		dx = sourceImg->GetXSize();
		dy = sourceImg->GetYSize();

		// 출력 버퍼가 할당이 되지 않았거나 입력 버퍼와 크기가 다를 경우,
		// 출력 버퍼를 입력 버퍼와 동일한 크기로 재할당.
		if (dx != destImg->GetXSize() ||
			dy != destImg->GetYSize())
		{
			// ROI가 설정되어 있으면 Free()에서 ROI도 해제됨.
			destImg->Free();
			// Alloc()의 반환값 : 성공적이면 0, 실패이면 0이 아닌 에러 코드.
			if (destImg->Alloc(dx, dy))
			{
				::MessageBox(NULL, "Fail to allocate output buffer.",
					"convertRGBToGray", MB_OK);
				return FALSE;
			}
		}
		// 출력 버퍼의 크기가 입력 버퍼의 것과 동일할 경우,
		else
		{
			// 입출력 버퍼가 다를 경우, 0으로 초기화.
			// 초기화를 하지 않거나 사용자가 원하는 값으로 초기화해도 무방.

			destImg->InitTo(0);
		}
	}

// 실제 처리 부분 /////////////////////////////////////////////////////////////

	array2d<rgb_pixel> img;
	array2d<rgb_pixel> test;

	load_image(img, "v.bmp");
	load_image(test, "v.bmp");
	pyramid_up(img);
	pyramid_up(test);
	
	for (int i = 0; i < img.nr(); i++) {
		for (int j = 0; j < img.nc(); j++) {
			test[i][j] = rgb_pixel(255, 255, 255);
		}

	}
	frontal_face_detector detector = get_frontal_face_detector();
	shape_predictor pose_model;
	deserialize("shape_predictor_68_face_landmarks.dat") >> pose_model;

	std::vector<rectangle> faces;
	faces = detector(img);
	std::vector<full_object_detection> shapes;
	for (unsigned long i = 0; i < faces.size(); ++i)
	{
		// Landmark detection on full sized image
		full_object_detection shape = pose_model(img, faces[i]);
		shapes.push_back(shape);

		// Custom Face Render
	}

	std::vector<dlib::image_display::overlay_line> line = render_face_detections(shapes);

	destImg->Free();
	
	// Alloc()의 반환값 : 성공적이면 0, 실패이면 0이 아닌 에러 코드.
	destImg->Alloc(img.nc(), img.nr());

	KSdUint8** destR = destImg->Get2dArray(0);
	KSdUint8** destG = destImg->Get2dArray(1);
	KSdUint8** destB = destImg->Get2dArray(2);

	for (int i = 0; i < img.nr(); i++) {
		for (int j = 0; j < img.nc(); j++) {
			destR[i][j] = 0;
			destG[i][j] = 0;
			destB[i][j] = 0;
		}
	}

	for (int i = 0; i < 67; i++) {
		destR[shapes[0].part(i).y()][shapes[0].part(i).x()] = 255;
		destG[shapes[0].part(i).y()][shapes[0].part(i).x()] = 255;
		destB[shapes[0].part(i).y()][shapes[0].part(i).x()] = 255;
	}

	//Face Landmark index
	// 0 ~ 17 = 턱
	//18 ~ 22 = 왼쪽 눈썹
	//23 ~ 27 = 오른쪽 눈썹
	//28 ~ 36 = 코
	//37 ~ 42 = 왼쪽 눈
	//43 ~ 48 = 오른쪽 눈
	//49 ~ 68 = 입

	int FaceStyle[5];		// 0 : 턱, 1 : 눈썹, 2 : 눈, 3 : 미간, 4 : 입

	//턱 영역	-> 1. 원 형 / 2. 정사각 형 / 3. 직사각 형	/ 4. v 형 / 5. 달걀 형 
	//			   둥근 형인지 각진 형인지 먼저 판단 (중간 지점의 기울기의 변화량을 파악)

	int max_slope = 0;		//최대 기울기
	int chin_index;

	for (int i = 0; i < 18; i++) {
		if (max_slope < shapes[0].part(i).y()) {
			max_slope = shapes[0].part(i).y();
			chin_index = i;
		}
	}
	float slope = 0;
	for (int i = chin_index; i < chin_index + 4 ; i++) {
		float dy = -shapes[0].part(i + 1).y() + shapes[0].part(i).y();
		float dx = shapes[0].part(i + 1).x() - shapes[0].part(i).x();
		slope += dy / dx;
	}
	

	if (slope > 3.4) {		//v 형
		FaceStyle[0] = 4;
	}
	else if (slope > 2.24) {	//원형, 달걀형
		slope = (shapes[0].part(9).y() - shapes[0].part(17).y()) / (shapes[0].part(17).x() - shapes[0].part(0).x());
		if (slope > 1)
			FaceStyle[0] = 5;
		else
			FaceStyle[0] = 1;
	}
	else {			//직사각, 정사각형
		slope = (shapes[0].part(9).y() - shapes[0].part(17).y()) / (shapes[0].part(17).x() - shapes[0].part(0).x());
		if (slope > 1)
			FaceStyle[0] = 3;
		else
			FaceStyle[0] = 2;
	}

	//눈썹		-> 1. 초승달 형  / 2. 일자 형  / 3. 팔자 형 / 4. 칼 형 / 5. 용 형 / 6. 수양버들 형
	//			   최대 값이 어디에 있는지 비율을 찾음
	//			   최대 값이 앞일 경우 : 팔자, 중간인 경우 : 초승달, 수양버들 , 비교적 앞인 경우 : 용 형, 칼 형
	int max_height = 0;
	int low_height = 5000;
	int max_index = -1;
	int low_index = -1;
	int eyebrow[5];			//각 좌표에서 눈썹의 넓이를 위한 배열
	int count = 0;
	for (int i = 22; i < 27; i++) {
		count = 0;
		if (shapes[0].part(i).y() > max_height) {
			max_height = shapes[0].part(i).y();
			max_index = i;
		}
		if (shapes[0].part(i).y() < low_height) {
			low_height = shapes[0].part(i).y();
			low_index = i;
		}
	}
	KSdUint8** sourceR = sourceImg->Get2dArray(0);
	KSdUint8** sourceG = sourceImg->Get2dArray(1);
	KSdUint8** sourceB = sourceImg->Get2dArray(2);

	for (int i = 22; i < 27; i++) {
		count = 0;
		for (int j = 0; j < max_height - low_height; j++) {
			if (img[shapes[0].part(i).y()+j][shapes[0].part(i).x()].red +
				img[shapes[0].part(i).y()+j][shapes[0].part(i).x()].blue +
				img[shapes[0].part(i).y()+j][shapes[0].part(i).x()].green < 300) {
				count++;
			}
		}
		eyebrow[i - 22] = count;
	}

	switch (max_index) {
	case 22:
		FaceStyle[1] = 3;
		break;
	case 23:
		for (int i = 0; i < 4; i++) {
			if (abs(eyebrow[i] - eyebrow[i + 1]) > 10)
				FaceStyle[1] = 5;
			else
				FaceStyle[1] = 4;
		}
		break;
	case 24:
		for (int i = 0; i < 4; i++) {
			if (abs(eyebrow[i] - eyebrow[i + 1]) > 10)
				FaceStyle[1] = 1;
			else
				FaceStyle[1] = 6;
		}
		break;
	case 25:
		FaceStyle[1] = 2;
	case 26:
		FaceStyle[1] = 2;
		break;
	default:
		break;
	}


	//눈		-> 1. 용안 / 2. 원앙의 눈 / 3. 도화안 / 4. 삼백안 / 5. 사백안 
	// 3백안, 4백안, 2백안 인지 판단
	int sum = 0;
	int count_eye = 0;
	for (int i = 42; i < 48; i++) {
		sum += shapes[0].part(i).x();
	}
	for (int i = shapes[0].part(45).y(); i < shapes[0].part(47).y(); i++) {
		if (img[i][sum / 6].red + img[i][sum / 6].blue + img[i][sum / 6].green > 500) {
			count_eye++;
		}
	}

	switch (count_eye) {
	case 0:		//2백안
		sum = 0;
		for (int i = 42; i < 48; i++) {
			sum += shapes[0].part(i).y();
		}
		if (shapes[0].part(46).x() - shapes[0].part(45).x() < shapes[0].part(45).x() - shapes[0].part(44).x()) {
			FaceStyle[2] = 2;
		}
		else {
			if (shapes[0].part(45).y() > sum / 6) {		//눈꼬리가 올라간 경우 용안
				FaceStyle[2] = 1;
			}
			else {			//눈꼬리가 내려간 경우 도화안
				FaceStyle[2] = 3;
			}
		}
		break;
	case 1:		//3백안
		FaceStyle[2] = 4;
		break;
	case 2:		//4백안
		FaceStyle[2] = 5;
		break;
	}
	
	//미간	-> 1. 주름있는 미간 / 2. 좁은 미간 / 3. 넓은 미간
	count_eye = 0;
	for (int i = shapes[0].part(22).x(); i < shapes[0].part(23).x(); i++) {
		if (test[shapes[0].part(22).y()][i].red + test[shapes[0].part(22).y()][i].green + test[shapes[0].part(22).y()][i].blue < 100) {
			count_eye++;
		}
	}
	if (count_eye > 1) {
		FaceStyle[3] = 1;
	}
	else {
		if ((shapes[0].part(22).x() - shapes[0].part(21).x()) / (shapes[0].part(35).x() - shapes[0].part(31).x()) > 1)
			FaceStyle[3] = 3;
		else
			FaceStyle[3] = 2;
	}

	//입		-> 1. 아랫 입술이 두툼 / 2. 윗 입술이 두툼 / 3. 입술의 크기가 같은 / 4. 입꼬리가 올라간 / 5. 입꼬리가 내려간
	int up_size = shapes[0].part(62).y() - shapes[0].part(51).y();
	int down_size = shapes[0].part(58).y() - shapes[0].part(67).y();
	
	if (shapes[0].part(65).y() > shapes[0].part(55).y() - 10)		//입꼬리가 내려감
	{
		FaceStyle[4] = 5;
	}
	else if (shapes[0].part(65).y() < shapes[0].part(55).y() + 10){				//입꼬리가 올라감
		FaceStyle[4] = 4;
	}
	else {
		if (up_size > down_size)
			FaceStyle[4] = 2;
		else if (up_size < down_size)
			FaceStyle[4] = 1;
		else
			FaceStyle[4] = 3;
	}

// 후처리 /////////////////////////////////////////////////////////////////////
	facestyles = new int[5];
	for (int i = 0; i < 5; i++) {
		facestyles[i] = FaceStyle[i];
	}
	CMFCTestDialog dlg;
	dlg.set_faceData(facestyles);
	dlg.DoModal();
	return TRUE;
}

// 2 개 이상의 함수를 정의할 경우, 아래에 수동으로 삽입합니다.



