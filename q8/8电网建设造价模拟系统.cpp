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
	Edge(int either_,int other_, int cost_,Edge * link_) :either(either_),other(other_), cost(cost_), link(link_) {}


};

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
	// �����
	Vertex * NodeTable;
public:
	//��������ݺ������Ķ�Ӧ 
	map<string, int> findVertex;
	Graph() : v(0), e(0), NodeTable(NULL) {}
	Graph(int sz) {
		v = sz;
		NodeTable = new Vertex[v];
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
	}
	//��������
	void createVertex() {
		cout << "�������������������ƣ�" << endl;
		for (int i = 0; i < v; i++) {
			cin >> NodeTable[i].data;
			findVertex[NodeTable[i].data] = i;
		}
	}
	//������
	void createEdge() {	
		string v1data, v2data;
		int weight;
		cout << "�������������㼰��: ";
		cin >> v1data >> v2data >> weight;
		while (v1data != "?") {
			int v1 = findVertex[v1data];
			int v2 = findVertex[v2data];
			insertEdge(v1, v2, weight);
			cout << "�������������㼰��: ";
			cin >> v1data >> v2data >> weight;
		}
	}
	//ָ����������֮������
	void insertEdge(int v1, int v2, int weight) {
		Edge * e_v1 = new Edge(v1,v2, weight, NodeTable[v1].adj);
		Edge * e_v2 = new Edge(v2,v1, weight, NodeTable[v2].adj);
		NodeTable[v1].adj = e_v1;
		NodeTable[v2].adj = e_v2;
		e++;
	}
	//���
	void output() {
		for (int i = 0; i < v; i++) {
			cout << NodeTable[i].data;
			Edge * p = NodeTable[i].adj;
			while (p != NULL) {
				cout << p->cost << NodeTable[p->other].data << ' ';
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
	string nodeData(int v) {
		return NodeTable[v].data;
	}
};
struct cmp {
	bool operator()(Edge & e1, Edge & e2) {
		return e1.cost > e2.cost;
	}
};
class Prime {
private:
	////��־�����Ƿ񱻷��ʹ�������
	bool * marked;
	////���ձߵ�Ȩ�ش�ߵ����ȶ���
	priority_queue<Edge,vector<Edge>,cmp> pq;
	// ��С�������ı߼���
	vector<Edge> mst;
	//����ָ������
	void visit(Graph & G, int v) {
		marked[v] = true;
		Edge * p = G.adj(v);
		while (p != NULL) {
			if (!marked[p->other]) {
				pq.push(*p);
			}
			p = p->link;
		}
	}
public:
	Prime(Graph & G,string begin) {
		marked = new bool[G.getV()];
		for (int i = 0; i < G.getV(); i++) {
			marked[i] = false;
		}
		visit(G, G.findVertex[begin]);
		while (!pq.empty()) {
			Edge e = pq.top();
			pq.pop();
			int v = e.either, w = e.other;
			if (marked[v] && marked[w]) continue;
			mst.push_back(e);
			if (!marked[v]) visit(G, v);
			if (!marked[w]) visit(G, w);
		}
		cout << "����Prim��С��������" << endl;
	}
	~Prime() {
		delete[] marked;
	}
	//�����С������
	void output(Graph &G) {
		cout << "��С�������ĵĶ��㼰��Ϊ��" << endl;
		cout << endl;
		for (int i = 0; i < mst.size(); i++) {
			cout << G.nodeData(mst[i].either) << "<-("<<mst[i].cost <<")->"<< G.nodeData(mst[i].other) << '\t';
		}
		cout << endl;
	}

};


int main() {
	//freopen("Text8.txt", "r", stdin);
	priority_queue<Edge> pq;
	
	Graph * graph = NULL;
	int v;
	Prime * prime = NULL;
	char order;
	cout << "**                     �������ģ��ϵͳ                     **" << endl;
	cout << "==============================================================" << endl;
	cout << "**                     A---������������                     **" << endl;
	cout << "**                     B---��ӵ����ı�                     **" << endl;
	cout << "**                     C---������С������                   **" << endl;
	cout << "**                     D---��ʾ��С������                   **" << endl;
	cout << "**                     E---�˳�   ����                      **" << endl;
	cout << "==============================================================" << endl << endl;
	cout << "��ѡ�������";
	cin >> order;
	string begin;
	while (order != 'E') {
		switch (order)
		{
		case 'A':
			cout << "�����붥��ĸ�����";
			cin >> v;
			graph = new Graph(v);
			graph->createVertex();			
			break;
		case 'B':	
			if (graph) graph->createEdge();
			//graph->output();
			break;
		case 'C':
			
			cout << "��������ʼ���㣺";
			cin >> begin;
			prime = new Prime(*graph,begin);
			break;
		case 'D':
			if(prime) prime->output(*graph);
		default:
			break;
		}
		cout << endl;
		cout << "��ѡ�������";
		cin >> order;
	}
	return 0;
}

		



			


