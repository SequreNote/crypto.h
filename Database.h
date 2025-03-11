#ifndef DATABASE_H
#define DATABASE_H

#include "Note.h"
#include <QVector>
#include <QString>


class Database {
public:
    static void saveNote(const Note &note);
    static QVector<Note> loadNotes();
private:
    static const QString fileName;
};

#endif // DATABASE_H
