#pragma once

#include "resource.h"
// CMFCTestDialog ��ȭ �����Դϴ�.

class CMFCTestDialog : public CDialog
{
	DECLARE_DYNAMIC(CMFCTestDialog)

public:
	CMFCTestDialog(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMFCTestDialog();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	int* faceData;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedfacestyle();
	afx_msg void OnBnClickedanimal();
	afx_msg void OnBnClickedchange();
	afx_msg void OnBnClickedCancel();
	void set_int(int* data);
};
