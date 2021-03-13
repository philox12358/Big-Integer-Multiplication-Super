#include<iostream>
#include<deque>
#include<sstream>
#include <stdlib.h>
#include <time.h>
#include<stdlib.h>

using namespace std;     //使用命名空间

string ordinaryNMTP(const string s1, const string s2) {
    string res = "";//最终返回的字符串
    int num = 0;
    deque <int> vec(s1.size() + s2.size() - 1, 0); //使用deque是因为出现进位时可以在队列前插入数据，效率比vector高，大小设为最小
    //int nums[ s1.size() ];
    for (int i = 0; i < s1.size(); ++i) {
        for (int j = 0; j < s2.size(); ++j) {
            vec[i + j] += (s1[i] - '0') * (s2[j] - '0');//乘法
        }
    }
    //格式化10进制
    int addflag = 0;//进位标记
    for (int i = vec.size() - 1; i >= 0; --i) {
        int temp = vec[i] + addflag;
        vec[i] = temp % 10;
        addflag = temp / 10;
    }
    if (addflag != 0)  vec.push_front(addflag);     //判断是否有最高位。
    //整型转换成字符串
    for (auto elem : vec) {
        ostringstream ss;
        ss << elem;
        res = res + ss.str();
    }
    return res;
}

//产生随机数的函数
string generate(int len) {
    srand((unsigned int)time(0));
    string str = "";
    for (int i = 0; i < len; ++i) {
        ostringstream SS;
        SS << rand() % 10;
        str = str + SS.str();
    }
    //str[++i] = '\0';
    return str;
}



int main() {
    int len;
    cout << "请输入需要产生的整数位大小：" << endl;
    cin >> len;
    string str1, str2;                 //创建默认为空的字符串

    double duration;
    str1 = generate(len);                   //产生随机数字符串
    str2 = generate(len);
    cout << str1 << "\n*\n" << str2 << "\n=\n" << endl;
    clock_t start, end;                  //计时开始
    start = clock();
    cout << ordinaryNMTP(str1, str2) << endl;
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;    //输出计时器
    cout << duration << "s" << endl;
    system("pause");

    /*
    while (std::cin >> str1 >> str2)                //循环输入
    {
        cout << str1 << "*" << str2 << "=" << endl;
        cout << ordinaryNMTP(str1, str2) << endl;
    }*/

    return 0;
}