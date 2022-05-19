#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegularExpression>
#include <QDebug>
#include <QMap>
#include <QStack>
#include <QtSql/QSqlDatabase>
#include <Qtsql/qsqlquery.h>
#include <QMessageBox>
#include <QColorDialog>
#include <QFontDialog>
#include <QInputDialog>
#include <QDateTime>
#include <complex>
#include "login.h"
#include "reg.h"
#include "consttable.h"
#include "histroy.h"
#include "aboutcalc.h"
#include "functioninput.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    pr.insert('+',1);
    pr.insert('-',1);
    pr.insert('*',2);
    pr.insert('/',2);
    db =QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("");//数据库地址
    db.setUserName("user_demo");
    db.setPassword("");//数据库密码
    db.setDatabaseName("user_demo");
    updataConstDict();
    if(!db.open())
    {
        QMessageBox::information(this,"数据库连接失败","开启离线模式");
    }
    constNumbers.insert("a",0.1);
    constNumbers.insert("b",0.2);
    initFunctionMap();
    stu = MainWindow::blank;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initFunctionMap()
{
    functionMap.insert("SIN",1);
    functionMap.insert("COS",2);
    functionMap.insert("TAN",3);
    functionMap.insert("ARCSIN",4);
    functionMap.insert("ARCCOS",5);
    functionMap.insert("ARCTAN",6);
    functionMap.insert("EX",7);
    functionMap.insert("LN",8);
    functionMap.insert("SQRT",9);
}

void MainWindow::addSinx()
{
    ui->textEdit->textCursor().insertText("FUNCTION_SIN()");
}
void MainWindow::addCosx()
{
    ui->textEdit->textCursor().insertText("FUNCTION_COS()");
}
void MainWindow::addTanx()
{
    ui->textEdit->textCursor().insertText("FUNCTION_TAN()");
}
void MainWindow::addArcsinx()
{
    ui->textEdit->textCursor().insertText("FUNCTION_ARCSIN()");
}
void MainWindow::addArccosx()
{
    ui->textEdit->textCursor().insertText("FUNCTION_ARCCOS()");
}
void MainWindow::addArctanx()
{
    ui->textEdit->textCursor().insertText("FUNCTION_ARCTAN()");
}
void MainWindow::addEx()
{
    ui->textEdit->textCursor().insertText("FUNCTION_EX()");
}
void MainWindow::addLnx()
{
    ui->textEdit->textCursor().insertText("FUNCTION_LN()");
}
void MainWindow::addSqrtx()
{
    ui->textEdit->textCursor().insertText("FUNCTION_SQRT()");
}

void MainWindow::on_num0_clicked()
{
    ui->textEdit->textCursor().insertText("0");
}
void MainWindow::on_num1_clicked()
{
    ui->textEdit->textCursor().insertText("1");
}
void MainWindow::on_num2_clicked()
{
    ui->textEdit->textCursor().insertText("2");
}
void MainWindow::on_num3_clicked()
{
    ui->textEdit->textCursor().insertText("3");
}
void MainWindow::on_num4_clicked()
{
    ui->textEdit->textCursor().insertText("4");
}
void MainWindow::on_num5_clicked()
{
    ui->textEdit->textCursor().insertText("5");
}
void MainWindow::on_num6_clicked()
{
    ui->textEdit->textCursor().insertText("6");
}
void MainWindow::on_num7_clicked()
{
    ui->textEdit->textCursor().insertText("7");
}
void MainWindow::on_num8_clicked()
{
    ui->textEdit->textCursor().insertText("8");
}
void MainWindow::on_num9_clicked()
{
    ui->textEdit->textCursor().insertText("9");
}
void MainWindow::on_dot_clicked()
{
    ui->textEdit->textCursor().insertText(".");
}
void MainWindow::on_add_clicked()
{
    ui->textEdit->textCursor().insertText("+");
}
void MainWindow::on_sub_clicked()
{
    ui->textEdit->textCursor().insertText("-");
}
void MainWindow::on_multiply_clicked()
{
    ui->textEdit->textCursor().insertText("*");
}
void MainWindow::on_div_clicked()
{
    ui->textEdit->textCursor().insertText("/");
}
void MainWindow::on_backSpace_clicked()
{
    ui->textEdit->textCursor().deletePreviousChar();
}
void MainWindow::on_roundLeft_clicked()
{
    ui->textEdit->textCursor().insertText("(");
}
void MainWindow::on_roundRight_clicked()
{
    ui->textEdit->textCursor().insertText(")");
}
bool MainWindow::eval(QStack<double> &num,QStack<QChar> &op)
{
    double b = num.top();num.pop();
    double a = num.top();num.pop();
    qDebug()<<a<<" "<<b;
    auto c = op.top();op.pop();
    double x;
    if(c == '+')x = a + b;
    else if(c == '-')x = a - b;
    else if(c == '*')x = a * b;
    else
    {
        if(b == 0.0)
        {
            qDebug()<<a<<" "<<b;
            return false;
        }
        else x = a/b;
    }
    num.push(x);
    return true;
}

