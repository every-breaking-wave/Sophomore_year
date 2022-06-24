#ifndef CODE_H
#define CODE_H
#include "exp.h"
#include <QTextBrowser>
#include "evastate.h"
class EvaluationContext;
class parse;
class evaState;
class code  // 代码类
{
public:
    code();
  //  vector<parse> expVec;
    void insert(parse *par);
    struct codeNode{   // 代码节点，每个node为一句cmd
         codeNode(parse* par, string str, codeNode * next = NULL)
         {node = par; this->next = next; cmd = ""; this->cmd = str;}
         parse * node;
         codeNode * next;
         string cmd;
    };
    EvaluationContext context;
     codeNode *head;   // 第一句代码
     int num_of_cmd;
     QTextBrowser* syntax_display, *result_display;
     evaState * eva;   // 存放变量的state
     void parseState(codeNode * curCode);
     void clearCode();
     void runCode(QTextBrowser * treeBrowser, QTextBrowser * resultBrowser);
     void setBrowser(QTextBrowser *);
     codeNode * getCode(int id);  // 获得第 id 条代码节点的地址（含0）
     void delCode(int line);      //删除制定行的代码
     void handleREM(codeNode * cur);
     void handleLET(codeNode * cur);
     void handlePRINT(codeNode * cur);
     void handleEND(codeNode * cur);
     void handleINPUT(codeNode * cur);
     void handleGOTO(codeNode *cur);
     void handleIF(codeNode *cur);
};

#endif // CODE_H
