
// kuwoMusicPlay.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CkuwoMusicPlayApp:
// �йش����ʵ�֣������ kuwoMusicPlay.cpp
//

class CkuwoMusicPlayApp : public CWinApp
{
public:
	CkuwoMusicPlayApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CkuwoMusicPlayApp theApp;