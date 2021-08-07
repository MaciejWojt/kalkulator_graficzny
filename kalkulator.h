#ifndef KALKULATOR_H
#define KALKULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class kalkulator; }
QT_END_NAMESPACE

class kalkulator : public QMainWindow
{
    Q_OBJECT

public:
    kalkulator(QWidget *parent = nullptr);
    ~kalkulator();

private:
    Ui::kalkulator *ui;

private slots:
    void NumPressed();
    void MathPressed();
    void EqualPressed();
    void ChangeSignPressed();
    void CleanPressed();
};
#endif // KALKULATOR_H
