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

    QString& getName() {
        return name;
    }
    QString& getText() {
        return text;
    }
    void setText(const QString& txt){
        text=txt;
    }
private:
    QString name;
    QString text="";

};


#endif //DENOTE_NOTE_H
