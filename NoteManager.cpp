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
    std::list<Note*>::iterator it;
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
    bool found=createNewNote(name);
    Note* n= getNote(name);
    n->setText(text);
    if(!found)
        return name;
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

void NoteManager::changeFavourite(const QString &name) {

}

void NoteManager::changeBlocked(const QString &name) {

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
    if(n->isLocked())
        notefile<<"true\n";
    else
        notefile<<"false\n";
    notefile<<n->getText().toStdString();
}

