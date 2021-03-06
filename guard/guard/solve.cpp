#include <iostream>
#include<sstream>
using namespace std;
#define MAXNUM 22 //��������������������ֵ
int d[6][3] = { {0,0,0},{0,0,0},{0,0,-1},{0,-1,0},{0,0,1},{0,1,0} };
int guard_now[MAXNUM][MAXNUM]; //���õ�ǰ����
int monitorCondition[MAXNUM][MAXNUM]; //��ʾ������
int bestSolution[MAXNUM][MAXNUM]; //bestSolution�������ս��
int k = 0; //��ǰ�����õľ�����Ϊk
int t = 0; //�����ܼ��ӵĳ���������
int t1, t2, more; //�ж��½��֦����������
bool p;
int n;
int m;
int best; //��ǰ���پ�����Ϊbest

//��λ��(i, j)����һ�����������ı�����Χ�ܼ�����
void changeMonitoring(int i, int j) {
	guard_now[i][j] = 1;
	k++;
	//ÿ�����������˳��˼��������ڵĳ������⣬���ɼ����������ڳ��������ڵ��ϡ��¡�����4�������ҡ�
	//������Щλ�õļ������
	for (int r = 1; r <= 5; r++) {
		int p = i + d[r][1];
		int q = j + d[r][2];
		monitorCondition[p][q]++;
		if (monitorCondition[p][q] == 1) {
			t++;
		}
	}
}

//������λ��(i, j)�����õľ��������¼�����
void restore(int i, int j) {
	guard_now[i][j] = 0;
	k--;
	for (int r = 1; r <= 5; r++) {
		int p = i + d[r][1];
		int q = j + d[r][2];
		monitorCondition[p][q]--;
		if (monitorCondition[p][q] == 0)
			t--;
	}
}

//����
void search(int i, int j) {
	do { //����û����ص�λ�ã�������ϵ��£���������
		j++;
		if (j > m) {
			i++;
			j = 1;
		}
	} while (!((monitorCondition[i][j] == 0) || (i > n)));
	if (i > n) {
		if (k < best) { //ˢ�¾���ֵ
			best = k;
			for (int p = 1; p <= n; p++) {
				for (int q = 1; q <= m; q++) {
					bestSolution[p][q] = guard_now[p][q];
				}
			}
			return;
		}
	}
	if (k + (t1 - t) / 5 >= best) {//���þ������½�Ϊ�������õ����پ������������еľ�����
		return;
	}
	if ((i < n - 1) && (k + (t2 - t) / 5 >= best)) {//��������ž�������Ļ�����Ҫ��֦
		return;
	}
	if (i < n) { //���p
		changeMonitoring(i + 1, j);
		search(i, j); //�ݹ�������һ����
		restore(i + 1, j); //�ָ�
	}
	if (monitorCondition[i][j + 1] == 0) { //���q
		changeMonitoring(i, j);
		search(i, j);
		restore(i, j);
	}
	if ((j < m) && ((monitorCondition[i][j + 1] == 0) || (monitorCondition[i][j + 2] == 0))) { //���r
		changeMonitoring(i, j + 1);
		search(i, j);
		restore(i, j + 1);
	}
}

//����
void compute() {
	more = m / 4 + 1;
	if (m % 4 == 3)
		more++;
	else if (m % 4 == 2)
		more += 2;
	t2 = m * n + more + 4;
	t1 = m * n + 4;
	best = 65536;
	if (m == 1 && n == 1) {
		cout << 1 << "\n";
		cout << 1 << "\n";
	}
	for (int i = 0; i <= m + 1; i++) { //�������������һȦ�����ڴ���߽����
		monitorCondition[0][i] = 1;
		monitorCondition[n + 1][i] = 1;
	}
	for (int i = 0; i <= n + 1; i++) {
		monitorCondition[i][0] = 1;
		monitorCondition[i][m + 1] = 1;
	}
	search(1, 0);
}

//�ж��û�������Ƿ������ֵĺ���
int examine(string input) {
	int i = 0;
	int num;
	stringstream ss;
	//�����ַ�����ÿ���ַ����ж����Ƿ���������
	while (input[i] != '\0') {
		if (input[i] > '9' || input[i] < '0')
			return (-1); //����������֣�����-1
		i++;
	}
	ss << input;
	ss >> num;
	return num; //��������֣��������ֵ�ֵ
}

//��ȡ�û�������
void input() {
	int numberFlag; //�ж��Ƿ�Ϊ���ֵı�־
	string tempL; //���ַ�������ʽ�洢�û������룬�Է������������

	cout << "**********************��ȡ�û�����**********************\n\n";
	cout << "�����ó��й�����\n";

	//��ȡ�û����������m
	cout << "��������й�����m����ע�⣺1��m��20����";
	cin >> tempL;
	numberFlag = examine(tempL); //�ж��û�������Ƿ�������
	while (numberFlag <= 0 || numberFlag > 20) { //����û��������Ƿ������ֻ��Ƿ�Խ��
		cout << "���������������������룺";
		cin >> tempL;
		numberFlag = examine(tempL); //�ж��û�������Ƿ�������
	}
	n = numberFlag; //������ȷ�����û��������������n
	//��ȡ�û����������n
	cout << "��������й�����n����ע�⣺1��n��20����";
	cin >> tempL;
	numberFlag = examine(tempL); //�ж��û�������Ƿ�������
	while (numberFlag <= 0 || numberFlag > 20) { //����û��������Ƿ������ֻ��Ƿ�Խ��
		cout << "���������������������룺";
		cin >> tempL;
		numberFlag = examine(tempL); //�ж��û�������Ƿ�������
	}
	m = numberFlag; //������ȷ�����û��������������m
	cout << "\n";
}

//��ӡ���
void output() {
	cout << "���پ������ǣ�" << best << "����λ����������ʾ��" << "\n";
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cout << bestSolution[i][j] << " ";
		}
		cout << "\n";
	}
}

int main() {
	input(); //��ȡ�û�������
	compute(); //����
	cout << "**********************����������**********************\n\n";
	output(); //��ӡ���
	system("pause");
}
