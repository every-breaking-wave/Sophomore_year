#include <iostream>
#include <sstream>
#include "Editor.h"
#include<cstring>
#include<string.h>

using namespace std;

Editor::Editor()
{
    buffer = new Buffer();
}
Editor::~Editor()
{
    // TODO: Implement destructor
    delete [] buffer;
}

void Editor::run()
{
    string cmd;
    while (true)
    {
        cout << "cmd> ";
        cout.flush();
        getline(cin, cmd);
        if (cmd == "Q")
            break;
        try {
            dispatchCmd(cmd);
        } catch (const char *e) {
            cout << "? " << e << endl;
        } catch (const out_of_range &oor) {
            cout << "? " << oor.what() << endl;
        } catch (const range_error &re) {
            cout << "? " << re.what() << endl;
        }

    }
}
void Editor::cmdAppend()
{
    cout << "It's input mode now. Quit with a line with a single dot(.)" << endl;
    // TODO: finish cmdAppend.

    while (true)
    {
        string text;

        getline(cin, text);
        if (text == ".")
            break;

   //   if(text.length()<=0){text="enter";cout<<'?';cout<<text;}

           buffer->appendLine(text);
        }

    }


void Editor::cmdInsert()
{
    cout << "It's input mode now. Quit with a line with a single dot(.)" << endl;
     bool firstname=true;
    while (true)
    {
        string text;
        getline(cin, text);
        if (text == ".")
            break;
        if(firstname)
        {
            buffer->insertLine(text);
            firstname=false;
        }
        else
       {
           buffer->appendLine(text);
        }
    }
}

void Editor::cmdDelete(int start, int end)
{
    buffer->deleteLines(start, end);


}

void Editor::cmdNull(int line)
{
    buffer->moveToLine(line) ;
    cout<<endl;
}

void Editor::cmdNumber(int start, int end)
{
    buffer->showLines(start, end);
}

void Editor::cmdWrite(const string &filename)
{
    buffer->writeToFile(filename);
}

void Editor::dispatchCmd(const string &cmd)
{

    if (cmd == "a") {
        cmdAppend();
        return;

    }
    if (cmd == "i") {
        cmdInsert();

        return;
    }
    if(cmd=="w"||cmd=="w ") {cout<< "? Filename not specified"<<endl;return;}

    if (cmd[0] == 'w' && cmd[1] == ' ') {
        // TODO: call cmdWrite with proper arguments
       int pos=cmd.find(' ',1);
     string file;
       file=cmd.substr(2,pos-2);

        cmdWrite(file);

        return;
    }
    // TODO: handle special case "1,$n".
    int pos=cmd.find(',',1);
    if(cmd[pos+1]=='$')
    {   stringstream s(cmd);
        int firstNum;
        s>>firstNum;
        if(this->buffer->sl.length()==0){cout<<1;throw "Number range error";return;}
        if(firstNum>(this->buffer->sl.length())){throw "Line number out of range";return;}
        cmdNumber(-1,0);
        return;
    }
    int start, end;
    char comma, type = ' ';
    stringstream ss(cmd);
    ss >> start;
    if (ss.eof()) {

       if(start>this->buffer->sl.length()){throw "Line number out of range";return;}
        cmdNull(start);
        return;
    }
    ss >> comma >> end >> type;
//范围错误优先于行号越界
    if (ss.good()) {
        if (type == 'n') {
              if(start>end){throw "Number range error";return;}
              if(end>(this->buffer->sl.length()))
                  {throw "Line number out of range";return;}
            cmdNumber(start, end);
            return;
        } else if (type == 'd') {
              if(start>end){throw "Delete range error";return;}
              if(end>(this->buffer->sl.length()))
                  {throw "Line number out of range";return;}
            cmdDelete(start, end);
            return;
        }
    }

    throw "Bad/Unknown command";
}
