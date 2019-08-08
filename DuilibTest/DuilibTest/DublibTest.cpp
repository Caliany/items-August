#if 0
#include <Windows.h> 
#include <tchar.h> 

��Ϣ�ص����� 
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) { 
	switch (message) {
	case WM_CLOSE:
		if (IDOK == MessageBox(NULL, _T("��ȷ���˳���"), _T("�˳�"), MB_OKCANCEL)) { 
			_T("��ȷ���˳���")   //_T���ַ���ǰ��_T,��ʾVS��װһ���꣬ASCLL�뵥�ֽڸ�ʽת��Ϊinclude ��ʽ��

			DestroyWindow(hWnd); 
				return 0; 
		} 
	WinProc ������Ϣ�� 
	case WM_LBUTTONDOWN:{
			   MessageBox(NULL,_T("Test"),_T("hello"),IDOK);
	}
	case WM_DESTROY: 
		PostQuitMessage(0);
		return 0; 
	default: 
		return DefWindowProc(hWnd, message, wParam, lParam);
	} 
}
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
	Step1:ע��һ�������� 

	HWND hwnd; //���ڵľ�� 
	WNDCLASSEX wc; //������ṹ 
	wc.cbSize = sizeof(WNDCLASSEX); 
	wc.style = CS_VREDRAW | CS_HREDRAW; 
	wc.lpszMenuName = 0; 
	wc.lpszClassName = _T("Win32"); 
	wc.lpfnWndProc = WinProc; //��Ϣ�ص����� 
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = NULL; 
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); 
	wc.cbWndExtra = 0; 
	wc.cbClsExtra = 0;
	wc.hIconSm = NULL; 
	RegisterClassEx(&wc); //ע�ᴰ��

	Step2:����һ������ 
	hwnd = CreateWindow( 
		_T("Win32"), //���ڵ�������Ҳ�������������Զ���Ĵ���������� 
		_T("First 32"), //���ڵı��� 
		WS_OVERLAPPEDWINDOW, //����style 
		500, //����λ��x���� 
		300, //����λ��y���� 
		800, //���ڿ�� 
		600, //���ڸ߶�    �ĸ����ݱ�ʾ���ڵ�λ��
		NULL, //�����ھ�� 
		NULL, //�˵���� 
		hInstance, //ʵ����� 
		NULL //�������� 
		); 
	if (!hwnd) {
		return FALSE;
	}
	ShowWindow(hwnd, SW_SHOW); //��ʾ���� 
	UpdateWindow(hwnd); //ˢ�� 
	Step3:��Ϣѭ�� 
	MSG msg; 
	while (GetMessage(&msg, NULL, 0, 0)) { 
		TranslateMessage(&msg); 
		DispatchMessage(&msg);  //��Ӧ�ó���������ȡ��Ϣ
	}
	return 0;
}
#endif


#
#pragma once
#include <UIlib.h>
using namespace DuiLib;

#ifdef _DEBUG
#   ifdef _UNICODE
#       pragma comment(lib, "DuiLib_ud.lib")
#   else
#       pragma comment(lib, "DuiLib_d.lib")
#   endif
#else
#   ifdef _UNICODE
#       pragma comment(lib, "DuiLib_u.lib")
#   else
#       pragma comment(lib, "DuiLib.lib")
#   endif
#endif	

#if 0
//Duilib��������Ҳ��win32 ���򣬽�win32�����̷�װ
class CDuiFrameWnd : public CWindowWnd, public INotifyUI
{
public:
	//���ô����������
	virtual LPCTSTR GetWindowClassName() const { return _T("DUIMainFrame"); }

	//������Ϣ:duilib��װ����Ϣ   Notify�� ����ķ���
	virtual void    Notify(TNotifyUI& msg) {
		if (msg.sType == _T("click")){
			if (msg.pSender->GetName() == _T("btnHello")){
				::MessageBox(NULL, _T("��ʵ����һ����ť"), _T("�ҵ����ť"), NULL);
			}
		}
	}
	//����ϵͳ��Ϣ		  HandleMessage��Windowsϵͳ����Ӧ��������Ϣ
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		LRESULT lRes = 0;

		if (uMsg == WM_CREATE)
		{
			m_PaintManager.Init(m_hWnd);

			CDialogBuilder builder;
			CControlUI* pRoot = builder.Create(_T("duilib.xml"), (UINT)0, NULL, &m_PaintManager);   // duilib.xml��Ҫ�ŵ�exeĿ¼��
			ASSERT(pRoot && "Failed to parse XML");

			m_PaintManager.AttachDialog(pRoot);
			m_PaintManager.AddNotifier(this);   // ��ӿؼ�����Ϣ��Ӧ��������Ϣ�ͻᴫ�ﵽduilib����Ϣѭ�������ǿ�����Notify����������Ϣ����
			
			CControlUI *pWnd = new CButtonUI;
			pWnd->SetText(_T("btnHello"));  //���ÿؼ������ƣ�����������ڱ�ʶÿһ���ؼ�������Ψһ���൱��MFC����Ŀؼ�ID
			pWnd->SetText(_T("ӵ�������̫���ɣ�"));   // ��������
				//RGB��ԭɫ
			pWnd->SetBkColor(0xFFFF0000);       // ���ñ���ɫ----��ɫ��   (0xFFFF0000----��ɫ)

			m_PaintManager.Init(m_hWnd);
			m_PaintManager.AttachDialog(pWnd);
			m_PaintManager.AddNotifier(this); //��ӿؼ�����Ϣ��Ӧ��������Ϣ�ͻᴫ�ﵽduilib����Ϣѭ�������ǿ�����Notify����������Ϣ����

			return lRes;
		}
		else if (uMsg == WM_CLOSE){

			Close();
		}
		// ����3����ϢWM_NCACTIVATE��WM_NCCALCSIZE��WM_NCPAINT��������ϵͳ������
		else if (uMsg == WM_NCACTIVATE)
		{
			if (!::IsIconic(m_hWnd))
			{
				return (wParam == 0) ? TRUE : FALSE;
			}
		}
		else if (uMsg == WM_NCCALCSIZE)
		{
			return 0;
		}
		else if (uMsg == WM_NCPAINT)
		{
			return 0;
		}

