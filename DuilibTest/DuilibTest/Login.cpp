#include "Login.h"
#include "MainWnd.h"


//xml文件对应的目录
CDuiString LoginWnd::GetSkinFolder(){
	return _T("");
}

//xml文件的名字
CDuiString LoginWnd::GetSkinFile(){
	return _T("LoginWnd.xml"); //使用Unicode库
}

//窗口类的名字：在注册窗口是必须提供
LPCTSTR LoginWnd::GetWindowClassName(void) const{
	return _T("LoginWnd");
}

void LoginWnd::Notify(TNotifyUI& msg){
	CDuiString strName = msg.pSender->GetName();
	if (msg.sType == _T("click")){
		if (strName == _T("BTN_MIN"))
			::SendMessage(m_hWnd,WM_SYSCOMMAND,SC_MINIMIZE,0);//窗口最小化吧
			//MessageBox(NULL, _T("MIN"), _T("Cashier"), IDOK);

		else if (strName == _T("BTN_CLOSE"))
			Close();
		else if (strName == _T("BTN_LOGIN"))
			Login();
	}
}

void LoginWnd::Login(){
	//从编辑框获取用户名和密码
	CEditUI* pEditUserName =(CEditUI*)m_PaintManager.FindControl(_T("EDIT_USER_NAME"));
	CDuiString strUserName = pEditUserName->GetText();

	CEditUI* pEditPassword = (CEditUI*)m_PaintManager.FindControl(_T("EDIT_USER_PASSWORD"));
	CDuiString strPassword = pEditPassword->GetText();

	if (strUserName.IsEmpty()){
		MessageBox(m_hWnd, _T("请输入用名"), _T("Cashier"), IDOK);
		return;
	}
	if (strPassword.IsEmpty()){
		MessageBox(m_hWnd, _T("请输入密码"), _T("Cashier"), IDOK);
		return;
	}

	//查询数据库，检测用户是否存在

	//创建主窗口
	MainWnd mainwnd;
	mainwnd.Create(NULL, _T("MainWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	mainwnd.CenterWindow();
	mainwnd.ShowModal();

	//隐藏登录窗口
	ShowWindow(false);
}
