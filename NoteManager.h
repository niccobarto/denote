//
// Created by nicco on 10/05/2024.
//

#ifndef DENOTE_NOTEMANAGER_H
#define DENOTE_NOTEMANAGER_H

#include <list>
#include "Note.h"
#include <QTextStream>
#include <QFile>
#include <fstream>
#include <iostream>
using namespace std;

class NoteManager {

public:
    bool createNewNote(const QString& name);
    void deleteNote(const QString& name);
    void saveNote(const QString& name,const QString& text);
    QString loadNote(const QString& filepath);
    bool renameNote(const QString& oldname,const QString &newname);
    void changeFavouriteStatus(const QString& name);
    void changeBlockedStatus(const QString& name);
    bool isNameUsed(const QString& name);
    QStringList getSimilarNotes(const QString& searchtext);
    QStringList getDefaultNoteList();
    Note* getNote(const QString& name);

    ~NoteManager();
private:
    list<Note*> notelist;
    list<Note*> favouritenotes;
    list<Note*> blockednotes;
    filesystem::path path="../notes";
    void createNoteFile(Note* n);
};


#endif //DENOTE_NOTEMANAGER_H
