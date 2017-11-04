#pragma once

#include "resource.h"
// CMFCTestDialog 대화 상자입니다.

class CMFCTestDialog : public CDialog
{
	DECLARE_DYNAMIC(CMFCTestDialog)

public:
	CMFCTestDialog(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMFCTestDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	int* faceData;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedfacestyle();
	afx_msg void OnBnClickedanimal();
	afx_msg void OnBnClickedchange();
	afx_msg void OnBnClickedCancel();
	void set_int(int* data);
};
