#include"Student.h"
#include<fstream>
#include"globalFile.h"

//默认构造
Student::Student()
{
};

//有参构造
Student::Student(int id, string name, string pwd)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;

	//初始化机房信息
	//ifstream ifs(COMPUTER_FILE, ios::in);  两种打开方式都可以
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	computerRoom com;
	while (ifs >> com.m_ComId && ifs >> com.m_MaxNum)
	{
		//将文件读取的信息放到容器中
		vCom.push_back(com);
	}
	ifs.close();
}

//菜单界面
void Student::operMenu()
{
	cout << "\t----------欢迎" << this->m_Name << "来到学生系统-------------" << endl;
	cout << "请输入您的选择：" << endl;
	cout << "\t\t -----------------------------" << endl;
	cout << "\t\t|                             |" << endl;
	cout << "\t\t|         1.申请预约          |" << endl;
	cout << "\t\t|                             |" << endl;
	cout << "\t\t|         2.查看我的预约      |" << endl;
	cout << "\t\t|                             |" << endl;
	cout << "\t\t|         3.查看所有预约      |" << endl;
	cout << "\t\t|                             |" << endl;
	cout << "\t\t|         4.取消预约          |" << endl;
	cout << "\t\t|                             |" << endl;
	cout << "\t\t|         0.注销登录          |" << endl;
	cout << "\t\t|                             |" << endl;
	cout << "\t\t -----------------------------" << endl;
}

//申请预约
void Student::applyOrder()
{
	cout << "机房开放的时间为周一至周五!" << endl;
	cout << "请选择您要预约的日期：" << endl;
	cout << "1.周一" << endl;
	cout << "2.周二" << endl;
	cout << "3.周三" << endl;
	cout << "4.周四" << endl;
	cout << "5.周五" << endl;
	int date = 0;    //日期
	int interval = 0; //时间段
	int room = 0;   //机房
	while (true)
	{
		cin >> date;
		if (date >= 1 && date <= 5)
		{
			break;
		}
		cout << "输入有误，请重新输入：" << endl;
	}
	cout << "请选择您要预约的时间段：" << endl;
	cout << "1.上午" << endl;
	cout << "2.下午" << endl;
	while (true)
	{
		cin >> interval;
		if (interval == 1 || interval == 2)
		{
			break;
		}
		cout << "输入有误，请重新输入：" << endl;
	}
	cout << "请选择机房：" << endl;
	for (int i = 0;i < vCom.size();i++)
	{
		cout << vCom[i].m_ComId << "号机房的容量为：" << vCom[i].m_MaxNum << endl;
	}
	while (true)
	{
		cin >> room;
		if (room>=1&&room<=3)
		{
			break;
		}
		cout << "输入有误，请重新输入：" << endl;
	}
	cout << "预约成功，审核中" << endl;
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::app);
	ofs << "date:" << date<<" ";
	ofs << "interval:" << interval << " ";
	ofs << "stuName:" << this->m_Name << " ";
	ofs << "stuId:" << this->m_Id << " ";
	ofs << "room:" << room<<" ";
	ofs << "status:" << 1<<endl;
	ofs.close();
	system("pause");
	system("cls");
		
}

//查看自身预约
void Student::showMyOrder()
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
		//string 转int
		//string利用.c_str（）转为const char*
		//利用atoi(const char*) 转为int
		if (this->m_Id == atoi(of.m_orderData[i]["stuId"].c_str()))
		{
			cout << "星期：" << of.m_orderData[i]["date"];
			cout << " 时间段：" << (of.m_orderData[i]["interval"] == "1"? "上午" : "下午");
			cout << " 机房：" << of.m_orderData[i]["room"];
			string status= " 状态：";


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
			
	}
	system("pause");
	system("cls");
}

void //查看所有预约
Student::showAllOrder()
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
	return;
}

//取消预约
void Student::cancelOrder()
{
	orderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "审核中或预约成功的记录可取消预约，请选择要取消的记录：" << endl;

	vector<int> v;//存放可操作预约记录在最大容器中的下标
	int index = 1;
	for (int i = 0;i < of.m_Size;i++)
	{
		//先判断是自身学号
		if (this->m_Id == atoi(of.m_orderData[i]["stuId"].c_str()))
		{
			//再审核状态  预约中或预约成功
			if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2")
			{
				v.push_back(i);
				
				cout << index++ << "." << endl;
				cout << "星期" << of.m_orderData[i]["date"];
				cout << " 时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
				cout << " 机房：" << of.m_orderData[i]["room"];
				string status = " 状态：";
				if (of.m_orderData[i]["status"] == "1")
				{
					status += "预约中";
				}
				else if (of.m_orderData[i]["status"] == "2")
				{
					status += "已预约";
				}
				cout <<" "<< status << endl;
			}

		}
	}
	cout << "请输入要取消的预约记录，按0返回" << endl;
	int select = 0;
	while (true)
	{
		cin >> select;
		if (select >= 0 && select <= v.size())
		{
			if (select == 0)
			{
				system("cls");
				return;
			}
			else
			{
				of.m_orderData[v[select - 1]]["status"] = "0";
				cout << "成功取消预约！" << endl;
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
	return;
}