#include "kalkulator.h"
#include "ui_kalkulator.h"

double calcVal = 0.0;
bool sumTrigger = false;
bool subTrigger = false;
bool mulTrigger = false;
bool divTrigger = false;
bool potTrigger = false;
bool pierTrigger = false;

kalkulator::kalkulator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::kalkulator)
{
    ui->setupUi(this);


    ui->lineEdit->setText(QString::number(calcVal));
    QPushButton * NumButtons[10];
    for (int i = 0; i < 10; ++i) {
        QString butName = "guzik" + QString::number(i);
        NumButtons[i] = kalkulator::findChild<QPushButton *>(butName);
        connect(NumButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }

    connect(ui->suma, SIGNAL(released()), this, SLOT(MathPressed()));
    connect(ui->roznica, SIGNAL(released()), this, SLOT(MathPressed()));
    connect(ui->iloczyn, SIGNAL(released()), this, SLOT(MathPressed()));
    connect(ui->iloraz, SIGNAL(released()), this, SLOT(MathPressed()));
    connect(ui->potega, SIGNAL(released()), this, SLOT(MathPressed()));
    connect(ui->pierwiastek, SIGNAL(released()), this, SLOT(MathPressed()));

    connect(ui->wynik, SIGNAL(released()), this, SLOT(EqualPressed()));

    connect(ui->zmianaZnaku, SIGNAL(released()), this, SLOT(ChangeSignPressed()));
    connect(ui->cls, SIGNAL(released()), this, SLOT(CleanPressed()));

}

kalkulator::~kalkulator()
{
    delete ui;
}

void kalkulator::NumPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->lineEdit->text();
    if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)){
        ui->lineEdit->setText(butVal);
    }
    else{
        QString newVal = displayVal + butVal;
        double dblNewVal = newVal.toDouble();
        ui->lineEdit->setText(QString::number(dblNewVal,'g',16));
    }
}

void kalkulator::MathPressed(){
    sumTrigger = false;
    subTrigger = false;
    mulTrigger = false;
    divTrigger = false;
    potTrigger = false;
    pierTrigger = false;
    QString displayVal = ui->lineEdit->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    if(QString::compare(butVal,"+",Qt::CaseInsensitive) == 0){
        sumTrigger = true;
    }
    else if(QString::compare(butVal,"-",Qt::CaseInsensitive) == 0){
        subTrigger = true;
    }
    else if(QString::compare(butVal,"*",Qt::CaseInsensitive) == 0){
        mulTrigger = true;
    }
    else if(QString::compare(butVal,"/",Qt::CaseInsensitive) == 0){
        divTrigger = true;
    }
    else if(QString::compare(butVal,"x^y",Qt::CaseInsensitive) == 0){
        potTrigger = true;
    }
    else{
        pierTrigger = true;
    }
    ui->lineEdit->setText("");

}
double pot(double x,double y){
    double output = 1;
    for(int i = 1; i<=y; i++){
        output = output*x;
    }
    return output;
}
double pier(double x){
    for(int i=1;i<x;i++){
        if(i*i==x){
            return i;
        }
    }
    return 0;
}
void kalkulator::EqualPressed(){
    double wynik = 0.0;
    QString displayVal = ui->lineEdit->text();
    double dblDisplayVal = displayVal.toDouble();
    if(sumTrigger || subTrigger || mulTrigger || divTrigger || potTrigger || pierTrigger){
        if(sumTrigger){
            wynik = calcVal + dblDisplayVal;
        }
        else if(subTrigger){
            wynik = calcVal - dblDisplayVal;
        }
        else if(mulTrigger){
            wynik = calcVal * dblDisplayVal;
        }
        else if(divTrigger){
            wynik = calcVal / dblDisplayVal;
        }
        else if(potTrigger){
            wynik = pot(calcVal,dblDisplayVal);
        }
        else{
            wynik = pier(calcVal); //trzeba na końcu kliknąć przycisk =
        }
    }
    if((QString::number(wynik) == "inf") || (QString::number(wynik)=="-inf")){
        ui->lineEdit->setText("Nie można dzielić przez zero‬");
    }
    else{
        ui->lineEdit->setText(QString::number(wynik));
    }
}
void kalkulator::ChangeSignPressed(){
    QString displayVal = ui->lineEdit->text();
    double dblDisplayVal = displayVal.toDouble();
    double dblDisplayValSign = -1 * dblDisplayVal;
    ui->lineEdit->setText(QString::number(dblDisplayValSign));

}
void kalkulator::CleanPressed(){
    ui->lineEdit->setText("");
}
