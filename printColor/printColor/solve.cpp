#include <iostream>
using namespace std;
int color[100];
int n = 0;//����ͼ�Ķ�����
int m = 0;//�����û��������ɫ��
int c[101][101];
bool flag = false;//��¼�û������Ƿ�Ϊ��������false��ʾ��Ϊ��true��ʾΪ��
bool exam = false;

int examine(char a[]) {//����û��������Ƿ�Ϊ����
	flag = true;
	int i = 0;
	int result = 0;
	for (; a[i] != 0; i++) {
		if (a[i] < 48 || a[i]>57) {
			cout << "������һ����������" << endl;
			flag = false;
			break;
		}
	}
	if (flag) {
		for (int j = 0; a[j] != 0; j++) {//���û�����������ַ�ת��Ϊ��
			result = result + (a[j] - 48) * pow(10, i - j - 1);
		}
		flag = true;
	}
	return result;
}

void initC() {//��ʼ�������������
	for (int j = 0; j < n+1; j++) {
		for (int k = 0; k < n+1; k++) {
			c[j][k] = 0;
		}
	}
}

void getUserInput() {//��ȡ�û�����
	int k = 1;
	char tempL[20];//��ʱ�����û�����
	while (flag == false) {
		cout << "������ͼ�Ķ����������ó���100��:";
		cin >> tempL;
		n = examine(tempL);
		if (n > 100) {
			cout << "ͼ�Ķ��������ó���100�����������룡\n";
			flag = false;
		}
	}
	flag = false;
	while (flag == false) {
		cout << "������ͼ����ɫ��:";
		cin >> tempL;
		m = examine(tempL);
	}
	flag = false;
	cout << "��������"<<1<<"~"<<n<<"��ȷ��ͼ�����ӹ�ϵ�������������0�����˳���:\n";
	int c1, c2;
	while (k == 1) {
		while (flag == false) {
			cout << "������ߵ�һ�����㣺";
			cin >> tempL;
			c1 = examine(tempL);
		}
		flag = false;
		while (flag == false) {
			cout << "������ߵ���һ�����㣺";
			cin >> tempL;
			c2 = examine(tempL);
		}
		flag = false;
		if (c1 == 0 || c2 == 0) {
			if (c1 == 0 && c2 == 0) {
				k = 0;
			}
			else {
				cout << "��������һ��0��\n";
			}
		}
		else if (c[c1][c2] == 1) {
			cout << "�ñ��Ѿ��������\n";
		}
		else if (c1>n||c2>n) {
			cout << "�Ƿ��Ľ���ţ�����������ñߵ�������㣡\n";
		}
		else {
			flag = false;
			c[c1][c2] = 1;
			c[c2][c1] = 1;
		}
	}
	flag = false;
	cout << "\n";
}

bool Ok(int k) //�ж϶���k����ɫ�Ƿ�����ͻ
{
	for (int i = 1; i < k; i++)
		if (c[k][i] == 1 && color[i] == color[k])//��ʾ��ͻ����
			return false;
	return true;
}

void GraphColor(int n, int c[101][101], int m)
//���������±��1��ʼ
{
	for (int i = 1; i <= n; i++) //������color[n]��ʼ��Ϊ0
		color[i] = 0;
	int k = 1;
	while (k >= 1) {
		color[k] = color[k] + 1;//��������ɫ1~mΪ���KͿɫ
		while (color[k] <= m)
			if (Ok(k))//������k����ɫ��������ͻ����ͨ��
				break;
			else color[k] = color[k] + 1; //����������һ����ɫ
		if (color[k] <= m && k == n) //�����ϣ������
		{
			for (int i = 1; i <= n; i++)
				cout << color[i]<<"  ";
			cout << "\n";
			exam = true;//��ʾ�н�
			//����Ѱ����һ�ֽ�
		}
		else if (color[k] <= m && k < n)//δ������
			k = k + 1; //������һ������
		else {//������ϣ����ݣ�������һ�����
			color[k] = 0;
			k = k - 1; //����
		}
	}
}


int main() {
	initC();//��ʼ������
	cout << "*****************��ȡ�û�����*******************\n";
	getUserInput();//��ȡ�û�����
	cout << "\n*****************���·������*******************\n";
	cout << "·������1�������ڵ��бߣ�0����û�ߣ���\n";
	for (int j = 1; j < n+1; j++) {//��ӡ·������
		for (int k = 1; k < n+1; k++) {
			cout << c[j][k];
		}
		cout << "\n";
	}
	cout << "\n****************��֤��ɫ��*********************\n";
	cout << "\n����ɫ��Ϊ"<<m<<"ʱ�����" << 1 << "~" << n << "��ɫ������£�\n";
	GraphColor(n, c, m);
	if (exam == false) {//û�������ɫ
		cout << "��ɫ�����㣬�޷������ɫ\n";
	}
	exam = false;
	cout << "\n***************Ѱ��������ɫ��********************\n";
	for (int i = 1; i <= n; i++) {//��Ϊ���n����ɫ�������ͼ��ɫ���⣬������ɫ��Ӧ������n
		cout << "����ɫ��Ϊ" << i << "ʱ�����" << 1 << "~" << n << "��ɫ������£���\n";
		GraphColor(n, c, i);
		if (exam == true) {
			cout << "����������������ɫ��Ϊ��" << i << "\n";
			break;
		}
		else {
			cout << "��ɫ�����㣬�޷������ɫ\n";
		}
	}
	system("pause");
}