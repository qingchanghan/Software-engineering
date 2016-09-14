#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#define MAX 10000
using namespace std;

class station {
	public:
		station(int no0, string name0, int lineNum0, vector<int> lineNo0, int nextToStationNum0, vector<int> nextToStationNo0)
		{
			no = no0;
			name = name0;
			lineNum = lineNum0;
			lineNo = lineNo0;
			nextToStationNum = nextToStationNum0;
			nextToStationNo = nextToStationNo0;
		}

		void print() 
		{
			cout << "վ�����: " << no << " ";
			cout << "վ������: " << name << " ";
			cout << "������·: ";
			for (int i = 0; i < lineNum; i++) {
				cout << lineNo[i] << " ";
			}
			cout << "����վ�����: ";
			for (int i = 0; i < nextToStationNum; i++)
				cout << nextToStationNo[i] << " ";
			cout << endl;
		}

		bool ifBelongTo(int line)
		{
			for (int i = 0; i < lineNum; i++) {
				if (lineNo[i] == line)
					return true;
			}
			return false;
		}

		vector<int> findNext(int line, vector<station> list)//���������������վ�����ڵ�վ��
		{
			vector<int> nextSta;
			for (int i = 0; i < nextToStationNum; i++) {
				if (list[nextToStationNo[i]].ifBelongTo(line))
					nextSta.push_back(nextToStationNo[i]);
			}
			return nextSta;
		}

		int findNext(int line, vector<station> list, int lastSta)//��������һ���㲻һ����
		{
			for (int i = 0; i < nextToStationNum; i++) {
				if (lastSta == nextToStationNo[i])
					continue;
				if (list[nextToStationNo[i]].ifBelongTo(line))
					return nextToStationNo[i];
			}
			return -1;
		}

		int findNext(int line, vector<station> list, vector<int> used) //��һ�����Ѿ��������ĵ㲻һ����
		{
			for (int i = 0; i < nextToStationNum; i++) {
				unsigned int j;
				for (j = 0; j < used.size() && used[j] != nextToStationNo[i]; j++);
				if (j != used.size())
					continue;
				if (list[nextToStationNo[i]].ifBelongTo(line))
					return nextToStationNo[i];
			}
			return -1;
		}

		void printName()
		{
			cout << name << endl;
		}

		string getName()
		{
			return name;
		}

		bool ifName(string name0) 
		{
			if (name0 == name)
				return true;
			else
				return false;
		}

		vector<int> getLineNo()
		{
			return lineNo;
		}

		void reachableSta(vector<int> &staList, vector<int> lineSta[])
		{
			for (int i = 0; i < lineNum; i++) {//ѭ����վ��ļ�����·
				for (unsigned int j = 0; j < lineSta[lineNo[i]].size(); j++) {//ѭ������·�ϵ����е�
					unsigned int k;
					for (k = 0; k < staList.size(); k++) {//���Ҹõ��Ƿ���Ѽ���ü��ϵ����е㶼��ͬ
						if (staList[k] == lineSta[lineNo[i]][j])
							break;
					}
					if (k != staList.size()) {//�õ��Ѵ���
						continue;
					}
					staList.push_back(lineSta[lineNo[i]][j]);
				}
			}
		}

	private:
		int no;
		string name;
		int lineNum, nextToStationNum;
		vector<int> lineNo, nextToStationNo;
}; 

vector<station> list;//�洢վ����������
int matrix[275][275];//�ڽӾ���
int startStation[22] = { -1, 0, 23, -1, 39, 71, 91, 115, 134, 150, 159, -1, -1,
						38, 203, 214, 230, 21, 249, 71, 263, 27 };
string lines[22] = { "", "����һ����", "����������", "", "�����ĺ���", "���������", "����������", "�����ߺ���", "�����˺���",
					"�����ź���", "����ʮ����", "", "", "����ʮ������", "����ʮ�ĺ��߶���", "����ʮ�����", "����ʮ�ĺ�������",
					"������ͨ��", "������ƽ��", "������ׯ��", "������ɽ��", "����������" };
vector<int> lineStation[22];//�洢ÿ����·���е�վ��
vector<int> transfer[10];//�洢���㻻��ʱ�ľ���,���¼�����ÿ�μ����궼Ҫ����
vector<int> route;//�洢Ŀǰ�ҵ�����̵�·��
int shortestLength = MAX;//Ŀǰ�ҵ�����̵�·�߳���
int num;//��������

