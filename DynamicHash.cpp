#include <iostream>
#include <math.h>

using namespace std;

int hashing(char*, int);

class dynhash {
public:
	void put(char*, bool, int);
	void get(int);
	void collact(int, char*,int);
	char** doublearr(char**, int);
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
		arr[i] = new char[2];
		arr[i][0] = 'N';
	}
}

//collide reaction
void dynhash::collact(int index, char* key,int place) {
	char* cache = new char[2];
	//new key's index
	int keysite = hashing(key, place);
	//new array's index
	int site1 = hashing(arr[index * 2], place);//here
	int site2 = hashing(arr[index * 2 + 1], place);
	//compare key's and array's index
	//if array's index not fit current index, move to right place
	if (keysite == index) {
		//site1 is not fit
		if (site1 != index) {
			curr++;
			//double array size
			arr = doublearr(arr, place);
			//swap with key
			cache[0] = arr[index * 2][0];
			cache[1] = arr[index * 2][1];
			arr[index * 2][0] = key[0];
			arr[index * 2][1] = key[1];
			if (arr[site1 * 2][0] == 'N') {
				put(cache, 0, 2);
			}
			else {
				put(cache, 0, 2);
			}
			cout << index << endl;
		}
		//site2 is not fit
		else if (site2 != index) {
			curr++;
			//double array size
			arr = doublearr(arr, place);
			//swap with key
			cache[0] = arr[index * 2 + 1][0];
			cache[1] = arr[index * 2 + 1][1];
			arr[index * 2 + 1][0] = key[0];
			arr[index * 2 + 1][1] = key[1];
			if (arr[site2 * 2][0] == 'N') {
				put(cache, 0, 2);
			}
			else {
				put(cache, 0, 2);
			}
			cout << index << endl;
		}
		//all fit, need additional bit
		else {
			collact(index, key, place+1);
		}
	}
	//key's index not fit current index
	else {
		put(key, 1, 2);
	}
	delete[] cache;
}

void dynhash::put(char* key, bool show, int place) {
	char* input = new char[2];
	input[0] = key[0];
	input[1] = key[1];
	//get index by hash
	int index = hashing(input, place);
	//first is full
	if (arr[index * 2][0] != 'N') {
		//second is full
		if (arr[index * 2 + 1][0] != 'N') {
			collact(index, key, 2);
		}
		else {
			//second is empty, put in
			arr[index * 2 + 1] = input;
			if (show == 1)
				cout << index << endl;
		}
	}
	else {
		//first is empty, put in
		arr[index * 2] = input;
		if (show == 1)
			cout << index << endl;
	}

}

void dynhash::get(int index) {
	if (index * 2 > size) {
		cout << "Out of range." << endl;
		return;
	}

	if (arr[index * 2][0] != 'N') {
		cout << arr[index * 2][0] << arr[index * 2][1] << " ";
		if (arr[index * 2 + 1][0] != 'N') {
			cout << arr[index * 2 + 1][0] << arr[index * 2 + 1][1] << endl;
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
		if ((index - (int)pow(2, curr - 1)) >= 0) {
			this->get(index - (int)pow(2, curr - 1));
			return;
		}
		else if (index >= 4) {
			this->get(index % 4);
			return;
		}
		cout << "The bucket is empty." << endl;
		return;
	}
}

char** dynhash::doublearr(char** a, int time) {
	curr++;
	size *= 2;
	char** b = new char* [size * 2];
	for (int i = 0; i < size * 2; i++) {
		b[i] = new char[2];
		b[i][0] = 'N';
	}
	for (int i = 0; i < size; i++) {
		b[i] = a[i];
	}
	if (time > curr)
		arr = doublearr(arr, time + 1);
	else
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
			cin >> key;
			a.put(key, 1, 2);
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