double MainWindow::calc(QString str)
{
    qDebug()<<str;
    QStack<double> num;
    QStack<QChar> op;
    QString TempNum = "";
    zeroErr = false;
    for(int i = 0;i<str.size();i++)
    {
        bool flag = false;
        //错误auto c = str[i];
        //正确QChar c = str[i];
        QChar c = str[i];
        if((i==0&&str[i] == '-')||(i != 0&&str[i] == '-'&&(str[i-1]<'0'||str[i-1]>'9')&&str[i-1] != ')'))
        {
            TempNum += str[i];
            continue;
        }
        if((c>='0'&&c<='9')||c == '.')
        {
            TempNum += str[i];
            i++;
            c = str[i];
            for(;i<str.size();i++)
            {
                if((str[i]>='0'&&str[i]<='9')||str[i] == '.')
                    TempNum += str[i];
                else
                    break;
            }
            qDebug()<<TempNum;
            num.push(TempNum.toDouble());
            TempNum = "";
            i--;
        }
        else if(c == '(')op.push(c);
        else if(c == ')')
        {
            while(op.top()!='(')eval(num,op);
            op.pop();
        }
        else
        {
            if(!flag)
            {
                while(op.size()&&op.top() != '('&&pr[op.top()]>=pr[c])
                {
                    bool st = eval(num,op);
                    if(!st)
                    {
                        zeroErr = true;
                        return 0;
                    }
                }
                op.push(c);
                qDebug()<<"符号"<<c;
            }
        }

    }
    while(op.size())
    {
        bool st = eval(num,op);
        if(!st)
        {
            zeroErr = true;
            return 0;
        }
    }
    return num.top();
}

void MainWindow::record(QString input, QString output)
{
    QSqlQuery query = QSqlQuery(db);
    QDateTime curTime =  QDateTime::currentDateTime();
    QString TimeStr = curTime.toString("yyyy-MM-dd hh:mm:ss");
    QString sql = "insert into history(userid,time,input,output) values(:uid,'"+TimeStr+"','"+input+"','"+output+"')";
    query.prepare(sql);
    query.bindValue(":uid",userId);
    query.exec();
}


