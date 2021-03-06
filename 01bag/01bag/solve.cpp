#include <iostream>
#include <vector>
using namespace std;
struct goods {
	int weight;
	int value;
};
struct goods goods[100];//建立一个储存100件物品的结构体数组
int SUM;//储存物品总数
int bagContain;//储存背包能装的重量
int totalWeight = 0;//储存背包中现有的物品重量
int totalValue = 0;//储存背包中现有的物品价值
int MaxValue = 0;//储存目前背包中所装物品的最大价值
int index = 0;//储存可能解的个数
int possibleCombine[20][101];
vector<int> seq;//储存遍历序列
bool visit[100] = { false };//标记结点是否被访问过
bool flag = false;//记录用户输入是否为正整数（false表示不为，true表示为）

int examine(char a[]) {//检测用户的输入是否为数字
	flag = true;
	int i = 0;
	int result = 0;
	for (; a[i] != 0; i++) {
		if (a[i] < 48 || a[i]>57) {
			cout << "请输入一个正整数！" << endl;
			flag = false;
			break;
		}
	}
	if (flag) {
		for (int j = 0; a[j] != 0; j++) {//将用户输入的数字字符转化为数
			result = result + (a[j] - 48) * pow(10, i - j - 1);
		}
		flag = true;
	}
	return result;
}

//获取用户输入
void getUserInput() {
	char tempL[20];//暂时储存用户输入
	while (flag == false) {
		cout << "请输入背包能容纳的重量:";
		cin >> tempL;
		bagContain = examine(tempL);
	}
	flag = false;
	while (flag==false) {
		cout << "请输入物品个数:";
		cin >> tempL;
		SUM = examine(tempL);
	}
	flag = false;
	cout << "\n";
	for (int i = 0; i < SUM; i++) {
		while (flag == false) {
			cout << "请输入第"<<i+1<<"个物品的重量:";
			cin >> tempL;
			goods[i].weight = examine(tempL);
		}
		flag = false;
		while (flag == false) {
			cout << "请输入第" << i+1 << "个物品的价值:";
			cin >> tempL;
			goods[i].value = examine(tempL);
		}
		flag = false;
		cout << "\n";
	}
}

//检查是否需要剪枝
bool check(int node, int totalWeight, int totalValue,int tag) {
	if (tag == 1) {//装入背包的情况
		int temp = totalValue;
		for (int i = node; i < SUM; i++) {//计算该组合能达到的最大价值
			temp += goods[i].value;
		}
		if (totalWeight + goods[node].weight > bagContain) {//若加上该物品后，超重，则需要剪枝
			return true;
		}
		if (temp < MaxValue) {//若该组合能达到的最大价值比当前最优解小，则需要剪枝
			return true;
		}
		return false;
	}
	if (tag == 0) {//不装入背包的情况
		int temp = totalValue;
		if (node+1 < SUM) {
			for (int i = node+1; i < SUM; i++) {//计算该组合能达到的最大价值
				temp += goods[i].value;
			}
			if (temp < MaxValue) {//若该组合能达到的最大价值比当前最优解小，则需要剪枝
				return true;
			}
		}
		return false;
	}
}
/*
//剪枝函数
void cut(int node) {
	for (int i = node; i < SUM; i++) {
		visit[node] = 1;
	}
}*/

//储存结果函数
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
	cout << "物品的装入情况为：";
	for (int ele : seq) {
		cout << ele << " ";
	}
	cout << "；\t总重量为：" << currentWeight << "；";
	cout << "\t总价值为：" << currentValue << "\n";
}

//回溯法解决0/1背包问题
void dfs_search(int node,int totalWeight,int totalValue) {
	if (node >= SUM) {//找到一组结果，输出
		result(totalWeight, totalValue);
	}
	else {
		if (!visit[node]) {
			//要将node结点放入背包
			if (!check(node, totalWeight, totalValue,1)) {//验证是否需要剪枝
				visit[node] = true;//访问
				seq.push_back(1);//向序列相应位置填入1
				if (MaxValue < totalValue + goods[node].value) {//更新MaxValue
					MaxValue = totalValue + goods[node].value;
				}
				dfs_search(node + 1, totalWeight + goods[node].weight, totalValue + goods[node].value);//处理下一个结点
				seq.erase(seq.begin() + node);//擦除序列相应位置的值
				visit[node] = false;//重置
			}
			//不将node结点放入背包
			if (!check(node, totalWeight, totalValue, 0)) {//验证是否需要剪枝
				visit[node] = true;
				seq.push_back(0);//向序列相应位置填入0
				dfs_search(node + 1, totalWeight, totalValue);//处理下一个结点
				seq.erase(seq.begin() + node);//擦除序列相应位置的值
				visit[node] = false;//重置
			}
		}
	}
}

int main() {
	cout << "********************获取用户输入********************\n";
	getUserInput();//获取用户输入
	dfs_search(0,0,0);//回溯法解决问题
	cout << "**********************输出结果**********************\n";
	cout << "装入物品组合的最大价值为：" << MaxValue << "；\n";
	cout << "物品的装入情况为：";
	for (int k = 0; k < index; k++) {
		if (possibleCombine[k][0] == MaxValue) {
			for (int j = 1; j <= SUM; j++) {
				cout << possibleCombine[k][j] << " ";
			}
			cout << "；\n";
		}
	}
	system("pause");
	return 0;
}