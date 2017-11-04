//////////////////////////////////////////////////////////////////////////
//
// �� ȭ���� �Լ� ��Ͻ� �ڵ����� ������ ������Ʈ�Դϴ�.
//
// ����ڰ� ������ ���� ���, Project�� Setting...�� ������ �ʿ��ϹǷ�,
//
// �̴� ������ '�Լ� �ۼ���'�� ���� �ٶ��ϴ�.
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

// DLL�� ����� ���� �κ�
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

// �Լ��� ���� �κ�
int CDECL Detect_FaceLandMark(KScRgbImage2d* sourceImg,KScRgbImage2d* destImg,int* facestyles)
{
// ��ó�� /////////////////////////////////////////////////////////////////////


// �Է� ������ �ڷ� ���� �˻�.
	if (sourceImg->GetId() != KS_RGB_IMAGE_2D)
	{
		::MessageBox(NULL, "Input buffer type not suitable.",
			"convertRGBToUnit8", MB_OK);
		return FALSE;
	}

	// ��� ������ �ڷ� ���� �˻�.
	if (destImg->GetId() != KS_RGB_IMAGE_2D)
	{
		::MessageBox(NULL, "Output buffer type not suitable.",
			"convertRGBToGray", MB_OK);
		return FALSE;
	}

	// �Է� ������ �Ҵ� ���� �˻�.
	int dx = sourceImg->GetMainXSize();
	int dy = sourceImg->GetMainYSize();
	if (!dx || !dy)
	{
		::MessageBox(NULL, "Input buffer not allocated.",
			"convertRGBToGray", MB_OK);
		return FALSE;
	}

	// ROI ���� ///////////////////////////////////////////////////////////////
	// �Է� ���ۿ� ROI�� ������ �Ǿ� ���� ���,
	if (sourceImg->IsRoi())
	{
		// ����

		// ROI�� �����Ǹ� ������ ó���� ROI�� ���� ���� �����ϴ�.
	}
	// �Է� ���ۿ� ROI�� ������ �ȵǾ� ���� ���.
	else
	{
		// �Է� ���۸� �������� ���� ó�� ���� ����.
		dx = sourceImg->GetXSize();
		dy = sourceImg->GetYSize();

		// ��� ���۰� �Ҵ��� ���� �ʾҰų� �Է� ���ۿ� ũ�Ⱑ �ٸ� ���,
		// ��� ���۸� �Է� ���ۿ� ������ ũ��� ���Ҵ�.
		if (dx != destImg->GetXSize() ||
			dy != destImg->GetYSize())
		{
			// ROI�� �����Ǿ� ������ Free()���� ROI�� ������.
			destImg->Free();
			// Alloc()�� ��ȯ�� : �������̸� 0, �����̸� 0�� �ƴ� ���� �ڵ�.
			if (destImg->Alloc(dx, dy))
			{
				::MessageBox(NULL, "Fail to allocate output buffer.",
					"convertRGBToGray", MB_OK);
				return FALSE;
			}
		}
		// ��� ������ ũ�Ⱑ �Է� ������ �Ͱ� ������ ���,
		else
		{
			// ����� ���۰� �ٸ� ���, 0���� �ʱ�ȭ.
			// �ʱ�ȭ�� ���� �ʰų� ����ڰ� ���ϴ� ������ �ʱ�ȭ�ص� ����.

			destImg->InitTo(0);
		}
	}

// ���� ó�� �κ� /////////////////////////////////////////////////////////////

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
	
	// Alloc()�� ��ȯ�� : �������̸� 0, �����̸� 0�� �ƴ� ���� �ڵ�.
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
	// 0 ~ 17 = ��
	//18 ~ 22 = ���� ����
	//23 ~ 27 = ������ ����
	//28 ~ 36 = ��
	//37 ~ 42 = ���� ��
	//43 ~ 48 = ������ ��
	//49 ~ 68 = ��

	int FaceStyle[5];		// 0 : ��, 1 : ����, 2 : ��, 3 : �̰�, 4 : ��

	//�� ����	-> 1. �� �� / 2. ���簢 �� / 3. ���簢 ��	/ 4. v �� / 5. �ް� �� 
	//			   �ձ� ������ ���� ������ ���� �Ǵ� (�߰� ������ ������ ��ȭ���� �ľ�)

	int max_slope = 0;		//�ִ� ����
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
	

	if (slope > 3.4) {		//v ��
		FaceStyle[0] = 4;
	}
	else if (slope > 2.24) {	//����, �ް���
		slope = (shapes[0].part(9).y() - shapes[0].part(17).y()) / (shapes[0].part(17).x() - shapes[0].part(0).x());
		if (slope > 1)
			FaceStyle[0] = 5;
		else
			FaceStyle[0] = 1;
	}
	else {			//���簢, ���簢��
		slope = (shapes[0].part(9).y() - shapes[0].part(17).y()) / (shapes[0].part(17).x() - shapes[0].part(0).x());
		if (slope > 1)
			FaceStyle[0] = 3;
		else
			FaceStyle[0] = 2;
	}

	//����		-> 1. �ʽ´� ��  / 2. ���� ��  / 3. ���� �� / 4. Į �� / 5. �� �� / 6. ������� ��
	//			   �ִ� ���� ��� �ִ��� ������ ã��
	//			   �ִ� ���� ���� ��� : ����, �߰��� ��� : �ʽ´�, ������� , ���� ���� ��� : �� ��, Į ��
	int max_height = 0;
	int low_height = 5000;
	int max_index = -1;
	int low_index = -1;
	int eyebrow[5];			//�� ��ǥ���� ������ ���̸� ���� �迭
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


	//��		-> 1. ��� / 2. ������ �� / 3. ��ȭ�� / 4. ���� / 5. ���� 
	// 3���, 4���, 2��� ���� �Ǵ�
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
	case 0:		//2���
		sum = 0;
		for (int i = 42; i < 48; i++) {
			sum += shapes[0].part(i).y();
		}
		if (shapes[0].part(46).x() - shapes[0].part(45).x() < shapes[0].part(45).x() - shapes[0].part(44).x()) {
			FaceStyle[2] = 2;
		}
		else {
			if (shapes[0].part(45).y() > sum / 6) {		//�������� �ö� ��� ���
				FaceStyle[2] = 1;
			}
			else {			//�������� ������ ��� ��ȭ��
				FaceStyle[2] = 3;
			}
		}
		break;
	case 1:		//3���
		FaceStyle[2] = 4;
		break;
	case 2:		//4���
		FaceStyle[2] = 5;
		break;
	}
	
	//�̰�	-> 1. �ָ��ִ� �̰� / 2. ���� �̰� / 3. ���� �̰�
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

	//��		-> 1. �Ʒ� �Լ��� ���� / 2. �� �Լ��� ���� / 3. �Լ��� ũ�Ⱑ ���� / 4. �Բ����� �ö� / 5. �Բ����� ������
	int up_size = shapes[0].part(62).y() - shapes[0].part(51).y();
	int down_size = shapes[0].part(58).y() - shapes[0].part(67).y();
	
	if (shapes[0].part(65).y() > shapes[0].part(55).y() - 10)		//�Բ����� ������
	{
		FaceStyle[4] = 5;
	}
	else if (shapes[0].part(65).y() < shapes[0].part(55).y() + 10){				//�Բ����� �ö�
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

// ��ó�� /////////////////////////////////////////////////////////////////////
	facestyles = new int[5];
	for (int i = 0; i < 5; i++) {
		facestyles[i] = FaceStyle[i];
	}
	CMFCTestDialog dlg;
	dlg.set_faceData(facestyles);
	dlg.DoModal();
	return TRUE;
}

// 2 �� �̻��� �Լ��� ������ ���, �Ʒ��� �������� �����մϴ�.



