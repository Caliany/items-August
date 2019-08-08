#include "Login.h"
#include "MainWnd.h"


//xml�ļ���Ӧ��Ŀ¼
CDuiString LoginWnd::GetSkinFolder(){
	return _T("");
}

//xml�ļ�������
CDuiString LoginWnd::GetSkinFile(){
	return _T("LoginWnd.xml"); //ʹ��Unicode��
}

//����������֣���ע�ᴰ���Ǳ����ṩ
LPCTSTR LoginWnd::GetWindowClassName(void) const{
	return _T("LoginWnd");
}

void LoginWnd::Notify(TNotifyUI& msg){
	CDuiString strName = msg.pSender->GetName();
	if (msg.sType == _T("click")){
		if (strName == _T("BTN_MIN"))
			::SendMessage(m_hWnd,WM_SYSCOMMAND,SC_MINIMIZE,0);//������С����
			//MessageBox(NULL, _T("MIN"), _T("Cashier"), IDOK);

		else if (strName == _T("BTN_CLOSE"))
			Close();
		else if (strName == _T("BTN_LOGIN"))
			Login();
	}
}

void LoginWnd::Login(){
	//�ӱ༭���ȡ�û���������
	CEditUI* pEditUserName =(CEditUI*)m_PaintManager.FindControl(_T("EDIT_USER_NAME"));
	CDuiString strUserName = pEditUserName->GetText();

	CEditUI* pEditPassword = (CEditUI*)m_PaintManager.FindControl(_T("EDIT_USER_PASSWORD"));
	CDuiString strPassword = pEditPassword->GetText();

	if (strUserName.IsEmpty()){
		MessageBox(m_hWnd, _T("����������"), _T("Cashier"), IDOK);
		return;
	}
	if (strPassword.IsEmpty()){
		MessageBox(m_hWnd, _T("����������"), _T("Cashier"), IDOK);
		return;
	}

	//��ѯ���ݿ⣬����û��Ƿ����

	//����������
	MainWnd mainwnd;
	mainwnd.Create(NULL, _T("MainWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	mainwnd.CenterWindow();
	mainwnd.ShowModal();

	//���ص�¼����
	ShowWindow(false);
}
