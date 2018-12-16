#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <queue>
#pragma warning(disable:4996)
using namespace std;
struct Edge {
	int either;
	int other;
	int cost;
	Edge * link;
	Edge(int either_, int other_, int cost_, Edge * link_) :either(either_), other(other_), cost(cost_), link(link_) {}
};
//data�����������˳��
struct Vertex {
	string data;
	Edge * adj;
	Vertex() :data(""), adj(NULL) {}
};
class Graph {
private:
	//�ڵ���� 
	int v;
	//�ߵĸ���   
	int e;
	//�����
	Vertex * NodeTable;
public:
	//���������˳��������Ķ�Ӧ 
	map<string, int> findVertex;
	//�����������Ϊ�㶥��ջ
	int *count;
	Graph() : v(0), e(0), NodeTable(NULL) {}
	Graph(int sz) {
		v = sz;
		NodeTable = new Vertex[v];
		count = new int[v];
		for (int i = 0; i < v; i++) {
			count[i] = 0;
		}
	}
	~Graph() {
		for (int i = 0; i < v; i++) {
			Edge * p = NodeTable[i].adj;
			while (p != NULL) {
				Edge * tmp = p;
				p = p->link;
				delete tmp;
			}
		}
		delete[] NodeTable;
	}
	//������
	void createEdge(int m) {
		int v1, v2;
		int weight;

		for(int i = 0; i < m; i++) {
			cin >> v1 >> v2 >> weight;
			//���������㣬��һ���룬�����һ�ͺ�
			insertEdge(v1-1, v2-1, weight);

		}
	}
	// ָ����������֮������ 
	void insertEdge(int v1, int v2, int weight) {
		count[v2]++;
		Edge * e_v1 = new Edge(v1, v2, weight, NodeTable[v1].adj);
		NodeTable[v1].adj = e_v1;
		e++;
	}
	//���
	void output() {
		for (int i = 0; i < v; i++) {
			cout << i+1;
			Edge * p = NodeTable[i].adj;
			while (p != NULL) {
				cout << p->cost << p->other+1 << ' ';
				p = p->link;
			}
			cout << endl;
		}
	}
	//��ȡ�������
	int getV() {
		return v;
	}
	//��ȡ�ߵĸ���
	int getE() {
		return e;
	}
	//��ȡָ������ı�����
	Edge * adj(int v) {
		return NodeTable[v].adj;
	}
	//��ȡָ�����������
	string & nodeData(int v) {
		return NodeTable[v].data;
	}
};
bool topologicalSort(Graph &G) {
	int n = G.getV();
	int top = -1;
	for (int i = 0; i < n; i++) {
		if (G.count[i] == 0) {
			G.count[i] = top;
			top = i;
		}
	}
	int v;
	for (int i = 0; i < n; i++) {
		if (top == -1) {
			//cout << "�л�·" << endl;
			return false;
		}
		else {
			v = top;
			top = G.count[top];
			G.nodeData(v) = to_string(i);
			G.findVertex[to_string(i)] = v;
			//cout << G.nodeData(v);
			//cout << v+1;
			Edge * p = G.adj(v);
			while (p != NULL) {
				if (--G.count[p->other] == 0) {
					G.count[p->other] = top;
					top = p->other;
				}
				p = p->link;
			}
		}
	}
	return true;
}
void criticalPath(Graph &G) {
	int n = G.getV();
	vector<int > Ve(n);
	vector<int > Vl(n);
	int w;
	for (int i = 0; i < n; i++) {
		Ve[i] = 0;
	}
	for (int i = 0; i < n; i++) {
		int v = G.findVertex[to_string(i)];//�ҵ�����˳���Ӧ����
		Edge * p = G.adj(v);
		while (p != NULL) {
			w = p->cost;
			if (Ve[v] + w > Ve[p->other]) {
				Ve[p->other] = Ve[v] + w;//�������
			}
			p = p->link;
		}
	}
	
	cout << Ve[G.findVertex[to_string(n - 1)]] << endl;
	for (int i = 0; i < n; i++) {
		Vl[i] = Ve[G.findVertex[to_string(n-1)]];
	}
	for (int i = n - 2; i >= 0; i--) {
		int v = G.findVertex[to_string(i)];//�ҵ����������Ӧ����
		Edge * p = G.adj(v);
		while (p != NULL) {
			w = p->cost;
			if (Vl[p->other] - w < Vl[v]) {
				Vl[v] = Vl[p->other] - w;//�������
			}
			//cout << "debug:" << p->either + 1 << "->" << p->other + 1 << endl;
			p = p->link;
		}
		
	}
	for (int i = 0; i < n; i++) {
		Edge * p = G.adj(i);
		while (p != NULL) {
			w = p->cost;
			int Ae = Ve[i];
			int Al = Vl[p->other] - w;
			if (Ae == Al) {
				cout << i+1 << "->" << p->other+1 << endl; //�������
			}
			p = p->link;
		}
		
	}
}



int main() {
	//freopen("Text9.txt", "r", stdin);
	int n, m;
	cin >> n;
	cin >> m;
	Graph * graph = new Graph(n);
	graph->createEdge(m);
	//graph->output();
	cout << "���Ϊ:" << endl;
	if (topologicalSort(*graph)) {
		criticalPath(*graph);
	}
	else {
		cout << 0;
	}
	return 0;
}