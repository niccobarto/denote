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
    if(selected!=nullptr)
        selected->setText(text);
    ofstream notefile(path/(name.toStdString()+".txt"));
    notefile<<text.toStdString();
    string favourite,locked;
    std::ifstream file_lettura(path);
    std::getline(file_lettura, favourite);
    std::getline(file_lettura, locked);
    file_lettura.close();  // Chiudi il file dopo aver letto i parametri
    // Ora riapri il file in modalità scrittura per aggiornare solo il testo della nota
    std::ofstream file_scrittura(path);
    // Riscrivi i parametri
    file_scrittura << favourite << "\n";
    file_scrittura << locked << "\n";
    // Scrivi il nuovo testo della nota
    file_scrittura << "\"" << text.toStdString() << "\"\n";
    file_scrittura.close();  // Chiudi il file dopo la scrittura
    std::cout << "Nota aggiornata con successo in: " << path << std::endl;

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

list<Note *> NoteManager::getNoteList() {
    return notelist;
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
}

void NoteManager::createNoteFile(Note *n) {
    ofstream notefile(path/(n->getName().toStdString()+".txt"));
    notefile<<"favourite=";
    if(n->isFavourite())
        notefile<<"true\n";
    else
        notefile<<"false\n";
    notefile<<"locked=";
    if(n->isBlocked())
        notefile<<"true\n";
    else
        notefile<<"false\n";
    notefile<<n->getText().toStdString();
}

