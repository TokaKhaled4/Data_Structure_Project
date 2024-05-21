#include "frequencywindow.h"
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
struct Words {
    unordered_map<string, int>mp_word;
    set < pair<int, string>, greater<pair<int, string>> >st_words; 
   
};
Words words;


void FrequencyWindow::split_current_text() { 
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
void FrequencyWindow::split_target_text() { 
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
void FrequencyWindow::pre_sorting() {
    words.st_words.clear();
    pair<int, string>pr;
    for (const auto& pair : words.mp_word) {   
        pr.first = pair.second;          
        pr.second = pair.first;
        words.st_words.insert(pr);
    }
}

FrequencyWindow::FrequencyWindow(QWidget* parent) : QMainWindow(parent) {
    this->setStyleSheet("background-color: #000000;");

    setWindowTitle("Frequency Window");
    resize(400, 300);

    // Create a text edit widget
    frequencyTextEdit = new QTextEdit(this);
    frequencyTextEdit->setStyleSheet(" background-color: #FFFFFF; border-radius: 30px; font-size: 30px; padding-top: 20px; padding-left: 40px");
    frequencyTextEdit->setGeometry(297, 150, 990, 370);
    frequencyTextEdit->setReadOnly(true); 

    QFont textEditFont("Agency FB", 20);
    frequencyTextEdit->setFont(textEditFont);
    QFont buttonFont("Agency FB", 16);

    //sort button
    sort = new QPushButton("Sort", this);
    sort->setStyleSheet("background-color: #53F293; border-radius: 25px; color: #000000; font-size: 30px;font-weight: bold");
    connect(sort, &QPushButton::clicked, this, &FrequencyWindow::onPushsort);
    sort->setFont(buttonFont);
    sort->setGeometry(295, 600, 231, 70);

    //global button
    global = new QPushButton("Global", this);
    global->setStyleSheet("background-color: #53F293; border-radius: 25px; color: #000000; font-size: 30px;font-weight: bold");
    connect(global, &QPushButton::clicked, this, &FrequencyWindow::onPushglobal);
    global->setFont(buttonFont);
    global->setGeometry(1080, 600, 231, 70);

    split_current_text();
    pre_sorting();

    QString text = " ";
    text += "\t\t\t\t-->The Local frequency not sorted<--\n\n";
    for (const auto& pair : words.mp_word) {
        QString word = QString::fromStdString(pair.first);
        int frequency = pair.second;
        if (frequency > 0) {
            text += word + "\t" + "--->\t" + QString::number(frequency) + "\n";
        }
    }
    frequencyTextEdit->setText(text);
}
void FrequencyWindow::onPushsort()
{
    QString text = " ", text2 = " ";
    text += "\t\t\t\t-->The frequency sorted<--\n\n";
    for (const auto& pair : words.st_words) {
        QString word = QString::fromStdString(pair.second);
        int frequency = pair.first;
        if (frequency > 0) {
            text += word + "\t" + "--->\t" + QString::number(frequency) + "\n";
        }
    }
    frequencyTextEdit->setText(text + text2);
}
void FrequencyWindow::onPushglobal()
{
    split_target_text();
    pre_sorting();
    QString text = " ";
    text += "\t\t\t\t-->The Global frequency not sorted<--\n\n";
    for (const auto& pair : words.mp_word) {
        QString word = QString::fromStdString(pair.first);
        int frequency = pair.second;
        if (frequency > 0) {
            text += word + "\t" + "--->\t" + QString::number(frequency) + "\n";
        }
    }
    frequencyTextEdit->setText(text);
}