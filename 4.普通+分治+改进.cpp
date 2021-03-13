#include<iostream>
#include<sstream>
#include<stdlib.h>
#include<stdio.h>
#include<vector>
#include<time.h>
#include<windows.h>

using namespace std;
long long test_size = 128;//128是一个比较合适的值
long long answer[10][128] = { 0 };


//检查答案正确性
long long check(const vector< long long>& vec1, const vector<long long>& vec2) {
	long long len = vec1.size();
	for (long long i = 0; i < len; ++i) {
		if (vec1[i] != vec2[i]) {
			cout << "结果错误！！！" << endl;
			return 0;
		}
	}
	cout << "结果正确！" << endl;
	return 0;
}


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
	for (int i =len-1; i >= 0; i--) {
		if (vec1[i] == 0) continue; // 0跳过
		for (int j = len-1; j >= 0; j--) {
			vec[i + j] += vec1[i] * vec2[j];
		}
	}
	return vec;
}

//普通乘法2222222
vector<long long>  goodNMTP(const vector< long long>& vec1, const vector<long long>& vec2, long long len) {
	vector<long long> res(2 * len);
	for (long long i = 1; i < 10; ++i) {
		for (long long j = 0; j < len; ++j) {
			answer[i][j] = i * vec1[j];
		}
	}
	for (long long i = 0; i < len; ++i) {
		long long temp = vec2[i];
		if (!temp) continue;
		for (long long j = 0; j < len; ++j) {
			res[i + j] += answer[temp][j];
		}
	}
	if (vec2.size() == len || vec2[len]==0) {
		return res;
	}
	else if (vec2[len]) {
		
		for (long long i = 0; i < len; ++i) {
			res[i + len] += vec1[i];
		}
		return res;
	}
}

//中级乘法
vector<long long> betterNMTP(const vector<long long>& x, const vector<long long>& y, long long len) {
	if (len <= test_size) return ordinaryNMTP(x, y, len);
	long long k = len / 2;

	if (2 * k == len) { // 偶数
		vector<long long> res(2 * len, 0);

		vector<long long> XA{ x.begin(), x.begin() + k };//定义A、D、C、D
		vector<long long> XB{ x.begin() + k, x.end() };
		vector<long long> YC{ y.begin(), y.begin() + k };
		vector<long long> YD{ y.begin() + k, y.end() };

		vector<long long> AC = betterNMTP(XA, YC, k);//AC前头计算！！！！！！！！！！！！！递归
		vector<long long> BD = betterNMTP(XB, YD, k);//BD尾巴计算！！！！！！！！！！！！！递归

		vector<long long> XA_B(k);
		vector<long long> YD_C(k);

		for (long long i = k - 1; i >= 0; --i) {//计算（A+B）和（D+C）
			XA_B[i] = XA[i] + XB[i];
			YD_C[i] = YD[i] + YC[i];
		}

		vector<long long> A_B_D_C = betterNMTP(XA_B, YD_C, k);  //(A+B)(D+C)！！！！！！！！！！！！！递归	

		for (long long i = 0; i < len; ++i) {
			A_B_D_C[i] -= (AC[i] + BD[i]);//求【(A+B)(D+C)-AC-BD】
		}
		for (long long i = 0; i < len; ++i) {
			res[i] = AC[i];//头头加AC
		}
		for (long long i = len; i < 2 * len; ++i) {
			res[i] = BD[i - len];//末尾加BD
		}
		for (long long i = k; i < len + k; ++i) {
			res[i] += A_B_D_C[i - k];//中间加中间
		}
		return res;
	}
	else { // 奇数
		k++; // k加1
		len++; // len加1
		vector<long long> res(2 * len, 0);

		vector<long long> vec1 = x;
		vector<long long> vec2 = y;
		vec1.push_back(0);
		vec2.push_back(0);//最后一位插0

		vector<long long> XA{ vec1.begin(), vec1.begin() + k };//定义A、D、C、D
		vector<long long> XB{ vec1.begin() + k, vec1.end() };
		vector<long long> YC{ vec2.begin(), vec2.begin() + k };
		vector<long long> YD{ vec2.begin() + k, vec2.end() };

		vector<long long> AC = betterNMTP(XA, YC, k);//AC前头计算！！！！！！！！！！！！！递归
		vector<long long> BD = betterNMTP(XB, YD, k);//BD尾巴计算！！！！！！！！！！！！！递归

		vector<long long> XA_B(k);
		vector<long long> YD_C(k);

		for (long long i = k - 1; i >= 0; --i) {//计算（A+B）和（D+C）
			XA_B[i] = XA[i] + XB[i];
			YD_C[i] = YD[i] + YC[i];
		}

		vector<long long> A_B_D_C = betterNMTP(XA_B, YD_C, k);  //(A+B)(D+C)！！！！！！！！！！！！！递归	

		for (long long i = 0; i < len; ++i) {
			A_B_D_C[i] -= (AC[i] + BD[i]);//求【(A+B)(D+C)-AC-BD】
		}
		for (long long i = 0; i < len; ++i) {
			res[i] = AC[i];//头头加AC
		}
		for (long long i = len; i < 2 * len; ++i) {
			res[i] = BD[i - len];//末尾加BD
		}
		for (long long i = k; i < len + k; ++i) {
			res[i] += A_B_D_C[i - k];//中间加中间
		}
		res.pop_back();
		res.pop_back();
		return res;
	}
}

