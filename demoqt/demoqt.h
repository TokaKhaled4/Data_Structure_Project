#pragma once
#include <QtWidgets/QMainWindow>
#include<iostream>
#include "ui_demoqt.h"
#include <QTextEdit>
#include <QPushButton>
#include <qlineedit.h>
#include <QLabel>
#include <QPixmap>
#include "FrequencyWindow.h"
#include "RankingWindow.h"
#include <qcombobox.h>
class demoqt : public QMainWindow
{
    Q_OBJECT
public:
    demoqt(QWidget* parent = nullptr);
    ~demoqt();
    void upload_file();
    void onPushButtonClicked(); 
    void onPushCheck();
    void save_file();
    void split_current_text();
    void split_target_text();
    void onPushSave();
    void FindLocal();
    void FindGlobal();
    void onPushfreq();
    void onPushrank();
    void onPressEnter();
    void autocorrect();
    void autocomplete();
    void autocorrectsearch();
    void when_text_change();
    void autocompletesearch();

public slots:
    void onSuggestionSelected(const QString& suggestion);
    void onSuggestionSelectedTextBox(const QString& suggestionTB);
    int calculateWordCount(const QString& text);
    void onTextChanged();

private:
    Ui::demoqtClass ui;
    QTextEdit* textEdit;
    QPushButton* upload;
    QPushButton* check;
    QPushButton* save;
    QPushButton* frequency;
    QPushButton* ranking;
    QLineEdit* search;
    QLabel* logo;
    QLabel* count;
    QLabel* dots;
    QComboBox* suggestions;
    QComboBox* suggestionsTA;
    FrequencyWindow* frequencyWindow;   
    RankingWindow* rankingWindow;
};