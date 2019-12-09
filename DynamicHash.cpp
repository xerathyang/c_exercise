// DynamicHash.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include <math.h>

using namespace std;

void doublearr(char**, int);
int hashing(char*, int);

class dynhash {
public:
	void put(char*, bool);
	void get(int);
	void collact(int, char*);
	dynhash();
private:
	int size = 2;
	int curr = 2;
	char** arr = new char* [8];
};

dynhash::dynhash() {
	curr = 2;
	size = 8;
	for (int i = 0; i < 8; i++) {
		arr[i] = NULL;
	}
}

//collide reaction
void dynhash::collact(int index, char* key) {
	//system("pause");
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
	if (keysite == index) {
		//site1 is not fit
		if (site1 != index) {
			//swap with key
			cache[0] = arr[index * 2][0];
			cache[1] = arr[index * 2][1];
			arr[index * 2][0] = key[0];
			arr[index * 2][1] = key[1];
			if (arr[site1 * 2] == NULL) {
				arr[site1 * 2] = new char[2];
				arr[site1 * 2][0] = cache[0];
				arr[site1 * 2][1] = cache[1];
			}
			else {
				arr[site1 * 2 + 1] = new char[2];
				arr[site1 * 2 + 1][0] = cache[0];
				arr[site1 * 2 + 1][1] = cache[1];
			}
			cout << keysite << endl;
		}
		//site2 is not fit
		else if (site2 != index) {
			//swap with key
			cache[0] = arr[index * 2 + 1][0];
			cache[1] = arr[index * 2 + 1][1];
			arr[index * 2 + 1][0] = key[0];
			arr[index * 2 + 1][1] = key[1];
			cout << keysite << endl;
			if (arr[site2 * 2] == NULL) {
				arr[site2 * 2] = new char[2];
				arr[site2 * 2][0] = cache[0];
				arr[site2 * 2][1] = cache[1];
				//cout << &arr[site2 * 2] << endl;
			}
			else {
				arr[site2 * 2 + 1] = new char[2];
				arr[site2 * 2 + 1][0] = cache[0];
				arr[site2 * 2 + 1][1] = cache[1];
				//cout << &arr[site2 * 2 + 1] << endl;
			}
		}
		//all fit, need additional bit
		else {
			collact(index, key);
		}
	}
	//key's index not fit current index
	else {
		put(key, 1);
	}
	delete[] cache;
}

void dynhash::put(char* key, bool show) {
	char* input = new char[2];
	input[0] = key[0];
	input[1] = key[1];
	//get index by hash
	int index = hashing(input, curr);
	//first is full
	if (arr[index * 2] != NULL) {
		//second is full
		//cout << arr[index * 2] << endl;
		if (arr[index * 2 + 1] != NULL) {
			//collide
			//cout << arr[index * 2+1][0] << arr[index * 2+1][1] << endl;
			collact(index, key);
		}
		else {
			//second is empty, put in
			arr[index * 2 + 1] = input;
			if (show == 1)
				cout << index << endl;
			//cout << &arr[index * 2 + 1] << endl;
		}
	}
	else {
		//first is empty, put in
		arr[index * 2] = input;
		if (show == 1)
			cout << index << endl;
		//cout << &arr[index * 2] << endl;
	}

}

void dynhash::get(int index) {
	if (index * 2 > size) {
		cout << "Out of range." << endl;
		return;
	}

	if (arr[index * 2] != NULL) {
		cout << arr[index * 2][0] << arr[index * 2][1] << " ";
		if (arr[index * 2 + 1] != 0) {
			cout << arr[index * 2 + 1][0] << arr[index * 2 + 1][1] << endl;
		}
		else {
			cout << endl;
		}
		return;
	}
	else if (arr[index * 2 + 1] != NULL) {
		cout << arr[index * 2 + 1][0] << arr[index * 2 + 1][1] << endl;
		return;
	}
	else {
		if ((index * 2) >= 8) {
			this->get(index * 2 % 4);
			return;
		}
		cout << "The bucket is empty." << endl;
		return;
	}
}

void doublearr(char** a, int size) {
	char** b = new char* [size * 2];
	for (int i = 0; i < size * 2; i++) {
		b[i] = NULL;
	}
	for (int i = 0; i < size; i++) {
		b[i] = a[i];
	}
	a = b;
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
			cin >> key;
			a.put(key, 1);
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