void MainWindow::on_equal_clicked()
{
    qDebug()<<constNumbers;
    bool openRecord;
    if(userId == -1)openRecord = false;
    else openRecord = true;
    QString inputText = ui->textEdit->toPlainText();
    //第一次过滤-正则匹配
    QRegExp singleNum("\\(*((-?\\d+)(\\.\\d+)?|CONST\\(.+\\)|FUNCTION_.+\\(.+\\))\\)*");
    QRegExp calcTextModel("(\\(*(((-?\\d+)(\\.\\d+)?)|CONST\\(.+\\)|FUNCTION_.+\\(.+\\))\\)*(\\+|-|\\*|/))+\\(*(((-?\\d+)(\\.\\d+)?)|CONST\\(.+\\)|FUNCTION_.+\\(.+\\))\\)*");

    if((!calcTextModel.exactMatch(inputText))&&(!singleNum.exactMatch(inputText)))
    {
        if(openRecord)
        {
            record(inputText,"运算格式或常数(函数)格式错误");
        }
        ui->textBrowser->setText("运算格式或常数(函数)格式错误");
        stu = MainWindow::blank;
        return;
    }

    //第二次过滤-括号匹配
    QString roundTextList;
    for(int i = 0;i<inputText.length();i++)
    {
        if(inputText[i] == '(' ||inputText[i] == ')' )
            roundTextList += inputText[i];
    }
    int dep = 0;
    for(int i = 0;i<roundTextList.length();i++)
    {
        if(roundTextList[i] == '(')dep++;
        else dep--;
    }
    if(dep != 0)
    {
        if(openRecord)
        {
            record(inputText,"括号不匹配");
        }
        ui->textBrowser->setText("括号不匹配");
        stu = MainWindow::blank;
        return;
    }

    //第三次过滤-常数过滤
    QStringList constList;
    for(int i = 0;i<inputText.length();i++)
    {
        if(inputText[i] == 'C'&&i+6<inputText.size()&&inputText[i+1] == 'O'&&inputText[i+2] == 'N')
        {
            int beg = i;
            i++;
            while(inputText[i] != ')')i++;
            constList<<inputText.mid(beg,i-beg+1);
        }
    }
    qDebug()<<"提取常数"<<constList;
    QString hisText = inputText;
    for(auto i:constList)
    {
        QString _const;
        for(int j = 0;j<i.length();j++)
        {
            if(i[j] == '(')
            {
                int beg = j;
                j++;
                while(i[j] != ')')j++;
                _const = i.mid(beg+1,j-beg-1);
            }
        }
        if(constNumbers.contains(_const))
            qDebug()<<constNumbers[_const];
        else
        {
            if(openRecord)
            {
                record(inputText,"常数不存在");
            }
            ui->textBrowser->setText("常数不存在");
            stu = MainWindow::blank;
            return;
        }
        qDebug()<<i;
        inputText = inputText.replace(i, QString::number(constNumbers[_const],'f',15));
    }

    //第四次过滤 函数过滤
    QStringList functionList;
    QStringList numberList;
    QVector<double> numberParseList;
    for(int i = 0;i<inputText.length();i++)
    {
        if(inputText[i] == '_')
        {
            int beg = i+1;
            i++;
            while(inputText[i] != '(')i++;
            functionList<<inputText.mid(beg,i-beg);
            int numbeg = i+1;
            i++;
            while(inputText[i] != ')')i++;
            numberList<<inputText.mid(numbeg,i-numbeg);
        }
    }
    qDebug()<<"提取函数:"<<functionList;
    qDebug()<<"提取函数中的数值:"<<numberList;

    //判读函数中的是否是数值
    QRegExp numberMatch("(-?\\d+)(\\.\\d+)?");
    for(QString i:numberList)
    {
        if(!numberMatch.exactMatch(i))
        {
            if(openRecord)
            {
                record(inputText,"函数中需要输入数值");
            }
            ui->textBrowser->setText("函数中需要输入数值");
            stu = MainWindow::blank;
            return;
        }
        else
        {
            numberParseList.append(i.toDouble());
        }
    }

    for(int i = 0;i<functionList.size();i++)
    {
        if(!functionList.contains(functionList[i]))
        {
            if(openRecord)
            {
                record(inputText,"函数不存在");
            }
            ui->textBrowser->setText("函数不存在");
            stu = MainWindow::blank;
            return;
        }
        else
        {
            double res;
            int idx = functionMap[functionList[i]];
            QString merge = "FUNCTION_"+functionList[i]+"("+numberList[i]+")";
            qDebug()<<"函数中的数值"<<numberParseList[i];
            qDebug()<<"函数编号"<<idx;
            switch (idx)
            {
                case 0:
                    if(openRecord)
                    {
                        record(inputText,"函数不存在");
                    }
                    ui->textBrowser->setText("函数不存在");
                    stu = MainWindow::blank;
                    return;
                //sinx
                case 1:
                    res = sin(numberParseList[i]);
                    inputText = inputText.replace(merge, QString::number(res,'f',15));
                    break;
                //cosx
                case 2:
                    res = cos(numberParseList[i]);
                    inputText = inputText.replace(merge, QString::number(res,'f',15));
                    break;
                case 3:
                    res = tan(numberParseList[i]);
                    inputText = inputText.replace(merge, QString::number(res,'f',15));
                    break;
                case 4:
                    if(numberParseList[i] < -1 ||numberParseList[i] > 1)
                    {
                        qDebug()<<"函数中的数值"<<numberParseList[i];
                        if(openRecord)
                        {
                            record(inputText,"不在函数定义域");
                        }
                        ui->textBrowser->setText("不在函数定义域");
                        stu = MainWindow::blank;
                        return;
                    }
                    else
                    {
                        res = asin(numberParseList[i]);
                        inputText = inputText.replace(merge, QString::number(res,'f',15));
                        break;
                    }
                    break;
                case 5:
                    if(numberParseList[i] < -1.0 ||numberParseList[i] > 1.0)
                    {
                        if(openRecord)
                        {
                            record(inputText,"不在函数定义域");
                        }
                        ui->textBrowser->setText("不在函数定义域");
                        stu = MainWindow::blank;
                        return;
                    }
                    else
                    {
                        res = acos(numberParseList[i]);
                        inputText = inputText.replace(merge, QString::number(res,'f',15));
                        break;
                    }
                    break;
                case 6:
                    res = atan(numberParseList[i]);
                    inputText = inputText.replace(merge, QString::number(res,'f',15));
                    break;
                case 7:
                    res = exp(numberParseList[i]);
                    inputText = inputText.replace(merge, QString::number(res,'f',15));
                    break;
                case 8:
                    if(numberParseList[i] <= 0)
                    {
                        if(openRecord)
                        {
                            record(inputText,"不在函数定义域");
                        }
                        ui->textBrowser->setText("不在函数定义域");
                        stu = MainWindow::blank;
                        return;
                    }
                    else
                    {
                        res = log(numberParseList[i]);
                        inputText = inputText.replace(merge, QString::number(res,'f',15));
                        break;
                    }
                    break;
                case 9:
                    if(numberParseList[i] < 0)
                    {
                        if(openRecord)
                        {
                            record(inputText,"不在函数定义域");
                        }
                        ui->textBrowser->setText("不在函数定义域");
                        stu = MainWindow::blank;
                        return;
                    }
                    else
                    {
                        res = sqrt(numberParseList[i]);
                        inputText = inputText.replace(merge, QString::number(res,'f',15));
                        break;
                    }
                    break;
            }
        }
    }

    double res = calc(inputText);
    if(!zeroErr)
    {
        resultRes = res;
        ui->textBrowser->setText(QString::number(res));
        stu = MainWindow::result;
        if(openRecord)
        {
            record(hisText,QString::number(res));
        }
    }
    else
    {
        if(openRecord)
        {
            record(inputText,"除数不能为0");
        }
        ui->textBrowser->setText("除数不能为0");
    }

}

