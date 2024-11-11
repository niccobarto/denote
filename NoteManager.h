//
// Created by nicco on 10/05/2024.
//

#ifndef DENOTE_NOTEMANAGER_H
#define DENOTE_NOTEMANAGER_H

#include <list>
#include "Note.h"
#include <QTextStream>
#include <QFile>
#include <fstream>
#include <iostream>
#include "FileManager.h"
#include "Observable.h"
using namespace std;

class NoteManager : public Observable {

public:
    NoteManager();
    explicit NoteManager(filesystem::path directorypath);
    ~NoteManager();

    bool createNewNote(const QString& name,const QString& text="");
    bool deleteNote(const QString& name);
    bool saveNote(const QString& name,const QString& text);
    QString loadNote(QString& filepath);
    bool renameNote(QString& oldname,const QString &newname);
    void changeFavouriteStatus(const QString& name);
    void changeBlockedStatus(const QString& name);
    bool isNameUsed(const QString& name);
    void addObserver(Observer* o) override;
    void removeObserver(Observer* o) override;

    QStringList getAllNotesName();
    Note* getNote(const QString& name);
    QStringList getFavouriteNotes()const;
    QStringList getBlockedNotes()const;
    QStringList getFavBlockNotes()const;
    int getTotalNumber()const ;
    int getFavNumber()const;
    int getBlockNumber()const;
    QStringList getFilteredNameList(bool favchecked, bool blockchecked, const QString& searchbar);
    //Getter per test
    int getNoteListSize()const;
    int getFavouriteListSize()const;
    int getBlockedListSize()const;
private:
    list<Note*> notelist;
    list<Note*> favouritenotes;
    list<Note*> blockednotes;
    FileManager* fmanager;
    int totalnumber=0;
    int favnumber=0;
    int blocknumber=0;
    void initializeNotes();
    bool initializeSingularNote(QString& name, bool fav, bool block, QString& text);
};


#endif //DENOTE_NOTEMANAGER_H
