#include "speechManager.h"
#include <algorithm>
#include <functional>
#include <numeric>
#include <deque>
#include <fstream>
#include <ctime>

SpeechManager::SpeechManager() {
	this->initSpeech();
	this->createSpeaker();
	//���������¼
	this->loadRecord();
}

SpeechManager::~SpeechManager() {

}

void SpeechManager::exitSystem() {
	cout << "��л����ʹ�ã�" << endl;
	system("pause");
	exit(0); //�˳�
}

void SpeechManager::show_Menu() {
	cout << "***********************************************" << endl;
	cout << "*****************   ��ӭ�μӱ���   ***************" << endl;
	cout << "*****************  1.��ʼ�ݽ�����  ****************" << endl;
	cout << "*****************  2.�鿴�����¼  ****************" << endl;
	cout << "*****************  3.��ձ�����¼  ****************" << endl;
	cout << "*****************  0.�˳���������  ****************" << endl;
	cout << "***********************************************" << endl;
	cout << endl;
}

void SpeechManager::initSpeech() {
	//����ȫ�����
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	this->m_Record.clear();
	//�����ִγ�ʼ��
	this->m_Index = 1;
}

void SpeechManager::createSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++) {
		string name = "ѡ��";
		name += nameSeed[i];

		Speaker sp;
		sp.m_Name = name;
		for (int i = 0; i < 2; i++) {
			sp.m_Score[i] = 0;
		}
		 
		this->v1.push_back(i + 10001); //��Աid

		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}

//��ǩ
void SpeechManager::speechDraw() {
	cout << "��<" << this->m_Index << ">��ѡ�����ڳ�ǩ" << endl;
	cout << "-------------------------------------------" << endl;
	cout << "��ǩ������£�" << endl;
	//�������
	srand((unsigned int)time(NULL));
	if (this->m_Index == 1) {
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}
	else {
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "-------------------------------------------" << endl;
	system("pause");
}

//����
void SpeechManager::speechContest() {
	cout << "--------------��<" << this->m_Index << ">����ʽ������ʼ��--------------" << endl;
	multimap<double, int, greater<double>> groupScore;  //��ʱ����������key������value��ѡ�ֱ��
	int num = 0;//��¼������6��һ��

	vector<int> v_Src;
	if (this->m_Index == 1) {
		v_Src = v1;
	}
	else {
		v_Src = v2;
	}

	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++) {
		num++;
		deque<double> d;
		for (int i = 0; i < 10; i++) {        //10����ί
			double score = (rand() % 401 + 600) / 10.f;  //600~100
			d.push_back(score);
		}
		sort(d.begin(), d.end(), greater<double>());
		//ȥ����ͺ���߷�
		d.pop_back();
		d.pop_front();

		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();

		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;  //��map�����б��������˵�һ�ֵķ���
		groupScore.insert(make_pair(avg, *it));   //��ʱ�������棬�����ж�num�Ƿ����6. 6��һ�鵥������
		if (num % 6 == 0) {
			cout << "��<" << num / 6 << ">С��������Σ�" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++) {
				cout << "��ţ�" << it->second << " ������" << this->m_Speaker[it->second].m_Name << " �ɼ���" << this->m_Speaker[it->second].m_Score[m_Index-1] << endl;
			}
			int count = 0;
			//ȡǰ����  multimap<double, int, greater<double>> �ݴ�ǰ������ÿ�β�����֮����գ�������һ�ִ洢��
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++) {
				count++;
				if (this->m_Index == 1) {
					v2.push_back(it->second);
				}
				else {
					vVictory.push_back(it->second);
				}
			}
			groupScore.clear();
		}
	}
	cout << "--------------��<" << this->m_Index << ">�ֱ������-------------" << endl;
	system("pause");
}

//���Ʊ�������
void SpeechManager::startSpeech() {
	//��һ��
	//1.��ǩ
	this->speechDraw();
	//2.����
	this->speechContest();
	//3.��ʾ�������
	this->showRes();
	//�ڶ���
	this->m_Index++;
	//1.��ǩ
	this->speechDraw();
	//2.����
	this->speechContest();
	//3.��ʾ���ս��
	this->showRes();
	//4.�������
	this->saveRecord();

	//������Ϣ
	this->initSpeech();
	this->createSpeaker();
	this->loadRecord();

	cout << "��������ѽ�����" << endl;
	system("pause");
	system("cls");
}

void SpeechManager::showRes() {
	cout << "-----------------------��<"<< this->m_Index <<">�ֱ����������-------------------------" << endl;
	vector<int> v;
	if (this->m_Index == 1) {
		v = v2;
	}
	else
	{
		v = vVictory;
	}
	//int number = 1;
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << "ѡ�ֱ��"<< *it <<" ������" << this->m_Speaker[*it].m_Name << " �÷֣�" << this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
		//number++;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_Menu();
}
void SpeechManager::saveRecord() {
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++) {
		ofs << *it << "," << this->m_Speaker[*it].m_Name << "," << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "��¼�ѱ��棡" << endl;
	//�ļ���Ϊ��
	this->fileIsEmpty = false;
}

//�鿴��¼
void SpeechManager::loadRecord() {
	ifstream ifs;
	ifs.open("speech.csv", ios::in);
	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		//cout << "�ļ�������..." << endl;
		ifs.close();
		return;
	}

	//�ļ�����չ�
	char ch;
	ifs >> ch;
	//�����ļ���β
	if (ifs.eof()) {
		//cout << "�ļ�Ϊ��..." << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	this->fileIsEmpty = false;
	ifs.putback(ch);//��Ϊ�ո�Ϊ���ж��ļ��Ƿ񵽴��β��������һ���ַ���

	string data;
	int index = 0;
	while (ifs >> data) {
		vector<string> v;
		int pos = -1;
		int start = 0;

		while (true) {
			pos = data.find(",",start);   //����ʼλ�ÿ�ʼ��
			if (pos == -1) {
				break;
			}
			string temp = data.substr(start, pos - start);
			v.push_back(temp);
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
}

void SpeechManager::showRecord() {
	if (this->fileIsEmpty) {
		cout << "�ļ������ڻ�Ϊ��..." << endl;
		return;
	}
	for (int i = 0; i < m_Record.size();i++) {
		cout << "------��<" << i + 1 << ">��------\n" << "�ھ����" << m_Record[i][0] << "����" << m_Record[i][1] << "�÷�" << m_Record[i][2] << endl \
			<< "�Ǿ����" << m_Record[i][3] << "����" << m_Record[i][4] << "�÷�" << m_Record[i][5] << endl \
			<< "�������" << m_Record[i][6] << "����" << m_Record[i][7] << "�÷�" << m_Record[i][8] << endl;
		cout << endl;
	}
	system("pause");
	system("cls");
}
