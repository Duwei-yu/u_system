#pragma once
#include"Identity.h"
#include <fstream>
#include"globalFile.h"
#include<vector>
#include"Student.h"
#include"Teacher.h"
#include<algorithm>
#include"computerRoom.h"
class Manager :public Identity
{
public:
	//Ĭ�Ϲ���
	Manager();

	//�вι���
	Manager(string name, string pwd);

	//�˵�����
	virtual void operMenu();

	//����˺�
	void addPerson();

	//�鿴�˺�
	void showPerson();

	//�鿴������Ϣ
	void showComputer();

	//����ļ�
	void cleanFile();

	//��ʼ������
	void initVector();

	//����ظ�   ����1 ��� ѧ��/ְ����   ����2  ��������
	bool checkRepeat(int id, int type);

	//ѧ������
	vector<Student> vStu;

	//��ʦ����
	vector<Teacher> vTe;

	//��������
	vector<computerRoom> vCom;

};