//���ĳ������·����վ��
void searchAllStations(int line)
{
	int current, next;
	current = startStation[line];
	lineStation[line].push_back(current);
	while (true) {
		next = -1;
		next = list[current].findNext(line, list, lineStation[line]);
		if (next == -1)
			break;
		current = next;
		lineStation[line].push_back(current);
	}
	return;
}

//�������ȡ��·����
void allStations(string name) 
{
	/*cout << "������ĳ��·���ƣ�" << endl;
	string name;
	getline(cin, name);*/
	int line;
	if (name == "����һ����") {
		line = 1;
	}
	else if (name == "����������"){
		line = 2;
	}
	else if (name == "�����ĺ���"){
		line = 4;
	}
	else if (name == "���������") {
		line = 5;
	}
	else if (name == "����������") {
		line = 6;
	}
	else if (name == "�����ߺ���") {
		line = 7;
	}
	else if (name == "�����˺���") {
		line = 8;
	}
	else if (name == "�����ź���") {
		line = 9;
	}
	else if (name == "����ʮ����") {
		line = 10;
	}
	else if (name == "����ʮ������") {
		line = 13;
	}
	else if (name == "����ʮ�ĺ��߶���") {
		line = 14;
	}
	else if (name == "����ʮ�ĺ�������") {
		line = 16;
	}
	else if (name == "����ʮ�����") {
		line = 15;
	}
	else if (name == "������ͨ��") {
		line = 17;
	}
	else if (name == "������ƽ��") {
		line = 18;
	}
	else if (name == "������ׯ��") {
		line = 19;
	}
	else if (name == "������ɽ��") {
		line = 20;
	}
	else if (name == "����������") {
		line = 21;
	}
	else {
		cout << "�������������" << endl;
		return;
	}
	for (unsigned int i = 0; i < lineStation[line].size(); i++)
		list[lineStation[line][i]].printName();
	return;
}

//�ҹ�����·
vector<int> commonLine(station sta1, station sta2)
{
	vector<int> lineNo1, lineNo2;
	lineNo1 = sta1.getLineNo();
	lineNo2 = sta2.getLineNo();
	vector<int> common;
	for (unsigned int i = 0; i < lineNo1.size(); i++)
		for (unsigned int j = 0; j < lineNo2.size(); j++)
			if (lineNo1[i] == lineNo2[j])
				common.push_back(lineNo1[i]);
	return common;
}

//�����·��
void shortestRoute(int sta1, int sta2)
{
	//��ʼ��
	int s[275], dis[275];
	vector<int> path[275];
	for (int i = 0; i < 275; i++) {
		dis[i] = matrix[sta1][i];
		s[i] = 0;
		path[i].push_back(sta1);
	}
	s[sta1] = 1;

	//dijkstra�㷨
	while (s[sta2] == 0) {
		int u, minDis = MAX;
		for (int i = 0; i < 275; i++) {
			if (s[i] == 1)
				continue;
			if (dis[i] < minDis) {
				minDis = dis[i];
				u = i;
			}
		}
		path[u].push_back(u);
		s[u] = 1;

		for (int i = 0; i < 275; i++) {
			if (s[i] == 1 || matrix[u][i] != 1)
				continue;
			if (dis[u] + 1 < dis[i]) {
				dis[i] = dis[u] + 1;
				path[i].clear();
				for (unsigned int j = 0; j < path[u].size(); j++)
					path[i].push_back(path[u][j]);
			}
		}
	}

	cout << path[sta2].size() << endl;
	int lastLine, nextLine;
	vector<int> common = commonLine(list[path[sta2][0]], list[path[sta2][1]]);
	
	if (common.size() == 0) {
		cerr << "·�߳���" << endl;
		return;
	}
	lastLine = common[0];

	cout << list[path[sta2][0]].getName() << endl;
	for (unsigned int i = 1; i < path[sta2].size() - 1; i++) {
		common.clear();
		common = commonLine(list[path[sta2][i]], list[path[sta2][i + 1]]);
		if (common.size() == 0) {
			cerr << "·�߳���" << endl;
			return;
		}
		nextLine = common[0];
		cout << list[path[sta2][i]].getName();
		if (nextLine != lastLine) {
			cout << "����" << lines[nextLine];
		}
		cout << endl;
		lastLine = nextLine;
	}
	cout << list[path[sta2].back()].getName() << endl;

	return;
}