		if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes))
		{
			return lRes;
		}

		return __super::HandleMessage(uMsg, wParam, lParam);
	}


protected:
	CPaintManagerUI m_PaintManager;
};

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());   // ������Դ��Ĭ��·�����˴�����Ϊ��exe��ͬһĿ¼��
	
	CDuiFrameWnd duiFrame;
	duiFrame.Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	duiFrame.CenterWindow();
	duiFrame.ShowModal();
	return 0;
}
#endif

#pragma once
#include <UIlib.h>
using namespace DuiLib;

#ifdef _DEBUG
#   ifdef _UNICODE
#       pragma comment(lib, "DuiLib_ud.lib")
#   else
#       pragma comment(lib, "DuiLib_d.lib")
#   endif
#else
#   ifdef _UNICODE
#       pragma comment(lib, "DuiLib_u.lib")
#   else
#       pragma comment(lib, "DuiLib.lib")
#   endif
#endif

#if 0
class CDuiFrameWnd : public CWindowWnd, public INotifyUI
{
public:
	virtual LPCTSTR GetWindowClassName() const { return _T("DUIMainFrame"); }
	virtual void    Notify(TNotifyUI& msg)
	{
		if (msg.sType == _T("click"))
		{
			if (msg.pSender->GetName() == _T("btnHello"))
			{
				::MessageBox(NULL, _T("���ǰ�ť"), _T("����˰�ť"), NULL);
			}
		}
	}

	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		LRESULT lRes = 0;

		if (uMsg == WM_CREATE)
		{
			m_PaintManager.Init(m_hWnd);

			CDialogBuilder builder;
			CControlUI* pRoot = builder.Create(_T("duilib.xml"), (UINT)0, NULL, &m_PaintManager);   // duilib.xml��Ҫ�ŵ�exeĿ¼��
			ASSERT(pRoot && "Failed to parse XML");

			m_PaintManager.AttachDialog(pRoot);
			m_PaintManager.AddNotifier(this);   // ��ӿؼ�����Ϣ��Ӧ��������Ϣ�ͻᴫ�ﵽduilib����Ϣѭ�������ǿ�����Notify����������Ϣ����
			return lRes;
		}
		// ����3����ϢWM_NCACTIVATE��WM_NCCALCSIZE��WM_NCPAINT��������ϵͳ������
		else if (uMsg == WM_NCACTIVATE)
		{
			if (!::IsIconic(m_hWnd))
			{
				return (wParam == 0) ? TRUE : FALSE;
			}
		}
		else if (uMsg == WM_NCCALCSIZE)
		{
			return 0;
		}
		else if (uMsg == WM_NCPAINT)
		{
			return 0;
		}

		if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes))
		{
			return lRes;
		}

		return __super::HandleMessage(uMsg, wParam, lParam);
	}

protected:
	CPaintManagerUI m_PaintManager;
};

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());   // ������Դ��Ĭ��·�����˴�����Ϊ��exe��ͬһĿ¼��

	CDuiFrameWnd duiFrame;
	duiFrame.Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	duiFrame.CenterWindow();
	duiFrame.ShowModal();
	return 0;
}
#endif

#if 0
//���ڶ�һ��xml�ļ����û��Լ�д
//designed����---bug:ͻȻ���� ���ܻ��޸�xml�ļ��е������ؼ����������еĿؼ���֧��
class CDuiFrameWnd : public WindowImplBase
{
public:
	virtual LPCTSTR    GetWindowClassName() const   { return _T("DUIMainFrame"); }//�����������
	virtual CDuiString GetSkinFile()                { return _T("duilib.xml"); }//��ȡһ��xml���֣�����ȡƤ�����ļ�
	virtual CDuiString GetSkinFolder()              { return _T(""); }//��ȡƤ����Ŀ¼�ļ�


	//
	virtual void    Notify(TNotifyUI& msg)
	{
		if (msg.sType == _T("click"))
		{
			if (msg.pSender == m_PaintManager.FindControl(_T("BIN_CLOSE")))
				Close();
			//else if (msg.pSender == m_PaintManager.FindControl(_T("BIN_MIN")))
			//	Close();
		}
	}
};

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);

	CDuiFrameWnd duiFrame;
	duiFrame.Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	duiFrame.CenterWindow();
	duiFrame.ShowModal();// ģ�ضԻ���
	//duiFrame.ShowWindow();
	return 0;
}
#endif

#include "MainWnd.h"
#include "Login.h"
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//MSG msg;
	//CPaintManagerUI::SetInstance(hInstance);

	//MainWnd duiFrame;
	//duiFrame.Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	//duiFrame.CenterWindow();
	//duiFrame.ShowModal();// ģ�ضԻ���

	MSG msg;
	CPaintManagerUI::SetInstance(hInstance);

	LoginWnd duiFrame;
	duiFrame.Create(NULL, _T("LOGINWND"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	duiFrame.CenterWindow();
	duiFrame.ShowModal();// ģ�ضԻ���
	return 0;
}
