#include "MainWnd.h"

//ASCLL---> 7������λ��ʾ�������͵��ַ����������.....

//xml�ļ���Ӧ��Ŀ¼
 CDuiString MainWnd::GetSkinFolder(){
	 return _T("");
}

//xml�ļ�������
 CDuiString MainWnd::GetSkinFile(){
	 return _T("MainWnd.xml"); //ʹ��Unicode��
}

//����������֣���ע�ᴰ���Ǳ����ṩ
 LPCTSTR MainWnd::GetWindowClassName(void) const{
	 return _T("MainWnd");
}

 void MainWnd::Notify(TNotifyUI& msg){
	 CDuiString strName = msg.pSender->GetName();
	 if (msg.sType == _T("click")){		  
		 if (strName == _T("BTN_MIN"))
			 ::SendMessage(m_hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);//������С��
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