//��վ����ת�������
void shortest(string name1, string name2)
{
	int sta1 = -1, sta2 = -1;
	for (unsigned int i = 0; i < list.size(); i++) {
		if (sta1 == -1 && list[i].ifName(name1))
			sta1 = i;
		if (sta2 == -1 && list[i].ifName(name2))
			sta2 = i;
		if (sta1 != -1 && sta2 != -1)
			break;
	}
	if (sta1 == -1 || sta2 == -1) {
		cerr << "�������������" << endl;
		return;
	}
	shortestRoute(sta1, sta2);
}

void printDirect(int sta1, int sta2, int flag)
{
	vector<int> common = commonLine(list[sta1], list[sta2]);
	int minLength = MAX;
	int minNo = -1;
	vector<int> rou[10];
	int rouLine[10];
	int m = 0;
	for (unsigned int i = 0; i < common.size(); i++) {
		vector<int> nextSta = list[sta1].findNext(common[i], list);
		for (unsigned int j = 0; j < nextSta.size(); j++) {
			if (sta2 == nextSta[j]) {
				if (flag == 0) {
					cout << list[sta1].getName() << endl;
				}
				else if (flag == 1) {
					cout << list[sta1].getName() << "����" << lines[common[i]] << endl;
				}
				return;
			}
			rouLine[m] = common[i];
			rou[m].push_back(sta1);
			int length = 1;
			int lastSta = sta1;
			int currentSta = nextSta[j];
			rou[m].push_back(currentSta);
			int next = -1;
			while (currentSta != sta2) {
				next = list[currentSta].findNext(common[i], list, lastSta);
				if (next == -1)
					break;
				length++;
				lastSta = currentSta;
				currentSta = next;
				rou[m].push_back(currentSta);
			}
			m++;
			if (next == -1)
				continue;
			if (length < minLength) {
				minLength = length;
				minNo = m - 1;
			}
			
		}
	}
	if (minNo != -1) {
		if (flag == 0) {
			cout << list[rou[minNo][0]].getName() << endl;
		}
		else {
			cout << list[rou[minNo][0]].getName() << "����" << lines[rouLine[minNo]] << endl;
		}
		for (unsigned int i = 1; i < rou[minNo].size() - 1; i++) {
			cout << list[rou[minNo][i]].getName() << endl;
		}
	}
}

void printTransfer()
{
	cout << (shortestLength + 1) << endl;
	for (int i = route.size() - 1; i >= 1; i--) {
		if (i == route.size() - 1) {
			printDirect(route[i], route[i - 1], 0);
		}
		else {
			printDirect(route[i], route[i - 1], 1);
		}
	}
	cout << list[route[0]].getName() << endl;

	for (int i = 0; i < 10; i++)
		transfer[i].clear();
	route.clear();
	shortestLength = MAX;
	num = 0;
}

int directLength(int sta1, int sta2)
{
	vector<int> common = commonLine(list[sta1], list[sta2]);
	int minLength = MAX;
	for (unsigned int i = 0; i < common.size(); i++) {
		vector<int> nextSta = list[sta1].findNext(common[i], list);
		for (unsigned int j = 0; j < nextSta.size(); j++) {
			if (sta2 == nextSta[j])
				return 1;
			int length = 1;
			int lastSta = sta1;
			int currentSta = nextSta[j];
			int next = -1;
			while (currentSta != sta2) {
				next = list[currentSta].findNext(common[i], list, lastSta);
				if (next == -1)
					break;
				length++;
				lastSta = currentSta;
				currentSta = next;
			}
			if (next == -1)
				continue;
			if (length < minLength)
				minLength = length;
		}
	}
	return minLength;
}

//�ݹ�
void transfer3(vector<int> sta, vector<int> ro, int m, int length)
{
	//���mΪ0,�����ݹ�
	if (m == -1) {
		int l = directLength(transfer[0][0], ro.back()) + length;
		if (l < shortestLength) {
			shortestLength = l;
			route.clear();
			for (unsigned int i = 0; i < ro.size(); i++)
				route.push_back(ro[i]);
			route.push_back(transfer[0][0]);
		}
		return;
	}

	for (unsigned int i = 0; i < sta.size(); i++) {
		//����sta�е�ÿ����sta[i],���sta[i]������·��transfer[m]�Ľ���
		//�ݹ�ʱ��·��
		vector<int> rou;
		for (unsigned int j = 0; j < ro.size(); j++)
			rou.push_back(ro[j]);
		//�����ro.back()��sta[i]�ľ����ټ���ԭ���ľ��룬���̫Զ�Ͳ�������
		int l = length + directLength(sta[i], ro.back());
		if (l > shortestLength)
			continue;
		rou.push_back(sta[i]);
		//sta[i]��ֱ�ӵ����վ��
		vector<int> sta1;
		list[sta[i]].reachableSta(sta1, lineStation);
		//��sta1��transfer[m-1]�Ľ���
		vector<int> intersection;
		for (unsigned int j = 0; j < sta1.size(); j++) {
			unsigned int k;
			for (k = 0; k < transfer[m].size(); k++) {
				if (transfer[m][k] == sta1[j])
					break;
			}
			if (k != transfer[m].size()) {
				intersection.push_back(sta1[j]);
			}
		}
		transfer3(intersection, rou, m - 1, l);
	}
	if (m == num - 1) {
		printTransfer();
	}
}

