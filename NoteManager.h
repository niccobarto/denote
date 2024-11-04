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
    void deleteNote(const QString& name);
    void saveNote(const QString& name,const QString& text);
    QString loadNote(QString& filepath);
    bool renameNote(QString& oldname,const QString &newname);
    void changeFavouriteStatus(const QString& name);
    void changeBlockedStatus(const QString& name);
    bool isNameUsed(const QString& name);
    QStringList getAllNotesName();
    Note* getNote(const QString& name);
    QStringList getFavouriteNotes();
    QStringList getBlockedNotes();
    QStringList getFavBlockNotes();
    int getTotalNumer();
    int getFavNumber();
    int getBlockNumber();
    void addObserver(Observer* o) override;
    void removeObserver(Observer* o) override;
private:
    list<Note*> notelist;
    list<Note*> favouritenotes;
    list<Note*> blockednotes;
    FileManager* fmanager;
    void initializeNotes();
    bool initializeSingularNote(QString& name, bool fav, bool block, QString& text);
};


#endif //DENOTE_NOTEMANAGER_H
