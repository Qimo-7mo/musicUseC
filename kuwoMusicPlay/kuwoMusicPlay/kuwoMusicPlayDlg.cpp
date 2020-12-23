
// kuwoMusicPlayDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "kuwoMusicPlay.h"
#include "kuwoMusicPlayDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CkuwoMusicPlayDlg 对话框



MCI_OPEN_PARMS micOpenParms;
CkuwoMusicPlayDlg::CkuwoMusicPlayDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CkuwoMusicPlayDlg::IDD, pParent)
	, m_nVolume(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_DeviceID = 0;
}

void CkuwoMusicPlayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_slider);
	DDX_Text(pDX, IDC_EDIT1, m_nVolume);

	DDX_Control(pDX, IDC_LIST1, m_listitems);
}

BEGIN_MESSAGE_MAP(CkuwoMusicPlayDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPEN, &CkuwoMusicPlayDlg::OnBnClickedBtnOpen)
	ON_BN_CLICKED(IDC_BTN_PLAY, &CkuwoMusicPlayDlg::OnBnClickedBtnPlay)
	ON_BN_CLICKED(IDC_BTN_PAUSE, &CkuwoMusicPlayDlg::OnBnClickedBtnPause)
	ON_BN_CLICKED(IDC_BTN_STOP, &CkuwoMusicPlayDlg::OnBnClickedBtnStop)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CkuwoMusicPlayDlg::OnCustomdrawSlider1)
	ON_WM_NCHITTEST()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_CLOSE, &CkuwoMusicPlayDlg::OnBnClickedClose)
	ON_BN_CLICKED(IDC_BTN_BEFORE, &CkuwoMusicPlayDlg::OnBnClickedBtnBefore)
	ON_BN_CLICKED(IDC_BUTTON3, &CkuwoMusicPlayDlg::OnBnClickedButton3)
	//ON_BN_CLICKED(IDC_BTN_PLAYITEM, &CkuwoMusicPlayDlg::OnBnClickedBtnPlayitem)
	ON_LBN_SELCHANGE(IDC_LIST1, &CkuwoMusicPlayDlg::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_BTN_NEXT, &CkuwoMusicPlayDlg::OnBnClickedBtnNext)
END_MESSAGE_MAP()


// CkuwoMusicPlayDlg 消息处理程序

//初始化
BOOL CkuwoMusicPlayDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//音量滑动范围
	m_slider.SetRange(0,1000);
	m_slider.SetPos(1000);//设置音量最大
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

//样式设置
void CkuwoMusicPlayDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		//获取客户区大小
		CRect rect,captionRect;
		GetClientRect(&rect);
		captionRect = rect;
		captionRect.bottom = 30;
		dc.FillSolidRect(&captionRect,RGB(204,204,204));
		CFont font;
		font.CreatePointFont(120,L"黑体");
		dc.SelectObject(&font);
		dc.TextOutW(20,7,L"酷我音乐播放器");
		//加图片
		CBitmap bmp;
		bmp.LoadBitmap(IDB_BITMAP3);
		//获取图片宽高
		BITMAP logBmp;//图片信息
		bmp.GetBitmap(&logBmp);//获取图片信息
		//创建内存DC
		CDC memDC;
		memDC.CreateCompatibleDC(&dc);
		memDC.SelectObject(&bmp);

		//贴图
		//dc.BitBlt(0,0,rect.Width(),rect.Height(),&memDC,0,0,SRCCOPY);
		dc.SetStretchBltMode(HALFTONE);
		//拉伸贴图
		dc.StretchBlt(0,30,rect.Width(),rect.Height(),&memDC,0,0,logBmp.bmWidth,logBmp.bmHeight,SRCCOPY);

		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CkuwoMusicPlayDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//打开音乐
