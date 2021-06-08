#include"Manager.h"
//默认构造
Manager::Manager()
{

}

//有参构造
Manager::Manager(string name, string pwd)
{
	this->m_Name = name;
	this->m_Pwd = pwd;

	//初始化容器 获取所有学生和老师信息
	this->initVector();

	//初始化机房信息
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	computerRoom c;
	while (ifs >> c.m_ComId&& ifs >> c.m_MaxNum)
	{
		vCom.push_back(c);
	}
	ifs.close();
	cout << "机房数量为：" << vCom.size()<<endl;

}

//菜单界面
void Manager::operMenu()
{
	cout << "\t----------欢迎"<<this->m_Name<<"来到管理系统-------------" << endl;
	cout << "请输入您的选择：" << endl;
	cout << "\t\t -----------------------------" << endl;
	cout << "\t\t|                             |" << endl;
	cout << "\t\t|         1.添加账号          |" << endl;
	cout << "\t\t|                             |" << endl;
	cout << "\t\t|         2.查看账号          |" << endl;
	cout << "\t\t|                             |" << endl;
	cout << "\t\t|         3.查看机房信息      |" << endl;
	cout << "\t\t|                             |" << endl;
	cout << "\t\t|         4.清空文件          |" << endl;
	cout << "\t\t|                             |" << endl;
	cout << "\t\t|         0.注销登录          |" << endl;
	cout << "\t\t|                             |" << endl;
	cout << "\t\t -----------------------------" << endl;
}

//添加账号
void Manager::addPerson()
{
	cout << "请选择你要添加的账号类型：" << endl;
	cout << "1.添加学生" << endl;
	cout << "2.添加教师" << endl;
	string tip;
	string errTip;
	string fileName; //操作文件名
	int select;
	ofstream ofs;   //文件操作对象
	
	while (true)
	{
		cin >> select;
		if (select == 1)
		{
			fileName = STUDENT_FILE;
			tip = "请输入学号";
			errTip = "学号重复，请重新输入：" ;
			break;
		}
		else if (select == 2)
		{
			fileName = TEACHER_FILE;
			tip = "请输入教师编号";
			errTip = "职工号重复，请重新输入：";
			break;
		}
		else
		{
			cout << "输入有误，请重新输入" << endl;
			system("pause");
			system("cls");
		}
	}
	//利用追加的方式写文件
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
	cout << "请输入姓名：" << endl;
	cin >> name;
	cout << "请输入密码：" << endl;
	cin >> pwd;
	//向文件中添加数据
	ofs << id << " " << name << " " << pwd << endl;
	cout << "添加成功!" << endl;

	system("pause");
	system("cls");
	ofs.close();

	//初始化容器，让容器中的元素及时更新，避免能连续添加相同学号/职工号的BUG
	this->initVector();
}

void printStudent(Student& s)
{
	cout << "学号：" << s.m_Id << " 姓名：" << s.m_Name <<  "  密码：" << s.m_Pwd << endl;
}
class printTeacher
{
public:
	void operator()(Teacher& t)
	{
		cout<< "职工号：" << t.m_empId << " 姓名：" <<t.m_Name <<  "  密码：" << t.m_Pwd << endl;
	}
};

//查看账号
void Manager::showPerson()
{
	cout << "请选择查看内容：" << endl;
	cout << "1.查看所有学生信息" << endl;
	cout << "2.查看所有教师信息" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		cout << "所有学生信息如下：" << endl;
		for_each(vStu.begin(), vStu.end(), printStudent);  //调用普通函数printStudent

	}
	else
	{
		cout << "所有老师信息如下：" << endl;
		for_each(vTe.begin(), vTe.end(), printTeacher());  //调用仿函数printTeacher()
	}
	system("pause");
	system("cls");
}

//查看机房信息
void Manager::showComputer()
{
	cout << "机房的信息如下：" << endl;
	for (vector<computerRoom>::iterator it = vCom.begin();it != vCom.end();it++)
	{
		cout << "机房编号：" << it->m_ComId << "  机房最大容量：" << it->m_MaxNum << endl;
	}
	system("pause");
	system("cls");
}

//清空文件
void Manager::cleanFile()
{
	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();

	cout << "清空成功!"<<endl;
	system("pause");
	system("cls");
}

//初始化容器
void  Manager::initVector()
{
	vStu.clear();
	vTe.clear();

	//读取信息 学生 
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件读取失败" << endl;

	}
	Student s;
	while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd)
	{
		vStu.push_back(s);
	}
	cout << "学生人数为：" << vStu.size() << endl;
	ifs.close();

	//读取信息 老师 
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件读取失败" << endl;

	}
	Teacher t;
	while (ifs >> t.m_empId && ifs >> t.m_Name && ifs >> t.m_Pwd)
	{
		vTe.push_back(t);
	}
	cout << "老师人数为：" << vTe.size() << endl;
	ifs.close();
}
//检测重复   参数1 检测 学号/职工号   参数2  检测的类型
bool Manager::checkRepeat(int id, int type)
{
	if (type == 1)  //检测学生
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
	{              //检测老师
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