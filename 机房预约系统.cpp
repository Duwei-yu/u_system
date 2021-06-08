#include <iostream>
using namespace std;
#include"Identity.h"
#include<fstream>
#include"globalFile.h"
#include"Student.h"
#include"Teacher.h"
#include"Manager.h"

void teacherMenu(Identity* teacher)
{
	while (true)
	{
		teacher->operMenu();
		Teacher* tea = (Teacher*)teacher;
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			tea->showAllOrder();
		}
		else if (select == 2)
		{
			tea->validOrder();
		}
		else
		{
			cout << "注销成功" << endl;
			delete teacher;
			system("pause");
			system("cls");
			return;
		}
	}
}
void studentMenu(Identity* student)
{
	while (true)
	{
		student->operMenu();

		Student* stu = (Student*)student;
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			stu->applyOrder();
		}
		else if (select == 2)
		{
			stu->showMyOrder();
		}
		else if (select == 3)
		{
			stu->showAllOrder();
		}
		else if(select==4)
		{
			stu->cancelOrder();
		}
		else
		{
			cout << "注销成功" << endl;          //注销登录
			delete student;
			system("pause");
			system("cls");
			return;
		}
	}
}
void managerMenu(Identity* manager)
{
	while (true)
	{
		//调用管理员子菜单界面
		manager->operMenu();  //通过多态，父类调用子类的重写函数

		//将父类指针强制类型转换成子类指针，调用子类其他特有接口（非公共接口，即非重写函数）
		Manager* man = (Manager*)manager;

		int select = 0;
		cin >> select;
		if (select == 1)
		{
			man->addPerson();
		}
		else if (select == 2)
		{
			man->showPerson();
		}
		else if (select == 3)
		{
			man->showComputer();
		}
		else if (select == 4)
		{
			man->cleanFile();
		}
		else
		{
			cout << "注销成功" << endl;
			delete manager;
			system("pause");
			system("cls");
			return;
		}
	}
}

//登录功能  参数一：操作文件名   参数二：操作身份类型
void loginIn(string filename, int type)
{
	//父类指针 用于指向子类对象
	Identity* person = NULL;

	//读文件
	ifstream ifs;
	ifs.open(filename, ios::in);

	//判断文件是否存在
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	//准备接收用户信息
	int id = 0;
	string name;
	string pwd;

	//判断身份
	if (type == 1)
	{
		cout << "请输入你的学号：" << endl;
		cin >> id;
	}
	else if (type == 2)
	{
		cout << "请输入你的职工号：" << endl;
		cin >> id;
	}
	cout << "请输入用户名：" << endl;
	cin >> name;
	cout << "请输入密码：" << endl;
	cin >> pwd;

	if (type == 1)
	{
	    //验证学生信息
		int Fid;        //从文件中读取的ID号
		string Fname;  //从文件中读取的姓名
		string Fpwd;   //从文件中读取的密码
		while (ifs >> Fid && ifs >> Fname && ifs >> Fpwd)
		{
			if (Fid == id && Fname == name && Fpwd == pwd)
			{
				cout << "学生验证登录成功！" << endl;
				system("pause");
				system("cls");
				person = new Student(id, name, pwd);
				//进入学生子菜单
				studentMenu(person);


				return;
			}
		}
	}
	else if (type == 2)
	{
		//验证教师信息
		int Fid;
		string Fname;
		string Fpwd;
		while (ifs >> Fid && ifs >> Fname && ifs >> Fpwd)
		{
			if (Fid == id && Fname == name && Fpwd == pwd)
			{
				cout << "教师验证登录成功！" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				//进入教师子菜单
				teacherMenu(person);

				return;
			}
		}

	}
	else if (type == 3)
	{
		//验证管理员信息
		string Fname;
		string Fpwd;
		ifs >> Fname && ifs >> Fpwd;
		if (Fname == name && Fpwd == pwd)
		{
			cout << "管理员验证登录成功！" << endl;
			system("pause");
			system("cls");
			person = new Manager(name, pwd);
			//进入管理员子菜单界面
			managerMenu(person);

			return;
		}
	}

	cout << "验证登录失败" << endl;
	system("pause");
	system("cls");
	return;
}
void Menu()
{
	cout << "\t----------欢迎来到机房预约系统-------------" << endl;
	cout << "请输入您的选择：" << endl;
	cout << "\t\t -------------------------" << endl;
	cout << "\t\t|                         |" << endl;
	cout << "\t\t|         1.学生          |" << endl;
	cout << "\t\t|                         |" << endl;
	cout << "\t\t|         2.教师          |" << endl;
	cout << "\t\t|                         |" << endl;
	cout << "\t\t|         3.管理员        |" << endl;
	cout << "\t\t|                         |" << endl;
	cout << "\t\t|         0.退出          |" << endl;
	cout << "\t\t|                         |" << endl;
	cout << "\t\t -------------------------" << endl;
}
int main()
{
	int select = 0;
	while (1)
	{
		Menu();
		cout << "请输入你的选择：" << endl;
		cin >> select;
		switch (select)
		{
		case 1:
			loginIn(STUDENT_FILE, 1);
			break;
		case 2:
			loginIn(TEACHER_FILE, 2);
			break;
		case 3:
			loginIn(ADMIN_FILE, 3);
			break;
		case 0:        //退出
			cout << "欢迎下次使用" << endl;
			system("pause");
			return 0; 
			break;
		default:
			cout << "输入有误，请重新输入" << endl;
			system("pause");
			system("cls");
			break;
		}

	}
	system("pause");
	return 0;
}