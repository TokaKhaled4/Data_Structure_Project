#include "RankingWindow.h"
#include <iostream>
#include<QMessageBox>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QRegularExpression>
#include <qlineedit.h>
#include <QLabel>
#include <QPixmap>
#include<QPushButton>
#include<unordered_map>
#include<set>
#include<sstream>
#include<fstream>

using namespace std;
struct Word {
    unordered_map<string, int>mp_word;
    set < pair<int, string>, greater<pair<int, string>> >st_words; //switch string with integer
    set<pair<int, string>>st_rank;
    
};
Word words;


void RankingWindow::split_current_text() { //function to split the text to words from current_file
    words.mp_word.clear();
    string str;
    ifstream myfile;
    myfile.open("currentFile.txt");
    while (getline(myfile, str)) {
        stringstream stream(str);
        while (stream >> str) {
            transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
                return std::tolower(c);
                });
            words.mp_word[str]++;
        }
    }
    myfile.close();
}
void RankingWindow::split_target_text() { //function to split the text to words from target_file
    words.mp_word.clear();
    string str;
    ifstream myfile;
    myfile.open("targetFile.txt");
    while (getline(myfile, str)) {
        stringstream stream(str);
        while (stream >> str) {
            transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
                return std::tolower(c);
                });
            words.mp_word[str]++;
        }
    }
    myfile.close();
}
void RankingWindow::pre_sorting() {
    words.st_words.clear();
    pair<int, string>pr;
    for (const auto& pair : words.mp_word) {   //extract the data from map to set for sorting
        pr.first = pair.second;           //switch !!!!!!
        pr.second = pair.first;
        words.st_words.insert(pr);
    }
}
void RankingWindow::store_rank() {
    pair<int, string>pr;
    words.st_rank.clear();
    int count = 1;
    for (const auto& pair : words.st_words) {
        if (pair.first == 0) {
            continue;
        }
        else {
            pr.first = count;
            pr.second = pair.second;
            words.st_rank.insert(pr);
            count++;
        }
    }
}

RankingWindow::RankingWindow(QWidget* parent) : QMainWindow(parent) {
    this->setStyleSheet("background-color: #000000;");

    setWindowTitle("Ranking Window");
    resize(400, 300);

    // Create a text edit widget
    rankingTextEdit = new QTextEdit(this);
    rankingTextEdit->setStyleSheet(" background-color: #FFFFFF; border-radius: 30px; font-size: 30px; padding-top: 20px; padding-left: 40px");
    rankingTextEdit->setGeometry(297, 150, 990, 370);
    rankingTextEdit->setReadOnly(true); // Set the text edit as read-only

    QFont textEditFont("Agency FB", 20);
    rankingTextEdit->setFont(textEditFont);
    QFont buttonFont("Agency FB", 16);

    globalrank = new QPushButton("Global", this);
    globalrank->setStyleSheet("background-color: #53F293; border-radius: 25px; color: #000000; font-size: 30px;font-weight: bold");
    connect(globalrank, &QPushButton::clicked, this, &RankingWindow::onPushglobalrank);
    globalrank->setFont(buttonFont);
    globalrank->setGeometry(295, 600, 231, 70);

    split_current_text();
    pre_sorting();
    store_rank();
    QString text = " ";
    text += "\t\t\t\t-->The Local Rank<--\n\n";
    for (const auto& pair : words.st_rank) {
        QString word = QString::fromStdString(pair.second);
        int rank = pair.first;
        if (rank > 0) {
            text += QString::number(rank) + ")\t" + word + "\n";
        }
    }
    rankingTextEdit->setText(text);

}
void RankingWindow::onPushglobalrank()
{
    split_target_text();
    pre_sorting();
    store_rank();
    QString text = " ";
    text += "\t\t\t\t-->The Global Rank<--\n\n";
    for (const auto& pair : words.st_rank) {
        QString word = QString::fromStdString(pair.second);
        int rank = pair.first;
        if (rank > 0) {
            text += QString::number(rank) + ")\t" + word + "\n";
        }
    }
    rankingTextEdit->setText(text);
}
