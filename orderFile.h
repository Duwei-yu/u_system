#pragma once
#include<iostream>
#include<map>
#include"globalFile.h"
using  namespace std;
#include<fstream>


class orderFile
{
public:

	//构造函数
	orderFile();

	//更新预约记录
	void updateOrder();

	//记录预约条数
	int m_Size;

	//记录所有预约信息的容器 key记录条数   value记录具体键值对信息
	map<int, map<string, string>> m_orderData;

};