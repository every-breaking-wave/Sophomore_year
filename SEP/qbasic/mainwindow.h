#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "statement.h"
#include <vector>
#include <list>
#include "exp.h"
#include "code.h"
#include "programrunner.h"
#include "error.h"
#include <QDesktopServices>


//class parse;
class Expression;
class code;
class programRunner;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void loadCode();
    void append_code(QString str);
    void showTree(parse * par);

private slots:
    void on_cmdLineEdit_editingFinished();

   // void on_btnClearCode_clicked();

    void on_btnLoadCode_clicked();

    void on_label_4_linkActivated(const QString &link);

    void on_label_4_windowIconTextChanged(const QString &iconText);

    void on_cmdLineEdit_textChanged();

    void on_btnClearCode_clicked();


    void on_btnRunCode_clicked();

    void on_CodeDisplay_textChanged();

private:
    Ui::MainWindow *ui;

    class code savedCode;
   // parse *par;
    class programRunner runner;

private slots:
    void press_enter();



    void on_actionHelp_triggered();
};
#endif // MAINWINDOW_H
