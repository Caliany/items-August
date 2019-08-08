#include "MainWnd.h"

//ASCLL---> 7个比特位表示数字类型的字符，特殊符号.....

//xml文件对应的目录
 CDuiString MainWnd::GetSkinFolder(){
	 return _T("");
}

//xml文件的名字
 CDuiString MainWnd::GetSkinFile(){
	 return _T("MainWnd.xml"); //使用Unicode库
}

//窗口类的名字：在注册窗口是必须提供
 LPCTSTR MainWnd::GetWindowClassName(void) const{
	 return _T("MainWnd");
}

 void MainWnd::Notify(TNotifyUI& msg){
	 CDuiString strName = msg.pSender->GetName();
	 if (msg.sType == _T("click")){		  
		 if (strName == _T("BTN_MIN"))
			 ::SendMessage(m_hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);//窗口最小化
		 else if (strName == _T("BTN_CLOSE"))
			 Close();
	 }


	 else if (msg.sType == _T("itemselect")){
		 if (strName == _T("Option_Employee"))
			 MessageBox(m_hWnd, _T("Employee"), _T("Cashier"), IDOK);
		 if (strName == _T("Option_Goods"))
			 MessageBox(m_hWnd, _T("Goods"), _T("Cashier"), IDOK);
	}
 }