void MainWindow::on_pushButton_clicked()
{
    QString input = ui->textBrowser->toPlainText();
    if(stu == MainWindow::result)
    {
        ui->textEdit->setText(input);
        ui->textEdit->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
    }
    if(stu == MainWindow::help)ui->textEdit->setText(input);
}

void MainWindow::on_actionsize_triggered()
{
    QPalette pal = ui->textEdit->palette();
    QColor iniColor = pal.color(QPalette::Text);
    QColor color = QColorDialog::getColor(iniColor,this,"选择颜色");
    if(!color.isValid())return;
    pal.setColor(QPalette::Text,color);
    ui->textEdit->setPalette(pal);
    ui->textBrowser->setPalette(pal);
}

void MainWindow::on_actioncolar_triggered()
{
    bool ok = false;
    QFont iniFont=ui->textEdit->font();
    QFont font=QFontDialog::getFont(&ok,iniFont,this,"选择字体");
    if(!ok) return;
    ui->textBrowser->setFont(font);
    ui->textEdit->setFont(font);
}

void MainWindow::on_actiondenglu_triggered()
{

    login *lg = new login(this);
    lg->show();
}

int MainWindow::userlogin(QString name, QString password)
{
    db.open();
    if(!db.open())return -2;
    QSqlQuery query=QSqlQuery(db);
    query.prepare("select * from user where name = :sname");
    query.bindValue(":sname",name);
    query.exec();
    bool flag = false;
    while(query.next())
    {
        flag = true;
        if(query.value("password").toString() == password)
        {
            userId = query.value("id").toInt();
            userName = name;
            QSqlQuery subQuery=QSqlQuery(db);
            subQuery.prepare("select * from userconst where userid = :uid");
            subQuery.bindValue(":uid",userId);
            subQuery.exec();
            constNumbers.clear();
            updataConstDict();
            while(subQuery.next())
            {
                QString constName = subQuery.value("constname").toString();
                double constValue = subQuery.value("number").toDouble();
                if(constNumbers.contains(constName))
                {
                    constNumbers[constName] = constValue;
                }
                else
                {
                    constNumbers.insert(constName,constValue);
                }
            }
            return 1;
        }
    }
    if(!flag)return 0;
    else return -1;
}

