//
// Created by nicco on 10/05/2024.
//

#include "NoteManager.h"
bool NoteManager::createNewNote(QString &name) {
    bool found=false;
    for(Note* n:notelist){
        if(n->getName()==name){ //verifica se esiste già una nota con quel nome
            found=true;
            break;
        }
    }
    if(!found){
        Note* n=new Note(name); //se non esiste già una nota con questo nome, crea una nuova nota
        notelist.push_back(n);
    }
    return found;
}

Note* NoteManager::getNote(const QString& name) {
    for(Note* note: notelist){
        if(note->getName()==name)
            return note;
    }
    return nullptr;
}

void NoteManager::saveNote(const QString& name, const QString& text) {
    Note* selected=getNote(name);
    if(selected!=nullptr)
        selected->setText(text);
}

void NoteManager::deleteNote(QString &name) {
    std::list<Note*>::iterator it;
    for(it=notelist.begin();it !=notelist.end();it++){
        if((*it)->getName()==name){
            notelist.erase(it);
            break;
        }
    }
}
