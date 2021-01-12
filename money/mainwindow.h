#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <bits/stdc++.h>
#include <QDebug>
#include <QTextCodec>
using namespace  std;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
struct Node
{
    string from,to;
    string val;
};

struct Root
{
    int to;
    double val;
};

const int maxn=1e3;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int n;//有多少条规则
    int path[maxn];
    Node rule[maxn];
    vector<Root> edge[maxn];
    set<string> s;
    map<string, int> mp;
    string target;

    void init();
    void spfa();
    double spfa(int begin);
    void get(string temp);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_lineEdit_cursorPositionChanged(int arg1, int arg2);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
