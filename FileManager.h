//
// Created by nicco on 12/10/2024.
//

#ifndef DENOTE_FILEMANAGER_H
#define DENOTE_FILEMANAGER_H
#include <QFile>
#include <fstream>
#include <iostream>
#include <list>
#include <qfileinfo.h>
#include <filesystem>
#include "NoteManager.h"
using namespace std;
class FileManager {
public:
    QStringList getFileContent(int i);
    void createNoteFile(const Note* n);
    void saveFile(const QString& name, const QString& text, bool fav, bool blo);
    void saveFile(const QString& name, bool f, bool b);
    void loadNote(const QString& filepath);
    void renameFile(const QString& name);
    void deleteNoteFile(const QString& name);
    int getFileNumber();
private:
    filesystem::path directorypath="../notes";
};


#endif //DENOTE_FILEMANAGER_H
