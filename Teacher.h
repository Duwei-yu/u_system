#pragma once
#include<iostream>
#include"Identity.h"
#include"orderFile.h"
#include<vector>
class Teacher :public Identity
{
public:

	//默认构造
	Teacher();

	//有参构造
	Teacher(int empid, string name, string pwd);

	//菜单界面
	virtual void operMenu();

	//查看所有预约
	void showAllOrder();

	//审核预约
	void validOrder();

	//教师编号
	int m_empId;
};