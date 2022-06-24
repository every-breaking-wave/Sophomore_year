#ifndef EXP_H
#define EXP_H
#include <iostream>
#include <string>
#include <map>
#include <errno.h>
#include <QErrorMessage>
#include <evastate.h>
#include <QtDebug>
#include <QDebug>
#include <qtextbrowser.h>
#include "error.h"
#include "stack"



#define NUM 50
using namespace std;

enum ExpressionType { CONSTANT, IDENTIFIER, COMPOUND };

class EvaluationContext {  // 对exp进行操作

public:
    evaState * eva;
    EvaluationContext();
    void setValue(std::string var, int value);
    int getValue(std::string var);
    bool isDefined(std::string var);
    void clearTable();

private:

    map<std::string,int> symbolTable;

};


class Expression {

public:
    ExpressionType expType;
    Expression();
    Expression(ExpressionType type, string op, int value,string name, Expression * lhs = NULL, Expression *rhs = NULL);
     ~Expression();
    int eval(EvaluationContext & context) ;
    std::string toString(){}
     int type();

    /* Getter methods for convenience */

    int getConstantValue();
     std::string getIdentifierName();
     string getOperator();
     Expression *getLHS() ;
     Expression *getRHS() ;

    Expression *lhs, *rhs;
    string op;
    int value;
    string cmpOp = "";
    std::string name;

};



class parse  // 一个parse 存了一条命令
{
public:
   // vector<Expression > exps;
    parse();
    parse(int line, string statement,parse * next);
    std::string cmdState;  //  命令的类别
    int line;      //行号
    int line_of_if;
    Expression * exps[NUM];
    Expression * expTree();
    void  getToken(string &str);
    int size = 0;
    void showTree(QTextBrowser *);
    parse * next;
    Expression * root;  // 根节点，一般存放的是优先级度最低的符号
    string cmd;
    string cmd_without_pre;
    void cal();     // 对当前的栈执行一次运算
    bool legal = true;


    stack<Expression*> Operator;
    stack<Expression*> Operands;
     //cmpTree()

};



#endif // EXP_H
