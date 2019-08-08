#include "Common.h"


class LoginWnd : public WindowImplBase{

public:
	virtual void Notify(TNotifyUI& msg);
	void Login();

protected:
	//WindowImplBase�����е��������麯��
	//xml�ļ���Ӧ��Ŀ¼
	virtual CDuiString GetSkinFolder();

	//xml�ļ�������
	virtual CDuiString GetSkinFile();

	//����������֣���ע�ᴰ���Ǳ����ṩ
	virtual LPCTSTR GetWindowClassName(void) const;
};