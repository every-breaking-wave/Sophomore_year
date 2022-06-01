#include <iostream>
#include <fstream>
#include <cstdio>
#include <random>
#include <string>
//#include <string.h>
#include <signal.h>
#include <windows.h>
#include "FixedSP.h"

using namespace std;

#define RED "\033[31m"
#define GREEN "\033[32m"
#define WHITE "\033[m"
#define TEMP_FILE "temp"
#define TEST_NUM 4

string grade_inputs[TEST_NUM] = {
        "fsp_input1",
        "fsp_input2",
        "fsp_input3",
        "fsp_input4"
};

string test_inputs[20] = {
        "input20",
        "input50",
        "input100",
        "input150",
        "input200",
        "input300",
        "input400"
};
string grade_outputs[TEST_NUM] = {
        "fsp_output1",
        "fsp_output2",
        "fsp_output3",
        "fsp_output4"
};
int grade_scores[TEST_NUM] = {
        25,
        25,
        25,
        25
};
string grade_tag[TEST_NUM] = {
        " TEST1:  ",
        " TEST2:  ",
        " TEST3:  ",
        " TEST4:  "
};

int grade;
int test_number = 0;
streambuf *backup;
fstream temp;
int threadNum[10] ={1,2,3,4,5,6,7,8};

void do_test(string input_file_path) {
    for (int i = 0; i < 8; ++i) {
        ifstream inputData;
        inputData.open(input_file_path, ios::in);
        if (!inputData) {
            cout << "[error]: file " << input_file_path << " not found." << endl;
            // inputData.close();
            return;
        }

        string str = "";
        inputData >> str;
        int node_num = atoi(str.c_str());

        vector<vector<int>> matrix(node_num, vector<int>(node_num));

        for (int i = 0; i < node_num; ++i) {
            for (int j = 0; j < node_num; ++j) {
                inputData >> str;
                if (str == "") {
                    return;
                }
                matrix[i][j] = str == "@" ? INF : atoi(str.c_str());
            }
        }

        FixedSP fsp(matrix);
        fsp.setThreadNum(threadNum[i]);

        double time;
        while (inputData >> str) {
            int source = atoi(str.c_str());
            vector<int> intermediates;
            while (true) {
                inputData >> str;
                if (str == "$") {
                    break;
                }
                intermediates.emplace_back(atoi(str.c_str()));
            }

            vector<int> path = fsp.getFixedPointShortestPath(source, intermediates);

            // matrix = fsp.matrix;
            int dis = 0;
            for (int i = 0; i < path.size(); ++i) {
                dis += matrix[path[i]][path[(i + 1) % path.size()]];
            }
            if (dis == 0) {
                dis = INF;
            }
        }
        inputData.close();
    }
}



int main(int argc, char *argv[]) {
    if (argc != 2 && argc != 3) {
        cout << "[usage]: ./main options [input_file_path]" << endl;
        return 0;
    }

    switch (*argv[1]) {
        case 'd':
            do_test(argv[2]);
            break;
    }

    return 0;
}

