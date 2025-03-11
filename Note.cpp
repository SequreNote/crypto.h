#include "Note.h"
#include <iostream>

using namespace std;

Note::Note(const string &title, const string &content)
    : title(title), content(content) {}

string Note::getTitle() const {
    return title;
}

string Note::getContent() const {
    return content;
}
