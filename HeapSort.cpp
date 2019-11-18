// HeapSort.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include <vector>

using namespace std;

void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

void modifty(vector<int> &v,int root,int length) {
	int left = root * 2, right = root * 2 + 1, largest;
	if (left <= length && v[left] > v[root])
		largest = left;
	else {
		largest = root;
	}
	if (right <= length && v[right] > v[root]) {
		if (v[right] > v[left] || largest == root) {
			largest = right;
		}
	}
	if (largest != root) {
		swap(v[largest], v[root]);
		modifty(v, largest, length);
	}
}

void build(vector<int> &v) {
	//調整內容
	for (int i = v.size() / 2; i >= 1; i--) {
		modifty(v,i,v.size()-1);
	}
}

void heap(vector<int>& v) {
	v.insert(v.begin(), 0);
	build(v);
	v.erase(v.begin());
}

void pop(vector<int> &v,int n) {
	swap(v[0], v[n - 1]);
	v.erase(v.begin() + n-1);
	heap(v);
}

int main()
{
	int input=10,curr=1;
	string ins="";
	cin >> input;
	int* arr = new int[input];
	for (int i = 0; i < input; i++) {
		cin >> arr[i];
	}
	vector<int> v(arr, arr + input);
	heap(v);
	//for (int i = 0; i < input; i++) {
	//	cout << v[i] << " ";
	//}
	//cout << endl;
	while (cin >> ins) {
		if (ins == "show")
			cout << v[curr-1] << endl;
		else if (ins == "left") {
			curr *= 2;
			cout << v[curr-1] << endl;
		}
		else if (ins == "right") {
			curr = curr * 2 + 1;
			cout << v[curr - 1] << endl;
		}
		else if (ins == "heap") {
			pop(v,input);
			curr = 1;
			input--;
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
