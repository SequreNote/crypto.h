#ifndef NOTE_H
#define NOTE_H

#include <string>

using namespace std;

class Note {
public:
    Note(const string &title, const string &content);

    string getTitle() const;
    string getContent() const;

private:
    string title;
    string content;
};

#endif // NOTE_H
