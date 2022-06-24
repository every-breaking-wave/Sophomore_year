#include "exp.h"
#include <queue>
#include <qdebug.h>
#include<stack>
#include <cmath>



EvaluationContext::EvaluationContext()
{
    eva = new evaState;
}

void EvaluationContext::setValue(string var, int value)
{
    if(!isDefined(var))   // 如果变量没被定义
    {
        int size = symbolTable.size();
        this->symbolTable.insert(pair<string,int>(var,size));
    }
    eva->var[symbolTable[var]] = value;  // 对变量赋值
}

int EvaluationContext::getValue(string var)
{
    if(!this->isDefined(var))
    {error("var is not defined!");}  //变量未定义
    else return  eva->var[symbolTable[var]];
}

bool EvaluationContext::isDefined(string var)
{
    //  return eva->isDefined(symbolTable[var]);
    return  symbolTable.count(var);
}

void EvaluationContext::clearTable()
{
    this->symbolTable.clear();
}

Expression::Expression()
{
    this->lhs = NULL;
    this->rhs = NULL;
    this->value = 0;
    this->name = "";
}

Expression::Expression(ExpressionType type,string op, int value, string name, Expression * lhs , Expression *rhs)
{
    this->expType = type;
    this->lhs = lhs;
    this->rhs = rhs;
    this->value = value;
    this->name = name;
    this->op = op;
}
Expression::~Expression()
{

}

int Expression::eval(EvaluationContext &context)
{
    if(this == NULL) error("Illegal expression!");
    if(this->expType == COMPOUND)
    {int right = rhs->eval(context);
    if (op == "=") {
        context.setValue(lhs->name, right);
        return right;
    }
    int left = lhs->eval(context);
    if (op == "+") return left + right;
    if (op == "-") return left - right;
    if (op == "*") return left * right;
    if (op == "/") {
    if (right == 0) {
        error("Division by 0"); return 0;
    }
        return left / right;
    }
    if(op == "**"){
        return pow(left,right);
    }
    error("Illegal operator in expression");
    return 0;
    }

    else if(expType == CONSTANT)  return this->value;
    else if(expType == IDENTIFIER){
        if(!context.isDefined(name)){
            error("variable has not been defined");
            return  0 ;}
        return context.getValue(name);
    }

    return 0;
}

int Expression::type()
{

}

int Expression::getConstantValue()
{
    return  value;
}

string Expression::getIdentifierName()
{
    return  name;
}

string Expression::getOperator()
{
    return  op;
}

Expression *Expression::getLHS()
{
    return  lhs;
}

Expression *Expression::getRHS()
{
    return rhs;
}

parse::parse()
{

    for(int i = 0; i < NUM; i++){
        exps[i] = new Expression;
        exps[i]->lhs = NULL;
        exps[i]->rhs = NULL;
        exps[i]->op = '\0';
        exps[i]->name = "";
        exps[i]->value = 0;
    }
    root = new Expression;
    root = NULL;
    cmd = "";
}

parse::parse(int line, string statement, parse *next)
{

    this->line = line;
    this->cmdState = statement;
    this->next = next;
    cmd = "";
}


