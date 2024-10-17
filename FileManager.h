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
#include "Note.h"

using namespace std;
class FileManager {
public:
    QStringList getFileContent(int i);
    void createNoteFile(const Note* n);
    void saveFile(const Note* selected);
    QStringList readFileLoaded(const QString& filepath);
    void renameFile(const QString& name);
    void deleteNoteFile(const QString& name);
    int getFileNumber();
private:
    filesystem::path directorypath="../notes";
};


#endif //DENOTE_FILEMANAGER_H
