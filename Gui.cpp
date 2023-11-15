#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QColor>
#include "Vole_Machine.h"
class Vole_Machine_Gui: public Machine,public QWidget
{
private:
    QGridLayout *mainLayout;
    QTextEdit *Register_text;
    QTextEdit *Memory_text;
    QTextEdit *instruction_text;
    QGroupBox *Register_group;
    QGroupBox *Memory_group;
    QGroupBox *instruction_group;
    QPushButton *Run_button;
    QLineEdit *Run_Box;
    QHBoxLayout *Register_Box;
    QHBoxLayout *Memory_Box;
    QHBoxLayout *instruction_Box;
    void setRegisterValues()
    {
        Register_text->clear();
        for (int i = 0; i < 16; ++i) {
            stringstream hexIndex;
            hexIndex<<hex<<i;

            Register_text->append(QString::fromStdString((hexIndex.str())+"     "+
                                                getRegister(hexIndex.str())));
            Register_text->append(QString::fromStdString("----------"));
        }
        Register_group->setStyleSheet("font:bold 18px;background:black");
        Register_text->setStyleSheet("Background:white;color:Black;font:bold 18px");
    }
    void setMemoryValues()
    {
        Memory_text->clear();
        for (int i = 0; i < 256; ++i) {
            stringstream hexIndex;
            hexIndex<<hex<<i;

            Memory_text->append(QString::fromStdString((hexIndex.str())+"     "+
                                                         getMemory(hexIndex.str())));
            Memory_text->append(QString::fromStdString("----------"));
        }
        Memory_group->setStyleSheet("font:bold 18px;background:black");
        Memory_text->setStyleSheet("Background:white;color:Black;font:bold 18px");
    }
    void GetInput()
    {
        string in=Run_Box->text().toStdString();
        if(Run_Box->text().size()!=4)
        {
            QMessageBox *Error=new QMessageBox(this);
            Error->setText("the input is not valid");
            Error->setWindowTitle("Error!");
            Error->setStyleSheet("background:white;color:black;font:bold 20px;");
            Error->show();
            Run_Box->setText(u8"");
            return;
        }
        Run_Box->setText(u8"");
        vector<string>tmp;
        for (int i = 0; i < 4; ++i) {
            string s;s.push_back(in[i]);
            tmp.push_back(s);
        }
        B.push_back(tmp);
        stringstream hexIndex;
        hexIndex<<hex<<counter_sz;
        instruction_text->append(QString::fromStdString(hexIndex.str()+"   "+in));
        instruction_text->append(QString::fromStdString("----------"));
        counter_sz++;
        for (; counter < counter_sz; ++counter) {
            int i=stoi(B[counter][0],0,16);
            Instruction(i);
            if(Exit)
                QCoreApplication::quit();
        }
        setRegisterValues();
        setMemoryValues();
    }
    QColor mixColors(const QColor& color1, const QColor& color2, double ratio)
    {
        ratio = qBound(0.0, ratio, 1.0);
        int red = color1.red() + (color2.red() - color1.red()) * ratio;
        int green = color1.green() + (color2.green() - color1.green()) * ratio;
        int blue = color1.blue() + (color2.blue() - color1.blue()) * ratio;

        return QColor(red, green, blue);
    }
public:
    Vole_Machine_Gui(QWidget*parent=nullptr):Machine(16,"00",256,"00"),QWidget(parent)
    {
        this->setGeometry(200,50,1000,700);

        mainLayout=new QGridLayout(this);
        Run_button=new QPushButton("Run");
        Run_Box=new QLineEdit;
        mainLayout->addWidget(Run_Box,1,0);
        mainLayout->addWidget(Run_button,1,1);
        mainLayout->setRowStretch(0,1);
        mainLayout->setRowStretch(2,1);
        Register_group=new QGroupBox("Register Values");
        Register_Box=new QHBoxLayout(Register_group);
        Register_text=new QTextEdit;
        Register_text->setReadOnly(true);
        Register_Box->addWidget(Register_text);
        mainLayout->setRowStretch(3,4);
        mainLayout->addWidget(Register_group,3,2);
        instruction_group=new QGroupBox("instruction Values");
        instruction_Box=new QHBoxLayout(instruction_group);
        instruction_text=new QTextEdit;
        mainLayout->setColumnStretch(1,1);
        instruction_text->setReadOnly(true);
        instruction_Box->addWidget(instruction_text);
        mainLayout->addWidget(instruction_group,3,0);
        mainLayout->setColumnStretch(2,2);
        Memory_group=new QGroupBox("Memory Values");
        Memory_Box=new QHBoxLayout(Memory_group);
        Memory_text=new QTextEdit;
        Memory_text->setReadOnly(true);
        Memory_Box->addWidget(Memory_text);
        mainLayout->addWidget(Memory_group,3,4);
        mainLayout->setColumnStretch(3,1);
        connect(Run_button,&QPushButton::clicked,this,&Vole_Machine_Gui::GetInput);
        setRegisterValues();
        setMemoryValues();
        //colors
        QColor color1(Qt::black);
        QColor color2(Qt::red);
        QColor mixedColor = mixColors(color1, color2, 0.7);
        Run_button->setStyleSheet(QString("font:bold 18px;background-color: %1;").arg(mixedColor.name()));
        Run_Box->setStyleSheet("background:white;font:bold 18px;color:Black");
        instruction_group->setStyleSheet(QString("font:bold 18px;background-color: %1;").arg(mixedColor.name()));
        instruction_text->setStyleSheet("font:bold 18px;color:black;background:white");
        QColor color3(Qt::black);
        QColor color4(Qt::white);
        QLabel *title=new QLabel("Vole Machine");
        QLabel *copyRight=new QLabel("© 2023 YoussefKarem-ArsanyNageh-JuliGeorge. All rights reserved.");
        copyRight->setStyleSheet("color:Black;font:bold 15px");
        mainLayout->addWidget(title,0,2);
        mainLayout->addWidget(copyRight,4,4);
        title->setStyleSheet("color:black;font:bold 60px");
        mixedColor= mixColors(color3, color4, 0.65);
        this->setStyleSheet(QString("background-color: %1;").arg(mixedColor.name()));
        this->setWindowTitle("Vole_Machine");
        this->setLayout(mainLayout);
        this->show();
    }

};
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Vole_Machine_Gui test;
    return app.exec();
}
