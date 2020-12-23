
// kuwoMusicPlayDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "kuwoMusicPlay.h"
#include "kuwoMusicPlayDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CkuwoMusicPlayDlg �Ի���



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


// CkuwoMusicPlayDlg ��Ϣ�������

//��ʼ��
BOOL CkuwoMusicPlayDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//����������Χ
	m_slider.SetRange(0,1000);
	m_slider.SetPos(1000);//�����������
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

//��ʽ����
void CkuwoMusicPlayDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		//��ȡ�ͻ�����С
		CRect rect,captionRect;
		GetClientRect(&rect);
		captionRect = rect;
		captionRect.bottom = 30;
		dc.FillSolidRect(&captionRect,RGB(204,204,204));
		CFont font;
		font.CreatePointFont(120,L"����");
		dc.SelectObject(&font);
		dc.TextOutW(20,7,L"�������ֲ�����");
		//��ͼƬ
		CBitmap bmp;
		bmp.LoadBitmap(IDB_BITMAP3);
		//��ȡͼƬ���
		BITMAP logBmp;//ͼƬ��Ϣ
		bmp.GetBitmap(&logBmp);//��ȡͼƬ��Ϣ
		//�����ڴ�DC
		CDC memDC;
		memDC.CreateCompatibleDC(&dc);
		memDC.SelectObject(&bmp);

		//��ͼ
		//dc.BitBlt(0,0,rect.Width(),rect.Height(),&memDC,0,0,SRCCOPY);
		dc.SetStretchBltMode(HALFTONE);
		//������ͼ
		dc.StretchBlt(0,30,rect.Width(),rect.Height(),&memDC,0,0,logBmp.bmWidth,logBmp.bmHeight,SRCCOPY);

		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CkuwoMusicPlayDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//������
void CkuwoMusicPlayDlg::OnBnClickedBtnOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//MessageBox(L"�����",L"��ʾ",MB_OK);//L:���ÿ��ַ����༭
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,L"MP3�ļ�(*.mp3)|*.mp3|WMA�ļ�(*.wma)|*.wma|WAV�ļ�(*.wav)|*.wav|�����ļ�(*.*)|*.*||");
	//�򿪶Ի���ɸѡ�ļ�����
	if(IDCANCEL == dlg.DoModal()){
		return;//�û�������ȡ�����򲻽����κβ���
	}else{
		//��ֹͣ��ǰ������
		OnBnClickedBtnStop();
		//����û���ĳ�������ļ����Ͱ�·�����뵽m_listitems��
		CString strMusicPath = dlg.GetPathName();
		m_listitems.InsertString(m_listitems.GetCount(), strMusicPath);
		m_listitems.SetCurSel(m_listitems.GetCount() - 1);//�������һ������ֵ

		//��ȡ·��
		CString strMusicFile = dlg.GetPathName();
		//MessageBox(strMusicFile);//����·����Ϣ

		//��
		//MCI_OPEN_PARMS micOpenParms;
		micOpenParms.lpstrElementName = strMusicFile;//��Ŀ������浽һ��������
		MCIERROR mciErro = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT|MCI_WAIT,(DWORD)&micOpenParms);
		//���򿪴���ʱ��ִ��if�е�ָ��
		if(mciErro){
			//��ȡ������Ϣ
			wchar_t szErrorMsg[256];
			mciGetErrorString(mciErro,szErrorMsg,256);
			MessageBox(szErrorMsg,L"�������ֲ�����");
			return;
		}
		//�򿪳ɹ��󣬼���
		m_DeviceID = micOpenParms.wDeviceID;
		//�򿪸���·���󣬿��Զ����ţ����ò��Ÿ����ĺ�����
		OnBnClickedBtnPlay();
	}

		
	

	
	
}

//���Ÿ���
void CkuwoMusicPlayDlg::OnBnClickedBtnPlay()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MCI_PLAY_PARMS mciPlayParms;
	mciPlayParms.dwCallback = NULL;
	mciPlayParms.dwFrom = 0;//��ͷ��ʼ���Ÿ���
	//����������ſ�ʼλ�ã��ɵ�������
	mciSendCommand(m_DeviceID, MCI_PLAY, MCI_FROM | MCI_NOTIFY,(DWORD)&mciPlayParms);//����һ��
	
}

//��ͣ/��������
void CkuwoMusicPlayDlg::OnBnClickedBtnPause()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	GetDlgItemText(IDC_BTN_PAUSE, str);//��ȡ�ı�
	//�ж��Ƿ���ͣ
	if(str == L"��ͣ"){
		//������ͣ����
		mciSendCommand(m_DeviceID, MCI_PAUSE, 0 , 0);
		//�޸��ı�����ͣ===������
		SetDlgItemText(IDC_BTN_PAUSE, L"����");
	}else if(str == "����"){
		//���ͻָ�����
		mciSendCommand(m_DeviceID, MCI_RESUME, 0 , 0);
		//�޸��ı�������===����ͣ
		SetDlgItemText(IDC_BTN_PAUSE, L"��ͣ");
	}
}

//ֹͣ
void CkuwoMusicPlayDlg::OnBnClickedBtnStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//����ֹͣ����
	mciSendCommand(m_DeviceID, MCI_STOP, 0, 0);
	mciSendCommand(m_DeviceID, MCI_CLOSE, 0, 0);
}

