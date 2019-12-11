// DynamicHash.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include <math.h>

using namespace std;

int hashing(char*, int);

class dynhash {
public:
	void put(char*, bool, int, bool);
	void get(int);
	void collact(int, char*);
	char** doublearr(char**, int);
	dynhash();
private:
	int size = 2;
	int curr = 2;
	int pos = 2;
	char** arr = new char* [8];
};

dynhash::dynhash() {
	curr = 2;
	size = 8;
	pos = 2;
	for (int i = 0; i < 8; i++) {
		arr[i] = new char[2];
		arr[i][0] = 'N';
	}
}

//collide reaction
void dynhash::collact(int index, char* key) {
	char* cache = new char[2];
	curr++;
	if (curr > pos) {
		//double array size
		arr = doublearr(arr, size);
		size *= 2;
	}
	//new key's index
	int keysite = hashing(key, curr);
	//new array's index
	int site1 = hashing(arr[index * 2], curr);//here
	int site2 = hashing(arr[index * 2 + 1], curr);
	//compare key's and array's index
	//if array's index not fit current index, move to right place
	if (keysite == index) {
		//site1 is not fit
		if (site1 != index) {
			//swap with key
			cache[0] = arr[index * 2][0];
			cache[1] = arr[index * 2][1];
			arr[index * 2][0] = key[0];
			arr[index * 2][1] = key[1];
			if (arr[site1 * 2][0] == 'N') {
				//arr[site1 * 2] = new char[2];
				arr[site1 * 2][0] = cache[0];
				arr[site1 * 2][1] = cache[1];
				//put(cache, 0, 2, 1);
			}
			else {
				//arr[site1 * 2 + 1] = new char[2];
				arr[site1 * 2 + 1][0] = cache[0];
				arr[site1 * 2 + 1][1] = cache[1];
				//put(cache, 0, 2, 1);
			}
			cout << index << endl;
		}
		//site2 is not fit
		else if (site2 != index) {
			//swap with key
			cache[0] = arr[index * 2 + 1][0];
			cache[1] = arr[index * 2 + 1][1];
			arr[index * 2 + 1][0] = key[0];
			arr[index * 2 + 1][1] = key[1];
			if (arr[site2 * 2][0] == 'N') {
				arr[site2 * 2][0] = cache[0];
				arr[site2 * 2][1] = cache[1];
				//put(cache, 0, 2, 1);
			}
			else {
				arr[site2 * 2 + 1][0] = cache[0];
				arr[site2 * 2 + 1][1] = cache[1];
			}
			cout << index << endl;
		}
		//all fit, need additional bit
		else {
			collact(index, key);
		}
	}
	//key's index not fit current index
	else {
		put(key, 1, curr, 1);
	}
}

void dynhash::put(char* key, bool show, int place, bool col) {
	curr = 2;
	//get index by hash
	int index = hashing(key, place);
	//first is full
	if (arr[index * 2][0] != 'N') {
		//second is full
		if (arr[index * 2 + 1][0] != 'N') {

			if (place < curr) {
				put(key, show, place + 1, 1);
			}
			else {
				//collide
				collact(index, key);
			}

		}
		else {
			//second is empty, put in
			arr[index * 2 + 1][0] = key[0];
			arr[index * 2 + 1][1] = key[1];
			if (show == 1)
				cout << index << endl;
		}
	}
	else {
		//first is empty, put in
		arr[index * 2][0] = key[0];
		arr[index * 2][1] = key[1];
		if (show == 1)
			cout << index << endl;
	}

}

void dynhash::get(int index) {
	if (index * 2 >= size) {
		cout << "Out of range." << endl;
		return;
	}

	if (arr[index * 2][0] != 'N') {
		cout << arr[index * 2][0] << arr[index * 2][1];
		if (arr[index * 2 + 1][0] != 'N') {
			cout << " " <<arr[index * 2 + 1][0] << arr[index * 2 + 1][1] << endl;
		}
		else {
			cout << endl;
		}
		return;
	}
	else if (arr[index * 2 + 1][0] != 'N') {
		cout << arr[index * 2 + 1][0] << arr[index * 2 + 1][1] << endl;
		return;
	}
	else {
		if (index >= 4) {
			int cache = index, reget = 0, point = 0;
			for (int i = 0; cache > 0; i++) {
				reget += (int)pow(10, i)*(cache%2);
				cache /= 2;
				point++;

			}

			reget %= (int)pow(10, point - 1);
			cache = 0;
			for (int i = 0; reget > 0; i++) {
				cache += (int)pow(2, i)*(reget%10);
				reget /= 10;
			}
			get(cache);
			return;
		}
		//if ((index - (int)pow(2, pos - 1)) >= 0) {
		//	this->get(index - (int)pow(2, pos - 1));
		//	return;
		//}
		//else if (index >= 4) {
		//	this->get(index % 4);
		//	return;
		//}
		cout << "The bucket is empty." << endl;
		return;
	}
}

char** dynhash::doublearr(char** a, int size) {
	pos++;
	char** b = new char* [size * 2];
	for (int i = 0; i < size * 2; i++) {
		b[i] = new char[2];
		b[i][0] = 'N';
	}
	for (int i = 0; i < size; i++) {
		b[i][0] = a[i][0];
		b[i][1] = a[i][1];
	}
	return b;
}

int hashing(char* in, int length) {
	int ans = 0;
	int r = 0;
	int l = (int)pow(10, length);
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
	ans = ans + (num % 2) * 10;
	num /= 2;
	ans = ans + (num % 2) * 100;

	ans = ans % l;

	for (int i = 0; ans != 0; i++) {
		r += (int)pow(2, i) * (ans % 10);
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
			cin >> key[0] >> key[1];
			a.put(key, 1, 2, 0);
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