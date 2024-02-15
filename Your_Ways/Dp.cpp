#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <thread>

using namespace std;

class Coordinate{
public:
    long long x, y;
    Coordinate();
    Coordinate(long long x, long long y);
    bool isBigger(Coordinate other);
    bool isBiggerAndEquals(Coordinate other);
};

Coordinate::Coordinate(){
}

Coordinate::Coordinate(long long x, long long y){
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

class Obstacle{
public:
    Coordinate s, t;
};

long long partition(vector<Obstacle> *obstacles, long long low, long long high);
void recursiveQuickSort(vector<Obstacle> *obstacles, long long low, long long high);
void quickSort(vector<Obstacle> *obstacles);
vector<Obstacle> getSubA(Obstacle A, vector<Obstacle> *obstacleList);
long long dp(Coordinate target, vector<Obstacle> *obstacleList, long long r);
bool hasObstacle(vector<Obstacle> *obstacles, long long x1, long long y1, long long x2, long long y2);
void dpAlg(long long w, long long h);

BOOL QueryPerformanceFrequency(LARGE_INTEGER *lpFrequency);
BOOL QueryPerformanceCounter(LARGE_INTEGER *lpPerformanceCount);
long long **graph = new long long*[1000];

int main(){
    long long w, h, k;
    cin >> w >> h >> k;
    long long n;
    long long totalOfDp = 0;
    vector<Obstacle> obstacleList;
    vector<Obstacle> obstacles;
    /*LARGE_INTEGER time_start;
    LARGE_INTEGER time_over;
    LARGE_INTEGER f;
    QueryPerformanceFrequency(&f);
    QueryPerformanceCounter(&time_start);*/
    dpAlg(w+1, h+1);
    /*QueryPerformanceCounter(&time_over);
    /*long long timeOfNanoSecond = (double)(time_over.QuadPart - time_start.QuadPart) * 1e9 / (double)f.QuadPart;
    totalOfDp += timeOfNanoSecond;*/
    for (long long i = 0;i<k;i++){
        cin >> n;
        for (long long j = 0;j<n;j++){
            Obstacle obstacle;
            cin >> obstacle.s.x
                >> obstacle.s.y
                >> obstacle.t.x
                >> obstacle.t.y;
            obstacleList.push_back(obstacle);
        }
        /*QueryPerformanceFrequency(&f);
        QueryPerformanceCounter(&time_start);*/

        quickSort(&obstacleList);
        Coordinate temp(w, h);
        long long p1 = graph[w][h];
        long long dp1 = dp(temp, &obstacleList, 2552);
        long long temp1 = p1 - dp1;
        //cout << "p1:"<< p1 << ' ' << "dp1:"<<dp1 << '\n';
        if (temp1 >= 2552)
            temp1 -= 2552;
        if (temp1 < 0)
            temp1 += 2552;
        //cout << p1 << ' ' << dp1 << ' ';
        cout << temp1 << '\n';
        /*QueryPerformanceCounter(&time_over);
        long long timeOfNanoSecond = (double)(time_over.QuadPart - time_start.QuadPart) * 1e9 / (double)f.QuadPart;
        totalOfDp += timeOfNanoSecond;*/
        obstacleList.clear();
    }

    /*cout<<"dp execution time : "<<totalOfDp<<'\n';*/
    return 0;
}

long long partition(vector<Obstacle> *obstacles, long long low, long long high){
    Obstacle target = obstacles->at(low);
    long long down = low;
    long long up = high;
    Obstacle temp;
    while (down < up){
        while (!(obstacles->at(down).t.isBigger(target.s))
          && down < high){
            down++;
        }
        while (obstacles->at(up).t.isBigger(target.s)){
            up--;
        }
        if (down < up){
            temp = obstacles->at(down);
            obstacles->at(down) = obstacles->at(up);
            obstacles->at(up) = temp;
        }
    }
    obstacles->at(low) = obstacles->at(up);
    obstacles->at(up) = target;
    return up;
}

void recursiveQuickSort(vector<Obstacle> *obstacles, long long low, long long high){
    if (low >= high){
        return;
    }
    long long j = partition(obstacles, low, high);
    recursiveQuickSort(obstacles, low, j-1);
    recursiveQuickSort(obstacles, j+1, high);
}

void quickSort(vector<Obstacle> *obstacles){
    return recursiveQuickSort(obstacles, 0, obstacles->size()-1);
}

vector<Obstacle> getSubA(Obstacle A, vector<Obstacle> *obstacleList){
    vector<Obstacle> result;
    for (long long i = 0;i<obstacleList->size();i++){
        if (A.s.isBiggerAndEquals(obstacleList->at(i).t))
            result.push_back(obstacleList->at(i));
    }
    return result;
}

long long dp(Coordinate target, vector<Obstacle> *obstacleList, long long r){
    if (obstacleList->empty())
        return 0;
    Obstacle A = obstacleList->at(obstacleList->size()-1);
    obstacleList->pop_back();
    vector<Obstacle> subA = getSubA(A, obstacleList);

    return (dp(target, obstacleList, r) + ((graph[A.s.x][A.s.y]%r - dp(A.s, &subA, r)) * graph[target.x - A.t.x][target.y - A.t.y]%r) % r) % r;
}



void dpAlg(long long w, long long h){

    for (long long i = 0;i < w;i++){
        graph[i] = new long long[h];
    }
    long long defaultNum = 1;
    for (long long i = 0;i<w;i++){
        graph[i][0] = defaultNum;
    }
    defaultNum = 1;
    for (long long i = 0;i<h;i++){
        graph[0][i] = defaultNum;
    }
    long long sum = 0;
    for (long long i = 1;i<w;i++){
        for (long long j = 1;j<h;j++){
            sum = 0;
                sum += graph[i-1][j];
                sum += graph[i][j-1];
            if (sum >= 2552)
                sum -= 2552;
            graph[i][j] = sum;
        }
    }
    return;
}

