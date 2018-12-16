#include <iostream>
#include <string>
#pragma warning(disable:4996)
using namespace std;
class TreeNode {
public:
	string data;
	TreeNode * child;
	TreeNode * sibling;
	TreeNode() : data(""), child(NULL), sibling(NULL) {}
	TreeNode(string name) : data(name), child(NULL), sibling(NULL) {}
};
class Tree {
	
private:
	//ɾ��һ���ڵ�������ֵ� 
	void del_sibling(TreeNode *&p) {
		if (p != NULL) {
			del_sibling(p->sibling);
			delete p;
			p = NULL;
		}
	}
	TreeNode * root;
public:
	Tree() : root(NULL) {};
	//��������
	TreeNode * root_() {
		return root;
	}
	~Tree() {
		del_family(root);
	}
	//������
	void create(string name) {
		root = new TreeNode(name);
	}
	//��dataΪĳһ���ݵĽڵ�
	TreeNode * find(TreeNode * p, string name) {
		if (p == NULL) return NULL;
		if (p->data == name) {
			return p;
		}
		else {
			TreeNode * res = find(p->child, name);
			if (res != NULL) {
				return res;
			}
			else {
				return find(p->sibling, name);
			}
		}
	}
	//��ĳһ��Ů�����丸�׵ļ�ͥ
	bool insert(TreeNode * parent, string child) {
		TreeNode * p = parent;
		if (p == NULL) return false;
		if (p->child == NULL) {
			p->child = new TreeNode(child);
		}
		else {
			p = p->child;
			while (p->sibling != NULL) {
				p = p->sibling;
			}
			p->sibling = new TreeNode(child);
		}
		return true;
	}
	//����ĳһ����Ա����
	bool change(string oldname, string newname) {
		TreeNode * p = find(root, oldname);
		if (p == NULL) return false;
		p->data = newname;
		return true;
	}
	//ɾ��ĳһ��Ա��������Ů
	bool del_family(TreeNode * parent) {
		TreeNode * p = parent;
		if (p == NULL) return false;
		del_sibling(p->child);
		return true;
	}
	//���ĳһ��Ա������Ů
	void showChildren(TreeNode * parent) {
		if (parent->child == NULL) {
			cout << parent->data << "û����Ů" << endl;
		}
		else {
			TreeNode * p = parent->child;
			cout << parent->data << "�ĵ�һ��������:";
			while (p != NULL) {
				cout << p->data << ' ' ;
				p = p->sibling;
			}
			cout << endl;
		}
	}
};
void completeFamily(Tree * family) {
	string name;
	cout << "������Ҫ������ͥ���˵�����:" ;
	cin >> name;
	cout << endl;
	TreeNode * p = family->find(family->root_(), name);
	if (p == NULL) {
		cout << "δ�ҵ�����" << endl;
		return;
	}
	if (p->child) {
		cout << p->data << "�Ѿ���������ͥ" << endl;
		return;
	}
	cout << "������" << p->data << "�Ķ�Ů������" ;
	int child_num = 0;
	cin >> child_num;
	cout << endl;
	cout << "����������" << p->data << "�Ķ�Ů��������";
	for (int i = 0; i < child_num; i++) {
		cin >> name;
		family->insert(p, name);
	}
	cout << endl;
	family->showChildren(p);
	cout << endl;
}
void insertFamily(Tree * family) {
	string name;
	cout << "������Ҫ��Ӷ��ӣ���Ů�������˵�������";
	cin >> name;
	TreeNode * p = family->find(family->root_(), name);
	if (p == NULL) {
		cout << "δ�ҵ�����" << endl;
		return;
	}
	cout << endl;
	cout << "������" << p->data << "����ӵĶ��ӣ���Ů������������";
	cin >> name;
	cout << endl;
	family->insert(p, name);
	family->showChildren(p);
	cout << endl;
}
void deleteFamily(Tree * family) {
	string name;
	cout << "������Ҫ��ɢ��ͥ���˵�������" ;
	cin >> name;
	cout << endl;
	TreeNode * p = family->find(family->root_(), name);
	if (p == NULL) {
		cout << "���޴���" << endl;
		return;
	}
	cout << "Ҫ��ɢ��ͥ�����ǣ�" << name << endl;
	family->showChildren(p);
	family->del_family(p);
	//family->showChildren(p);
	cout << endl;
}
void changeMember(Tree * family) {
	string name;
	cout << "������Ҫ�����������˵�����:" ;
	cin >> name;
	cout << endl;
	TreeNode * p = family->find(family->root_(), name);
	if (p == NULL) {
		cout << "���޴���" << endl;
		cout << endl;
		return;
	}
	cout << "��������ĺ������:";
	cin >> p->data;
	cout << endl;
	cout << name << "�Ѿ�����Ϊ" << p->data << endl;
	cout << endl;
}
int main() {
	//freopen("Text6.txt", "r", stdin);
	cout << "**                         ���׹���ϵͳ                         **" << endl;
		cout << "==================================================================" << endl;
	cout << "**                     ��ѡ��Ҫִ�еĲ�����                     **" << endl;
	cout << "**                     A --- ���Ƽ�ͥ                           **" << endl;
	cout << "**                     B --- ��Ӽ�ͥ��Ա                       **" << endl;
	cout << "**                     C --- ��ɢ�ֲ���Ա                       **" << endl;
	cout << "**                     D --- ���ļ�ͥ��Ա����                   **" << endl;
	cout << "**                     E --- �˳�����                           **" << endl;
	cout << "==================================================================" << endl;

	
	string name;
	cout << "���Ƚ���һ�����ף�" << endl
		<< "���������ȵ�������";
	cin >> name;
	Tree * family = new Tree();
	family->create(name);
	cout << "�˼��׵������ǣ�" << name << endl;
	cout << endl;
	char order;
	cout << "��ѡ��Ҫִ�еĲ���:";
	cin >> order;
	cout << endl;
	while (order != 'E') {
		switch (order) {
		case 'A':
			completeFamily(family);
			break;
		case 'B':
			insertFamily(family);
			break;
		case 'C':
			deleteFamily(family);
			break;
		case 'D':
			changeMember(family);
			break;
		case 'E':
			break;
		default :
			cout << "������Ч�����������" << endl << endl;
			break;
		}
		cout << "��ѡ��Ҫִ�еĲ���:" ;
		cin >> order;
		cout << endl;
	}
	return 0;
}
		



