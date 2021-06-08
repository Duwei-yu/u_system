#include"orderFile.h"


//构造函数
orderFile::orderFile()
{
	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);
	string date;
	string interval;
	string name;
	string stuId;
	string room ;
	string status;
	this->m_Size = 0; //预约条数
	while (ifs >> date && ifs >> interval && ifs >> name && ifs
		>> stuId && ifs >> room && ifs >> status)
	//{
	//	cout << date << endl;
	//	cout << interval << endl;
	//	cout << name << endl;
	//	cout << stuId << endl;
	//	cout << room << endl;
	//	cout << status << endl;
	//}
	{
		string key;
		string value;
		map<string, string> m;

		//date:1  截取日期
		int pos = date.find(":");//4

		if (pos != -1)
		{
			key = date.substr(0, pos);//从下标为零的字符开始截，截4（pos）个字符
			value = date.substr(pos + 1, date.size() - pos - 1);//size=6 pos=4 size-pos-1=1
			//cout << "key=" << key << endl;
			//cout << "value=" << value << endl;   测试代码
			m.insert(make_pair(key, value));
		}
		//截取时间段
		pos = interval.find(":");
		if (pos != -1)
		{
			key = interval.substr(0, pos);
			value = interval.substr(pos + 1, interval.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		//截取姓名
		 pos = name.find(":");
		if (pos != -1)
		{
			key = name.substr(0, pos);
			value = name.substr(pos + 1, name.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		//截取学号
		 pos = stuId.find(":");
		if (pos != -1)
		{
			key = stuId.substr(0, pos);
			value = stuId.substr(pos + 1, stuId.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		//截取机房信息
		 pos = room.find(":");
		if (pos != -1)
		{
			key = room.substr(0, pos);
			value = room.substr(pos + 1, room.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		//截取预约状态
		 pos = status.find(":");
		if (pos != -1)
		{
			key = status.substr(0, pos);
			value = status.substr(pos + 1, status.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		//将小map容器中放入到大map容器 
		m_orderData.insert(make_pair(this->m_Size, m));
		this->m_Size++;
			
	}
	ifs.close();

	//测试
	/*for (map<int, map<string, string>>::iterator it = m_orderData.begin();it != m_orderData.end();it++)
	{
		cout << "条数为：" << it->first <<" value="<< endl;
		for (map<string, string>::iterator mit = it->second.begin();mit != it->second.end();mit++)
		{
			cout << "key=" << mit->first << "  value=" << mit->second << endl;
		}
	}*/
}

//更新预约记录
void orderFile::updateOrder()
{
	if (this->m_Size == 0)
	{
		return; // 预约记录零条 直接return
	}
	ofstream ofs(ORDER_FILE, ios::out | ios::trunc);
	for (int i = 0;i < this->m_Size;i++)
	{
		ofs << "date:" << this->m_orderData[i]["date"] << " ";
		ofs << "interval:" << this->m_orderData[i]["interval"] << " ";
		ofs << "stuName:" << this->m_orderData[i]["stuName"] << " ";
		ofs << "stuId:" << this->m_orderData[i]["stuId"] << " ";
		ofs << "room:" << this->m_orderData[i]["room"] << " ";
		ofs << "status:" << this->m_orderData[i]["status"] <<endl;
	}
	ofs.close();
}

