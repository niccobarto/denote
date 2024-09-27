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

    bool isNameUsed(const QString& name);
    list<Note*> getNoteList(){
        return notelist;
    }
    Note* getNote(const QString& name);

    Note* getLatestNoteCreated(){
        return notelist.back();
    }
    ~NoteManager();
private:
    list<Note*> notelist;
    filesystem::path path="../notes";
    void createNoteFile(Note* n);
};


#endif //DENOTE_NOTEMANAGER_H
