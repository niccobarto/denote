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
    NoteManager(){

    }
    void createNewNote(QString& name);
    Note getLatestNoteCreated(){
        return notelist.back();
    }
private:
    list<Note> notelist;

};


#endif //DENOTE_NOTEMANAGER_H
