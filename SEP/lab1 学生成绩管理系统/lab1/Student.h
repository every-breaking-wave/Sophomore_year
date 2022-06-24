#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>
#include <vector>
#include<cstdio>
using namespace std;

class Class;

enum Degree {
    undergraduate,
    graduate
};

class Student {
    // TODO: implement class Student.
private:


protected:
    const std::string name;
    const std::string year;
    Degree degree;

    vector<Class*> classes;
public:
    const std::string id;
   // Student(std::string &id,std::string &name,std::string &year):id(id),name(name),year(year)
    //{}
    std::string toString() const;
    Student(const std::string id, const std::string name, const std::string year):name(name), year(year), id(id){}

   virtual double getGrade()=0;
    void addClass (Class *c);



};

// TODO: implement class Graduate.
class Graduate:public Student{
private:

protected:
public:

    Graduate(const std::string id, const std::string name, const std::string year):Student(id, name, year){
           this->degree = graduate;
       }
    double getGrade() override ;
};

// TODO: implement class Undergraduate.
class Undergraduate:public Student{
private:
protected:
public:
    Undergraduate(const std::string id, const std::string name, const std::string year):Student(id, name, year){
           this->degree = undergraduate;
       }
    double getGrade() override;

};
class StudentWrapper {
private:
    const Student &student;
    double score = 0.0;

public:
    const std::string id;
    // TODO: fix error
  /*  StudentWrapper(const std::string &id, const Student &student) {
        this->id = id;
        this->student = student;
    }*/
    StudentWrapper(const std::string &id, const Student &student):student(student),id(id) {

       }

    void setScore(double score)
    {
        if (score < 0 || score > 100)
            throw "Wrong score!";
        this->score = score;
    }

    double getScore() const
    {
        return this->score;
    }

    std::string toString() const
    {
        return student.toString();
    }
};

#endif // STUDENT_H_