//��������
void CkuwoMusicPlayDlg::OnCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ȡ��ǰ�����ؼ�λ��
	m_nVolume = m_slider.GetPos()/10;
	UpdateData(FALSE);//ˢ����ʾ��ֵ

	//��������(��������)
	MCI_DGV_SETAUDIO_PARMS mciSetVolume;
	mciSetVolume.dwItem = MCI_DGV_SETAUDIO_VOLUME;
	mciSetVolume.dwValue = m_slider.GetPos();//ͬ������ֵ����ʾ�ڱ༭����
	mciSendCommand(m_DeviceID, MCI_SETAUDIO,MCI_DGV_SETAUDIO_VALUE|MCI_DGV_SETAUDIO_ITEM,(DWORD)&mciSetVolume);//��������

	*pResult = 0;
}

//��ʽ����
LRESULT CkuwoMusicPlayDlg::OnNcHitTest(CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	UINT nHitTest = CDialogEx::OnNcHitTest(point);
	//��ȡ�ͻ�ȥ��С
	CRect rect;
	GetClientRect(&rect);
	rect.bottom = 30;
	//�ж������λ���ڲ��ڱ�������
	ScreenToClient(&point);//ת����Ļ����ϵ
	if(rect.PtInRect(point)){
		if(nHitTest == HTCLIENT)
		nHitTest = HTCAPTION;
	}
	
	return nHitTest;
}

//���ټ���
BOOL CkuwoMusicPlayDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//return CDialogEx::OnEraseBkgnd(pDC);
	return TRUE;
}

//�رնԻ���
void CkuwoMusicPlayDlg::OnBnClickedClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	EndDialog(IDOK);
}


//��һ��
void CkuwoMusicPlayDlg::OnBnClickedBtnBefore()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int index;
	index = m_listitems.GetCurSel();
	
	index = index - 1;
	
	if (index < 0)
	{
		//MessageBox(TEXT("�Ѿ��ǵ�һ�׸�"));
		return;
	}
	m_listitems.SetCurSel(index);//ָ��ǰ����
	mciSendCommand(m_DeviceID, MCI_CLOSE, 0, 0);
	//��

	CString strPath2;
	m_listitems.GetText(index,strPath2);
	micOpenParms.lpstrElementName = strPath2;//��Ŀ������浽һ��������
	MCIERROR mciError = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_WAIT, (DWORD)&micOpenParms);
	if (mciError)
	{
		//��ȡ������Ϣ
		wchar_t szError[256];//ר�������������Ϣ
		mciGetErrorString(mciError, szError, 256);
		MessageBox(szError, TEXT("���ֲ�����"), MB_ICONERROR);
		return;
	}
	//MessageBox(strPath2);
	//�򿪳ɹ��󣬼���
	m_DeviceID = micOpenParms.wDeviceID;
	//�򿪸���·���󣬿��Զ����ţ����ò��Ÿ����ĺ�����
	OnBnClickedBtnPlay();

	//MessageBox(L"heihei");
	
}


//ɾ������
void CkuwoMusicPlayDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_listitems.DeleteString(m_listitems.GetCurSel());
	OnBnClickedBtnStop();
}


//˫������
void CkuwoMusicPlayDlg::OnLbnSelchangeList1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int index;
	index = m_listitems.GetCurSel();//��ȡ��ǰ����������ֵ

	m_listitems.SetCurSel(index);//ָ��ǰ����
	mciSendCommand(m_DeviceID, MCI_CLOSE, 0, 0);
	
	CString strPath2;
	m_listitems.GetText(index,strPath2);
	micOpenParms.lpstrElementName = strPath2;//��Ŀ������浽һ��������
	MCIERROR mciError = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_WAIT, (DWORD)&micOpenParms);
	if (mciError)
	{
		//��ȡ������Ϣ
		wchar_t szError[256];//ר�������������Ϣ
		mciGetErrorString(mciError, szError, 256);
		MessageBox(szError, TEXT("���ֲ�����"), MB_ICONERROR);
		return;
	}
	//MessageBox(strPath2);
	//�򿪳ɹ��󣬼���
	m_DeviceID = micOpenParms.wDeviceID;
	//�򿪸���·���󣬿��Զ����ţ����ò��Ÿ����ĺ�����
	OnBnClickedBtnPlay();

	//MessageBox(L"heihei");
	
}

//��һ��
void CkuwoMusicPlayDlg::OnBnClickedBtnNext()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int index;
	index = m_listitems.GetCurSel();
	
	index += 1 ;
	
	if (index==m_listitems.GetCount())
	{
		return;
	}
	m_listitems.SetCurSel(index);//ָ��ǰ����
	mciSendCommand(m_DeviceID, MCI_CLOSE, 0, 0);
	//��

	CString strPath2;
	m_listitems.GetText(index,strPath2);
	micOpenParms.lpstrElementName = strPath2;//��Ŀ������浽һ��������
	MCIERROR mciError = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_WAIT, (DWORD)&micOpenParms);
	if (mciError)
	{
		//��ȡ������Ϣ
		wchar_t szError[256];//ר�������������Ϣ
		mciGetErrorString(mciError, szError, 256);
		MessageBox(szError, TEXT("���ֲ�����"), MB_ICONERROR);
		return;
	}
	//MessageBox(strPath2);
	//�򿪳ɹ��󣬼���
	m_DeviceID = micOpenParms.wDeviceID;
	//�򿪸���·���󣬿��Զ����ţ����ò��Ÿ����ĺ�����
	OnBnClickedBtnPlay();

	//MessageBox(L"heihei");
}
