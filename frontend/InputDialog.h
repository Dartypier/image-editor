#ifndef MULTIPLEINPUTDIALOG_H
#define MULTIPLEINPUTDIALOG_H

#include <QSpinBox>
#include <QDialog>

class QLabel;

class InputDialog : public QDialog
{
    Q_OBJECT
public:
    explicit InputDialog(const QList<QString>& fields, int min=0, int max=100, int step=1, QWidget *parent = nullptr);

    static QList<int> getFields(QWidget *parent, QList<QString> fields, int min, int max, int step, bool *ok);

private:
    QList<QSpinBox* > values;
    QList<QString> fields;
    int min;
    int max;
    int step;
};

#endif // MULTIPLEINPUTDIALOG_H
