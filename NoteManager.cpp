//
// Created by nicco on 10/05/2024.
//

#include <qfileinfo.h>
#include "NoteManager.h"
#include <filesystem>

NoteManager::NoteManager() {
    fmanager=new FileManager();
    initializeNotes();
}
NoteManager::NoteManager(filesystem::path directorypath) {
    fmanager=new FileManager(directorypath);
    initializeNotes();
}

bool NoteManager::createNewNote(const QString &name, const QString& text) {
    bool found= isNameUsed(name);
    if(!found){
        Note* n=new Note(name,text); //se non esiste già una nota con questo nome, crea una nuova nota
        notelist.push_back(n);
        fmanager->createNoteFile(n);
        totalnumber++;
        notify();
    }
    return !found;
}
bool NoteManager::initializeSingularNote(QString& name, bool fav, bool block, QString& text ) {
    bool found= isNameUsed(name);
    if(!found){
        Note* n=new Note(name,fav,block,text); //se non esiste già una nota con questo nome, crea una nuova nota
        notelist.push_back(n);
        totalnumber++;
        if(fav){
            favouritenotes.push_back(n);
            favnumber++;
        }
        if(block){
            blockednotes.push_back(n);
            blocknumber++;
        }

    }
    return !found;
}
void NoteManager::deleteNote(const QString &name) {
    Note* n= getNote(name);
    list<Note*>::iterator it;
    for(it=notelist.begin();it !=notelist.end();it++){
        if((*it)->getName()==name){
            notelist.erase(it);
            totalnumber--;
            break;
        }
    }
    if(n->isFavourite()){
        for(it=favouritenotes.begin();it !=favouritenotes.end();it++){
            if((*it)->getName()==name){
                favouritenotes.erase(it);
                favnumber--;
                break;
            }
        }
    }
    if(n->isBlocked()){
        for(it=blockednotes.begin();it !=blockednotes.end();it++){
            if((*it)->getName()==name){
                blockednotes.erase(it);
                blocknumber--;
                break;
            }
        }
    }
    fmanager->deleteNoteFile(name);
    notify();
}

void NoteManager::saveNote(const QString& name, const QString& text) {
    Note* selected=getNote(name);
    if(selected!=nullptr){
        selected->setText(text); //salvo il nuovo text della nota
        fmanager->saveFile(selected); //Salvo i cambiamenti nel file tramite FileManager
    }
}

QString NoteManager::loadNote(QString& filepath) {
   QStringList content= fmanager->readExternalFile(filepath); //Leggo il contenuto del file
    bool result=createNewNote(content[0],content[1]); //creo la nota inserendo anche il testo caricato
    if(result) //in caso esista una nota con lo stesso nome (result==false) il caricamento non avviene
        return content[0]; //restituisco il nome della nota per mostrarla sulla window
    return ""; //restituisco "" invece del nome della nota
}

bool NoteManager::renameNote(QString &oldname,const QString &newname) {
    bool found= isNameUsed(newname);
    if(!found){
        Note* n= getNote(oldname);
        n->setName(newname);
        fmanager->renameFile(oldname,newname);
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
                favnumber--;
                break;
            }
        }
    }
    else{
        selected->changeFavourite(true); //Altrimenti rendila preferita
        favouritenotes.push_back(selected); //Inseriscila nella lista dei preferiti
        favnumber++;
    }
    fmanager->saveFile(selected);
    notify();
}

void NoteManager::changeBlockedStatus(const QString& name) {
    Note* selected= getNote(name);
    if(selected->isBlocked()){ //Se la nota è bloccata
        selected->changeBlocked(false);//Rimuovila dai bloccata
        list<Note*>::iterator it;
        for(it=blockednotes.begin();it !=blockednotes.end();it++){
            if((*it)->getName()==selected->getName()){
                blockednotes.erase(it);//Rimuovila dalla lista di bloccata
                blocknumber--;
                break;
            }
        }
    }
    else{
        selected->changeBlocked(true);//Altrimenti rendila bloccata
        blockednotes.push_back(selected);//Inseriscila nella lista dei bloccati
        blocknumber++;
    }
    fmanager->saveFile(selected);
    notify();
}

bool NoteManager::isNameUsed(const QString &name) {
    for(Note* n: notelist){
        if(n->getName()==name)
            return true;
    }
    return false;
}


QStringList NoteManager::getAllNotesName() {
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

void NoteManager::initializeNotes() {
    int max=fmanager->getFileNumber();
    for (int i = 0; i < max; i++) {
        try{
            QStringList filecontent=fmanager->getFileContent(i);
            initializeSingularNote(filecontent[0],filecontent[1]=="true",filecontent[2]=="true",filecontent[3]);
        }
        catch(out_of_range e){
        }
    }
}

QStringList NoteManager::getFavouriteNotes()const {
    QStringList names;
    for(Note* n:favouritenotes)
        names.push_back(n->getName());
    return names;
}

QStringList NoteManager::getBlockedNotes()const {
    QStringList names;
    for(Note* n:blockednotes)
        names.push_back(n->getName());
    return names;
}

QStringList NoteManager::getFavBlockNotes()const {
    QStringList names;
    for(Note* n:favouritenotes)
        if(n->isBlocked())
            names.push_back(n->getName());
    return names;
}

void NoteManager::addObserver(Observer *o) {
    observers.push_back(o);
}

void NoteManager::removeObserver(Observer *o) {
    observers.remove(o);
}

int NoteManager::getTotalNumber()const {
    return totalnumber;
}

int NoteManager::getFavNumber()const {
    return favnumber;
}

int NoteManager::getBlockNumber()const {
    return blocknumber;
}

int NoteManager::getNoteListSize() const {
    return notelist.size();
}

int NoteManager::getFavouriteListSize() const {
    return favouritenotes.size();
}

int NoteManager::getBlockedListSize() const {
    return blockednotes.size();
}










