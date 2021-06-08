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
			cout << "ע���ɹ�" << endl;
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
			cout << "ע���ɹ�" << endl;          //ע����¼
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
		//���ù���Ա�Ӳ˵�����
		manager->operMenu();  //ͨ����̬����������������д����

		//������ָ��ǿ������ת��������ָ�룬���������������нӿڣ��ǹ����ӿڣ�������д������
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
			cout << "ע���ɹ�" << endl;
			delete manager;
			system("pause");
			system("cls");
			return;
		}
	}
}

//��¼����  ����һ�������ļ���   �������������������
void loginIn(string filename, int type)
{
	//����ָ�� ����ָ���������
	Identity* person = NULL;

	//���ļ�
	ifstream ifs;
	ifs.open(filename, ios::in);

	//�ж��ļ��Ƿ����
	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}
	//׼�������û���Ϣ
	int id = 0;
	string name;
	string pwd;

	//�ж����
	if (type == 1)
	{
		cout << "���������ѧ�ţ�" << endl;
		cin >> id;
	}
	else if (type == 2)
	{
		cout << "���������ְ���ţ�" << endl;
		cin >> id;
	}
	cout << "�������û�����" << endl;
	cin >> name;
	cout << "���������룺" << endl;
	cin >> pwd;

	if (type == 1)
	{
	    //��֤ѧ����Ϣ
		int Fid;        //���ļ��ж�ȡ��ID��
		string Fname;  //���ļ��ж�ȡ������
		string Fpwd;   //���ļ��ж�ȡ������
		while (ifs >> Fid && ifs >> Fname && ifs >> Fpwd)
		{
			if (Fid == id && Fname == name && Fpwd == pwd)
			{
				cout << "ѧ����֤��¼�ɹ���" << endl;
				system("pause");
				system("cls");
				person = new Student(id, name, pwd);
				//����ѧ���Ӳ˵�
				studentMenu(person);


				return;
			}
		}
	}
	else if (type == 2)
	{
		//��֤��ʦ��Ϣ
		int Fid;
		string Fname;
		string Fpwd;
		while (ifs >> Fid && ifs >> Fname && ifs >> Fpwd)
		{
			if (Fid == id && Fname == name && Fpwd == pwd)
			{
				cout << "��ʦ��֤��¼�ɹ���" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				//�����ʦ�Ӳ˵�
				teacherMenu(person);

				return;
			}
		}

	}
	else if (type == 3)
	{
		//��֤����Ա��Ϣ
		string Fname;
		string Fpwd;
		ifs >> Fname && ifs >> Fpwd;
		if (Fname == name && Fpwd == pwd)
		{
			cout << "����Ա��֤��¼�ɹ���" << endl;
			system("pause");
			system("cls");
			person = new Manager(name, pwd);
			//�������Ա�Ӳ˵�����
			managerMenu(person);

			return;
		}
	}

	cout << "��֤��¼ʧ��" << endl;
	system("pause");
	system("cls");
	return;
}
void Menu()
{
	cout << "\t----------��ӭ��������ԤԼϵͳ-------------" << endl;
	cout << "����������ѡ��" << endl;
	cout << "\t\t -------------------------" << endl;
	cout << "\t\t|                         |" << endl;
	cout << "\t\t|         1.ѧ��          |" << endl;
	cout << "\t\t|                         |" << endl;
	cout << "\t\t|         2.��ʦ          |" << endl;
	cout << "\t\t|                         |" << endl;
	cout << "\t\t|         3.����Ա        |" << endl;
	cout << "\t\t|                         |" << endl;
	cout << "\t\t|         0.�˳�          |" << endl;
	cout << "\t\t|                         |" << endl;
	cout << "\t\t -------------------------" << endl;
}
int main()
{
	int select = 0;
	while (1)
	{
		Menu();
		cout << "���������ѡ��" << endl;
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
		case 0:        //�˳�
			cout << "��ӭ�´�ʹ��" << endl;
			system("pause");
			return 0; 
			break;
		default:
			cout << "������������������" << endl;
			system("pause");
			system("cls");
			break;
		}

	}
	system("pause");
	return 0;
}