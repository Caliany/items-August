#pragma once

#include "Common.h"

class MainWnd : public WindowImplBase{
public:
	virtual void Notify(TNotifyUI& msg);

protected:
	//WindowImplBase�����е��������麯��
	//xml�ļ���Ӧ��Ŀ¼
	virtual CDuiString GetSkinFolder();

	//xml�ļ�������
	virtual CDuiString GetSkinFile() ;

	//����������֣���ע�ᴰ���Ǳ����ṩ
	virtual LPCTSTR GetWindowClassName(void) const ;
};