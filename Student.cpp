#include"Student.h"
#include<fstream>
#include"globalFile.h"

//Ĭ�Ϲ���
Student::Student()
{
};

//�вι���
Student::Student(int id, string name, string pwd)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;

	//��ʼ��������Ϣ
	//ifstream ifs(COMPUTER_FILE, ios::in);  ���ִ򿪷�ʽ������
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	computerRoom com;
	while (ifs >> com.m_ComId && ifs >> com.m_MaxNum)
	{
		//���ļ���ȡ����Ϣ�ŵ�������
		vCom.push_back(com);
	}
	ifs.close();
}

//�˵�����
void Student::operMenu()
{
	cout << "\t----------��ӭ" << this->m_Name << "����ѧ��ϵͳ-------------" << endl;
	cout << "����������ѡ��" << endl;
	cout << "\t\t -----------------------------" << endl;
	cout << "\t\t|                             |" << endl;
	cout << "\t\t|         1.����ԤԼ          |" << endl;
	cout << "\t\t|                             |" << endl;
	cout << "\t\t|         2.�鿴�ҵ�ԤԼ      |" << endl;
	cout << "\t\t|                             |" << endl;
	cout << "\t\t|         3.�鿴����ԤԼ      |" << endl;
	cout << "\t\t|                             |" << endl;
	cout << "\t\t|         4.ȡ��ԤԼ          |" << endl;
	cout << "\t\t|                             |" << endl;
	cout << "\t\t|         0.ע����¼          |" << endl;
	cout << "\t\t|                             |" << endl;
	cout << "\t\t -----------------------------" << endl;
}

//����ԤԼ
void Student::applyOrder()
{
	cout << "�������ŵ�ʱ��Ϊ��һ������!" << endl;
	cout << "��ѡ����ҪԤԼ�����ڣ�" << endl;
	cout << "1.��һ" << endl;
	cout << "2.�ܶ�" << endl;
	cout << "3.����" << endl;
	cout << "4.����" << endl;
	cout << "5.����" << endl;
	int date = 0;    //����
	int interval = 0; //ʱ���
	int room = 0;   //����
	while (true)
	{
		cin >> date;
		if (date >= 1 && date <= 5)
		{
			break;
		}
		cout << "�����������������룺" << endl;
	}
	cout << "��ѡ����ҪԤԼ��ʱ��Σ�" << endl;
	cout << "1.����" << endl;
	cout << "2.����" << endl;
	while (true)
	{
		cin >> interval;
		if (interval == 1 || interval == 2)
		{
			break;
		}
		cout << "�����������������룺" << endl;
	}
	cout << "��ѡ�������" << endl;
	for (int i = 0;i < vCom.size();i++)
	{
		cout << vCom[i].m_ComId << "�Ż���������Ϊ��" << vCom[i].m_MaxNum << endl;
	}
	while (true)
	{
		cin >> room;
		if (room>=1&&room<=3)
		{
			break;
		}
		cout << "�����������������룺" << endl;
	}
	cout << "ԤԼ�ɹ��������" << endl;
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

//�鿴����ԤԼ
void Student::showMyOrder()
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
		//string תint
		//string����.c_str����תΪconst char*
		//����atoi(const char*) תΪint
		if (this->m_Id == atoi(of.m_orderData[i]["stuId"].c_str()))
		{
			cout << "���ڣ�" << of.m_orderData[i]["date"];
			cout << " ʱ��Σ�" << (of.m_orderData[i]["interval"] == "1"? "����" : "����");
			cout << " ������" << of.m_orderData[i]["room"];
			string status= " ״̬��";


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
			
	}
	system("pause");
	system("cls");
}

void //�鿴����ԤԼ
Student::showAllOrder()
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
	return;
}

//ȡ��ԤԼ
void Student::cancelOrder()
{
	orderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "����л�ԤԼ�ɹ��ļ�¼��ȡ��ԤԼ����ѡ��Ҫȡ���ļ�¼��" << endl;

	vector<int> v;//��ſɲ���ԤԼ��¼����������е��±�
	int index = 1;
	for (int i = 0;i < of.m_Size;i++)
	{
		//���ж�������ѧ��
		if (this->m_Id == atoi(of.m_orderData[i]["stuId"].c_str()))
		{
			//�����״̬  ԤԼ�л�ԤԼ�ɹ�
			if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2")
			{
				v.push_back(i);
				
				cout << index++ << "." << endl;
				cout << "����" << of.m_orderData[i]["date"];
				cout << " ʱ��Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
				cout << " ������" << of.m_orderData[i]["room"];
				string status = " ״̬��";
				if (of.m_orderData[i]["status"] == "1")
				{
					status += "ԤԼ��";
				}
				else if (of.m_orderData[i]["status"] == "2")
				{
					status += "��ԤԼ";
				}
				cout <<" "<< status << endl;
			}

		}
	}
	cout << "������Ҫȡ����ԤԼ��¼����0����" << endl;
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
				cout << "�ɹ�ȡ��ԤԼ��" << endl;
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
	return;
}