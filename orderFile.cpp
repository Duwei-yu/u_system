#include"orderFile.h"


//���캯��
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
	this->m_Size = 0; //ԤԼ����
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

		//date:1  ��ȡ����
		int pos = date.find(":");//4

		if (pos != -1)
		{
			key = date.substr(0, pos);//���±�Ϊ����ַ���ʼ�أ���4��pos�����ַ�
			value = date.substr(pos + 1, date.size() - pos - 1);//size=6 pos=4 size-pos-1=1
			//cout << "key=" << key << endl;
			//cout << "value=" << value << endl;   ���Դ���
			m.insert(make_pair(key, value));
		}
		//��ȡʱ���
		pos = interval.find(":");
		if (pos != -1)
		{
			key = interval.substr(0, pos);
			value = interval.substr(pos + 1, interval.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		//��ȡ����
		 pos = name.find(":");
		if (pos != -1)
		{
			key = name.substr(0, pos);
			value = name.substr(pos + 1, name.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		//��ȡѧ��
		 pos = stuId.find(":");
		if (pos != -1)
		{
			key = stuId.substr(0, pos);
			value = stuId.substr(pos + 1, stuId.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		//��ȡ������Ϣ
		 pos = room.find(":");
		if (pos != -1)
		{
			key = room.substr(0, pos);
			value = room.substr(pos + 1, room.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		//��ȡԤԼ״̬
		 pos = status.find(":");
		if (pos != -1)
		{
			key = status.substr(0, pos);
			value = status.substr(pos + 1, status.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		//��Сmap�����з��뵽��map���� 
		m_orderData.insert(make_pair(this->m_Size, m));
		this->m_Size++;
			
	}
	ifs.close();

	//����
	/*for (map<int, map<string, string>>::iterator it = m_orderData.begin();it != m_orderData.end();it++)
	{
		cout << "����Ϊ��" << it->first <<" value="<< endl;
		for (map<string, string>::iterator mit = it->second.begin();mit != it->second.end();mit++)
		{
			cout << "key=" << mit->first << "  value=" << mit->second << endl;
		}
	}*/
}

//����ԤԼ��¼
void orderFile::updateOrder()
{
	if (this->m_Size == 0)
	{
		return; // ԤԼ��¼���� ֱ��return
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