Expression * parse::expTree()
{
    if(legal == false) return root;


    for(int i = 0; i < this->size; i++){
        switch (exps[i]->expType) {
        case CONSTANT:case IDENTIFIER:
        {
            Operands.push(exps[i]);
            break;
        }
        case COMPOUND:
        {   //没考虑比较符
            if(exps[i]->op == "(") {Operator.push(exps[i]); continue;}
            if(cmdState != "IF" && (exps[i]->op == ">" || exps[i]->op == "<") ){
                legal = false;
                return root;
            }
            while(cmdState == "IF" && (exps[i]->op == ">" || exps[i]->op == "<")){
                if(Operator.size()!=0) cal();
                else {break;}
                if(!legal) return root;
            }
            while ((exps[i]->op == "+" ||exps[i]->op == "-") &&(Operator.size() != 0) && (Operator.top()->op != "=" && Operator.top()->op != "("  ) ){
                cal();
                if(!legal) return root;
            }
            while ((exps[i]->op == "*" ||exps[i]->op == "/") && (Operator.size() != 0) && (Operator.top()->op == "*" || Operator.top()->op == "/"
                   || (Operator.top()->op == "**") )) {
                cal();
                if(!legal) return root;
            }
            while (exps[i]->op == "**" &&  Operator.top()->op == "**" ) {
                cal();
                if(!legal) return root;
            }
            if(exps[i]->op == ")"){
                while(!Operator.empty()){
                    if(Operator.top()->op != "("){
                        if(!legal) return root;
                        if(Operator.size() == 1) {
                            legal = false;
                            return root;
                        }
                        cal();
                        if(!legal) return root;
                    }
                    else{
                        Operator.pop();
                        break;
                    }
                }
                continue;
            }
             Operator.push(exps[i]);
        }

        }
    }
    while(!Operator.empty())
    {
        cal();
        if(!legal) return root;
    }
    if(cmdState == "END" || cmdState == "REM"){
        return  NULL;
    }
     this->root = Operands.top();
    if(cmdState !="IF" && root->op == "=" && root->lhs->expType != IDENTIFIER){   // 如果在非if里出现了对const 赋值
        legal = false;
    }
     return root;

//    Expression * tmproot = NULL;
//    Expression * p;

//    while (i < size) {
//        switch (exps[i]->expType) {
//        case CONSTANT:
//            p = new Expression();
//            p->expType = CONSTANT;
//            p->value = exps[i]->value;
//            if(tmproot != NULL){
//                if(tmproot->rhs != NULL && tmproot->rhs->rhs!=NULL){
//                    tmproot->rhs->rhs->rhs = p;
//                    break;
//                }
//                if(tmproot->rhs != NULL){
//                    tmproot->rhs->rhs = p;
//                }
//                else tmproot->rhs = p;
//            }
//            else if (tmproot == NULL){
//                tmproot = p;
//            }

//            break;
//        case IDENTIFIER:
//            p =  new Expression();
//            p->expType = IDENTIFIER;
//            p->name = exps[i]->name;
//            if(tmproot != NULL){
//                if(tmproot->rhs != NULL && tmproot->rhs->rhs!=NULL){
//                    tmproot->rhs->rhs->rhs = p;
//                    break;
//                }
//                if(tmproot->rhs != NULL){
//                    tmproot->rhs->rhs = p;
//                }
//                else tmproot->rhs = p;
//            }
//            break;

//        case COMPOUND:
//            if(exps[i]->op == "("){
//                p = expTree(i + 1);  // 形成一个括号内的子树
//                if(tmproot != NULL){
//                    if(tmproot->rhs != NULL) tmproot->rhs->rhs = p;
//                    else tmproot->rhs = p;
//                }
//                else tmproot = p;
//                for(; i < size; i++){
//                    if(exps[i]->op == ")"){
//                        i = i + 1;
//                        break;
//                }
//                }
//                break;
//            }
//            if(exps[i]->op == ")") return tmproot;   //返回括号内的expression
//            if(exps[i]->op == "=" || exps[i]->op==">" || exps[i]->op=="<"){ // 最低优先级（一定为root）
//                if(tmproot == NULL){
//                    tmproot = new Expression(COMPOUND,exps[i]->op,0,"",p,NULL);
//                    tmproot->cmpOp = exps[i]->cmpOp;
//                }
//                else {
//                    tmproot = new Expression(COMPOUND,exps[i]->op,0,"",tmproot,NULL);
//                }
//                break;
//            }
//            if(exps[i]->op == "+" || exps[i]->op == "-"){
//                if(tmproot == NULL){
//                    tmproot = new Expression(COMPOUND,exps[i]->op,0,"",p,NULL);
//                }
//                else if(tmproot->op == "=" || tmproot->op==">" || tmproot->op=="<")
//                {tmproot->rhs = new Expression(COMPOUND,exps[i]->op,0,"",tmproot->rhs,NULL);}
//                else {
//                    tmproot =new Expression(COMPOUND,exps[i]->op,0,"",tmproot,NULL);
//                }
//                break;
//            }
//            if(exps[i]->op == "*" || exps[i]->op == "/"){
//                if(tmproot == NULL){
//                    tmproot = new Expression(COMPOUND,exps[i]->op,0,"",p,NULL);
//                }
//                else if(tmproot->rhs!= NULL && (tmproot->rhs->op != "+" && tmproot->rhs->op != "-" )){
//                    tmproot->rhs = new Expression(COMPOUND,exps[i]->op,0,"",tmproot->rhs,NULL);
//                }
//                else if(tmproot->rhs!= NULL &&  (exps[i]->op == "=" || exps[i]->op==">" || exps[i]->op=="<")){
//                    tmproot->rhs->rhs = new Expression(COMPOUND,exps[i]->op,0,"",tmproot->rhs->rhs,NULL);
//                }
//                else if(tmproot->rhs!= NULL){
//                    tmproot->rhs->rhs = new Expression(COMPOUND,exps[i]->op, 0 , "",tmproot->rhs->rhs,NULL);
//                }
//                break;
//            }
//        }
//        i++;
//    }
//    if(size == 1) tmproot = p;   // SIZE 为1 说明是constant
//    return  tmproot;

}

