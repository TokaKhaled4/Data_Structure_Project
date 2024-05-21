#ifndef FREQUENCYWINDOW_H
#define FREQUENCYWINDOW_H
#include <QMainWindow>
#include <QTextEdit>
#include<QPushButton>
class FrequencyWindow : public QMainWindow {
    Q_OBJECT

public:
    FrequencyWindow(QWidget* parent = nullptr);
    void onPushsort();
    void onPushglobal();
    void split_current_text();
    void split_target_text();
    void pre_sorting();
    
   
private:
    QTextEdit* frequencyTextEdit;
    QPushButton* sort;
    QPushButton* global;
};

#endif


