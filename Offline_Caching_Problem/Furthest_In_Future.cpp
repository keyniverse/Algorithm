#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>
#include <windows.h>
#include <thread>
#include <stdlib.h>
#include <time.h>
#include <string>

using namespace std;
#define furthest 10000000
/*BOOL QueryPerformanceFrequency(LARGE_INTEGER *lpFrequency);
BOOL QueryPerformanceCounter(LARGE_INTEGER *lpPerformanceCount);
*/
int main()
{
    string str = "";
    string input = "";
    long long x, k, n, tmp; ///k=cache size/ n = length of request sequence
    map<long long,long long> mymap; ///to make arr
    vector <long long> vec;

    map<long long,long long> m1;
    map<long long,map<long long,long long>> m2;
    map<long long,long long>::iterator iter;

    /*LARGE_INTEGER time_start;
    LARGE_INTEGER time_over;
    LARGE_INTEGER f;*/

    cin>>k>>n;
    unsigned seed;
    seed = (unsigned)(time(NULL));
    srand(seed);
    long long *arr = new long long[n];

    for(long long i = 0;i < n;i++){
        cin>>tmp;
        vec.push_back(tmp);
        input += to_string(tmp);
        input += " ";
    }

    /*QueryPerformanceFrequency(&f);
    QueryPerformanceCounter(&time_start);*/
    for(long long i = n-1;i >= 0;i--) {
        tmp = vec[i];
        iter = mymap.find(tmp);
        if (iter != mymap.end()) {
            arr[i] = mymap.find(tmp)->second;
            mymap.find(tmp)->second = i;
        }
        else {
            mymap[tmp] = i;
            arr[i] = furthest;
        }
    }

    for(long long i = 0;i < n;i++) {

        tmp =vec[i];
        if(m1.count(tmp)){          ///hit
            str += "hit \n";
            auto *m = &(m2.find(i)->second);
            long long s = (m->begin())->first;
            m2.erase(m2.find(m1.find(tmp)->second));
            m2.insert(make_pair(arr[i], map<long long, long long>()));
            m2[arr[i]].insert(make_pair(s,tmp));
            m1.erase(tmp);
            m1.insert(make_pair(tmp,arr[i]));
        }
        else if(m1.size() != k) {
            m1.insert(make_pair(tmp,arr[i]));
            if(m2.find(arr[i])->first) {
                m2[arr[i]].insert(make_pair(i,tmp));
            }
            else {
                map<long long, long long> m;
                m.insert(make_pair(i,tmp));
                m2.insert(make_pair(arr[i], m));
            }


            str += "miss \n";
        }
        else {
            long long t = ((prev(m2.end())->second).begin())->first;
            long long u = ((prev(m2.end())->second).begin())->second; ///numIncache
            auto iter = prev(m2.end());
            if ((prev(m2.end())->second).size() <= 1)
                m2.erase(iter);
            else
                (prev(m2.end())->second).erase(t);
            map<long long, long long> m;
            m.insert(make_pair(i,tmp));
            m2.insert(make_pair(arr[i], m));
            m1.erase(u);
            m1.insert(make_pair(tmp,arr[i]));
            str += "miss \n";
            str += "evict ";
            str += to_string(u);
            str += "\n";

        }
        ///print element of m2
        /*
        cout << "map2 start"<<co<<'\n';
        cout << "cache size : " << m2.size() << '\n';
        for (auto const &x : m2) {
            cout << x.first << '\n';
            auto *m1 = &(x.second);
            for (auto const &x1 : *m1){
                cout << x1.first << " " << x1.second << '\n';
            }
        }
        cout << "map2 end\n";
        co++;
        */

    }
    cout<<str;
    /*QueryPerformanceCounter(&time_over);
    long long timeOfNanoSecond = (double)(time_over.QuadPart - time_start.QuadPart) * 1e9 / (double)f.QuadPart;
    cout<<timeOfNanoSecond<<'\n';*/

    return 0;
}
