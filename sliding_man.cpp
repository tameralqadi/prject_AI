
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

const int N = 5;
const int ACTIONS = 4;
const double gamma_ = 0.8;
const int episodes = 10000;
const int max_steps = 100;

int grid[N][N] = {
    {3, 0, 0, 0, 0},
    {0, 2, 0, 2, 0},
    {0, 0, 0, 0, 0},
    {0, 2, 0, 2, 0},
    {0, 0, 0, 0, 1}
};

double Q[N][N][ACTIONS] = {};
int R[N][N][ACTIONS];

int actions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
string action_names[4] = { "up", "down", "left", "right" };

bool is_valid(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < N;
}

void initialize_rewards() {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            for (int a = 0; a < ACTIONS; ++a) {
                int glide = 1;
                int ni = i + glide * actions[a][0];
                int nj = j + glide * actions[a][1];
                if (!is_valid(ni, nj))
                    R[i][j][a] = -100;
                else if (grid[ni][nj] == 2)
                    R[i][j][a] = -100;
                else if (grid[ni][nj] == 3)
                    R[i][j][a] = 100;
                else
                    R[i][j][a] = -1;
            }
}

void train_q_learning() {
    srand(time(0));
    for (int ep = 0; ep < episodes; ++ep) {
        int x = -1, y = -1;

        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                if (grid[i][j] == 1) {
                    x = i;
                    y = j;
                    break;
                }

        for (int step = 0; step < max_steps; ++step) {
            int action = rand() % 4;
            int glide = (rand() % 100 < 50) ? 1 : 2;

            int nx = x + glide * actions[action][0];
            int ny = y + glide * actions[action][1];

            if (!is_valid(nx, ny)) continue;


            double maxQ = Q[nx][ny][0];
            for (int a = 1; a < ACTIONS; ++a)
                if (Q[nx][ny][a] > maxQ)
                    maxQ = Q[nx][ny][a];

            Q[x][y][action] = R[x][y][action] + gamma_ * maxQ;

            if (grid[nx][ny] == 3 || grid[nx][ny] == 2) break;

            x = nx;
            y = ny;
        }
    }
}

void print_grid() {
    cout << "Grid:\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            cout << setw(2) << grid[i][j] << " ";
        cout << "\n";
    }
}

void find_best_path() {
    cout << "Path with actions:\n";
    int x = -1, y = -1;


    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (grid[i][j] == 1) {
                x = i;
                y = j;
                break;
            }

    for (int step = 0; step < max_steps; ++step) {
        int best_action = 0;
        double best_value = Q[x][y][0];
        for (int a = 1; a < ACTIONS; ++a)
            if (Q[x][y][a] > best_value) {
                best_value = Q[x][y][a];
                best_action = a;
            }

        int glide = 1;
        int nx = x + glide * actions[best_action][0];
        int ny = y + glide * actions[best_action][1];

        if (!is_valid(nx, ny)) break;

        cout << "-> " << action_names[best_action] << " ";

        if (grid[nx][ny] == 3) {
            cout << " [GOAL]\n";
            return;
        }
        else if (grid[nx][ny] == 2) {
            cout << " [MONSTER]\n";
            return;
        }

        x = nx;
        y = ny;
    }


    cout << "\nThe goal was not reached within the maximum steps (" << max_steps << ").\n";
}

int main() {
    initialize_rewards();
    train_q_learning();
    print_grid();
    find_best_path();
    return 0;
}
