//
// Created by nicco on 10/05/2024.
//

#ifndef DENOTE_NOTE_H
#define DENOTE_NOTE_H
using namespace std;
#include <Qstring>

class Note {
public:
    Note(QString n):name(n){};
private:
    QString name;
    string text="";

};


#endif //DENOTE_NOTE_H
