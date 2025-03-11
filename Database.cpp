#include "Database.h"
#include <fstream>
#include <iostream>
#include <QFileDialog>


const QString Database::fileName = "notes.db";

QStringList Filename = QFileDialog::getOpenFileNames(
        this,
        tr("Choose your File"),
        "C://",
    if (!file) {
        cerr << "Ошибка: не удалось открыть файл для записи!\n";
        return;
    }

    file << note.getTitle() << '\n' 
         << note.getContent() << '\n';
    
    file.close();
}

QVector<Note> Database::loadNotes() {
    QVector<Note> notes;
    ifstream file(fileName);
    
    if (!file) {
        return notes;
    }

    QString title, content;
    while (readLine(file, title) && readLine(file, content)) {
        notes.emplace_back(title, content);
    }

    file.close();
    return notes;
}
