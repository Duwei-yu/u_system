#pragma once
#include<iostream>
#include<map>
#include"globalFile.h"
using  namespace std;
#include<fstream>


class orderFile
{
public:

	//���캯��
	orderFile();

	//����ԤԼ��¼
	void updateOrder();

	//��¼ԤԼ����
	int m_Size;

	//��¼����ԤԼ��Ϣ������ key��¼����   value��¼�����ֵ����Ϣ
	map<int, map<string, string>> m_orderData;

};