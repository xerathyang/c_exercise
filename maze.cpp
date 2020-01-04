#include <iostream>
#include <string>
#include <vector>

using namespace std;

class maze {
private:
    vector<vector<int>> pathdir;
public:
    void output();
    void findpath(vector<vector<int>> board, int x, int y, vector<int> path);
    void reset() {
        pathdir.clear();
    }
};

void maze::output(){
    if (pathdir.size() == 0) {
        cout << "No path" << endl;
    }
    else {
        for (int i = 0; i < pathdir.size(); i++) {
            int x = 0, y = 0;
            cout << "(0,0)";
            for (int j=0; j < pathdir[i].size(); j++) {
                switch (pathdir[i][j]) {
                case 0:
                    x--;
                    break;
                case 1:
                    y--;
                    break;
                case 2:
                    y++;
                    break;
                case 3:
                    x++;
                    break;
                }
                cout << ",(" << x << "," << y << ")";
            }
            cout << endl;
        }
    }
}

void maze::findpath(vector<vector<int>> board, int x, int y, vector<int> path) {
    if (x == board.size() - 1 && y == board[0].size() - 1) {
        pathdir.push_back(path);
        return;
    }
    board[x][y] = 1;
    if (x != 0 && board[x - 1][y] == 0) {
        x--;
        path.push_back(0);
        findpath(board, x, y, path);
        path.pop_back();
        x++;
    }
    if (y != 0 && board[x][y - 1] == 0) {
        y--;
        path.push_back(1);
        findpath(board, x, y, path);
        path.pop_back();
        y++;
    }
    if (y != board[x].size() - 1 && board[x][y + 1] == 0) {
        y++;
        path.push_back(2);
        findpath(board, x, y, path);
        path.pop_back();
        y--;
    }
    if (x != board.size() - 1 && board[x + 1][y] == 0) {
        x++;
        path.push_back(3);
        findpath(board, x, y, path);
        path.pop_back();
        x--;
    }
}

int main()
{
    maze man = maze();

    int m, n;
    while (cin >> m) {
        cin >> n;
        vector<vector<int>> board;
        for (int i = 0; i < m; i++) {
            board.push_back(vector<int>());
            string tmp;
            cin >> tmp;
            for (int j = 0; j < n; j++) {
                board[i].push_back(tmp[j] - '0');
            }
        }
        man.reset();

        vector<int> path;
        board[0][0] = 1;
        man.findpath(board, 0, 0, path);

        man.output();
    }
}


