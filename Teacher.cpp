#include"Teacher.h"
//默认构造
Teacher::Teacher()
{

}

//有参构造
Teacher::Teacher(int empid, string name, string pwd)
{
	this->m_empId = empid;
	this->m_Name = name;
	this->m_Pwd = pwd;
}

//菜单界面
void Teacher::operMenu()
{
	cout << "\t----------欢迎教师" << this->m_Name << "登录-------------" << endl;
	cout << "请输入您的选择：" << endl;
	cout << "\t\t -----------------------------" << endl;
	cout << "\t\t|                             |" << endl;
	cout << "\t\t|         1.查看所有预约      |" << endl;
	cout << "\t\t|                             |" << endl;
	cout << "\t\t|                             |" << endl;
	cout << "\t\t|         2.审核预约          |" << endl;
	cout << "\t\t|                             |" << endl;
	cout << "\t\t|                             |" << endl;
	cout << "\t\t|         0.注销登录          |" << endl;
	cout << "\t\t|                             |" << endl;
	cout << "\t\t -----------------------------" << endl;

}

//查看所有预约
void Teacher::showAllOrder()
{
	orderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0;i < of.m_Size;i++)
	{
		cout << i + 1 << ".";
		cout << "星期" << of.m_orderData[i]["date"];
		cout << " 时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
		cout << " 机房：" << of.m_orderData[i]["room"];
		cout << " 姓名：" << of.m_orderData[i]["stuName"];
		cout << " 学号：" << of.m_orderData[i]["stuId"];
		string status = " 状态：";


		//1 预约中 2 已预约 -1 预约失败 0取消预约
		if (of.m_orderData[i]["status"] == "1")
		{
			status += "预约中";
		}
		else if (of.m_orderData[i]["status"] == "2")
		{
			status += "已预约";
		}
		else if (of.m_orderData[i]["status"] == "-1")
		{
			status += "预约失败,审核未通过";
		}
		else
		{
			status += "已取消预约";
		}

		cout << " " << status << endl;

	}
	system("pause");
	system("cls");
}

//审核预约
void Teacher::validOrder()
{
	orderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "待审核的记录如下：" << endl;
	vector<int> v;
	int index = 0;
	for (int i = 0;i < of.m_Size;i++)
	{
		if (of.m_orderData[i]["status"] == "1")
		{
			v.push_back(i);
			cout <<++index << ".";
			cout << "星期" << of.m_orderData[i]["date"];
			cout << " 时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
			cout << " 机房：" << of.m_orderData[i]["room"];
			cout << " 姓名：" << of.m_orderData[i]["stuName"];
			cout << " 学号：" << of.m_orderData[i]["stuId"];
			cout << " 状态：预约中" << endl;
			
		}
	}
	cout << "请选择要审核的预约记录，按0返回" << endl;
	int select = 0;
	int ret = 0;
	while (true)
	{
		cin >> select;
		if (select >= 0&&select<=v.size())
		{
			if (select == 0)
			{
				break;
			}
			else
			{
				cout << "请输入审核结果:" << endl;
				cout << "1.通过" << endl;
				cout << "2.不通过" << endl;
				cin >> ret;
				if (ret == 1)
				{
					of.m_orderData[v[select - 1]]["status"] = "2";
				}
				else
				{
					of.m_orderData[v[select - 1]]["status"] = "-1";
				}
				cout << "审核完毕" << endl;
				of.updateOrder();
				break;
			}
		}
		else
		{
			cout << "输入有误，请重新输入" << endl;
		}

	}
	
	system("pause");
	system("cls");
}