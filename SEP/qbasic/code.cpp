#include "code.h"
#include <QInputDialog>

code::code()
{
    this->num_of_cmd = 0;
    head = NULL;
}



void code::parseState(codeNode * curCode)   // 根据node 的state来执行不同的处理函数
{
    // 每parse一条语句打印一棵树
    if(curCode == NULL) return;
    if(curCode->node->legal == false) {
       // curCode->node->showTree(syntax_display);
        parseState(curCode->next);
        return;
    }

    if(curCode->node->cmdState == "REM"){
        handleREM(curCode);
        return;
    }
    if(curCode->node->cmdState == "LET"){
        handleLET(curCode);
        return;
    }
    if(curCode->node->cmdState == "INPUT"){
        handleINPUT(curCode);
        return;
    }
    if(curCode->node->cmdState == "PRINT"){
        handlePRINT(curCode);
        return;
    }
    if(curCode->node->cmdState == "GOTO"){
        handleGOTO(curCode);
        return;
    }
    if(curCode->node->cmdState == "IF"){
        handleIF(curCode);
        return;
    }
    if(curCode->node->cmdState == "END"){
        handleEND(curCode);
        return;
    }
    else curCode->node->legal = false;

 //   curCode->node->legal = false;
    curCode->node->showTree(syntax_display);
    parseState(curCode->next);
    return;

}

void code::clearCode()
{
    this->head = NULL;
    this->num_of_cmd = 0;
}

void code::runCode(QTextBrowser * treeBrowser, QTextBrowser * resultBrowser)
{
    for(int i = 0 ; i < this->num_of_cmd; i++){
            getCode(i)->node->showTree(treeBrowser);
    }
    codeNode * pos = this->head;
    this->result_display = new QTextBrowser;
    result_display = resultBrowser;
    this->syntax_display = new QTextBrowser;
    syntax_display = treeBrowser;
    parseState(pos);

}

void code::setBrowser(QTextBrowser  * tree_browser)
{
    this->syntax_display = tree_browser;
}

void code::insert(parse *par)
{

    codeNode * pos = this->head;
    for(int i = 0; i < num_of_cmd + 1; i++){
        if(pos!=NULL && pos->next!=NULL&& pos->next->node->line == par->line){  // 替换同line的指令
            pos->next = new codeNode(par,par->cmd,pos->next->next);
            break;
        }
        if(pos!=NULL && pos == head && pos->node->line == par->line){ // 替换head
            head = new codeNode(par,par->cmd,head->next);
            break;
        }
        if(pos != NULL && pos->next != NULL &&(par->line > pos->node->line && par->line < pos->next->node->line)){  // 插在中间
            pos->next = new codeNode(par,par->cmd,pos->next);
            pos->next->node->root = par->root;
            num_of_cmd++;
            break;
        }
        else if(pos != NULL && pos->next == NULL && par->line > pos->node->line){ // 插在尾部
            pos->next = new codeNode(par,par->cmd,NULL);
            pos->next->node->root = par->root;
            num_of_cmd++;
            break;
        }
        else if(pos != NULL && pos == head && par->line < pos->node->line){ // 只有最前面
            head = new codeNode(par,par->cmd, pos);
            head->node->root = par->root;
            num_of_cmd++;
            return;
        }
        else if(pos == NULL){   // length = 0
            head = new codeNode(par,par->cmd,NULL);
            head->node->root = par->root;
            num_of_cmd++;
            return;
        }
        pos = pos->next;
    }
}

code::codeNode *code::getCode(int id)   // 获得code列表中第i条代码（含0）
{
    codeNode * pos = this->head;
    if(id >= num_of_cmd) return NULL;
    int i = 0;
    while (i < id ) {
        pos = pos->next;
        i++;
    }
//    if(id >= num_of_cmd){
//        return NULL;
//    }
    return  pos;
}

void code::delCode(int line)
{
    if(head == NULL)  {error("no such line number!");}
    codeNode * pos = this->head;
    for(int i = 0; i < num_of_cmd; i++){
        if( pos->next!=NULL && pos->next->node->line == line){
            pos->next = pos->next->next;
            num_of_cmd -= 1;
            return;
        }
        else if(pos==head && pos->node->line == line){
            head = NULL;
            num_of_cmd = 0;
            return;
        }
        pos = pos->next;
    }
    error("no such line number!");
}

void code::handleREM(code::codeNode *cur)
{
    // this->result_display->append("REM"+QString::fromStdString(cur->node->cmd));
    //cur->node->showTree(syntax_display);
    this->parseState(cur->next);
}

void code::handleLET(code::codeNode *cur)
{
    try {
        cur->node->root->eval(this->context);
      //  cur->node->showTree(syntax_display);
    } catch (string msg) {

       this->result_display->append(QString::fromStdString(msg));
    }
    this->parseState(cur->next);    //this->context.setValue(cur->node->root->lhs->name,cur->node.)
}

void code::handlePRINT(code::codeNode *cur)
{
    try {
        int result = cur->node->root->eval(context);
        this->result_display->append( QString::fromStdString(to_string(result)));
     //   cur->node->showTree(syntax_display);
    } catch (string msg) {
        this->result_display->append(QString::fromStdString(msg));
    }
    parseState(cur->next);
}

void code::handleEND(code::codeNode *cur)
{
    //cur->node->showTree(syntax_display);
    parseState(NULL);
}

void code::handleINPUT(code::codeNode *cur)
{
    QString name = QString::fromStdString((cur->node->root->name))  ;
    int inputNum = QInputDialog::getInt(NULL, "Input Dialog", "Please input " + name+ ":");
    this->context.setValue(name.toStdString(),inputNum);
   // cur->node->showTree(syntax_display);
    parseState(cur->next);
}

void code::handleGOTO(code::codeNode *cur)
{
   // cur->node->showTree(syntax_display);
    int i = 0;
    for( i = 0; i < this->num_of_cmd; i++){
        if(cur->node->root->value == getCode(i)->node->line){
            parseState(getCode(i));
            return;
        }
    }
    if(i >= num_of_cmd){
       this->result_display->append("no such line!");
        parseState(NULL);
    }
}

void code::handleIF(code::codeNode *cur)
{
    bool flag;
    int left = cur->node->root->lhs->eval(context);
    int right = cur->node->root->rhs->eval(context);
    if(cur->node->root->op == ">"){
        flag = left > right;
    }
    if(cur->node->root->op == "<"){
        flag = left < right;
    }
    if(cur->node->root->op == "="){
        flag = left == right;
    }

    if(flag) {  // if 条件成立
        for(int i = 0; i < this->num_of_cmd; i++){
            if(cur->node->line_of_if == getCode(i)->node->line){
                parseState(getCode(i));
                return;
            }
    }
    }
    else {
        parseState(cur->next);
    }

}


