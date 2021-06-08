#include"Manager.h"
//Ĭ�Ϲ���
Manager::Manager()
{

}

//�вι���
Manager::Manager(string name, string pwd)
{
	this->m_Name = name;
	this->m_Pwd = pwd;

	//��ʼ������ ��ȡ����ѧ������ʦ��Ϣ
	this->initVector();

	//��ʼ��������Ϣ
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	computerRoom c;
	while (ifs >> c.m_ComId&& ifs >> c.m_MaxNum)
	{
		vCom.push_back(c);
	}
	ifs.close();
	cout << "��������Ϊ��" << vCom.size()<<endl;

}

//�˵�����
void Manager::operMenu()
{
	cout << "\t----------��ӭ"<<this->m_Name<<"��������ϵͳ-------------" << endl;
	cout << "����������ѡ��" << endl;
	cout << "\t\t -----------------------------" << endl;
	cout << "\t\t|                             |" << endl;
	cout << "\t\t|         1.����˺�          |" << endl;
	cout << "\t\t|                             |" << endl;
	cout << "\t\t|         2.�鿴�˺�          |" << endl;
	cout << "\t\t|                             |" << endl;
	cout << "\t\t|         3.�鿴������Ϣ      |" << endl;
	cout << "\t\t|                             |" << endl;
	cout << "\t\t|         4.����ļ�          |" << endl;
	cout << "\t\t|                             |" << endl;
	cout << "\t\t|         0.ע����¼          |" << endl;
	cout << "\t\t|                             |" << endl;
	cout << "\t\t -----------------------------" << endl;
}

//����˺�
void Manager::addPerson()
{
	cout << "��ѡ����Ҫ��ӵ��˺����ͣ�" << endl;
	cout << "1.���ѧ��" << endl;
	cout << "2.��ӽ�ʦ" << endl;
	string tip;
	string errTip;
	string fileName; //�����ļ���
	int select;
	ofstream ofs;   //�ļ���������
	
	while (true)
	{
		cin >> select;
		if (select == 1)
		{
			fileName = STUDENT_FILE;
			tip = "������ѧ��";
			errTip = "ѧ���ظ������������룺" ;
			break;
		}
		else if (select == 2)
		{
			fileName = TEACHER_FILE;
			tip = "�������ʦ���";
			errTip = "ְ�����ظ������������룺";
			break;
		}
		else
		{
			cout << "������������������" << endl;
			system("pause");
			system("cls");
		}
	}
	//����׷�ӵķ�ʽд�ļ�
	ofs.open(fileName, ios::out | ios::app);
	int id;
	string name;
	string pwd;
	cout << tip << endl;
	while (true)
	{
		cin >> id;
		bool ret = checkRepeat(id, select);
		if (ret)
		{
			cout << errTip << endl;
		}
		else
		{
			break;
		}
	}
	cout << "������������" << endl;
	cin >> name;
	cout << "���������룺" << endl;
	cin >> pwd;
	//���ļ����������
	ofs << id << " " << name << " " << pwd << endl;
	cout << "��ӳɹ�!" << endl;

	system("pause");
	system("cls");
	ofs.close();

	//��ʼ���������������е�Ԫ�ؼ�ʱ���£����������������ͬѧ��/ְ���ŵ�BUG
	this->initVector();
}

void printStudent(Student& s)
{
	cout << "ѧ�ţ�" << s.m_Id << " ������" << s.m_Name <<  "  ���룺" << s.m_Pwd << endl;
}
class printTeacher
{
public:
	void operator()(Teacher& t)
	{
		cout<< "ְ���ţ�" << t.m_empId << " ������" <<t.m_Name <<  "  ���룺" << t.m_Pwd << endl;
	}
};

//�鿴�˺�
void Manager::showPerson()
{
	cout << "��ѡ��鿴���ݣ�" << endl;
	cout << "1.�鿴����ѧ����Ϣ" << endl;
	cout << "2.�鿴���н�ʦ��Ϣ" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		cout << "����ѧ����Ϣ���£�" << endl;
		for_each(vStu.begin(), vStu.end(), printStudent);  //������ͨ����printStudent

	}
	else
	{
		cout << "������ʦ��Ϣ���£�" << endl;
		for_each(vTe.begin(), vTe.end(), printTeacher());  //���÷º���printTeacher()
	}
	system("pause");
	system("cls");
}

//�鿴������Ϣ
void Manager::showComputer()
{
	cout << "��������Ϣ���£�" << endl;
	for (vector<computerRoom>::iterator it = vCom.begin();it != vCom.end();it++)
	{
		cout << "������ţ�" << it->m_ComId << "  �������������" << it->m_MaxNum << endl;
	}
	system("pause");
	system("cls");
}

//����ļ�
void Manager::cleanFile()
{
	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();

	cout << "��ճɹ�!"<<endl;
	system("pause");
	system("cls");
}

//��ʼ������
void  Manager::initVector()
{
	vStu.clear();
	vTe.clear();

	//��ȡ��Ϣ ѧ�� 
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ȡʧ��" << endl;

	}
	Student s;
	while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd)
	{
		vStu.push_back(s);
	}
	cout << "ѧ������Ϊ��" << vStu.size() << endl;
	ifs.close();

	//��ȡ��Ϣ ��ʦ 
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ȡʧ��" << endl;

	}
	Teacher t;
	while (ifs >> t.m_empId && ifs >> t.m_Name && ifs >> t.m_Pwd)
	{
		vTe.push_back(t);
	}
	cout << "��ʦ����Ϊ��" << vTe.size() << endl;
	ifs.close();
}
//����ظ�   ����1 ��� ѧ��/ְ����   ����2  ��������
bool Manager::checkRepeat(int id, int type)
{
	if (type == 1)  //���ѧ��
	{
		for (vector<Student>::iterator it = vStu.begin();it != vStu.end();it++)
		{
			if (it->m_Id == id)
			{
				return true;
			}
		}
	}
	else
	{              //�����ʦ
	  for (vector<Teacher>::iterator it = vTe.begin();it != vTe.end();it++)
	  {
		if (it->m_empId == id)
		{
			return true;
		}
	  }
	}
	return false;
	
}