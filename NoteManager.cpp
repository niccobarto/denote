//
// Created by nicco on 10/05/2024.
//

#include "NoteManager.h"
void NoteManager::createNewNote(QString &name) {
    Note* n=new Note(name);
    notelist.push_back(n);
}

Note* NoteManager::getNote(const QString& name) {
    for(Note* note: notelist){
        if(note->getName()==name)
            return note;
    }
    return nullptr;
}

void NoteManager::saveNote(const QString& name, const QString& text) {
    for(Note* note: notelist){
        if(note->getName()==name)
            note->setText(text);
    }
}

void NoteManager::deleteNote(QString &name) {
    std::list<Note*>::iterator it;
    for(it=notelist.begin();it !=notelist.end();it++){
        if((*it)->getName()==name)
            notelist.erase(it);
    }
}
