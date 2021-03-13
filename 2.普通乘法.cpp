#include<iostream>
#include<sstream>
#include<stdlib.h>
#include<stdio.h>
#include<vector>
#include<time.h>
#include<windows.h>

using namespace std;
int testnum = 1;//测试次数

//输出所有值函数
void printout(const std::vector<long long>& res, long long len) {
	long long i = len - 1;
	while (res[i] == 0) --i;
	for (i; i >= 0; --i) {
		cout << res[i];
	}
}

//标准化10进制函数
void stand(vector<long long>& vec) {
	long long len = vec.size();
	long long addflag = 0;//进位标记
	long long temp = 0;
	for (long long i = 0; i < len; ++i) {
		temp = vec[i] + addflag;
		while (temp < 0 && i + 1 < len) {
			temp += 10;
			vec[i + 1]--;
		}
		vec[i] = temp % 10;
		addflag = temp / 10;
	}
}

//普通乘法111111
vector<long long>  ordinaryNMTP(const vector< long long>& vec1, const vector<long long>& vec2, long long len) {
	vector<long long> vec(len * 2);
	for (int i = len - 1; i >= 0; i--) {
		if (vec1[i] == 0) continue; // 0跳过
		for (int j = len - 1; j >= 0; j--) {
			vec[i + j] += vec1[i] * vec2[j];
		}
	}
	return vec;
}

//随机数生成函数
int generate(vector<long long>& vec, long long len) {
	srand((unsigned long)time(NULL));
	cout << "\n\n产生的随机数如下：" << endl;
	Sleep(1000);
	vec[len - 1] = rand() % 9; // 第一位不为0
	vec[len - 1]++;
	cout << vec[len - 1];
	for (int i = len - 2; i >= 0; --i) {
		vec[i] = rand() % 10;
		cout << vec[i];
	}
	return 0;
}

int agent(long long len) {
	
	double duration;
	
	vector<long long> vec1(len);
	vector<long long> vec2(len);
	vector<long long> res(2 * len);
	generate(vec1, len);//随机产生数1
	generate(vec2, len);//随机产生数2
	clock_t start, end;    
	start = clock();//开始计时
	
	res = ordinaryNMTP(vec1, vec2, len);

	end = clock();//结束计时
	stand(res);   //标准化
	printout(res,2*len);//输出
	duration = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "\n乘法用时:" << duration << "S" << endl;//输出乘法用时
	
	return 0;
}


int main() {
	long long len;
	while (true) {
		cout << "请输入位数：" << endl;
		cin >> len;
		agent(len);
	}
	return 0;
}