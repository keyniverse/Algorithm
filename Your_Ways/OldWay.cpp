#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <thread>

using namespace std;

class Coordinate{
public:
    int x, y;
    Coordinate();
    Coordinate(int x, int y);
    bool isBigger(Coordinate other);
    bool isBiggerAndEquals(Coordinate other);
};

Coordinate::Coordinate(){
}

Coordinate::Coordinate(int x, int y){
    this->x = x;
    this->y = y;
}

bool Coordinate::isBigger(Coordinate other){
    if (this->x > other.x &&
        this->y > other.y)
        return true;
    return false;
}

bool Coordinate::isBiggerAndEquals(Coordinate other){
    if (this->x >= other.x &&
        this->y >= other.y)
        return true;
    return false;
}

/*BOOL QueryPerformanceFrequency(LARGE_INTEGER *lpFrequency);
BOOL QueryPerformanceCounter(LARGE_INTEGER *lpPerformanceCount);*/

class Obstacle{
public:
    Coordinate s, t;
    void print();
};

void Obstacle::print(){
    cout << s.x << ' ' << s.y << ' ' << t.x << ' ' << t.y << '\n';
}

bool hasObstacle(vector<Obstacle> *obstacles, int x1, int y1, int x2, int y2);
int dpAlg(vector<Obstacle> *obstacles, int w, int h);

int main(){
    int w, h, k;
    cin >> w >> h >> k;
    int n;
    long long totalOfCombine = 0;
    vector<Obstacle> obstacles;
    for (int i = 0;i<k;i++){
        cin >> n;
        for (int j = 0;j<n;j++){
            Obstacle obstacle;
            cin >> obstacle.s.x
                >> obstacle.s.y
                >> obstacle.t.x
                >> obstacle.t.y;
            obstacles.push_back(obstacle);
        }
        /*
        LARGE_INTEGER time_start;
        LARGE_INTEGER time_over;
        LARGE_INTEGER f;
        QueryPerformanceFrequency(&f);
        QueryPerformanceCounter(&time_start);*/

        cout << dpAlg(&obstacles, w+1, h+1) << '\n';

        /*QueryPerformanceCounter(&time_over);
        long long timeOfNanoSecond = (double)(time_over.QuadPart - time_start.QuadPart) * 1e9 / (double)f.QuadPart;
        totalOfCombine+=timeOfNanoSecond;*/

        obstacles.clear();
    }
    /*cout<<"combine execution time : "<<totalOfCombine<<'\n';*/
    return 0;
}

int dpAlg(vector<Obstacle> *obstacles, int w, int h){
    int **dp = new int*[w];
    for (int i = 0;i < w;i++){
        dp[i] = new int[h];
    }
    int defaultNum = 1;
    for (int i = 1;i<w;i++){
        if (hasObstacle(obstacles, i-1, 0, i, 0))
            defaultNum = 0;
        dp[i][0] = defaultNum;
    }
    defaultNum = 1;
    for (int i = 1;i<h;i++){
        if (hasObstacle(obstacles, 0, i-1, 0, i))
            defaultNum = 0;
        dp[0][i] = defaultNum;
    }
    int sum = 0;
    for (int i = 1;i<w;i++){
        for (int j = 1;j<h;j++){
            sum = 0;
            if (!hasObstacle(obstacles, i-1, j, i, j))
                sum += dp[i-1][j];
            if (!hasObstacle(obstacles, i, j-1, i, j))
                sum += dp[i][j-1];
            if (sum >= 2552)
                sum -= 2552;
            dp[i][j] = sum;
        }
    }
    int output = dp[w-1][h-1];
    for (int i = 0;i<w;i++){
        delete [] dp[i];
    }
    delete [] dp;
    return output;
}

bool hasObstacle(vector<Obstacle> *obstacles, int x1, int y1, int x2, int y2){
    for (int i = 0;i<obstacles->size();i++){
        if (obstacles->at(i).s.x == x1 &&
            obstacles->at(i).s.y == y1 &&
            obstacles->at(i).t.x == x2 &&
            obstacles->at(i).t.y == y2){
            return true;
        }
    }
    return false;
}
