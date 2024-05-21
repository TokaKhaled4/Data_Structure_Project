#ifndef RANKINGWINDOW_H
#define RANKINGWINDOW_H
#include <QMainWindow>
#include <QTextEdit>
#include<QPushButton>
static class RankingWindow :public QMainWindow {
    Q_OBJECT

public:
    RankingWindow(QWidget* parent = nullptr);
    void onPushglobalrank();
    void split_current_text();
    void split_target_text();
    void pre_sorting();
    void store_rank();
private:
    QTextEdit* rankingTextEdit;
    QPushButton* globalrank;
};

#endif

