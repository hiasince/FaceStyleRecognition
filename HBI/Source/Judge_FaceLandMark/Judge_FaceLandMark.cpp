//////////////////////////////////////////////////////////////////////////
//
// 이 화일은 함수 등록시 자동으로 생성된 프로젝트입니다.
//
// 사용자가 임으로 만든 경우, Project의 Setting...의 설정이 필요하므로,
//
// 이는 도움말의 '함수 작성법'을 참조 바랍니다.
//
//////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <ctime>
#include "Judge_FaceLandMark.h"

// DLL을 만들기 위한 부분
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

// 함수의 정의 부분
/*int CDECL Judge_FaceLandMark(KScRgbImage2d* input_origin,KScRgbImage2d* input_landmark,KScScalarImage2dInt16* output)*/
int CDECL Judge_FaceLandMark(KScRgbImage2d* input_origin, KScRgbImage2d* input_landmark,KScRgbImage2d* output)
{
// 전처리 /////////////////////////////////////////////////////////////////////

	if (input_landmark->GetId() != KS_RGB_IMAGE_2D)
	{
		::MessageBox(NULL, "Input buffer type not suitable.",
			"convertRGBToUnit8", MB_OK);
		return FALSE;
	}

	// 출력 버퍼의 자료 형태 검사.
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
	// 입력 버퍼의 할당 여부 검사.
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
		// 생략

		// ROI가 설정되면 나머지 처리는 ROI가 없는 경우와 동일하다.
	}
	// 입력 버퍼에 ROI가 설정이 안되어 있을 경우.
	else
	{
		// 입력 버퍼를 기준으로 실제 처리 영역 설정.
		dx = input_origin->GetXSize();
		dy = input_origin->GetYSize();

		// 출력 버퍼가 할당이 되지 않았거나 입력 버퍼와 크기가 다를 경우,
		// 출력 버퍼를 입력 버퍼와 동일한 크기로 재할당.
		if (dx != output->GetXSize() ||
			dy != output->GetYSize())
		{
			// ROI가 설정되어 있으면 Free()에서 ROI도 해제됨.
			output->Free();
			// Alloc()의 반환값 : 성공적이면 0, 실패이면 0이 아닌 에러 코드.
			if (output->Alloc(dx, dy))
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

			output->InitTo(0);
		}
	}
// 실제 처리 부분 /////////////////////////////////////////////////////////////

	//Face Landmark index
	// 0 ~ 17 = 턱
	//18 ~ 22 = 왼쪽 눈썹
	//23 ~ 27 = 오른쪽 눈썹
	//28 ~ 36 = 코
	//37 ~ 42 = 왼쪽 눈
	//43 ~ 48 = 오른쪽 눈
	//49 ~ 68 = 입

	//턱 영역	-> 원 형 / 정사각 형 / 직사각 형	/ v 형 / 타원 형 
	//			   둥근 형인지 각진 형인지 먼저 판단 (중간 지점의 기울기의 변화량을 파악)
	for (int i = 4; i < 14; i++) {
		int max_slope = 0;		//최대 기울기

	}
	
	




// 후처리 /////////////////////////////////////////////////////////////////////

	return TRUE;
}

// 2 개 이상의 함수를 정의할 경우, 아래에 수동으로 삽입합니다.