int MainWindow::userReg(QString name, QString password)
{
    db.open();
    if(!db.open())return -2;
    QSqlQuery query=QSqlQuery(db);
    query.prepare("select * from user where name = :sname");
    query.bindValue(":sname",name);
    query.exec();
    if(query.next())return -1;
    QSqlQuery subQuery=QSqlQuery(db);
    QString sql = "insert into user(name,password) VALUES('"+name+"', '"+password+"')";
    subQuery.prepare(sql);
    if(!subQuery.exec())qDebug()<<"错误";
    query.prepare("select * from user where name = :sname");
    query.bindValue(":sname",name);
    query.exec();
    query.next();
    userId = query.value("id").toInt();
    userName = name;
    return 1;
}

void MainWindow::updataConstDict()
{
    if(db.open())
    {
        QSqlQuery globalConstInSql = db.exec("select * from globalconst");
        while(globalConstInSql.next())
        {
            QString constName = globalConstInSql.value("constname").toString();
            double constValue = globalConstInSql.value("number").toDouble();
            if(!constNumbers.contains(constName))constNumbers.insert(constName,constValue);
        }
    }
}

void MainWindow::on_actionzhuce_triggered()
{
    Reg *re = new Reg(this);
    re->show();
}

void MainWindow::on_actionuser_triggered()
{
    if(userId == -1)QMessageBox::information(this,"用户信息","未登录");
    else QMessageBox::information(this,"用户信息","用户名:"+userName+" 用户ID"+QString::number(userId));
}

void MainWindow::on_saveConst_clicked()
{
    if(stu != result)
    {
        QMessageBox::information(this,"常数存储","没有合法的运算结果");
        return;
    }
    if(userId == -1)
    {
        QMessageBox::information(this,"常数存储","未登录");
        return;
    }
    bool ok;
    QString text = QInputDialog::getText(this,"存储常数","输入常数的名称",QLineEdit::Normal,"",&ok);
    if(ok&&!text.isEmpty())
    {
        QSqlQuery query=QSqlQuery(db);
        query.prepare("select * from userconst where constname = :sname");
        query.bindValue(":sname",text);
        query.exec();
        if(query.next())
        {
            QMessageBox::information(this,"常数存储","常数已存在");
            return;
        }
        QString sql = "insert into userconst(userid,constname,number) VALUES("+QString::number(userId)+", '"+text+"',"+QString::number(resultRes)+")";
        query.prepare(sql);
        query.exec();
        constNumbers.insert(text,resultRes);
        QMessageBox::information(this,"常数存储","存储成功");
    }
    else
    {
        QMessageBox::information(this,"常数存储","无效输入");
    }
}

