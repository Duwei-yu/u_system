#include"Teacher.h"
//Ĭ�Ϲ���
Teacher::Teacher()
{

}

//�вι���
Teacher::Teacher(int empid, string name, string pwd)
{
	this->m_empId = empid;
	this->m_Name = name;
	this->m_Pwd = pwd;
}

//�˵�����
void Teacher::operMenu()
{
	cout << "\t----------��ӭ��ʦ" << this->m_Name << "��¼-------------" << endl;
	cout << "����������ѡ��" << endl;
	cout << "\t\t -----------------------------" << endl;
	cout << "\t\t|                             |" << endl;
	cout << "\t\t|         1.�鿴����ԤԼ      |" << endl;
	cout << "\t\t|                             |" << endl;
	cout << "\t\t|                             |" << endl;
	cout << "\t\t|         2.���ԤԼ          |" << endl;
	cout << "\t\t|                             |" << endl;
	cout << "\t\t|                             |" << endl;
	cout << "\t\t|         0.ע����¼          |" << endl;
	cout << "\t\t|                             |" << endl;
	cout << "\t\t -----------------------------" << endl;

}

//�鿴����ԤԼ
void Teacher::showAllOrder()
{
	orderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0;i < of.m_Size;i++)
	{
		cout << i + 1 << ".";
		cout << "����" << of.m_orderData[i]["date"];
		cout << " ʱ��Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
		cout << " ������" << of.m_orderData[i]["room"];
		cout << " ������" << of.m_orderData[i]["stuName"];
		cout << " ѧ�ţ�" << of.m_orderData[i]["stuId"];
		string status = " ״̬��";


		//1 ԤԼ�� 2 ��ԤԼ -1 ԤԼʧ�� 0ȡ��ԤԼ
		if (of.m_orderData[i]["status"] == "1")
		{
			status += "ԤԼ��";
		}
		else if (of.m_orderData[i]["status"] == "2")
		{
			status += "��ԤԼ";
		}
		else if (of.m_orderData[i]["status"] == "-1")
		{
			status += "ԤԼʧ��,���δͨ��";
		}
		else
		{
			status += "��ȡ��ԤԼ";
		}

		cout << " " << status << endl;

	}
	system("pause");
	system("cls");
}

//���ԤԼ
void Teacher::validOrder()
{
	orderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "����˵ļ�¼���£�" << endl;
	vector<int> v;
	int index = 0;
	for (int i = 0;i < of.m_Size;i++)
	{
		if (of.m_orderData[i]["status"] == "1")
		{
			v.push_back(i);
			cout <<++index << ".";
			cout << "����" << of.m_orderData[i]["date"];
			cout << " ʱ��Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
			cout << " ������" << of.m_orderData[i]["room"];
			cout << " ������" << of.m_orderData[i]["stuName"];
			cout << " ѧ�ţ�" << of.m_orderData[i]["stuId"];
			cout << " ״̬��ԤԼ��" << endl;
			
		}
	}
	cout << "��ѡ��Ҫ��˵�ԤԼ��¼����0����" << endl;
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
				cout << "��������˽��:" << endl;
				cout << "1.ͨ��" << endl;
				cout << "2.��ͨ��" << endl;
				cin >> ret;
				if (ret == 1)
				{
					of.m_orderData[v[select - 1]]["status"] = "2";
				}
				else
				{
					of.m_orderData[v[select - 1]]["status"] = "-1";
				}
				cout << "������" << endl;
				of.updateOrder();
				break;
			}
		}
		else
		{
			cout << "������������������" << endl;
		}

	}
	
	system("pause");
	system("cls");
}