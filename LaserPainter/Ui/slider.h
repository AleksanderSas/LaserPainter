#ifndef SPLIDER_H
#define SPLIDER_H

#include <QObject>
#include <QScrollBar>
#include <QString>
#include <QLabel>
#include <QScrollBar>

class Slider : public QWidget
{
    Q_OBJECT
public:
    explicit Slider(QString prefix, QString sufix, int min, int max, unsigned int* value, QWidget *parent = nullptr);
    void setValue(int value);

signals:

public slots:
    void updateLabel(int value);

private:
    QString prefix, sufix;
    QLabel* moveScaleLabel;
    QScrollBar* bar;
    unsigned int* value;
};

#endif // SPLIDER_H
