//
// Created by nicco on 10/05/2024.
//

#ifndef DENOTE_NOTEMANAGER_H
#define DENOTE_NOTEMANAGER_H

#include <list>
#include "Note.h"

using namespace std;


class NoteManager {

public:

    bool createNewNote(QString& name);
    void deleteNote(QString& name);
    void saveNote(const QString& name,const QString& text);

    list<Note*> getNoteList(){
        return notelist;
    }
    Note* getNote(const QString& name);

    Note* getLatestNoteCreated(){
        return notelist.back();
    }

private:
    list<Note*> notelist;
};


#endif //DENOTE_NOTEMANAGER_H