//高级乘法
vector<long long> bestNMTP(const vector<long long>& x, const vector<long long>& y, long long len) {
	if (len <= test_size) return goodNMTP(x, y, len);
	long long k = len / 2;

	if (2 * k == len) { // 偶数
		vector<long long> res(2 * len, 0);

		vector<long long> XA{ x.begin(), x.begin() + k };//定义A、D、C、D
		vector<long long> XB{ x.begin() + k, x.end() };
		vector<long long> YC{ y.begin(), y.begin() + k };
		vector<long long> YD{ y.begin() + k, y.end() };

		vector<long long> AC = bestNMTP(XA, YC, k);//AC前头计算！！！！！！！！！！！！！递归
		vector<long long> BD = bestNMTP(XB, YD, k);//BD尾巴计算！！！！！！！！！！！！！递归

		vector<long long> XA_B(k);
		vector<long long> YD_C(k);

		for (long long i = k - 1; i >= 0; --i) {//计算（A+B）和（D+C）
			XA_B[i] = XA[i] + XB[i];
			YD_C[i] = YD[i] + YC[i];
		}
		XA_B.push_back(0);
		YD_C.push_back(0); // 加一个最高位，防止丢失
		stand(XA_B);
		stand(YD_C);
		vector<long long> A_B_D_C = bestNMTP(XA_B, YD_C, k+1);  //(A+B)(D+C)！！！！！！！！！！！！！递归	

		for (long long i = 0; i < len; ++i) {
			A_B_D_C[i] -= (AC[i] + BD[i]);//求【(A+B)(D+C)-AC-BD】
		}
		for (long long i = 0; i < len; ++i) {
			res[i] = AC[i];//头头加AC
		}
		for (long long i = len; i < 2 * len; ++i) {
			res[i] = BD[i - len];//末尾加BD
		}
		for (long long i = k; i < len + k+2; ++i) {
			res[i] += A_B_D_C[i - k];//中间加中间
		}
		stand(res);
		return res;
	}
	else { // 奇数
		k++; // k加1
		len++; // len加1
		vector<long long> res(2 * len, 0);

		vector<long long> vec1 = x;
		vector<long long> vec2 = y;
		vec1.push_back(0);
		vec2.push_back(0);//最后一位插0

		vector<long long> XA{ vec1.begin(), vec1.begin() + k };//定义A、D、C、D
		vector<long long> XB{ vec1.begin() + k, vec1.end() };
		vector<long long> YC{ vec2.begin(), vec2.begin() + k };
		vector<long long> YD{ vec2.begin() + k, vec2.end() };

		//YC.push_back(0);
		//YD.push_back(0);
		vector<long long> AC = bestNMTP(XA, YC, k);//AC前头计算！！！！！！！！！！！！！递归
		vector<long long> BD = bestNMTP(XB, YD, k);//BD尾巴计算！！！！！！！！！！！！！递归

		vector<long long> XA_B(k);
		vector<long long> YD_C(k);

		for (long long i = k - 1; i >= 0; --i) {//计算（A+B）和（D+C）
			XA_B[i] = XA[i] + XB[i];
			YD_C[i] = YD[i] + YC[i];
		}

		XA_B.push_back(0);// 加一个最高位，防止丢失
		YD_C.push_back(0); 
		stand(XA_B);
		stand(YD_C);
		vector<long long> A_B_D_C = bestNMTP(XA_B, YD_C, k+1);  //(A+B)(D+C)！！！！！！！！！！！！！递归	

		for (long long i = 0; i < len; ++i) {
			A_B_D_C[i] -= (AC[i] + BD[i]);//求【(A+B)(D+C)-AC-BD】
		}
		for (long long i = 0; i < len; ++i) {
			res[i] = AC[i];//头头加AC
		}
		for (long long i = len; i < 2 * len; ++i) {
			res[i] = BD[i - len];//末尾加BD
		}
		for (long long i = k; i < len + k+2; ++i) {
			res[i] += A_B_D_C[i - k];//中间加中间
		}
		res.pop_back();
		res.pop_back();
		stand(res);
		return res;
	}
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

//主函数
int main() {
	long long len = 0;
	double duration1 = 0;
	double duration2 = 0;
	double duration3 = 0;
	while (true) {
		cout << "请输入位数：" << endl;
		cin >> len;
		vector<long long> vec1(len, 0);
		vector<long long> vec2(len, 0);
		vector<long long> res1(2 * len, 0);
		vector<long long> res2(2 * len, 0);
		vector<long long> res3(2 * len, 0);

		generate(vec1, len);//随机产生数1
		generate(vec2, len);//随机产生数2
		clock_t start, end;

		cout << "\n\n改进分治乘法结果：" << endl;
		start = clock();//开始计时
		res1 = bestNMTP(vec1, vec2, len);
		end = clock();//结束计时
		stand(res1);//标准化
		printout(res1, 2 * len);//输出
		duration1 = (double)(end - start) / CLOCKS_PER_SEC;
		cout << "\n改进分治用时: " << duration1 << " s" << endl;//输出乘法时间

		cout << "\n\n分治乘法结果：" << endl;
		start = clock();//开始计时
		res2 = betterNMTP(vec1, vec2, len);
		end = clock();//结束计时
		stand(res2);//标准化
		printout(res2, 2 * len);//输出
		duration2 = (double)(end - start) / CLOCKS_PER_SEC;
		cout << "\n分治用时: " << duration2 << " s" << endl;//输出乘法时间

		cout << "\n普通乘法结果：" << endl;
		start = clock();//开始计时
		res3 = ordinaryNMTP(vec1, vec2, len);
		end = clock();//结束计时
		stand(res3);
		printout(res3, 2 * len);
		duration3 = (double)(end - start) / CLOCKS_PER_SEC;
		cout << "\n普通乘法用时: " << duration3 << " s" << endl;//输出乘法时间


		cout << "\n改进分治用时：" << duration1 << " s" << endl;
		cout << "分治用时：    " << duration2 << " s" << endl;
		cout << "普通乘法用时：" << duration3 << " s\n" << endl;

		check(res3, res1);//检查答案正确性
		check(res3, res2);
		cout << endl;
	}
	system("pause");
	return 0;
}