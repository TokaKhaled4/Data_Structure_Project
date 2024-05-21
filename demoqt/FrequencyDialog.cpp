#include "FrequencyDialog.h"
#include <QVBoxLayout>

FrequencyDialog::FrequencyDialog(QWidget* parent)
    : QDialog(parent)
{
    outputTextEdit = new QTextEdit(this);
    outputTextEdit->setReadOnly(true);
    outputTextEdit->setStyleSheet("background-color: #FFFFFF; border-radius: 10px; font-size: 16px;");

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(outputTextEdit);
    setLayout(layout);
}

void FrequencyDialog::setOutput(const QString& output)
{
    outputTextEdit->setText(output);
}

