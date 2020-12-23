
// kuwoMusicPlayDlg.h : ͷ�ļ�
//

#pragma once
#include <mmsystem.h>
#include <Digitalv.h>
#include "afxcmn.h"
#include "afxwin.h"
#pragma comment(lib,"winmm.lib")

// CkuwoMusicPlayDlg �Ի���
class CkuwoMusicPlayDlg : public CDialogEx
{
// ����
public:
	CkuwoMusicPlayDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_KUWOMUSICPLAY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	MCIDEVICEID m_DeviceID;
	
	afx_msg void OnBnClickedBtnOpen();
	afx_msg void OnBnClickedBtnPlay();
	afx_msg void OnBnClickedBtnPause();
	afx_msg void OnBnClickedBtnStop();
	CSliderCtrl m_slider;
	int m_nVolume;
	afx_msg void OnCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedClose();
	CListBox m_list;
	CListBox m_listitems;
	afx_msg void OnBnClickedBtnBefore();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedBtnPlayitem();
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnBnClickedBtnNext();
};
