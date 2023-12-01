#include <iostream>
#include <vector>

using namespace std;

const int MAX = 1000;
int rows, cols;
int image[MAX][MAX];
bool visited[MAX][MAX];

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

void floodFill(int x, int y, int prevColor, int newColor) {
    if (x < 0 || x >= rows || y < 0 || y >= cols) return;
    if (visited[x][y] || image[x][y] != prevColor) return;

    visited[x][y] = true;
    image[x][y] = newColor;

    for (int i = 0; i < 4; i++) {
        floodFill(x + dx[i], y + dy[i], prevColor, newColor);
    }
}

int main() {
    cin >> rows >> cols;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            cin >> image[i][j];

    int x, y, newColor;
    cin >> x >> y >> newColor;

    int prevColor = image[x][y];
    floodFill(x, y, prevColor, newColor);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << image[i][j] << " ";
        }
        cout << std::endl;
    }

    return 0;
}

