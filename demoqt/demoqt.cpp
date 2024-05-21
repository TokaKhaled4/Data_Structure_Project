#include "demoqt.h"
#include"qlineedit.h"
#include<QMessageBox>
#include <iostream>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QRegularExpression>
#include <QLabel>
#include <QPixmap>
#include <qlineedit.h>
#include<unordered_map>
#include<qcombobox.h>
#include<set>
#include<sstream>
#include<fstream>
#include <QTextStream>
#include <QFile>
#include <QSet>
#include <QTimer>
#include <QDebug>

using namespace std;
struct Words {
    unordered_map<string, int>mp_word;
    set < pair<int, string>, greater<pair<int, string>> >st_words;

};
Words search_local;
Words search_global;

void demoqt::split_current_text() {
    search_local.mp_word.clear();
    string str;
    ifstream myfile;
    myfile.open("currentFile.txt");
    while (getline(myfile, str)) {
        stringstream stream(str);
        while (stream >> str) {
            search_local.mp_word[str]++;
        }
    }
    myfile.close();
}
void demoqt::split_target_text() {
    search_global.mp_word.clear();
    string str;
    ifstream myfile;
    myfile.open("targetFile.txt");
    while (getline(myfile, str)) {
        stringstream stream(str);
        while (stream >> str) {
            search_global.mp_word[str]++;
        }
    }
    myfile.close();
}

demoqt::demoqt(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    this->setStyleSheet("background-color: #090C0B;");

    QFont textEditFont("Agency FB", 20);
    QFont buttonFont("Agency FB", 16);


    //text area
    textEdit = new QTextEdit(this);
    connect(textEdit, &QTextEdit::textChanged, this, &demoqt::autocomplete);
    textEdit->setStyleSheet(" background-color: #FFFFFF; border-radius: 30px; font-size: 30px; padding-top: 35px; padding-left: 15px");
    textEdit->setPlaceholderText("Write a text or upload a file...");
    textEdit->setGeometry(297, 201, 766, 362);
    textEdit->setFont(textEditFont);




    //upload button
    upload = new QPushButton("Upload", this);
    connect(upload, &QPushButton::clicked, this, &demoqt::onPushButtonClicked);
    upload->setStyleSheet("background-color: #53F293; border-radius: 25px; color: #000000; font-size: 30px; font-weight: bold");
    upload->setFont(buttonFont);
    upload->setGeometry(295, 600, 231, 70);

    //check button
    check = new QPushButton("Check", this);
    connect(check, &QPushButton::clicked, this, &demoqt::onPushCheck);
    check->setStyleSheet("background-color: #53F293; border-radius: 25px; color: #000000; font-size: 30px; font-weight: bold");
    check->setFont(buttonFont);
    check->setGeometry(565, 600, 231, 70);

    //save button
    save = new QPushButton("Save", this);
    connect(save, &QPushButton::clicked, this, &demoqt::onPushSave);
    save->setStyleSheet("background-color: #53F293; border-radius: 25px; color: #000000; font-size: 30px; font-weight: bold");
    save->setFont(buttonFont);
    save->setGeometry(832, 600, 231, 70);

    //frequency button
    frequency = new QPushButton("Frequency", this);
    connect(frequency, &QPushButton::clicked, this, &demoqt::onPushfreq);
    frequency->setStyleSheet("background-color: #FFFFFF; border-radius: 25px; color: #000000; font-size: 30px; font-weight: bold");
    frequency->setFont(buttonFont);
    frequency->setGeometry(580, 111, 231, 70);


    //ranking button
    ranking = new QPushButton("Ranking", this);
    connect(ranking, &QPushButton::clicked, this, &demoqt::onPushrank);
    ranking->setStyleSheet("background-color: #FFFFFF; border-radius: 25px; color: #000000; font-size: 30px; font-weight: bold");
    ranking->setFont(buttonFont);
    ranking->setGeometry(832, 111, 231, 70);

    //search bar
    search = new QLineEdit(this);
    connect(search, &QLineEdit::textChanged, this, &demoqt::autocompletesearch);
    connect(search, &QLineEdit::returnPressed, this, &demoqt::onPressEnter);
    connect(search, &QLineEdit::returnPressed, this, &demoqt::when_text_change);
    search->setPlaceholderText("Search for a word");
    search->setStyleSheet("background-color: #FFFFFF; border-radius: 20px; padding-left: 10px");
    search->setFont(buttonFont);
    search->setGeometry(295, 140, 260, 40);

    //add icon to search bar
    QIcon searchIcon("search_icon_ds.png");
    search->addAction(searchIcon, QLineEdit::LeadingPosition);

    //logo
    logo = new QLabel(this);
    QPixmap image("RUBIX1.png");
    int width = 247;
    int height = 83;
    QPixmap scaledImage = image.scaled(width, height, Qt::KeepAspectRatio);
    logo->setPixmap(image);
    logo->setGeometry(10, 25, width, height);

    //three dots 
    dots = new QLabel(this);
    QPixmap image1("Three_dots.png");
    int width1 = 280;
    int height1 = 100;
    QPixmap scaledImage1 = image1.scaled(width1, height1, Qt::KeepAspectRatio);
    dots->setPixmap(image1);
    dots->setGeometry(1175, 10, width1, height1);

    //combobox
    suggestions = new  QComboBox(this);
    suggestions->setEditable(true);
    suggestions->setGeometry(295, 180, 260, 20);
    suggestions->setStyleSheet("QComboBox QAbstractItemView {color: #FFFFFF}");
    connect(suggestions, QOverload<int>::of(&QComboBox::activated), [=]() {
        onSuggestionSelected(suggestions->currentText());
        });

    //combobox textedit
    suggestionsTA = new QComboBox(this);
    suggestionsTA->setEditable(true);
    suggestionsTA->setGeometry(25, 180, 260, 20);
    suggestionsTA->setStyleSheet("QComboBox QAbstractItemView {color: #FFFFFF}");
    connect(suggestionsTA, QOverload<int>::of(&QComboBox::activated), [=]() {
        onSuggestionSelectedTextBox(suggestionsTA->currentText());
        });

    // word counter
    count = new QLabel("Word count: 0", this);
    count->setGeometry(940, 505, 100, 30);
    count->setStyleSheet("background-color: white; color: black;");
    count->setFont(QFont("Agency FB", 16));
    count->show();
    connect(textEdit, &QTextEdit::textChanged, this, &demoqt::onTextChanged);
}

