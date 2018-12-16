#include <iostream>
#include <queue>
using namespace std;
char maze[7][7] = {
{'#','#','#','#','#','#','#'},
{'#','0','#','0','0','0','#'},
{'#','0','#','0','#','#','#'},
{'#','0','0','0','#','0','#'},
{'#','0','#','0','0','0','#'},
{'#','0','#','0','#','0','#'},
{'#','#','#','#','#','#','#'},
};
typedef struct pos {
	int x;
	int y;
} pos;
pos direc[4] = { {0,1},{0,-1},{1,0},{-1,0} };
queue<pos> path_seq;//Ĭ�ϳ�ʼ��

bool seekPath(pos begin, pos end) {
	if (begin.x == end.x && begin.y == end.y) {
		maze[begin.x][begin.y] = 'x';
		path_seq.push(begin);
		return true;
	}
	pos cur = begin;
	maze[cur.x][cur.y] = 'x';
	path_seq.push(cur);
	bool isSucceed = false;
	for (int i = 0; i < 4; i++) {
		if (maze[cur.x + direc[i].x][cur.y + direc[i].y] == '0') {
			pos next;
			next.x = cur.x + direc[i].x;
			next.y = cur.y + direc[i].y;
			isSucceed = isSucceed || seekPath(next, end);
		}
	}
	if (isSucceed == false) {
		maze[cur.x][cur.y] = '0';
		path_seq.pop();
		return false;
	}
	else {
		return true;
	}
}
int main() {
	pos begin = { 1,1 };
	pos end = { 5,5 };
	if (seekPath(begin, end)) {
		cout << "�Թ���ͼ��" << endl << endl;
		cout << "   " << '\t';
		for (int i = 0; i < 7; i++) {
			cout << i << "��" << '\t';
		}
		cout << endl;
		for (int i = 0; i < 7; i++) {
			cout << i << "��" << '\t';
			for (int j = 0; j < 7; j++) {
				cout << maze[i][j] << '\t';
			}
			cout << endl << endl;
		}
		int flag = 0;
		cout << "�Թ�·����"<< endl;
		while (!path_seq.empty()) {
			if (flag) {
				cout << " --> ";
			}
			cout << '<'<<path_seq.front().x <<','<< path_seq.front().y << '>';
			path_seq.pop();
			flag = 1;
		}
		cout << endl;
	}
	else {
		cout << "Ѱ·ʧ��\n";
	}
	return 0;
}
	






