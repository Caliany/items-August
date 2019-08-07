#include "MySQL.h"
#include<iostream>
using namespace std;

MySQL::MySQL(){
	_mySQL = mysql_init(nullptr);
}
bool MySQL::ConnectMySQL(const char* host, const char* user, const char* passward, const char* dbname){
	if (!mysql_real_connect(_mySQL, host, user, passward, dbname, 3306, nullptr, 0))
	{
		cout << "���ݿ�����ʧ��" << endl;
		return false;
	}
	/*
	��һ���������������ӣ���ʼ���ķ���ֵ��
	�ڶ����������û������������ӣ�
	���������������루�û�����
	���ĸ���������ǰ���ݿ�����
	������������˿ں�
	�������������׽��֣��ò�����
	���߸��������ͻ��˷�ʽ���ò�����

	c++����mysqlʱ�������ѯ����к������ģ����ߵõ�����к������ģ��������ֱ������������� �⡣
	VS������Ĭ��ʹ��gbk���롣 �����mysql����Ϊutf-8���룬����Ҫ�Ƚ�c++�еĸ��������ַ���תΪutf-8��������mysql��
	�õ� �Ľ��Ϊutf-8���룬��ҪתΪgbk����������ʾ��ת��תȥ���鷳��
	*/
	mysql_query(_mySQL, "set names 'gbk'");
	return true;
}

vector<vector<string>> MySQL::Select(const string& strSQL){
	vector<vector<string>> vvRet;
 	if (mysql_query(_mySQL, strSQL.c_str())){
		//SQL��Ӧʧ��
		cout<< mysql_error(_mySQL) << endl;
		return vvRet;
	}
	//��ȡ��ѯ�ļ�¼
	MYSQL_RES * mySQLRes = mysql_store_result(_mySQL);
	if (nullptr == mySQLRes){
		cout << mysql_error(_mySQL) << endl;
		return vvRet;
	}
	//��ȡ��¼�еĶ��ٸ��ֶ�e
	int itemCount = mysql_num_fields(mySQLRes);
	MYSQL_ROW mysqlRow;
	while (mysqlRow = mysql_fetch_row(mySQLRes)){
		//��ȡһ������
		vector<string> vItem;
		for (size_t i = 0; i < itemCount; ++i){
			vItem.push_back(mysqlRow[i]);
		}
		vvRet.push_back(vItem);
	}
	mysql_free_result(mySQLRes);
	return vvRet;
}

bool MySQL::Insert(const string& strSQL){
	if (mysql_query(_mySQL, strSQL.c_str())){
		//SQL��Ӧʧ��
		cout << mysql_error(_mySQL) << endl;
		return false;
	}
	return true;
}
MySQL::~MySQL(){

}