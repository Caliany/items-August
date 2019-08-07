#include "MySQL.h"
#include<iostream>
using namespace std;

MySQL::MySQL(){
	_mySQL = mysql_init(nullptr);
}
bool MySQL::ConnectMySQL(const char* host, const char* user, const char* passward, const char* dbname){
	if (!mysql_real_connect(_mySQL, host, user, passward, dbname, 3306, nullptr, 0))
	{
		cout << "数据库连接失败" << endl;
		return false;
	}
	/*
	第一个参数：本地连接（初始化的返回值）
	第二个参数：用户名（本地连接）
	第三个参数：密码（用户名）
	第四个参数：当前数据库名字
	第五个参数：端口号
	第六个参数：套接字（用不到）
	第七个参数：客户端方式（用不到）

	c++连接mysql时，比如查询语句中含有中文，或者得到结果中含有中文，经常出现编译出错或乱码问 题。
	VS编译器默认使用gbk编码。 如果将mysql设置为utf-8编码，则需要先将c++中的各种中文字符串转为utf-8编码输入mysql，
	得到 的结果为utf-8编码，需要转为gbk才能正常显示。转来转去很麻烦。
	*/
	mysql_query(_mySQL, "set names 'gbk'");
	return true;
}

vector<vector<string>> MySQL::Select(const string& strSQL){
	vector<vector<string>> vvRet;
 	if (mysql_query(_mySQL, strSQL.c_str())){
		//SQL响应失败
		cout<< mysql_error(_mySQL) << endl;
		return vvRet;
	}
	//获取查询的记录
	MYSQL_RES * mySQLRes = mysql_store_result(_mySQL);
	if (nullptr == mySQLRes){
		cout << mysql_error(_mySQL) << endl;
		return vvRet;
	}
	//获取记录中的多少个字段e
	int itemCount = mysql_num_fields(mySQLRes);
	MYSQL_ROW mysqlRow;
	while (mysqlRow = mysql_fetch_row(mySQLRes)){
		//获取一行内容
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
		//SQL响应失败
		cout << mysql_error(_mySQL) << endl;
		return false;
	}
	return true;
}
MySQL::~MySQL(){

}