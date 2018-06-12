#include "widget.h"
#include <chrono>
#include <QDebug>
#include <QMessageBox>

bool check(QList<int> field){
    int result = 0;

    for(int i = 0; i < 15; i++)
        for(int j = i + 1; j < 15; j++)
            result += (field[i] > field[j]);

    return (result % 2 == 0);
}

Widget::Widget(QWidget *parent) : QWidget(parent){
    QList<int> field = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    do{
        int seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(field.begin(), field.end(), std::default_random_engine(seed));
    }while(!check(field)); field.append(16);

    layout = new QGridLayout;
    for(int i = 0; i < 16; i++)
        button[i] = new QPushButton(QString::number(field[i])),
        button[i] -> setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred),
        button[i] -> setProperty("position", i),
        connect(button[i], SIGNAL(clicked()), this, SLOT(move())),
        layout -> addWidget(button[i], i / 4, i % 4),
        correctNum += (i + 1 == field[i]);

    button[15] -> hide(); resize(200, 320); setLayout(layout);
    QWidget::setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
}
Widget::~Widget(){

}

void Widget::move() {
    int p = QObject::sender() -> property("position").toInt();
    int n = QObject::sender() -> property("text").toInt();
    int t = abs(p - currentZero), dCorrect = 0;

    dCorrect -= (p + 1 ==  n) + (currentZero + 1 == 16);
    dCorrect += (p + 1 == 16) + (currentZero + 1 ==  n);

    if(t == 1 || t == 4){
        button[currentZero] -> setText(QString::number(n));
        button[currentZero] -> show();

        button[p] -> setText("16"); button[p] -> hide();

        currentZero = p; correctNum += dCorrect; turnsNum++;
    }

    if(correctNum == 16)
        QMessageBox::about(this, tr("Win! Turns: %1").arg(turnsNum), tr("<b>You completed the game!</b>"));
}
