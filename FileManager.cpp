//
// Created by nicco on 12/10/2024.
//

#include "FileManager.h"



QStringList FileManager::getFileContent(int filenumber) {
    QStringList content;
    int i=0;
    for (const auto& entry : filesystem::directory_iterator(directorypath)) {
        if(filenumber==i){
            QFile file(entry.path());
            file.open(QIODevice::ReadOnly); //apro il file in modalità lettura
            QTextStream reader(&file); //con QTextStream posso leggere il contenuto
            QFileInfo f(file); //Con QFileInfo posso ottenere il nome del singolo file e non la directorypath completa
            QString name=f.fileName(); //Leggo il nome del file
            if(name.endsWith(".txt"))
                name.replace(".txt", "");
//Splitta il testo in base a dei criteri
            QString allfiletext=reader.readAll();//Leggi tutto il testo
            QStringList splitter=allfiletext.split('|',Qt::SkipEmptyParts); //Splittalo in base a |
            QStringList notesettings=splitter[0].split(',',Qt::SkipEmptyParts); //splitta splitter[0] per avere i valori di favourite e blocked
            content.push_back(name); //Aggiungi il nome alla lista
            content.push_back(notesettings[0]); //Aggiungi favourite
            content.push_back(notesettings[1]); //Aggiungi blocked
            content.push_back(splitter[1]); //Aggiungi testo della nota
            file.close();
            return content;
        }
        i++;
    }
    throw out_of_range("Errore nel numero di file fornito");
}

void FileManager::createNoteFile(const Note* n) {
    ofstream notefile(directorypath / (n->getName().toStdString() + ".txt"));
    notefile << (n->isFavourite() ? "true" : "false") << ",";
    notefile << (n->isBlocked() ? "true" : "false") << "|";
    notefile<<n->getText().toStdString();
}

void FileManager::saveFile(const Note* selected) {
    ofstream notefile(directorypath / (selected->getName().toStdString() + ".txt"));
    notefile << (selected->isFavourite() ? "true" : "false") << ",";
    notefile << (selected->isBlocked() ? "true" : "false") << "|";
    notefile << selected->getText().toStdString() << "\n";
}

QStringList FileManager::readFileLoaded(const QString& filepath) {
    QStringList content;
    QFile file(filepath); //creo un QFile associandolo dando il directorypath del file
    file.open(QIODevice::ReadOnly); //apro il file in modalità lettura
    QTextStream reader(&file); //con QTextStream posso leggere il contenuto
    QFileInfo f(file); //Con QFileInfo posso ottenere il nome del singolo file e non la directorypath completa
    QString name=f.fileName(); //Leggo il nome del file
    if(name.endsWith(".txt"))
        name.replace(".txt", "");
    QString text=reader.readAll(); //Leggo il file selezionato
    content.push_back(name);
    content.push_back(text);
    file.close(); //chiudo il file
    return content;
}

void FileManager::renameFile(const QString& oldname,const QString& newname) {
    filesystem::rename(directorypath/(oldname.toStdString()+".txt"),directorypath/(newname.toStdString()+".txt"));
}

void FileManager::deleteNoteFile(const QString &name) {
    filesystem::remove(directorypath/(name.toStdString()+".txt"));
}

int FileManager::getFileNumber() {
    int number_of_files = 0;
    for (auto const & file : std::filesystem::directory_iterator(directorypath))
        number_of_files++;
    return number_of_files;
}