void CkuwoMusicPlayDlg::OnBnClickedBtnOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	//MessageBox(L"点击了",L"提示",MB_OK);//L:采用宽字符串编辑
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,L"MP3文件(*.mp3)|*.mp3|WMA文件(*.wma)|*.wma|WAV文件(*.wav)|*.wav|所有文件(*.*)|*.*||");
	//打开对话框并筛选文件类型
	if(IDCANCEL == dlg.DoModal()){
		return;//用户若点了取消，则不进行任何操作
	}else{
		//先停止当前的音乐
		OnBnClickedBtnStop();
		//如果用户打开某个音乐文件，就把路径加入到m_listitems中
		CString strMusicPath = dlg.GetPathName();
		m_listitems.InsertString(m_listitems.GetCount(), strMusicPath);
		m_listitems.SetCurSel(m_listitems.GetCount() - 1);//返回最后一个索引值

		//获取路径
		CString strMusicFile = dlg.GetPathName();
		//MessageBox(strMusicFile);//弹出路径信息

		//打开
		//MCI_OPEN_PARMS micOpenParms;
		micOpenParms.lpstrElementName = strMusicFile;//把目标歌曲存到一个变量中
		MCIERROR mciErro = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT|MCI_WAIT,(DWORD)&micOpenParms);
		//当打开错误时，执行if中的指令
		if(mciErro){
			//获取错误信息
			wchar_t szErrorMsg[256];
			mciGetErrorString(mciErro,szErrorMsg,256);
			MessageBox(szErrorMsg,L"酷我音乐播放器");
			return;
		}
		//打开成功后，继续
		m_DeviceID = micOpenParms.wDeviceID;
		//打开歌曲路径后，可自动播放（调用播放歌曲的函数）
		OnBnClickedBtnPlay();
	}

		
	

	
	
}

//播放歌曲
void CkuwoMusicPlayDlg::OnBnClickedBtnPlay()
{
	// TODO: 在此添加控件通知处理程序代码
	MCI_PLAY_PARMS mciPlayParms;
	mciPlayParms.dwCallback = NULL;
	mciPlayParms.dwFrom = 0;//从头开始播放歌曲
	//播放命令：播放开始位置，可调节音量
	mciSendCommand(m_DeviceID, MCI_PLAY, MCI_FROM | MCI_NOTIFY,(DWORD)&mciPlayParms);//播放一次
	
}

//暂停/继续播放
void CkuwoMusicPlayDlg::OnBnClickedBtnPause()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	GetDlgItemText(IDC_BTN_PAUSE, str);//获取文本
	//判断是否暂停
	if(str == L"暂停"){
		//发送暂停命令
		mciSendCommand(m_DeviceID, MCI_PAUSE, 0 , 0);
		//修改文本：暂停===》继续
		SetDlgItemText(IDC_BTN_PAUSE, L"继续");
	}else if(str == "继续"){
		//发送恢复命令
		mciSendCommand(m_DeviceID, MCI_RESUME, 0 , 0);
		//修改文本：继续===》暂停
		SetDlgItemText(IDC_BTN_PAUSE, L"暂停");
	}
}

//停止
void CkuwoMusicPlayDlg::OnBnClickedBtnStop()
{
	// TODO: 在此添加控件通知处理程序代码
	//发送停止命令
	mciSendCommand(m_DeviceID, MCI_STOP, 0, 0);
	mciSendCommand(m_DeviceID, MCI_CLOSE, 0, 0);
}

//音量调节
void CkuwoMusicPlayDlg::OnCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	//获取当前滑动控件位置
	m_nVolume = m_slider.GetPos()/10;
	UpdateData(FALSE);//刷新显示数值

	//发送命令(调节音量)
	MCI_DGV_SETAUDIO_PARMS mciSetVolume;
	mciSetVolume.dwItem = MCI_DGV_SETAUDIO_VOLUME;
	mciSetVolume.dwValue = m_slider.GetPos();//同步音量值并显示在编辑框中
	mciSendCommand(m_DeviceID, MCI_SETAUDIO,MCI_DGV_SETAUDIO_VALUE|MCI_DGV_SETAUDIO_ITEM,(DWORD)&mciSetVolume);//设置音量

	*pResult = 0;
}

//样式设置
LRESULT CkuwoMusicPlayDlg::OnNcHitTest(CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	UINT nHitTest = CDialogEx::OnNcHitTest(point);
	//获取客户去大小
	CRect rect;
	GetClientRect(&rect);
	rect.bottom = 30;
	//判断鼠标点的位置在不在标题区间
	ScreenToClient(&point);//转换屏幕坐标系
	if(rect.PtInRect(point)){
		if(nHitTest == HTCLIENT)
		nHitTest = HTCAPTION;
	}
	
	return nHitTest;
}

