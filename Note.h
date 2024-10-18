//
// Created by nicco on 10/05/2024.
//

#ifndef DENOTE_NOTE_H
#define DENOTE_NOTE_H
using namespace std;
#include <Qstring>
#include <utility>

class Note {
public:
    Note(QString n,QString text):name(std::move(n)),text(std::move(text)){}
    Note(QString& n, bool f, bool b,QString& text):name(n),favourite(f),blocked(b),text(text){}

    QString getName() const {
        return name;
    }
    QString getText() const {
        return text;
    }
    void changeFavourite(bool newstatus){ favourite=newstatus; }
    void changeBlocked(bool newstatus){ blocked=newstatus; }
    bool isFavourite() const { return favourite; }

    bool isBlocked() const { return blocked; }

    void setName(const QString &n) { name = n; }

    void setText(const QString& txt){ text=txt; }
private:
    QString name;
    QString text="";
    bool favourite=false;
    bool blocked=false;
};


#endif //DENOTE_NOTE_H