//��������
void transfer2(int sta1, int sta2)
{
	//ÿ����һ�Σ����ɵ����վ�������µľ���
	transfer[0].push_back(sta1);
	list[sta1].reachableSta(transfer[1], lineStation);
	unsigned int n;
	for (n = 0; n < transfer[1].size(); n++)
		if (sta2 == transfer[1][n])
			break;
	if (n != transfer[1].size()) {//���sta2��transfer[1]�����ֱ�ӵ���
		route.push_back(sta2);
		route.push_back(sta1);
		shortestLength = directLength(sta1, sta2);
		printTransfer();
		return;
	}

	//stopStaΪĿ�ĵ�վ���ֱ�ӵ����վ��
	vector<int> stopSta;
	list[sta2].reachableSta(stopSta, lineStation);
	int m = 1;//mΪĿǰ�����Ĳ���
	vector<int> intersection;
	while (true) {
		//��transfer[m]��stopSta�Ľ���
		//������Ϊ�գ����������
		intersection.clear();
		for (unsigned int i = 0; i < stopSta.size(); i++) {
			unsigned int j;
			for (j = 0; j < transfer[m].size(); j++) {
				if (stopSta[i] == transfer[m][j])
					break;
			}
			if (j != transfer[m].size()) {
				intersection.push_back(stopSta[i]);
			}
		}

		if (intersection.size() == 0) {
			for (unsigned int i = 0; i < transfer[m].size(); i++) {
				list[transfer[m][i]].reachableSta(transfer[m + 1], lineStation);
			}
			for (int i = 0; i <= m; i++) {
				//��transfer[m+1]�г�ȥtransfer[i]���е�Ԫ��
				for (unsigned int j = 0; j < transfer[m + 1].size(); j++) {
					unsigned int k;
					for (k = 0; k < transfer[i].size(); k++) {
						if (transfer[m + 1][j] == transfer[i][k])
							break;
					}
					if (k != transfer[i].size()) {
						transfer[m + 1].erase(transfer[m + 1].begin() + j);
						j--;
					}
				}
			}
			m++;
		}
		else {
			break;
		}
	}


	//�����ҵ���...
	vector<int> ro;
	ro.push_back(sta2);
	num = m;
	transfer3(intersection, ro, m - 1, 0);
}

//��վ����ת��Ϊ���
void transfer1(string name1, string name2)
{
	int sta1 = -1, sta2 = -1;
	for (unsigned int i = 0; i < list.size(); i++) {
		if (sta1 == -1 && list[i].ifName(name1))
			sta1 = i;
		if (sta2 == -1 && list[i].ifName(name2))
			sta2 = i;
		if (sta1 != -1 && sta2 != -1)
			break;
	}
	if (sta1 == -1 || sta2 == -1) {
		cerr << "�������������" << endl;
		return;
	}
	transfer2(sta1, sta2);
}

