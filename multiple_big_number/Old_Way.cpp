#include <iostream>
#include <windows.h>
#include <string>
#include <thread>

using namespace std;

BOOL QueryPerformanceFrequency(LARGE_INTEGER *lpFrequency);
BOOL QueryPerformanceCounter(LARGE_INTEGER *lpPerformanceCount);

string add(string left, string right) {
    int length;
    int carry = 0;
    int sum;
    string result;

    if(left.size()>right.size())
        length = left.size();
    else
        length = right.size();

    while (left.size() < length)
      left.insert(0,"0");

    while (right.size() < length)
      right.insert(0,"0");

    for (int i = length-1; i >= 0; i--) {
      sum = (left[i]-'0') + (right[i]-'0') + carry;
      carry = sum/10;
      result.insert(0,to_string(sum % 10));
    }

    if (carry)
      result.insert(0,to_string(carry));

    return result.erase(0, min(result.find_first_not_of('0'), result.size()-1));
}


string multiply(string left, string right) {
    int length;
    if(left.size()>right.size())
        length = left.size();
    else
        length = right.size();

    while (left.size() < length)
      left.insert(0,"0");

    while (right.size() < length)
      right.insert(0,"0");

    if (length == 1)
        return to_string((left[0]-'0')*(right[0]-'0'));

    string left0 = left.substr(0,length/2);
    string left1 = left.substr(length/2,length-length/2);
    string right0 = right.substr(0,length/2);
    string right1 = right.substr(length/2,length-length/2);

    string p0 = multiply(left0,right0);
    string p1 = multiply(left0,right1);
    string p2 = multiply(right0,left1);
    string p3 = multiply(left1,right1);


    for (int i = 0; i < 2*(length-length/2); i++)
        p0.append("0");

    for (int i = 0; i < length-length/2; i++){
        p1.append("0");
        p2.append("0");
    }
    string result = add(add(add(p0,p1),p2),p3);

    return result.erase(0, min(result.find_first_not_of('0'), result.size()-1));
}

int main() {
    long long total=0;
    string str1, str2;
    cin >> str1 >> str2;
    for(int i=0;i<2000;i++) {
        LARGE_INTEGER time_start;
        LARGE_INTEGER time_over;
        LARGE_INTEGER f;
        QueryPerformanceFrequency(&f);
        QueryPerformanceCounter(&time_start);

        multiply(str1,str2);

        QueryPerformanceCounter(&time_over);
        long long timeOfSecond = (double)(time_over.QuadPart - time_start.QuadPart) / (double)f.QuadPart;

        long long timeOfNanoSecond = (double)(time_over.QuadPart - time_start.QuadPart) * 1e9 / (double)f.QuadPart;
        total += timeOfNanoSecond;
    }

    cout<<multiply(str1,str2)<<endl<<total/2000<<" ns"<<endl;

    return 0;
}
