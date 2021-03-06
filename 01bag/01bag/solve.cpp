#include <iostream>
#include <vector>
using namespace std;
struct goods {
	int weight;
	int value;
};
struct goods goods[100];//����һ������100����Ʒ�Ľṹ������
int SUM;//������Ʒ����
int bagContain;//���汳����װ������
int totalWeight = 0;//���汳�������е���Ʒ����
int totalValue = 0;//���汳�������е���Ʒ��ֵ
int MaxValue = 0;//����Ŀǰ��������װ��Ʒ������ֵ
int index = 0;//������ܽ�ĸ���
int possibleCombine[20][101];
vector<int> seq;//�����������
bool visit[100] = { false };//��ǽ���Ƿ񱻷��ʹ�
bool flag = false;//��¼�û������Ƿ�Ϊ��������false��ʾ��Ϊ��true��ʾΪ��

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

//��ȡ�û�����
void getUserInput() {
	char tempL[20];//��ʱ�����û�����
	while (flag == false) {
		cout << "�����뱳�������ɵ�����:";
		cin >> tempL;
		bagContain = examine(tempL);
	}
	flag = false;
	while (flag==false) {
		cout << "��������Ʒ����:";
		cin >> tempL;
		SUM = examine(tempL);
	}
	flag = false;
	cout << "\n";
	for (int i = 0; i < SUM; i++) {
		while (flag == false) {
			cout << "�������"<<i+1<<"����Ʒ������:";
			cin >> tempL;
			goods[i].weight = examine(tempL);
		}
		flag = false;
		while (flag == false) {
			cout << "�������" << i+1 << "����Ʒ�ļ�ֵ:";
			cin >> tempL;
			goods[i].value = examine(tempL);
		}
		flag = false;
		cout << "\n";
	}
}

//����Ƿ���Ҫ��֦
bool check(int node, int totalWeight, int totalValue,int tag) {
	if (tag == 1) {//װ�뱳�������
		int temp = totalValue;
		for (int i = node; i < SUM; i++) {//���������ܴﵽ������ֵ
			temp += goods[i].value;
		}
		if (totalWeight + goods[node].weight > bagContain) {//�����ϸ���Ʒ�󣬳��أ�����Ҫ��֦
			return true;
		}
		if (temp < MaxValue) {//��������ܴﵽ������ֵ�ȵ�ǰ���Ž�С������Ҫ��֦
			return true;
		}
		return false;
	}
	if (tag == 0) {//��װ�뱳�������
		int temp = totalValue;
		if (node+1 < SUM) {
			for (int i = node+1; i < SUM; i++) {//���������ܴﵽ������ֵ
				temp += goods[i].value;
			}
			if (temp < MaxValue) {//��������ܴﵽ������ֵ�ȵ�ǰ���Ž�С������Ҫ��֦
				return true;
			}
		}
		return false;
	}
}
/*
//��֦����
void cut(int node) {
	for (int i = node; i < SUM; i++) {
		visit[node] = 1;
	}
}*/

//����������
void result(int currentWeight, int currentValue) {
	int j = 1;
	for (int ele : seq) {
		possibleCombine[index][j] = ele;
		j++;
	}
	possibleCombine[index][0] = currentValue;
	index++;
}

void result1(int currentWeight, int currentValue) {
	cout << "��Ʒ��װ�����Ϊ��";
	for (int ele : seq) {
		cout << ele << " ";
	}
	cout << "��\t������Ϊ��" << currentWeight << "��";
	cout << "\t�ܼ�ֵΪ��" << currentValue << "\n";
}

//���ݷ����0/1��������
void dfs_search(int node,int totalWeight,int totalValue) {
	if (node >= SUM) {//�ҵ�һ���������
		result(totalWeight, totalValue);
	}
	else {
		if (!visit[node]) {
			//Ҫ��node�����뱳��
			if (!check(node, totalWeight, totalValue,1)) {//��֤�Ƿ���Ҫ��֦
				visit[node] = true;//����
				seq.push_back(1);//��������Ӧλ������1
				if (MaxValue < totalValue + goods[node].value) {//����MaxValue
					MaxValue = totalValue + goods[node].value;
				}
				dfs_search(node + 1, totalWeight + goods[node].weight, totalValue + goods[node].value);//������һ�����
				seq.erase(seq.begin() + node);//����������Ӧλ�õ�ֵ
				visit[node] = false;//����
			}
			//����node�����뱳��
			if (!check(node, totalWeight, totalValue, 0)) {//��֤�Ƿ���Ҫ��֦
				visit[node] = true;
				seq.push_back(0);//��������Ӧλ������0
				dfs_search(node + 1, totalWeight, totalValue);//������һ�����
				seq.erase(seq.begin() + node);//����������Ӧλ�õ�ֵ
				visit[node] = false;//����
			}
		}
	}
}

int main() {
	cout << "********************��ȡ�û�����********************\n";
	getUserInput();//��ȡ�û�����
	dfs_search(0,0,0);//���ݷ��������
	cout << "**********************������**********************\n";
	cout << "װ����Ʒ��ϵ�����ֵΪ��" << MaxValue << "��\n";
	cout << "��Ʒ��װ�����Ϊ��";
	for (int k = 0; k < index; k++) {
		if (possibleCombine[k][0] == MaxValue) {
			for (int j = 1; j <= SUM; j++) {
				cout << possibleCombine[k][j] << " ";
			}
			cout << "��\n";
		}
	}
	system("pause");
	return 0;
}