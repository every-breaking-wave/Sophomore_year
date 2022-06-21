#include <iostream>
#include <cstring>
#include <vector>
#include <Windows.h>
#include <ctime>
#include <cstdlib>

using namespace std;

int match(const char *s, const char *p) {
    int sLen = strlen(s);
    int pLen = strlen(p);
    int i = 0;
    int j = 0;
    while (i < sLen && j < pLen) {
        if (s[i] == p[j]) {
            i++;
            j++;
        } else {
            i = i - j + 1;
            j = 0;
        }
    }
    if (j == pLen)
        return (i - j);
    else
        return -1;
}

int kmp(const char *s, const char *p, int *next) {
    int i = 0;
    int j = 0;
    int sLen = strlen(s);
    int pLen = strlen(p);
    while (i < sLen && j < pLen) {
        if (j == -1 || s[i] == p[j]) {
            i++;
            j++;
        } else {
            j = next[j];
        }
    }
    if (j == pLen)
        return i - j;
    else
        return -1;
}

int *next(const char *p) {
    int pLen = strlen(p);
    int *next = new int[pLen];
    next[0] = -1;
    int k = -1;
    int j = 0;
    while (j < pLen - 1) {
        if (k == -1 || p[j] == p[k]) {
            ++j;
            ++k;
            if (p[j] != p[k])
                next[j] = k;
            else
                next[j] = next[k];
        } else {
            k = next[k];
        }
    }
    return next;
}

string generateRandstr(const int len) {
    string str;
    char c;
    int idx;
    for (idx = 0; idx < len; idx++) {
        c = 'a' + rand() % 26;
        str.push_back(c);
    }
    return str;
}


const int plen[3] = {100, 200, 500};
const int tlen[4] = {100000, 1000000, 10000000, 100000000};

int main() {
    srand(time(nullptr));
    vector<string> p_Strings;
    vector<string> s_Strings;
    for (int i: plen) {
        p_Strings.emplace_back(generateRandstr(i));
    }
    for (int i: tlen) {
        s_Strings.emplace_back(generateRandstr(i));
    }
    LARGE_INTEGER tc;
    LARGE_INTEGER t1;
    LARGE_INTEGER t2;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            double deltime;
            const char *s = s_Strings[i].data();
            const char *p = p_Strings[j].data();
            QueryPerformanceFrequency(&tc);
            QueryPerformanceCounter(&t1);        //开始计时
            match(s, p);
            QueryPerformanceCounter(&t2);        //停止计时
            deltime = (double) (t2.QuadPart - t1.QuadPart) / (double) tc.QuadPart;
            cout << "simple:  t: " << s_Strings[i].length() << "p: = " << p_Strings[j].length() << "time = "
                 << deltime * 1000 << "ms" << '\n';
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            double deltime;
            const char *s = s_Strings[i].data();
            const char *p = p_Strings[j].data();
            QueryPerformanceCounter(&t1);        //开始计时
            kmp(s, p, next(p));
            QueryPerformanceCounter(&t2);        //停止计时
            deltime = (double) (t2.QuadPart - t1.QuadPart) / (double) tc.QuadPart;
            cout << "kmp:  t: = " << s_Strings[i].length() << "p: = " << p_Strings[j].length() << "time = "
                 << deltime * 1000 << "ms" << '\n';
        }
    }
}