int demoqt::calculateWordCount(const QString& text) {
    QString trimmedText = text.trimmed();
    int wordCount = trimmedText.split(" ", Qt::SkipEmptyParts).size();
    return wordCount;
}
void demoqt::onTextChanged() {
    int wordCount = calculateWordCount(textEdit->toPlainText().trimmed());
    count->setText("Word count: " + QString::number(wordCount));
}

void demoqt::onSuggestionSelected(const QString& suggestion) {
    search->setText(suggestion);
}
void demoqt::onSuggestionSelectedTextBox(const QString& suggestionTB) {
    QString currentText = textEdit->toPlainText().trimmed();
    int lastSpaceIndex = currentText.lastIndexOf(' ');
    if (lastSpaceIndex != -1) {
        QString newText = currentText.left(lastSpaceIndex + 1) + suggestionTB + " ";
        textEdit->setText(newText);
    }
    else {
        textEdit->setText(suggestionTB + " ");
    }
}

void demoqt::upload_file()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open File", "", "Text files (*.txt)");

    if (!filePath.isEmpty()) {

        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QString fileContent = in.readAll();


            textEdit->setText(fileContent);

            file.close();
        }
    }

}
void demoqt::onPushButtonClicked() {
    upload_file();

}

void demoqt::autocorrect() {
    QString content = textEdit->toPlainText();

    QTextCursor clearCursor(textEdit->document());
    clearCursor.select(QTextCursor::Document);
    clearCursor.setCharFormat(QTextCharFormat());

    QStringList words = content.split(" ", Qt::SkipEmptyParts);


    QFile file("wiki.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Unable to open predefined words file.");
        return;
    }
    QTextStream in(&file);
    QStringList predefinedWords;
    while (!in.atEnd()) {
        QString word = in.readLine().trimmed();
        if (!word.isEmpty()) {
            predefinedWords << word;
        }
    }
    file.close();
    QTextCursor cursor(textEdit->document());
    QTextCharFormat format;
    format.setUnderlineStyle(QTextCharFormat::SpellCheckUnderline);
    format.setUnderlineColor(Qt::red);
    for (const QString& word : words) {
        if (!predefinedWords.contains(word, Qt::CaseInsensitive)) {
            QTextCursor highlightCursor = cursor;
            while (!highlightCursor.isNull() && !highlightCursor.atEnd()) {
                highlightCursor = textEdit->document()->find(word, highlightCursor);
                if (!highlightCursor.isNull()) {
                    highlightCursor.mergeCharFormat(format);
                }
            }
        }
    }

}
void demoqt::onPushCheck() {
    autocorrect();
}

void demoqt::save_file()
{
    QString targetFilename = "targetFile.txt";
    QString currentFilename = "currentFile.txt";


    QFile targetFile(targetFilename);
    if (!targetFile.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Error opening target file.");
        return;
    }

    QString contentToAppend = textEdit->toPlainText();
    QTextStream targetOut(&targetFile);
    targetOut << contentToAppend;
    targetOut << "\n";
    targetFile.close();



    QFile currentFile(currentFilename);
    if (!currentFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Error opening current file.");
        return;
    }

    QTextStream currentOut(&currentFile);
    currentOut << contentToAppend;
    currentFile.close();

    QMessageBox::information(this, "Success", "<font color='white'>  Content Saved Successfully.</font>");
}
void demoqt::onPushSave() {
    save_file();

}

