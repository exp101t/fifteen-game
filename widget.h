#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QPushButton>
#include <QGridLayout>

class Widget : public QWidget{
    Q_OBJECT

    private slots:
        void move();

    private:
        int correctNum  =  0;
        int currentZero = 15;
        int turnsNum    =  0;

        QPushButton* button[16];
        QGridLayout* layout;

    public:
        Widget(QWidget *parent = 0);
        ~Widget();
};

#endif // WIDGET_H
