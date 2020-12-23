
// kuwoMusicPlayDlg.h : 头文件
//

#pragma once
#include <mmsystem.h>
#include <Digitalv.h>
#include "afxcmn.h"
#include "afxwin.h"
#pragma comment(lib,"winmm.lib")

// CkuwoMusicPlayDlg 对话框
class CkuwoMusicPlayDlg : public CDialogEx
{
// 构造
public:
	CkuwoMusicPlayDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_KUWOMUSICPLAY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
