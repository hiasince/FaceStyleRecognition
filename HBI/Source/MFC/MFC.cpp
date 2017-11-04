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
#include "MFC.h"
#include "MFCTestDialog.h"

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
int CDECL MFC(int* par0)
{
// 전처리 /////////////////////////////////////////////////////////////////////
	
    // 입력 버퍼 자료 형태 검사.

    // 출력 버퍼 자료 형태 검사.
	
    // 입력 버퍼 할당 여부 검사.

	// 출력 버퍼 할당 여부 검사.

// 실제 처리 부분 /////////////////////////////////////////////////////////////
	
	// 이 곳에 함수의 실제 처리 코드를 삽입합니다.

// 후처리 /////////////////////////////////////////////////////////////////////
	CMFCTestDialog dlg;
	dlg.set_int(par0);
	dlg.DoModal();
	
	return TRUE;
}

// 2 개 이상의 함수를 정의할 경우, 아래에 수동으로 삽입합니다.




