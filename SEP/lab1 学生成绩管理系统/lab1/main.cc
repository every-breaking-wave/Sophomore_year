#include <vector>
#include <iostream>
#include <fstream>
#include "Class.h"
#include "Student.h"
#include <string>
#include<iomanip>
#include <stdio.h>
using namespace std;

class AppX {
private:
    vector<Student *> studentVec;
    vector<Class *> classVec;
    void loadFiles();
    void inputScore();
    void printAvgScore();
    void printGpa();

public:
    AppX();
    ~AppX();

    int run();
};

AppX::~AppX()
{
    // You can use the traditional loop, which is more clear.
    for (vector<Class *>::iterator it = classVec.begin();
         it != classVec.end();
         ++it) {
        if (*it) delete (*it);
    }
    // You can use modern and simpler loops only if you know what it is doing.
    for (const auto &s: studentVec) {
        if (s) delete (s);
    }
}

AppX::AppX()
{
    loadFiles();

}

void AppX::loadFiles()
{
    string line;
    size_t pos1, pos2;
    vector<string> bufv;
    Student *st = nullptr;
    string clsname;
    int point;
    Class *cl = nullptr;

    // Open a file as a input stream.
    ifstream stfile("./Students.txt");

    while (getline(stfile, line)) {

        if (line.empty()) // It's an empty line.
            continue;
        if (line[0] == '#') // It's a comment line.
            continue;

        // The bufv vector stores each columnes in the line.
        bufv.clear();
        // Split the line into columes.
        //   pos1: begining the the column.
        //   pos2: end of the column.
        pos1 = 0;
        while (true) {
            pos2 = line.find(';', pos1 + 1);
            if (pos2 == string::npos) { // No more columns.
                // Save the last column (pos1 ~ eol).
                bufv.push_back(line.substr(pos1, string::npos));
                break;
            } else {
                // Save the column (pos1 ~ pos2).
                bufv.push_back(line.substr(pos1, pos2 - pos1));
            }
            pos1 = pos2 + 1;
        }

        // TODO: uncomment next lines after implementing class Undergraduate
        // and Graduate.

        if (bufv[3] == "U")
            st = new Undergraduate(bufv[0], bufv[1], bufv[2]);
        else
            st = new Graduate(bufv[0], bufv[1], bufv[2]);


        studentVec.push_back(st);



    }
    stfile.close();

    // TODO: load data from ./Classes.txt and push objects to the vector.
    // Hint: how is student information read?
     ifstream stfile1("./Classes.txt");

     while (getline(stfile1, line)) {
         if (line.empty()) // It's an empty line.
                    continue;
          if (line[0] == '#') // It's a comment line.
                    continue;
         if(line[0]=='C')
         {      pos1=6;
                pos2=line.find(' ',pos1+1);
                 string str=line.substr(pos1,pos2-pos1);

                getline(stfile1,line);
                pos1=7;
                pos2=line.find(' ',pos1+1);
                string strnum=line.substr(pos1,pos2-pos1);
                point=atoi(strnum.c_str());
                cl=new Class(str,point);
                classVec.push_back(cl);//class添加成功
                while(getline(stfile1,line))
                {
                    if(line.empty()){
                        break;
                    }
                    pos1=0;
                    pos2=10;
                    string id=line.substr(pos1,pos2-pos1);
//

                   for(vector<Student *>::iterator it=studentVec.begin();it!=studentVec.end();it++)
                         {
                             if((*it)->id==id)
                             {
                                classVec.back()->addStudent(*(*it));
                                (*it)->addClass(classVec.back());

                             }
                          }


         }


     }}
     stfile1.close();



}

void AppX::inputScore()
{
    // TODO: implement inputScore.
    // Hint: Take a look at printAvgScore().
       Class *cl;
     //  StudentWrapper *Sw;
       double score;
       string sbuf;
       while (true) {
           cout << "Please input the class name (or input q to quit): ";//需要用户输入的有class，id，score
            cin>>sbuf;
            if (sbuf == "q")
                break;
            cl = nullptr;
            for (vector<Class *>::iterator it = classVec.begin();
                 it != classVec.end();
                 ++it) {
                if ((*it)->name == sbuf) {
                    cl = *it;
                    break;
                }
            }
            if (cl == nullptr) {
                cout << "No match class!" << endl;
                continue;
            }
            while(true){ cout << "Please input the id (or input q to quit): ";
             string putId;
             cin>>putId;
             if(putId=="q") break;
             try {
                  StudentWrapper &s = cl->getStudentWrapper(putId);
             } catch (const char * str) {
                 cout<<str<<endl;
                 continue;
             }
            cout<<cl->getStudentWrapper(putId).toString();

              //这里要加一个判断，如果没有找到是否重新输入

            cout<<"Please input the score: ";
            cin>>score;


            try {
                 cl->getStudentWrapper(putId).setScore(score);

            } catch (const char* str1) {
                cout<<str1<<endl;
                continue;
            }
            continue;




            }
       }
}

void AppX::printAvgScore()
{
    string sbuf;
    Class *cl;
    double avg;

    while (true) {
        cout << "Please input the class name (or input q to quit): ";
        cin >> sbuf;
        if (sbuf == "q")
            break;

        cl = nullptr;
        for (vector<Class *>::iterator it = classVec.begin();
             it != classVec.end();
             ++it) {
            if ((*it)->name == sbuf) {
                cl = *it;
                break;
            }
        }
        if (cl == nullptr) {
            cout << "No match class!" << endl;
            continue;
        }

        avg = cl->getAvgScore();
        cout << "The average score is: ";
        cout<<setiosflags(ios::fixed);//设置输入浮点形式
            cout.precision(2);   //设置两位有效数字
            cout << avg << endl; //输出并换行
    }
}

void AppX::printGpa()
{
    // TODO: implement printGpa.
    // Hint: Take a look at printAvgScore().
    string id;
    while(true)
    {cout<< "Please input the student id (or input q to quit): ";
    cin>>id;
    if(id=="q")
    {
        break;
    }
    bool flag=false;
    for(vector<Student *>::iterator it=studentVec.begin();it!=studentVec.end();it++)
    {
        if((*it)->id==id)
        {
          double GPA=(*it)->getGrade();
          cout << (*it)->toString();

                 printf("GPA = %.2f\n", GPA);
            flag=true;

            break;

        }
        //异常处理：错误id

    }
        if(!flag)
        {
            cout << "No match student!" << endl;
                       continue;
        }
    }
}

int AppX::run()
{
    char cmd;
    while (true) {
        cout << "Command menu:\n"
            << "\ti: Input score\n"
            << "\ta: Compute average score of a class\n"
            << "\tg: Compute grade of a student\n"
            << "\tq: Quit\n"
            << "Please input the command: ";
        cin >> cmd;
        if (cmd == 'i') {
            inputScore();
        } else if (cmd == 'a') {
            printAvgScore();
        } else if (cmd == 'g') {
            printGpa();
        } else if (cmd == 'q') {
            break;
        } else {
            cout << "Invalid command!\n" << endl;
        }
    }
    return 0;
}

int main()
{
    AppX app;
    return app.run();
}