int main(int argc, char *argv[]) 
{
	//�ڽӾ����ʼ��
	for (int i = 0; i < 275; i++)
		for (int j = 0; j < 275; j++) {
			if (i == j)
				matrix[i][j] = 0;
			else
				matrix[i][j] = MAX;
		}
	
	ifstream in; //ifstream���ļ�
	string filename = "D:\\beijing-subway.txt";

	in.open(filename);//���Ӵ򿪷�ʽ Ĭ����in��ʽ��

	if (!in) {
		cerr << "���ļ�����" << endl;
		return 1;
	}

	char ch[100];
	while (!in.eof()) {
		in.getline(ch, 100);
		int no, lineNum, nextToStationNum;
		vector<int> lineNo, nextToStationNo;
		int k = 0, sum;

		//��ȡվ�����
		for (sum = 0; isdigit(ch[k]) && k < 100; k++) {
			sum = sum * 10 + (ch[k] - '0');
		}
		no = sum;

		//��ȥ�ո���Ʊ��
		for (; (ch[k] == ' ' || ch[k] == '\t') && k < 100; k++);

		//��ȡվ������
		string name = "";
		for (; ch[k] != ' ' && ch[k] != '\t' && k < 100; k++)
			name = name + ch[k];

		//��ȥ�ո���Ʊ��
		for (; (ch[k] == ' ' || ch[k] == '\t') && k < 100; k++);

		//��ȡ������·����
		for (sum = 0; isdigit(ch[k]) && k < 100; k++)
			sum = sum * 10 + (ch[k] - '0');
		lineNum = sum;

		//��ȡ������·
		for (int i = 0; i < lineNum; i++) {
			//��ȥ�ո���Ʊ��
			for (; (ch[k] == ' ' || ch[k] == '\t') && k < 100; k++);

			for (sum = 0; isdigit(ch[k]) && k < 100; k++)
				sum = sum * 10 + (ch[k] - '0');
			lineNo.push_back(sum);
		}

		//��ȥ�ո���Ʊ��
		for (; (ch[k] == ' ' || ch[k] == '\t') && k < 100; k++);

		//��ȡ����վ�����
		for (sum = 0; isdigit(ch[k]) && k < 100; k++)
			sum = sum * 10 + (ch[k] - '0');
		nextToStationNum = sum;

		//��ȡ����վ�����
		for (int i = 0; i < nextToStationNum; i++) {
			//��ȥ�ո���Ʊ��
			for (; (ch[k] == ' ' || ch[k] == '\t') && k < 100; k++);

			for (sum = 0; isdigit(ch[k]) && k < 100; k++)
				sum = sum * 10 + (ch[k] - '0');
			nextToStationNo.push_back(sum);
			//�����ڽӾ���
			matrix[no][sum] = 1;
		}
		
		//��ȡ��ϣ�����վ���б�
		station s = station(no, name, lineNum, lineNo, nextToStationNum, nextToStationNo);
		list.push_back(s);
	}

	//�ر��ļ�
	in.close();

	//�������е�վ��
	for (int i = 0; i < 22; i++) {
		if (i == 0 || i == 3 || i == 11 || i == 12)
			continue;
		searchAllStations(i);
	}

	/*for (int i = 0; i < list.size(); i++) {
		list[i].print();
	}*/

	//��ȡ�����в���
	if (argc == 2) {
		allStations(argv[1]);
	}
	else if (argc == 4 && argv[1][0] == '-' && argv[1][1] == 'b') {
		shortest(argv[2], argv[3]);
	}
	else if (argc == 4 && argv[1][0] == '-' && argv[1][1] == 'c') {
		transfer1(argv[2], argv[3]);
	}

	string ins;
	while (getline(cin, ins)) {
		if (ins[0] == 'd') {
			string lineName;
			unsigned int i;
			for (i = 1; ins[i] == ' ' || ins[i] == '\t'; i++);
			for (; i < ins.size(); i++) {
				if (ins[i] == ' ' || ins[i] == '\t')
					continue;
				lineName = lineName + ins[i];
			}
			allStations(lineName);
		}
		else if (ins[0] == 'b') {
			string name1 = "", name2 = "";
			unsigned int i;
			for (i = 1; ins[i] == ' ' || ins[i] == '\t'; i++);
			for (; ins[i] != ' ' && ins[i] != '\t'; i++) {
				if (ins[i] == ' ' || ins[i] == '\t')
					continue;
				name1 = name1 + ins[i];
			}
			for (; ins[i] == ' ' || ins[i] == '\t'; i++);
			for (; i < ins.size(); i++) {
				if (ins[i] == ' ' || ins[i] == '\t')
					continue;
				name2 = name2 + ins[i];
			}
			shortest(name1, name2);
		}
		else if (ins[0] == 'c') {
			string name1 = "", name2 = "";
			unsigned int i;
			for (i = 1; ins[i] == ' ' || ins[i] == '\t'; i++);
			for (; ins[i] != ' ' && ins[i] != '\t'; i++) {
				if (ins[i] == ' ' || ins[i] == '\t')
					continue;
				name1 = name1 + ins[i];
			}
			for (; ins[i] == ' ' || ins[i] == '\t'; i++);
			for (; i < ins.size(); i++) {
				if (ins[i] == ' ' || ins[i] == '\t')
					continue;
				name2 = name2 + ins[i];
			}
			transfer1(name1, name2);
		}
	}

	/*while (true) {
		allStations();
	}*/
	system("pause");

	return 0;
}