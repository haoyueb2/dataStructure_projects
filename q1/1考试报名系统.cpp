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
	//输入学生信息
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
	//表头结点
	LinkNode * sentinal;
public:
	void output() {
		int space = 18;
		cout << "考号" << setw(space) << "姓名" << setw(space) << "性别" << setw(space) << "年龄"
			<< setw(space) << "报考类别" << endl;
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
	//插入学生信息
	bool insert(int index) {
		LinkNode * p = sentinal;
		//p为所插入位置的前驱指针
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
		cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别！" << endl;
		p->link->input();
		p->link->link = tmp;
		output();
		return true;
	}
	//建立学生信息
	void build() {
		int number;
		cout << "请输入考生人数：" << endl;
		cin >> number;
		LinkNode * p = sentinal;
		cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别！" << endl;
		for (int i = 0; i < number; i++) {
			p->link = new LinkNode();
			p->link->input();
			p = p->link;
		}
		output();
	}
	//删除学生
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
		cout << "你删除的考生信息是: ";
		outputstud(p);
		delete p;
		output();
	}
	//查找学生
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
	//修改学生信息
	bool modify(int id) {
		LinkNode * p = search(id);
		if (p == NULL) {
			return false;
		}
		cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别！" << endl;
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
	cout << "首先请建立考生信息系统：" << endl;
	List * students = new List();
	students->build();
	int operation;
	cout << "请选择您要进行的操作:(1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）" << endl;
	cin >> operation;
	while (operation != 0) {
		switch (operation) {
		case 1:
			cout << "请输入你要插入的考生的位置:" << endl;
			int index;
			cin >> index;
			students->insert(index);
			break;
		case 2:
			cout << "请输入要删除的考生的考号:" << endl;
			int id;
			cin >> id;
			students->deleteitem(id);
			break;
		case 3:
			cout << "请输入要查找的考生的考号:" << endl;;
			int id2;
			cin >> id2;
			LinkNode * p;
			p = students->search(id2);
			int space;
			space = 18;
			if (p != NULL)
				cout << "考号" << setw(space) << "姓名" << setw(space) << "性别" << setw(space) << "年龄"
				<< setw(space) << "报考类别" << endl;
			outputstud(p);
			break;
		case 4:
			cout << "请输入要修改的考生的考号:" << endl;
			int id3;
			cin >> id3;
			students->modify(id3);
			break;
		case 5:
			students->output();
			break;
		case 0:
			cout << "您已取消操作";
			break;

		}
		operation = 0;
		cout << "请选择您要进行的操作:(1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）";
		cin >> operation;
		cout << endl;
	}
	cout << "您已取消操作" << endl;
	return 0;
}