void  parse::getToken(string &str)  // 返回exp
{
     int i = 0,j = 0,k = 0;
     int line ;
     if(cmdState == "REM"){
         return;
     }
     if(cmdState == "IF"){ //  找到THEN的位置和要去的line
                           //i:then的位置，j:goto_line的开始， k:goto_line 的结束
         for( i = 0 ; i < str.size() - 4; i ++){
             if(str.substr(i,4) == "THEN"){
                 for( j = i + 4; j < str.size(); j++){
                     if(str[j] != ' '){
                         for( k = j ; k < str.size(); k++){
                              if(k == str.size()-1){
                                 line = atoi(str.substr(j,k-j+1).c_str());
                                 if(j==k) line = str[k]-'0';
                                 this->line_of_if = line;
                                 break;
                             }
                         }
                         break;
                     }
                 }
                 break;
             }
         }
     }

    string identifier;
    int index = 0;
    int data = 0;
    string  s = str; //记录str变化长度
    while (index < ((i != 0) ? (i-1) : str.size())) {

        while(str[index] == ' ') { index++; s = str;}

        if(str[index] >= '0' && str[index] <= '9'){
            data = 0;
            while(str[index] >= '0' && str[index] <= '9'){
                data= data * 10 + str[index] - '0';
                index++;
            }
            if((str[index] >= 'a' && str[index] <= 'z') || (str[index] >= 'A' && str[index] <= 'Z')){ //命名错误
                legal = false;
                return;
            }
            if(size >= 2){
                if( exps[size-1]->op == "-" && (exps[size-2]->op=="(" || exps[size-2]->op=="=" || exps[size-2]->op==">"|| exps[size-2]->op=="<")){
                    exps[size-1]->expType = CONSTANT;
                    exps[size-1]->value = (-1) * data;
                    continue;
                }
            }

            exps[size] = new Expression();
            exps[size]->value = data;
            exps[size]->expType = CONSTANT;
            size++;
            continue;
        }


        if((str[index] >= 'a' && str[index] <= 'z') || (str[index] >= 'A' && str[index] <= 'Z')){
            int pos = index;
            while(str[index] != '+' && str[index] != '-' && str[index] != '*' && str[index] != '/' && str[index] != ' ' && str[index] != '='){
                index++;
                if (index >= str.size()) break;
            }
            identifier =  str.substr(pos, index - pos);  // length may exists

            exps[size] = new Expression();
            exps[size]->name = identifier;
            exps[size]->expType = IDENTIFIER;
            size++;
            continue;
        }

        exps[size] = new Expression();
        if(str[index] == '*' && str[index+1] == '*'){
            exps[size]->op = "**";
            index++;
        }
        else {
            exps[size]->op = str[index];
        }
        index++;
        exps[size]->expType = COMPOUND;
        exps[size]->lhs = NULL;
        exps[size]->rhs = NULL;
        size++;
    }
}




void parse::cal()
{
    if(Operands.size()<=1) {this->legal = false; return;}


    Operator.top()->rhs = Operands.top();
    Operands.pop();
    Operator.top()->lhs = Operands.top();
    Operands.pop();
    Operands.push(Operator.top());
    Operator.pop();
}



void parse::showTree(QTextBrowser * treeBrowser)
{
    queue<Expression*> que;
    Expression * tmp;
    Expression *last = root, *nlast = root;  // 层次遍历，但是需要记录每一行的末尾节点
    string gap = "";

    if(!this->legal){
        treeBrowser->append(QString::fromStdString(to_string(line)+' '+"Error"));
        return;
    }
    que.push(root);
     if(this->cmdState == "REM"){
         treeBrowser->append(QString::fromStdString(to_string(line)+' '+cmdState+' '));
         treeBrowser->append("   "+QString::fromStdString(this->cmd_without_pre));
         return;
     }
     else if(cmdState == "PRINT" || cmdState == "INPUT" || cmdState == "GOTO" ){
          treeBrowser->append(QString::fromStdString(to_string(line)+' '+cmdState+' '));
          gap += "   ";
     }
     else if(cmdState == "IF"){
         treeBrowser->append(QString::fromStdString(to_string(line)+' '+cmdState+' '+"THEN"));
         gap += "   ";
     }
     else if(cmdState == "END"){
          treeBrowser->append(QString::fromStdString(to_string(line)+' '+cmdState+' '));
          return;
     }
     else if(cmdState == "LET") {}

     else {   // 若都不是以上，则为false
         this->legal = false;
         treeBrowser->append(QString::fromStdString(to_string(line)+' '+"Error"));
         return;
     }


    while (!que.empty()) {
        tmp = que.front();
        que.pop();
        if(tmp->lhs) {
            que.push(tmp->lhs);
            nlast = tmp->lhs;
        }
        if(tmp->rhs) {
            que.push(tmp->rhs);
            nlast = tmp->rhs;
        }
        switch (tmp->expType) {
        case CONSTANT:
        {
            treeBrowser->append(QString::fromStdString(gap+to_string(tmp->value)));
            treeBrowser->show();
            break;}
        case IDENTIFIER:
            treeBrowser->append(QString::fromStdString(gap+tmp->name));
            treeBrowser->show();
            break;
        case COMPOUND:
            QString qchar = QString::fromStdString(tmp->op);
            if(qchar == '=') {
                treeBrowser->append(QString::fromStdString(to_string(line)+' '+cmdState+' ')+QString::fromStdString(gap)+qchar);
            }
            else {
                treeBrowser->append(QString::fromStdString(gap)+qchar);
            }
            treeBrowser->show();
        }
        if(tmp == last){
            last = nlast;
            gap += "   ";
        }
    }
    if(cmdState == "IF"){  // 特殊处理IF的输出
        treeBrowser->append("   "+QString::fromStdString(to_string(this->line_of_if)));
    }
}


