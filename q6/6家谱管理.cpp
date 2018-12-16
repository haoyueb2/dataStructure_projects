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
	//删除一个节点的所有兄弟 
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
	//返回树根
	TreeNode * root_() {
		return root;
	}
	~Tree() {
		del_family(root);
	}
	//建树根
	void create(string name) {
		root = new TreeNode(name);
	}
	//找data为某一内容的节点
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
	//将某一子女插入其父亲的家庭
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
	//更改某一个成员姓名
	bool change(string oldname, string newname) {
		TreeNode * p = find(root, oldname);
		if (p == NULL) return false;
		p->data = newname;
		return true;
	}
	//删除某一成员的所有子女
	bool del_family(TreeNode * parent) {
		TreeNode * p = parent;
		if (p == NULL) return false;
		del_sibling(p->child);
		return true;
	}
	//输出某一成员所有子女
	void showChildren(TreeNode * parent) {
		if (parent->child == NULL) {
			cout << parent->data << "没有子女" << endl;
		}
		else {
			TreeNode * p = parent->child;
			cout << parent->data << "的第一代子孙是:";
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
	cout << "请输入要建立家庭的人的姓名:" ;
	cin >> name;
	cout << endl;
	TreeNode * p = family->find(family->root_(), name);
	if (p == NULL) {
		cout << "未找到此人" << endl;
		return;
	}
	if (p->child) {
		cout << p->data << "已经建立过家庭" << endl;
		return;
	}
	cout << "请输入" << p->data << "的儿女人数：" ;
	int child_num = 0;
	cin >> child_num;
	cout << endl;
	cout << "请依次输入" << p->data << "的儿女的姓名：";
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
	cout << "请输入要添加儿子（或女儿）的人的姓名：";
	cin >> name;
	TreeNode * p = family->find(family->root_(), name);
	if (p == NULL) {
		cout << "未找到此人" << endl;
		return;
	}
	cout << endl;
	cout << "请输入" << p->data << "新添加的儿子（或女儿的姓名）：";
	cin >> name;
	cout << endl;
	family->insert(p, name);
	family->showChildren(p);
	cout << endl;
}
void deleteFamily(Tree * family) {
	string name;
	cout << "请输入要解散家庭的人的姓名：" ;
	cin >> name;
	cout << endl;
	TreeNode * p = family->find(family->root_(), name);
	if (p == NULL) {
		cout << "查无此人" << endl;
		return;
	}
	cout << "要解散家庭的人是：" << name << endl;
	family->showChildren(p);
	family->del_family(p);
	//family->showChildren(p);
	cout << endl;
}
void changeMember(Tree * family) {
	string name;
	cout << "请输入要更改姓名的人的姓名:" ;
	cin >> name;
	cout << endl;
	TreeNode * p = family->find(family->root_(), name);
	if (p == NULL) {
		cout << "查无此人" << endl;
		cout << endl;
		return;
	}
	cout << "请输入更改后的姓名:";
	cin >> p->data;
	cout << endl;
	cout << name << "已经更名为" << p->data << endl;
	cout << endl;
}
int main() {
	//freopen("Text6.txt", "r", stdin);
	cout << "**                         家谱管理系统                         **" << endl;
		cout << "==================================================================" << endl;
	cout << "**                     请选择要执行的操作：                     **" << endl;
	cout << "**                     A --- 完善家庭                           **" << endl;
	cout << "**                     B --- 添加家庭成员                       **" << endl;
	cout << "**                     C --- 解散局部成员                       **" << endl;
	cout << "**                     D --- 更改家庭成员姓名                   **" << endl;
	cout << "**                     E --- 退出程序                           **" << endl;
	cout << "==================================================================" << endl;

	
	string name;
	cout << "首先建立一个家谱！" << endl
		<< "请输入祖先的姓名：";
	cin >> name;
	Tree * family = new Tree();
	family->create(name);
	cout << "此家谱的祖先是：" << name << endl;
	cout << endl;
	char order;
	cout << "请选择要执行的操作:";
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
			cout << "不是有效命令，重新输入" << endl << endl;
			break;
		}
		cout << "请选择要执行的操作:" ;
		cin >> order;
		cout << endl;
	}
	return 0;
}
		



