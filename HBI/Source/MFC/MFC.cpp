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
#include "MFC.h"
#include "MFCTestDialog.h"

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
int CDECL MFC(int* par0)
{
// ��ó�� /////////////////////////////////////////////////////////////////////
	
    // �Է� ���� �ڷ� ���� �˻�.

    // ��� ���� �ڷ� ���� �˻�.
	
    // �Է� ���� �Ҵ� ���� �˻�.

	// ��� ���� �Ҵ� ���� �˻�.

// ���� ó�� �κ� /////////////////////////////////////////////////////////////
	
	// �� ���� �Լ��� ���� ó�� �ڵ带 �����մϴ�.

// ��ó�� /////////////////////////////////////////////////////////////////////
	CMFCTestDialog dlg;
	dlg.set_int(par0);
	dlg.DoModal();
	
	return TRUE;
}

// 2 �� �̻��� �Լ��� ������ ���, �Ʒ��� �������� �����մϴ�.




