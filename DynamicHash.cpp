// DynamicHash.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include <math.h>

using namespace std;

void doublearr(char**, int);
int hashing(char*, int);

class dynhash {
public:
	void put(char*);
	void get(int);
	void collact(int,char*);
	dynhash();
private:
	int size=2;
	int curr=2;
	char **arr = new char* [8];
};

dynhash::dynhash() {
	curr = 2;
	size = 8;
	for (int i = 0; i < 8; i++) {
		arr[i] = 0;
	}
}

//collide reaction
void dynhash::collact(int index, char* key) {
	char* cache = new char[2];
	curr++;
	//double array size
	doublearr(arr, size);
	size *= 2;
	//new key's index
	int keysite = hashing(key, curr);
	//new array's index
	int site1 = hashing(arr[index * 2], curr);//here
	int site2 = hashing(arr[index * 2 + 1], curr);
	//compare key's and array's index
	//if array's index not fit current index, move to right place
	if (keysite==index) {
		//site1 is not fit
		if (site1 != index) {
			//swap with key
			cache[0] = arr[index * 2][0];
			cache[1] = arr[index * 2][1];
			arr[index * 2][0] = key[0];
			arr[index * 2][1] = key[1];
			put(cache);
		}
		//site2 is not fit
		else if (site2 != index) {
			//swap with key
			cache[0] = arr[index * 2 + 1][0];
			cache[1] = arr[index * 2 + 1][1];
			arr[index * 2 + 1][0] = key[0];
			arr[index * 2 + 1][1] = key[1];
			put(cache);
		}
		//all fit, need additional bit
		else {
			collact(index,key);
		}
	}
	//key's index not fit current index
	else {
		put(key);
	}
}

void dynhash::put(char* key) {
	char* input= new char[2];
	input[0] = key[0];
	input[1] = key[1];
	//get index by hash
	int index = hashing(input, curr);
	//first is full
	if (arr[index*2] != 0) {
		//second is full
		if (arr[index*2 + 1] != 0) {
			//collide
			collact(index,key);
		}
		else {
			//second is empty, put in
			arr[index*2 + 1] = input;
			cout << index << endl;
		}
	}
	else {
		//first is empty, put in
		arr[index*2] = input;
		cout << index << endl;
	}
}

void dynhash::get(int index) {
	if (index > size) {
		cout << "Out of range." << endl;
		return;
	}
	if (arr[index*2] != 0) {
		cout << arr[index * 2][0] << arr[index * 2][1] << " ";
		if (arr[index*2 + 1] != 0) {
			cout << arr[index*2 + 1][0] << arr[index * 2 + 1][1] << endl;
		}
	}
	else if(arr[index*2 + 1]!=0){
		cout << arr[index*2 + 1][0] << arr[index * 2 + 1][1] << endl;
	}
	else {
		cout << "The bucket is empty." << endl;
	}
}

void doublearr(char** a,int size) {
	char **b = new char* [size*2];
	for (int i = 0; i < size*2; i++) {
		b[i] = 0;
	}
	for (int i = 0; i < size; i++) {
		b[i] = a[i];
	}
	a = b;
}

int hashing(char* in,int length) {
	int ans = 0;
	int r = 0;
	int l = (int)pow(10,length);
	switch (in[0]) {//here
	case 'A':
		ans += 100000;
		break;
	case 'B':
		ans += 101000;
		break;
	case 'C':
		ans += 110000;
		break;
	case 'D':
		ans += 111000;
		break;
	}
	int num = in[1];
	ans = ans + (num % 2);
	num /= 2;
	ans = ans + (num % 2)*10;
	num /= 2;
	ans = ans + (num % 2)*100;
	
	ans = ans % l;

	for (int i = 0; ans != 0; i++) {
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
			break;
		case 'g':
			cin >> input >> input;
			cin >> index;
			a.get(index);
			break;
		case 'e':
			cin >> input >> input >> input;
			exit(0);
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
