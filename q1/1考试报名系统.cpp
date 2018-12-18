#include <iostream>
#include <string>
#include <iomanip>
#pragma warning(disable:4996)
using namespace std;
struct student {
	int id;
	string name;
	string sex;
	int age;
	string type;
};

class LinkNode {
public:
	struct student data;
	LinkNode * link;
	LinkNode() :link(NULL) {}
	//����ѧ����Ϣ
	void input() {
		cin >> data.id
			>> data.name
			>> data.sex
			>> data.age
			>> data.type;
	}
};
void outputstud(LinkNode *p);
class List {
private:
	//��ͷ���
	LinkNode * sentinal;
public:
	void output() {
		int space = 18;
		cout << "����" << setw(space) << "����" << setw(space) << "�Ա�" << setw(space) << "����"
			<< setw(space) << "�������" << endl;
		LinkNode * p = sentinal->link;
		while (p != NULL) {
			outputstud(p);
			p = p->link;
		}
	}
	List() {
		sentinal = new LinkNode();
	}
	~List() {
		LinkNode * p = sentinal;
		while (p->link != NULL) {
			LinkNode * tmp = p;
			p = p->link;
			delete p;
		}
	}
	//����ѧ����Ϣ
	bool insert(int index) {
		LinkNode * p = sentinal;
		//pΪ������λ�õ�ǰ��ָ��
		for (int i = 1; i < index; i++) {
			if (p != NULL) {
				p = p->link;
			}
			else {
				return false;
			}
		}
		LinkNode * tmp = p->link;
		p->link = new LinkNode();
		cout << "���������뿼���Ŀ��ţ��������Ա����估�������" << endl;
		p->link->input();
		p->link->link = tmp;
		output();
		return true;
	}
	//����ѧ����Ϣ
	void build() {
		int number;
		cout << "�����뿼��������" << endl;
		cin >> number;
		LinkNode * p = sentinal;
		cout << "���������뿼���Ŀ��ţ��������Ա����估�������" << endl;
		for (int i = 0; i < number; i++) {
			p->link = new LinkNode();
			p->link->input();
			p = p->link;
		}
		output();
	}
	//ɾ��ѧ��
	void deleteitem(int id) {
		LinkNode * p = sentinal->link;
		LinkNode * prev = sentinal;
		while (p != NULL) {
			if (p->data.id == id) break;
			else {
				prev = p;
				p = p->link;
			}
		}
		if (p) {
			prev->link = p->link;
		}
		int space = 18;
		cout << "��ɾ���Ŀ�����Ϣ��: ";
		outputstud(p);
		delete p;
		output();
	}
	//����ѧ��
	LinkNode * search(int id) {
		LinkNode * p = sentinal->link;
		while (p != NULL) {
			if (p->data.id == id) {
				return p;
			}
			else {
				p = p->link;
			}
		}
		cout << "can not find" << endl;
		return NULL;
	}
	//�޸�ѧ����Ϣ
	bool modify(int id) {
		LinkNode * p = search(id);
		if (p == NULL) {
			return false;
		}
		cout << "���������뿼���Ŀ��ţ��������Ա����估�������" << endl;
		p->input();
		output();
		return true;
	}

};
void outputstud(LinkNode *p) {
	int space = 18;
	if (p != NULL)
		cout << setw(4) << p->data.id << setw(space) << p->data.name << setw(space) << p->data.sex << setw(space) <<
		p->data.age << setw(space) << p->data.type << endl;
}
int main() {
	//freopen("Text1.txt", "r", stdin);
	cout << "�����뽨��������Ϣϵͳ��" << endl;
	List * students = new List();
	students->build();
	int operation;
	cout << "��ѡ����Ҫ���еĲ���:(1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ��������" << endl;
	cin >> operation;
	while (operation != 0) {
		switch (operation) {
		case 1:
			cout << "��������Ҫ����Ŀ�����λ��:" << endl;
			int index;
			cin >> index;
			students->insert(index);
			break;
		case 2:
			cout << "������Ҫɾ���Ŀ����Ŀ���:" << endl;
			int id;
			cin >> id;
			students->deleteitem(id);
			break;
		case 3:
			cout << "������Ҫ���ҵĿ����Ŀ���:" << endl;;
			int id2;
			cin >> id2;
			LinkNode * p;
			p = students->search(id2);
			int space;
			space = 18;
			if (p != NULL)
				cout << "����" << setw(space) << "����" << setw(space) << "�Ա�" << setw(space) << "����"
				<< setw(space) << "�������" << endl;
			outputstud(p);
			break;
		case 4:
			cout << "������Ҫ�޸ĵĿ����Ŀ���:" << endl;
			int id3;
			cin >> id3;
			students->modify(id3);
			break;
		case 5:
			students->output();
			break;
		case 0:
			cout << "����ȡ������";
			break;

		}
		operation = 0;
		cout << "��ѡ����Ҫ���еĲ���:(1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ��������";
		cin >> operation;
		cout << endl;
	}
	cout << "����ȡ������" << endl;
	return 0;
}
