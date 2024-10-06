//
// Created by nicco on 10/05/2024.
//

#include <qfileinfo.h>
#include "NoteManager.h"
bool NoteManager::createNewNote(const QString &name) {
    bool found= isNameUsed(name);
    if(!found){
        Note* n=new Note(name); //se non esiste già una nota con questo nome, crea una nuova nota
        notelist.push_back(n);
        createNoteFile(n);
    }
    return !found;
}

void NoteManager::deleteNote(const QString &name) {
    list<Note*>::iterator it;
    for(it=notelist.begin();it !=notelist.end();it++){
        if((*it)->getName()==name){
            notelist.erase(it);
            break;
        }
    }
}

void NoteManager::saveNote(const QString& name, const QString& text) {
    Note* selected=getNote(name);
    if(selected!=nullptr){
        selected->setText(text);
        ofstream notefile(path/(name.toStdString()+".txt"));
        notefile << "favourite = " << (selected->isFavourite() ? "true" : "false") << "\n";
        notefile << "blocked = " << (selected->isBlocked() ? "true" : "false") << "\n";
        notefile << text.toStdString() << "\n";
    }

}

QString NoteManager::loadNote(const QString& filepath) {
    QFile file(filepath); //creo un QFile associandolo dando il path del file
    file.open(QIODevice::ReadOnly); //apro il file in modalità lettura
    QTextStream reader(&file); //con QTextStream posso leggere il contenuto
    QFileInfo f(file); //Con QFileInfo posso ottenere il nome del singolo file e non la path completa
    QString name=f.fileName(); //Leggo il nome del file
    QString text=reader.readAll(); //Leggo il file selezionato
    file.close(); //chiudo il file
    bool result=createNewNote(name);
    if(result){
        Note* n= getNote(name);
        n->setText(text);
        return name;
    }
    return "";
}

bool NoteManager::renameNote(const QString &oldname,const QString &newname) {
    bool found= isNameUsed(newname);
    if(!found){
        Note* n= getNote(oldname);
        n->setName(newname);
    }
    return !found;
}

void NoteManager::changeFavouriteStatus(const QString& name) {
    Note* selected= getNote(name);
    if(selected->isFavourite()){ //Se la nota è preferita
        selected->changeFavourite(false);//Rimuovila dai preferiti
        list<Note*>::iterator it;
        for(it=favouritenotes.begin();it !=favouritenotes.end();it++){
            if((*it)->getName()==selected->getName()){
                favouritenotes.erase(it); //Rimuovila dalla lista di preferiti
                break;
            }
        }
    }
    else{
        selected->changeFavourite(true); //Altrimenti rendila preferita
        favouritenotes.push_back(selected); //Inseriscila nella lista dei preferiti
    }
}

void NoteManager::changeBlockedStatus(const QString& name) {
    Note* selected= getNote(name);
    if(selected->isBlocked()){ //Se la nota è bloccata
        selected->changeBlocked(false);//Rimuovila dai bloccata
        list<Note*>::iterator it;
        for(it=blockednotes.begin();it !=blockednotes.end();it++){
            if((*it)->getName()==selected->getName()){
                blockednotes.erase(it);//Rimuovila dalla lista di bloccata
                break;
            }
        }
    }
    else{
        selected->changeBlocked(true);//Altrimenti rendila bloccata
        blockednotes.push_back(selected);//Inseriscila nella lista dei bloccati
    }

}

bool NoteManager::isNameUsed(const QString &name) {
    for(Note* n: notelist){
        if(n->getName()==name)
            return true;
    }
    return false;
}

QStringList NoteManager::getSimilarNotes(const QString &searchtext) {
    QStringList similarnotes;
    for(Note* n:notelist){
        if(n->getName().contains(searchtext))
            similarnotes.push_back(n->getName());
    }
    return similarnotes;
}

QStringList NoteManager::getDefaultNoteList() {
    QStringList notenames;
    for(Note* n:notelist){
        notenames.push_back(n->getName());
    }
    return notenames;
}

Note* NoteManager::getNote(const QString& name) {
    for(Note* note: notelist){
        if(note->getName()==name)
            return note;
    }
    return nullptr;
}

NoteManager::~NoteManager() {
    for(Note* n:notelist)
        delete n;
    for(Note* n:favouritenotes)
        delete n;
    for(Note* n:blockednotes)
        delete n;
}

void NoteManager::createNoteFile(Note *n) {
    ofstream notefile(path/(n->getName().toStdString()+".txt"));
    notefile << "favourite = " << (n->isFavourite() ? "true" : "false") << "\n";
    notefile << "blocked = " << (n->isBlocked() ? "true" : "false") << "\n";
    notefile<<n->getText().toStdString();
}


