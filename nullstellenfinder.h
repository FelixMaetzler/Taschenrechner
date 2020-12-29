#ifndef NULLSTELLENFINDER_H
#define NULLSTELLENFINDER_H

#include <QMainWindow>
#include "komplex.h"

namespace Ui {
class Nullstellenfinder;
}

class Nullstellenfinder : public QMainWindow
{
    Q_OBJECT

public:
    explicit Nullstellenfinder(QWidget *parent = nullptr);
    ~Nullstellenfinder();

private:
    Ui::Nullstellenfinder *ui;

private slots:

};
QVector<komplex> abcFormel(QVector<double>);
QVector<komplex> cardano(QVector<double>);
#endif // NULLSTELLENFINDER_H