//快速加载
BOOL CkuwoMusicPlayDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//return CDialogEx::OnEraseBkgnd(pDC);
	return TRUE;
}

//关闭对话框
void CkuwoMusicPlayDlg::OnBnClickedClose()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(IDOK);
}


//上一曲
void CkuwoMusicPlayDlg::OnBnClickedBtnBefore()
{
	// TODO: 在此添加控件通知处理程序代码
	int index;
	index = m_listitems.GetCurSel();
	
	index = index - 1;
	
	if (index < 0)
	{
		//MessageBox(TEXT("已经是第一首歌"));
		return;
	}
	m_listitems.SetCurSel(index);//指向当前对象
	mciSendCommand(m_DeviceID, MCI_CLOSE, 0, 0);
	//打开

	CString strPath2;
	m_listitems.GetText(index,strPath2);
	micOpenParms.lpstrElementName = strPath2;//把目标歌曲存到一个变量中
	MCIERROR mciError = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_WAIT, (DWORD)&micOpenParms);
	if (mciError)
	{
		//获取错误信息
		wchar_t szError[256];//专门用来存错误信息
		mciGetErrorString(mciError, szError, 256);
		MessageBox(szError, TEXT("音乐播放器"), MB_ICONERROR);
		return;
	}
	//MessageBox(strPath2);
	//打开成功后，继续
	m_DeviceID = micOpenParms.wDeviceID;
	//打开歌曲路径后，可自动播放（调用播放歌曲的函数）
	OnBnClickedBtnPlay();

	//MessageBox(L"heihei");
	
}


//删除音乐
void CkuwoMusicPlayDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_listitems.DeleteString(m_listitems.GetCurSel());
	OnBnClickedBtnStop();
}


//双击播放
void CkuwoMusicPlayDlg::OnLbnSelchangeList1()
{
	// TODO: 在此添加控件通知处理程序代码
	int index;
	index = m_listitems.GetCurSel();//获取当前对象所索引值

	m_listitems.SetCurSel(index);//指向当前对象
	mciSendCommand(m_DeviceID, MCI_CLOSE, 0, 0);
	
	CString strPath2;
	m_listitems.GetText(index,strPath2);
	micOpenParms.lpstrElementName = strPath2;//把目标歌曲存到一个变量中
	MCIERROR mciError = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_WAIT, (DWORD)&micOpenParms);
	if (mciError)
	{
		//获取错误信息
		wchar_t szError[256];//专门用来存错误信息
		mciGetErrorString(mciError, szError, 256);
		MessageBox(szError, TEXT("音乐播放器"), MB_ICONERROR);
		return;
	}
	//MessageBox(strPath2);
	//打开成功后，继续
	m_DeviceID = micOpenParms.wDeviceID;
	//打开歌曲路径后，可自动播放（调用播放歌曲的函数）
	OnBnClickedBtnPlay();

	//MessageBox(L"heihei");
	
}

//下一曲
void CkuwoMusicPlayDlg::OnBnClickedBtnNext()
{
	// TODO: 在此添加控件通知处理程序代码
	int index;
	index = m_listitems.GetCurSel();
	
	index += 1 ;
	
	if (index==m_listitems.GetCount())
	{
		return;
	}
	m_listitems.SetCurSel(index);//指向当前对象
	mciSendCommand(m_DeviceID, MCI_CLOSE, 0, 0);
	//打开

	CString strPath2;
	m_listitems.GetText(index,strPath2);
	micOpenParms.lpstrElementName = strPath2;//把目标歌曲存到一个变量中
	MCIERROR mciError = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_WAIT, (DWORD)&micOpenParms);
	if (mciError)
	{
		//获取错误信息
		wchar_t szError[256];//专门用来存错误信息
		mciGetErrorString(mciError, szError, 256);
		MessageBox(szError, TEXT("音乐播放器"), MB_ICONERROR);
		return;
	}
	//MessageBox(strPath2);
	//打开成功后，继续
	m_DeviceID = micOpenParms.wDeviceID;
	//打开歌曲路径后，可自动播放（调用播放歌曲的函数）
	OnBnClickedBtnPlay();

	//MessageBox(L"heihei");
}
