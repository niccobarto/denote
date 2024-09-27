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

    bool isFavourite() const {
        return favourite;
    }

    bool isLocked() const {
        return locked;
    }

    void setName(const QString &n) {
        name = n;
    }

    void setText(const QString& txt){
        text=txt;
    }
private:
    QString name;
    QString text="";
    bool favourite=false;
    bool locked=false;
};


#endif //DENOTE_NOTE_H
