
// MymailDlg.h : ͷ�ļ�
//

#pragma once
#include "sql.h"

// CMymailDlg �Ի���
class CMymailDlg : public CDialogEx
{
// ����
public:
	CMymailDlg(CWnd* pParent = NULL);	// ��׼���캯��
	
// �Ի�������
	enum { IDD = IDD_MYMAIL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit2();

	static void  CALLBACK TimerProc (HWND, UINT, UINT,   DWORD ) ;

	CString m_curUrl;
	int state;

	long m_newUrl;
	long m_newMail;
	long ini_email;
	HANDLE pThread;

	CString m_totalMail;
	afx_msg void OnBnClickedButton4();

	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton3();
	CString m_iniUrl;
};
