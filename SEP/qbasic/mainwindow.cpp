#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QtDebug>
#include "statement.h"
#include <string>
#include <QFileDialog>
#include <fstream>
#include <Qstring>
#include<queue>

// 总算搞完了 fuck Qt!!


/*   一点教训
 *
 * 改变不了链表的第一个id
 * type 返回值不正确
 * vector存放的内容缺失
 * new 出来的值最好初始化
 * 莫名其妙runner指针就会失败
 */


using namespace  std;



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // this->ui->
    this->setWindowTitle("Qbasic written by FYF");
    ui->cmdLineEdit->setFocus();
    this->savedCode.setBrowser(ui->treeDisplay);
    connect(ui->cmdLineEdit, &QLineEdit::returnPressed, this, &MainWindow::press_enter);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::append_code(QString Str){

    enum Type {Rem, Let, Print, Input, Goto, If, End};
    QString cmd = ui->cmdLineEdit->text();
    if(Str != "") cmd = Str;
    if (cmd == "")  return;
    string str = cmd.toStdString();
    ui->CodeDisplay->append(cmd);
    int i = 0,j = 0;
    for( i = 0;  i < cmd.length(); i ++){  //寻找cmd中的第一个空格位置
        if(cmd[i] == ' ')
            break;
    }

    for( j = i+1;  j < cmd.length(); j ++){  //寻找cmd中的第二个空格位置
        if(cmd[j] == ' ')
            break;
    }
    string str_no_state;
    int id = atoi(str.substr(0, i==cmd.length()?cmd.length():i).c_str());  // 获取cmd的行号
    parse* par = new parse;
    if(id <= 0) {par->legal = false;}
    par->cmd = str;

    par->line = id;

    if(id == 0){
        par->legal = false;
        ui->textBrowser->append("you must begin with line!");
        return;
    }

    if(i == cmd.length()){  //仅有数字
        savedCode.delCode(id);
        ui->CodeDisplay->clear();
        for(int i = 0; i < savedCode.num_of_cmd; i++){
            QString str = QString::fromStdString(savedCode.getCode(i)->cmd);
            this->ui->CodeDisplay->append(str);
        }
        return;

//        par->legal = false;
//        str_no_state = "";
    }
    else if(j == cmd.length()) {
        str_no_state = "";
        par->cmdState = str.substr(i+1,(j - i-1));
        if(par->cmdState != "END"){
            par->legal = false;
        }
    }
    else  {
        par->cmdState = str.substr(i+1, j - i - 1);   //获取state种类
        str_no_state = str.substr(j+1,str.size()-(j+1));;
    }
    try{
        if(par->cmdState == "DELETE"){   // 为删除命令
            savedCode.delCode(id);
            ui->CodeDisplay->clear();
            for(int i = 0; i < savedCode.num_of_cmd; i++){
                QString str = QString::fromStdString(savedCode.getCode(i)->cmd);
                this->ui->CodeDisplay->append(str);
            }
            return;
        }
    }
    catch(string msg){
        ui->textBrowser->append(QString::fromStdString(msg));
        return;
    }
    par->next = NULL;
    par->getToken(str_no_state);
    par->root = par->expTree();
    par->cmd_without_pre = str_no_state;

    savedCode.insert(par);
    ui->CodeDisplay->clear();
    for(int i = 0; i < savedCode.num_of_cmd; i++){
        QString str = QString::fromStdString(savedCode.getCode(i)->cmd);
        this->ui->CodeDisplay->append(str);
    }

}

void MainWindow::press_enter()
{
    append_code("");
    ui->cmdLineEdit->clear();
}

void MainWindow::loadCode()
{
    on_btnClearCode_clicked();
    QString fileName = QFileDialog::getOpenFileName(this,tr("文件对话框！"), "F:",  tr("文本文件(*txt)"));
    std::string str = fileName.toStdString();
    std::ifstream file(str);
    std::string line;
    while(getline(file,line)){
        QString Qstr = QString::fromStdString(line);
        append_code(Qstr);
        // this->ui->CodeDisplay->append(Qstr);
    }
    return;
}


void MainWindow::on_cmdLineEdit_textChanged()
{

}

void MainWindow::on_btnLoadCode_clicked()
{
    this->loadCode();
}

void MainWindow::on_btnClearCode_clicked()
{
    this->ui->CodeDisplay->clear();
    ui->treeDisplay->clear();
    ui->textBrowser->clear();
    this->savedCode.num_of_cmd = 0;
    this->savedCode.head = NULL;
}

void MainWindow::on_btnRunCode_clicked()
{
    try {
        if(savedCode.head == NULL){
            error("no cmd has been input!");
            return;
        }
        this->savedCode.context.clearTable();
        this->ui->treeDisplay->clear();
        //   this->ui->CodeDisplay->clear();
        this->ui->textBrowser->clear();
        this->savedCode.runCode(ui->treeDisplay,ui->textBrowser);
    } catch (string msg) {
        this->ui->textBrowser->append("Error:"+QString::fromStdString(msg));
    }

}

void MainWindow::on_CodeDisplay_textChanged()
{

}


void MainWindow::showTree(parse * par)
{
    if(!par->legal){
        ui->treeDisplay->append("");
    }
    queue<Expression*> que;
    Expression * tmp;
    Expression *last = par->root, *nlast = par->root;
    string gap = "";
    que.push(par->root);
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
            this->ui->treeDisplay-> append(QString::fromStdString(to_string(tmp->value)));
            break;}
        case IDENTIFIER:
            this->ui->treeDisplay->append(QString::fromStdString(tmp->name));
            break;
        case COMPOUND:
            QString qchar = QString::fromStdString(tmp->op);
            this->ui->treeDisplay->append(qchar);
        }
        if(tmp == last){
            last = nlast;
            gap += "   ";
        }

    }
}

void MainWindow::on_actionHelp_triggered()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile("../qbasic/help.pdf"));

}
