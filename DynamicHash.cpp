// DynamicHash.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class dynhash {
public:
	void put(char*);
	void get(int);
	void colre(int,char*,int);
private:
	int size;
	char **arr = new char* [8];
};

dynhash::dynhash() {
	size = 2;
	for (int i = 0; i < 8; i++) {
		arr[i] = 0;
	}
}

void dynhash::colre(int index, char* key,int curr) {
	int point = index;
	doublearr(arr, size);
	size *= 2;
	if (hashing(arr[index], curr+1) != index) {
		
	}
}

void dynhash::put(char* key) {
	int curr = 2;
	int index = hashing(key, curr);
	if (arr[index] != 0) {
		if (arr[index + 1] != 0) {
			colre(index,key,curr);
		}
		else {
			arr[index + 1] = key;
		}
	}
	else {
		arr[index] = key;
	}
}

void dynhash::get(int index) {
	if (index > size) {
		cout << "Out of range." << endl;
		return;
	}
	if (arr[index] != 0) {
		cout << arr[index] << " ";
		if (arr[index + 1] != 0) {
			cout << arr[index + 1] << endl;
		}
	}
	else if(arr[index+1]!=0){
		cout << arr[index + 1] << endl;
	}
	else {
		cout << "The bucket is empty." << endl;
	}
}

void doublearr(char** a,int size) {
	int pre = size;
	size *= 2;
	char **b = new char* [size];
	for (int i = 0; i < size; i++) {
		b[i] = 0;
	}
	for (int i = 0; i < pre; i++) {
		b[i] = a[i];
	}
	a = b;
}

int hashing(char* in,int length) {
	int ans = 0;
	int r = 0;
	int l = 100000;
	switch (in[0]) {
	case 'A':
		ans += 100000;
	case 'B':
		ans += 101000;
	case 'C':
		ans += 110000;
	case 'D':
		ans += 111000;
	}
	ans = ans + (in[1] % 2);
	ans = ans + (in[1] % 2)*10;
	ans = ans + (in[1] % 2)*100;
	for (int i = length; i > 0; i--) {
		ans = ans % l;
		l /= 10;
	}
	for (int i = 0; ans > 0; i++) {
		r += (int)pow(2, i)*(ans%10);
		ans /= 10;
	}
	return r;
}

int main()
{
	char input;
	char key[2];
	int index;
	dynhash a = dynhash();
	while (cin >> input) {
		switch (input) {
		case 'p':
			cin >> input >> input;
			cin >> key;
			a.put(key);
		case 'g':
			cin >> input >> input;
			cin >> index;
		case 'e':
			cin >> input >> input >> input;
		}
	}
}

// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
