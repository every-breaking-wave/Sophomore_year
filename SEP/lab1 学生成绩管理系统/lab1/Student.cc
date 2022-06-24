#include "Student.h"
#include <string>
#include <sstream>
#include "Class.h"
#include<iostream>
using namespace std;
std::string Student::toString() const
{
    // TODO: uncomment the following code after implementing class Student.

    std::ostringstream oss;
    oss << "Student Information:"
        << "\n\tid: " << id
        << "\n\tname: " << name
        << "\n\tenrollment year: " << year
        << "\n\tdegree: " << (degree == graduate ? "graduate" : "undergraduate")
        << std::endl;
    return oss.str();

    return "";
}

// TODO: implement functions which are declared in Student.h.
void Student::addClass (Class* c)
{

   classes.push_back(c);
}
double into_GPA(double score)
{   int x=score/10;
    switch (x)
    {   case 10:return 4.0;break;
        case 9:return 4.0;break;
        case 8:return 3.5;break;
        case 7:return 3.0;break;
        case 6:return 2.5;break;
    default:return 2.0;
    }
}
double Graduate::getGrade() //getGPA
{
    double GPA;

    double scores=0.0;
    int total_point=0;
    for (std::vector<Class *>::iterator it = classes.begin();
             it != classes.end();it ++)
    {
        scores+=into_GPA((*it)->getStudentWrapper(this->id).getScore())*((*it)->point);
        total_point+=(*it)->point;
    }
    GPA=scores/total_point;
    return GPA;
}

double Undergraduate::getGrade()
{
    double GPA;
    double scores=0.0;
    int  totalpoint=0;

    for (std::vector<Class *>::iterator it = classes.begin();
             it != classes.end();it ++)
    {
        scores+=((*it)->getStudentWrapper(this->id).getScore())*((*it)->point)/20;

       totalpoint+=(*it)->point;


    }
    GPA=scores/totalpoint;

    return GPA;
}