void demoqt::FindLocal() {

    split_current_text();

    QString wordToFind = search->text();


    std::string wordToFindStdString = wordToFind.toStdString();

    if (search_local.mp_word.find(wordToFindStdString) != search_local.mp_word.end()) {
        int frequency = search_local.mp_word[wordToFindStdString];
        QMessageBox::information(this, "Word Found", QString("<font color='white'> The word '%1' exists  with local frequency %2.</font>").arg(wordToFind).arg(frequency));

    }
    else {
        QMessageBox::information(this, "Word Not Found", QString("<font color='white'> The word '%1' does not exist in the current paragraph.</font>").arg(wordToFind));
    }

}
void demoqt::FindGlobal() {
    split_target_text();

    QString wordToFind = search->text(); 

  
    std::string wordToFindStdString = wordToFind.toStdString();

  
    if (search_global.mp_word.find(wordToFindStdString) != search_global.mp_word.end()) {
       
        int frequency = search_global.mp_word[wordToFindStdString];
        QMessageBox::information(this, "Word Found Globally", QString("<font color='white'> The word '%1' exists with global frequency %2.</font>").arg(wordToFind).arg(frequency));
    }
    else {
       
        QMessageBox::information(this, "Word Not Found Globally", QString("<font color='white'> The word '%1' does not exist in your previous paragraphs.</font>").arg(wordToFind));
    }
}
void demoqt::onPressEnter() {
    FindLocal();
    FindGlobal();
}

void demoqt::autocorrectsearch() {
    QString content = search->text().trimmed();

    QFile file("wiki.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Unable to open predefined words file.");
        return;
    }

    QTextStream in(&file);
    QStringList predefinedWords;
    while (!in.atEnd()) {
        QString word = in.readLine().trimmed();
        if (!word.isEmpty()) {
            predefinedWords << word;
        }
    }
    file.close();

    if (!predefinedWords.contains(content, Qt::CaseInsensitive)) {
        QMessageBox::warning(this, "Warning", "<font color='red'> The entered word is incorrect.</font>");

    }


}
void demoqt::when_text_change() {
    autocorrectsearch();
}

void demoqt::autocompletesearch()
{
    QString searchText = search->text().trimmed();
    if (searchText.isEmpty()) {
        suggestions->clear();
        return;
    }

    suggestions->clear();

    QFile file("wiki.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "Error", "Unable to open dictionary file.");
        return;
    }

    QTextStream in(&file);
    QList<QString> dictionary;
    while (!in.atEnd()) {
        QString sug = in.readLine().trimmed();
        dictionary.append(sug);
    }
    file.close();
    QList<QString> matchingSuggestions;
    for (const QString& sug : dictionary) {
        if (sug.contains(searchText, Qt::CaseInsensitive) && sug.startsWith(searchText, Qt::CaseInsensitive)) {
            matchingSuggestions.append(sug);
        }
    }

    for (const QString& sug : matchingSuggestions) {
        suggestions->addItem(sug);
    }
    suggestions->showPopup();
}
void demoqt::autocomplete() {
    QString searchText = textEdit->toPlainText().trimmed();

    if (searchText.isEmpty()) {
        suggestionsTA->clear();
        return;
    }

    QFile file("wiki.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Unable to open dictionary file.");
        return;
    }

    QTextStream in(&file);
    QList<QString> dictionary;
    while (!in.atEnd()) {
        QString sug = in.readLine().trimmed();
        dictionary.append(sug);
    }
    file.close();

    suggestionsTA->clear();

    QList<QString> matchingSuggestions;
    QStringList words = searchText.split(" ", Qt::SkipEmptyParts);

    for (const QString& word : words) {
        matchingSuggestions.clear();
        for (const QString& sug : dictionary) {
            if (sug.startsWith(word, Qt::CaseInsensitive)) {
                matchingSuggestions.append(sug);
            }
        }

        suggestionsTA->clear();
        for (const QString& suggestion : matchingSuggestions) {
            suggestionsTA->addItem(suggestion);
        }
        suggestionsTA->showPopup();
    }
}

void demoqt::onPushfreq()
{
    frequencyWindow = new FrequencyWindow(this);
    frequencyWindow->show();
}
void demoqt::onPushrank()
{
    rankingWindow = new RankingWindow(this);
    rankingWindow->show();
}


demoqt::~demoqt()
{
    std::ofstream ofs("currentFile.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();

}