#include "Class.h"
#include <string>
#include "Student.h"
using namespace std;
void Class::addStudent(const Student &st)
{
    StudentWrapper sw(st.id, st);
    students.push_back(sw);
}

StudentWrapper &Class::getStudentWrapper(const std::string &studentId)
{
    for (std::vector<StudentWrapper>::iterator it = students.begin();
         it != students.end();
         ++it) {
        if (it->id == studentId)
            return *it;
    }
    throw "No match student!";
}

double Class::getAvgScore()
{
    // TODO: implement getAvgScore.
    int num_student=0;
    double scores=0.0;
    for(vector<StudentWrapper>::iterator it=students.begin();it!=students.end();it++)
    {
        scores+=it->getScore();
        num_student++;
    }
    return scores/num_student;
}
