#pragma once
#include"Identity.h"
#include <fstream>
#include"globalFile.h"
#include<vector>
#include"Student.h"
#include"Teacher.h"
#include<algorithm>
#include"computerRoom.h"
class Manager :public Identity
{
public:
	//默认构造
	Manager();

	//有参构造
	Manager(string name, string pwd);

	//菜单界面
	virtual void operMenu();

	//添加账号
	void addPerson();

	//查看账号
	void showPerson();

	//查看机房信息
	void showComputer();

	//清空文件
	void cleanFile();

	//初始化容器
	void initVector();

	//检测重复   参数1 检测 学号/职工号   参数2  检测的类型
	bool checkRepeat(int id, int type);

	//学生容器
	vector<Student> vStu;

	//教师容器
	vector<Teacher> vTe;

	//机房容器
	vector<computerRoom> vCom;

};