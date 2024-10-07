//
// Created by nicco on 10/05/2024.
//

#include <qfileinfo.h>
#include "NoteManager.h"
#include <filesystem>

NoteManager::NoteManager() {
    initializeNotes();
}
bool NoteManager::createNewNote(const QString &name) {
    bool found= isNameUsed(name);
    if(!found){
        Note* n=new Note(name); //se non esiste già una nota con questo nome, crea una nuova nota
        notelist.push_back(n);
        createNoteFile(n);
    }
    return !found;
}
bool NoteManager::initializeSingularNote(const QString& name, const bool& fav, const bool& block,const QString& text ) {
    bool found= isNameUsed(name);
    if(!found){
        Note* n=new Note(name,fav,block,text); //se non esiste già una nota con questo nome, crea una nuova nota
        notelist.push_back(n);
        if(fav)
            favouritenotes.push_back(n);
        if(block)
            blockednotes.push_back(n);
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
        ofstream notefile(directorypath / (name.toStdString() + ".txt"));
        notefile << (selected->isFavourite() ? "true" : "false") << ",";
        notefile << (selected->isBlocked() ? "true" : "false") << "|";
        notefile << text.toStdString() << "\n";
    }

}

QString NoteManager::loadNote(const QString& filepath) {
    QFile file(filepath); //creo un QFile associandolo dando il directorypath del file
    file.open(QIODevice::ReadOnly); //apro il file in modalità lettura
    QTextStream reader(&file); //con QTextStream posso leggere il contenuto
    QFileInfo f(file); //Con QFileInfo posso ottenere il nome del singolo file e non la directorypath completa
    QString name=f.fileName(); //Leggo il nome del file
    if(name.endsWith(".txt"))
        name = name.replace(".txt", "");
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
    ofstream notefile(directorypath / (n->getName().toStdString() + ".txt"));
    notefile << (n->isFavourite() ? "true" : "false") << ",";
    notefile << (n->isBlocked() ? "true" : "false") << "|";
    notefile<<n->getText().toStdString();
}

void NoteManager::initializeNotes() {
    for (const auto& entry : filesystem::directory_iterator(directorypath)) {
        QFile file(entry.path());
        file.open(QIODevice::ReadOnly); //apro il file in modalità lettura
        QTextStream reader(&file); //con QTextStream posso leggere il contenuto
        QFileInfo f(file); //Con QFileInfo posso ottenere il nome del singolo file e non la directorypath completa
        QString name=f.fileName(); //Leggo il nome del file
        if(name.endsWith(".txt"))
            name = name.replace(".txt", "");
        QString allfiletext=reader.readAll();//Leggi tutto il testo
        QStringList splitter=allfiletext.split('|',Qt::SkipEmptyParts); //Splittalo in base a |
        QStringList notesettings=splitter[0].split(',',Qt::SkipEmptyParts); //splitta splitter[0] per avere i valori di favourite e blocked
        initializeSingularNote(name, notesettings[0] == "true", notesettings[1] == "true",splitter[1]); //crea nota e inseriscila nelle varie liste
    }
}




