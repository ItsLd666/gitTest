#pragma once
#include <iostream>
#include "speaker.h"
#include <vector>
#include <map>
#include <fstream>

using namespace std;

class SpeechManager {
public:
	//���캯��
	SpeechManager();

	//��ʾ�˵�
	void show_Menu();

	//�˳�ϵͳ
	void exitSystem();

	//��������
	~SpeechManager();
	
	//��ʼ������
	void initSpeech();

	//����ѡ��
	void createSpeaker();

	//��ʼ����
	void startSpeech();
	void speechDraw();  //��ǩ
	void speechContest();  //����
	void showRes();
	void writeRes();

	//*****************************
	//******members available******
	//*****************************

	//��һ�� 12��
	vector<int> v1;

	//�ڶ��� 6��
	vector<int> v2;

	//ʤ�� 3��
	vector<int> vVictory;

	//ѡ�ֱ�� ��Ӧ������
	map<int, Speaker> m_Speaker;

	//�����ִ�
	int m_Index;
};