void MainWindow::on_constList_clicked()
{
    ConstTable *tb = new ConstTable(this);
    tb->show();
}

void MainWindow::on_addConst_clicked()
{
    ui->textEdit->textCursor().insertText("CONST()");
}

void MainWindow::on_actionyhxx_triggered()
{
    Histroy *his = new Histroy(this);
    his->show();
}

void MainWindow::on_actionauth_triggered()
{
    AboutCalc *about = new AboutCalc(this);
    about->show();
}

void MainWindow::on_function_clicked()
{
    FunctionInput *fun = new FunctionInput(this);
    fun->show();
}

QString reversalStr(QString &str)
{
    QString ret;
    for(QChar sz:str)
    {
        ret.push_front(sz);
    }
    return ret;
}

bool cmp(QString a,QString b)
{
    if(a.size()==b.size())return a>b;
    else return a.size()>b.size();
}

void MainWindow::on_longCalc_clicked()
{
    //适合输入大整数
    bool openRecord;
    if(userId == -1)openRecord = false;
    else openRecord = true;
    QString inputText = ui->textEdit->toPlainText();
    QRegExp longCalcNum("(\\d+)(\\+|-)(\\d+)");
    if(!longCalcNum.exactMatch(inputText))
    {
        if(openRecord)
        {
            record(inputText,"高精度运算适合长整型的运算，目前仅支持单次加法和减法运算");
        }
        ui->textBrowser->setText("高精度运算适合长整型的运算，目前仅支持单次加法和减法运算");
        stu = MainWindow::blank;
        return;
    }
    QString a = "";
    QString b = "";
    int pr = -1;
    bool flag = false;
    for(int i = 0;i<inputText.size();i++)
    {
        if(!flag)
        {
            if(inputText[i] != '+'&&inputText[i] != '-')
            {
                a += inputText[i];
            }
            else
            {
                if(inputText[i] == '+')pr = 1;
                else pr = 2;
                flag = true;
            }
        }
        else
        {
            b += inputText[i];
        }
    }
    QString a1 = reversalStr(a);
    QString b1 = reversalStr(b);
    QString c1 = "";
    //高精度加法运算
    if(pr == 1)
    {
        QString c = "";
        int t = 0;
        for(int i = 0;i<qMax(a1.size(),b1.size());i++)
        {
            if(i<a1.size())t+=int(QChar(a1[i]).toLatin1() - '0');
            if(i<b1.size())t+=int(QChar(b1[i]).toLatin1() - '0');
            c.append('0'+t%10);
            t /= 10;
        }
        if(t)c.append('1');
        c1 =  reversalStr(c);
        ui->textBrowser->setText(c1);
        return;
    }
    else
    {
        bool fl = false;
        QString c = "";
        if(a == b)
        {
            ui->textBrowser->setText("0");
            return;
        }
        if(!cmp(a,b))
        {
            fl = true;
            b1 = reversalStr(a);
            a1 = reversalStr(b);
        }
        int t = 0;
        for(int i = 0;i<a1.size();i++)
        {
            t+=int(QChar(a1[i]).toLatin1() - '0');
            if(i<b1.size())t-=int(QChar(b1[i]).toLatin1() - '0');
            c.append((t+10)%10+'0');
            if(t<0)t = -1;
            else t = 0;
        }
        while(c[c.size()-1] == '0'&&c.size()>1)c = c.remove(c.size()-1,1);
        if(fl)c1 = "-" + reversalStr(c);
        else c1 = reversalStr(c);
        ui->textBrowser->setText(c1);
        return;
    }
}
