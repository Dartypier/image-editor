#include "InputDialog.h"

#include <QLabel>
#include <QSpinBox>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QDebug>

//heap is managed by parent Widget (no leak), implementation with smart ptr is not suitable in this case.
//objects are used over the scope of this class.

InputDialog::InputDialog(const QList<QString>& fields, int min, int max, int step, QWidget *parent) : QDialog(parent),
    fields(fields), min(min), max(max), step(step)
{

    QFormLayout* layout = new QFormLayout(this);

    for(const auto &field : fields){

        QLabel* label = new QLabel(field, this);
        QSpinBox* edit = new QSpinBox(this);
        edit->setMinimum(min);
        edit->setMaximum(max);
        edit->setSingleStep(step);
        edit->setValue(0);
        layout->addRow(label, edit);
        values << edit;
    }

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, this);

    layout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted,
            this, &InputDialog::accept);

    connect(buttonBox, &QDialogButtonBox::rejected,
            this, &InputDialog::reject);

    setLayout(layout);
}

QList<int> InputDialog::getFields(QWidget *parent, QList<QString> fields, int min, int max, int step, bool *ok)
{
    InputDialog* dialog = new InputDialog(fields, min, max, step, parent);

    QList<int> list;

    bool okInput = dialog->exec();

    if(okInput){
        *ok = okInput;
        foreach(auto value, dialog->values){
            list << value->value();
        }
    }

    dialog->deleteLater();
    return list;
}
