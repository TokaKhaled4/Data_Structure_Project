#ifndef FREQUENCYDIALOG_H
#define FREQUENCYDIALOG_H

#include <QDialog>
#include <QTextEdit>

class FrequencyDialog : public QDialog
{
    Q_OBJECT

public:
    FrequencyDialog(QWidget* parent = nullptr);
    void setOutput(const QString& output);

private:
    QTextEdit* outputTextEdit;
};

#endif // FREQUENCYDIALOG_H


