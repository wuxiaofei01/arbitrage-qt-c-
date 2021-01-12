#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    for(int i=0;i<maxn;i++)edge[i].clear();
        mp.clear();
        s.clear();
    for(int i=0;i<maxn;i++)rule[i].from.clear(),rule[i].val.clear(),rule[i].to.clear();
    for(int i=0;i<maxn;i++)path[i]=-1;
    n=0;
}

void MainWindow::get(string temp)//得到temp对应的编号
{
    s.insert(temp);
    if (mp[temp] == 0) //还没定义
         mp[temp] = s.size();
}

double MainWindow::spfa(int begin)
{
    queue<int>q;
    q.push(begin);
    int vis[maxn];
    double root[maxn];
    for(int i=0;i<maxn;i++)vis[i]=0,root[i]=0;

    root[begin]=1;//当前转换率是1：1
    vis[begin]++;
    while(!q.empty())
    {
        int now=q.front();
        q.pop();
        for(int i=0;i<edge[now].size();i++)
        {
            int to=edge[now][i].to;
            double val=edge[now][i].val;

            if(val*root[now]>root[to]&&(vis[to]==0||to==begin))//价值比下一个大
             {
                root[to]=val*root[now];
                q.push(to);
                vis[now]++;
                path[to]=now;
             }
         }
     }
    if(vis[begin]==1)return -1;
    return root[begin];

}

void MainWindow::spfa()
{
    for(int i=1;i<=n;i++)
    {
        get(rule[i].from);
        get(rule[i].to);
        edge[mp[rule[i].from]].push_back(Root{mp[rule[i].to],atof(rule[i].val.c_str())});
       //qDebug()<<mp[rule[i].to];
       // cout<<atof(rule[i].val.c_str());
    }
    double ans=spfa(mp[target]);

    QMessageBox msg;
    msg.setStyleSheet("QLabel{"
                          "min-width:150px;"
                          "min-height:40px; "
                          "font-size:16px;"
                          "}");

    msg.setWindowTitle("wrong");//对话框标题
    msg.setText("input is invalied");//对话框提示文本
    msg.setIcon(QMessageBox::Information);//设置图标类型
    msg.setStandardButtons(QMessageBox::Ok );//对话框上包含的按钮
    if(ans==-1&&msg.exec() == QMessageBox::Ok)//模态调用
    {
       qDebug() << " Ok is clicked!";//数据处理
    }
    else
    {
        ans--;
        ans*=100;
       QString s1="your interest is  ";
       QString s2="%";
       ui->text2->insertPlainText(s1);
       ui->text2->insertPlainText(QString::number(ans));
       ui->text2->insertPlainText(s2);

       deque<string>q;
       int begin=mp[target];//开始目标
       int temp=begin;
       while(path[begin]!=temp)
       {
          for(map<string,int>::iterator it=mp.begin();it!=mp.end();it++)
          {
              if(it->second==begin)q.push_back(it->first);
          }
          begin=path[begin];
          if(path[begin]==temp)
          {
              for(map<string,int>::iterator it=mp.begin();it!=mp.end();it++)
              {
                  if(it->second==begin)q.push_back(it->first);
              }
          }
       }
       int n=0;
       ui->path->clear();
       ui->path->insertPlainText(QString::fromStdString(target));
       ui->path->insertPlainText("   ->   ");
       while(!q.empty())
       {
           string temp=q.back();
           ui->path->insertPlainText(QString::fromStdString(temp));
           q.pop_back();
           if(!q.empty())
           ui->path->insertPlainText("   ->   ");
           if(n==8)
           {
               ui->path->insertPlainText("\n");
               n==0;
           }
           n++;
       }
    }

}

void MainWindow::on_pushButton_clicked()//文件打开
{


    init();
    QString file;

    file = QFileDialog::getOpenFileName(this);

     QFile f(file);

     if (!f.open(QIODevice::ReadOnly|QIODevice::Text))//打开指定文件
     {
         QMessageBox::about(NULL, "文件", "文件打开失败");
         return;
     }

         QTextStream txtInput(&f);//读入文件内容;

         ui->text->clear();
     while(!txtInput.atEnd())
     {
         QString lineStr = txtInput.readLine();  //读取数据

         istringstream is(lineStr.toStdString());

         n++;
         is>>rule[n].from>>rule[n].to>>rule[n].val;

         ui->text->insertPlainText(lineStr);
         ui->text->insertPlainText("\n");
         ui->text->textCursor().movePosition(QTextCursor::Down);
     }


}

void MainWindow::on_pushButton_2_clicked()//开始套汇
{
    ui->text2->clear();
    spfa();
}

void MainWindow::on_lineEdit_cursorPositionChanged(int arg1, int arg2)
{
    target=ui->lineEdit->text().toStdString();
}
