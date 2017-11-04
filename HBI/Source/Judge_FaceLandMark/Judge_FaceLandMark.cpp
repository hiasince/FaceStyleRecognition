//////////////////////////////////////////////////////////////////////////
//
// �� ȭ���� �Լ� ��Ͻ� �ڵ����� ������ ������Ʈ�Դϴ�.
//
// ����ڰ� ������ ���� ���, Project�� Setting...�� ������ �ʿ��ϹǷ�,
//
// �̴� ������ '�Լ� �ۼ���'�� ���� �ٶ��ϴ�.
//
//////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <ctime>
#include "Judge_FaceLandMark.h"

// DLL�� ����� ���� �κ�
BOOL WINAPI DllMain (HINSTANCE hDLL, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
		case DLL_PROCESS_ATTACH: break;
		case DLL_THREAD_ATTACH:  break;
		case DLL_THREAD_DETACH:  break;
		case DLL_PROCESS_DETACH: break;
	}

	return TRUE;
}

// �Լ��� ���� �κ�
/*int CDECL Judge_FaceLandMark(KScRgbImage2d* input_origin,KScRgbImage2d* input_landmark,KScScalarImage2dInt16* output)*/
int CDECL Judge_FaceLandMark(KScRgbImage2d* input_origin, KScRgbImage2d* input_landmark,KScRgbImage2d* output)
{
// ��ó�� /////////////////////////////////////////////////////////////////////

	if (input_landmark->GetId() != KS_RGB_IMAGE_2D)
	{
		::MessageBox(NULL, "Input buffer type not suitable.",
			"convertRGBToUnit8", MB_OK);
		return FALSE;
	}

	// ��� ������ �ڷ� ���� �˻�.
	if (input_origin->GetId() != KS_RGB_IMAGE_2D)
	{
		::MessageBox(NULL, "Output buffer type not suitable.",
			"convertRGBToGray", MB_OK);
		return FALSE;
	}

	if (output->GetId() != KS_RGB_IMAGE_2D)
	{
		::MessageBox(NULL, "Output buffer type not suitable.",
			"convertRGBToGray", MB_OK);
		return FALSE;
	}
	// �Է� ������ �Ҵ� ���� �˻�.
	int dx = input_origin->GetMainXSize();
	int dy = input_origin->GetMainYSize();
	if (!dx || !dy)
	{
		::MessageBox(NULL, "Input buffer not allocated.",
			"convertRGBToGray", MB_OK);
		return FALSE;
	}

	if (input_origin->IsRoi())
	{
		// ����

		// ROI�� �����Ǹ� ������ ó���� ROI�� ���� ���� �����ϴ�.
	}
	// �Է� ���ۿ� ROI�� ������ �ȵǾ� ���� ���.
	else
	{
		// �Է� ���۸� �������� ���� ó�� ���� ����.
		dx = input_origin->GetXSize();
		dy = input_origin->GetYSize();

		// ��� ���۰� �Ҵ��� ���� �ʾҰų� �Է� ���ۿ� ũ�Ⱑ �ٸ� ���,
		// ��� ���۸� �Է� ���ۿ� ������ ũ��� ���Ҵ�.
		if (dx != output->GetXSize() ||
			dy != output->GetYSize())
		{
			// ROI�� �����Ǿ� ������ Free()���� ROI�� ������.
			output->Free();
			// Alloc()�� ��ȯ�� : �������̸� 0, �����̸� 0�� �ƴ� ���� �ڵ�.
			if (output->Alloc(dx, dy))
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

			output->InitTo(0);
		}
	}
// ���� ó�� �κ� /////////////////////////////////////////////////////////////

	//Face Landmark index
	// 0 ~ 17 = ��
	//18 ~ 22 = ���� ����
	//23 ~ 27 = ������ ����
	//28 ~ 36 = ��
	//37 ~ 42 = ���� ��
	//43 ~ 48 = ������ ��
	//49 ~ 68 = ��

	//�� ����	-> �� �� / ���簢 �� / ���簢 ��	/ v �� / Ÿ�� �� 
	//			   �ձ� ������ ���� ������ ���� �Ǵ� (�߰� ������ ������ ��ȭ���� �ľ�)
	for (int i = 4; i < 14; i++) {
		int max_slope = 0;		//�ִ� ����

	}
	
	




// ��ó�� /////////////////////////////////////////////////////////////////////

	return TRUE;
}

// 2 �� �̻��� �Լ��� ������ ���, �Ʒ��� �������� �����մϴ�.



