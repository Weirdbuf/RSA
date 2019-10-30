// RSA.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include<string>
#include<vector>
#include <time.h>
using namespace std;
//随机生成大素数算法-----> p,q
//int p = 11, q = 13;
//int n = p * q;
//check if a is coprime to b

int gcd(int a,int b ) {
	if (b == 0)
		return a;
	return gcd(b, a%b);
}

//EEA,扩展的欧几里得算法-------> 求e-1mode(phi)
int  ExtendedEuclid(int a, int b,int &x,int &y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	int res = ExtendedEuclid(b, a%b, x, y);
	int t = x;
	x = y;
	y = t - a / b * y;
	return res;
}


//快速指数运算    x^h % n

int sq_mul(int x, int h,int n ) {
	int res = 1;
	while (h) {
		if (h & 1) {
			res = res * x%n;
		}
		res = res * res%n;
		h >>= 1;
	}
	return res;

}
//加密
int encirpt(int m,int e,int n) {
	int c = sq_mul(m, e, n);
	return c;
}
//解密
int decript(int c, int d, int n) {
	int m = sq_mul(c, d, n);
	return m;
}
int main()
{
	srand((unsigned int )time(NULL));//make sure every time the seed is different 
	/*---------------------generate prime p and q at random -----------*/
	srand(time(NULL));
	
	
	int  p = 157, q = 211;
	int n = p * q;
	int phi = (p - 1)*(q - 1);
	/*-----------------generate a random e (public key) that coprime with phi -----------------------*/
	int e = (rand() % (phi - 3)) + 3;
	int g = gcd(e, phi);
	while (g!= 1) {
		e = (rand() % (phi - 3)) + 3;
		g = gcd(e, phi);
	}
	
	cout << "your public key is " << e << endl;
	/*--------------------get d --------------------------------------------*/
	int x, y;
	//x is the inverse of e , namely ,d
   ExtendedEuclid(e, phi,x,y);
   //to ensure d is positive
   int d = (x%phi + phi) % phi; 

   cout << "your private key is " << d << endl;
   cout << "check to see if d is the inverse of e ..." << " e * d%phi= "<<e * d%phi << endl;
   
   /*------------------------encirpt----------------------------------------*/
   cout << endl;
   cout << "enter message: ";
   string message;
   getline(cin, message);
   vector<int> cipher;
   for (char m : message) {
	   cipher.push_back(encirpt(int(m), e, n));
   }
   cout << "cipher value : ";
   for (int c : cipher) {
	   cout << c<< " ";
   }
   cout << endl;
   //string decirptMessage;
   cout << "decript :  ";
   for (int c : cipher) {
	   int m=decript(c, d, n);
	   cout << m << " ";
	   
   }






}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
