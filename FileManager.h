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
    FileManager(filesystem::path path="../notes"):directorypath(path){}
    QStringList getFileContent(int i);
    QStringList getFileContent(QString& name);
    void createFile(const Note* n);
    void saveFile(const Note* selected);
    QStringList readExternalFile(QString& filepath);
    void renameFile(QString& oldname,const QString& newname);
    void deleteFile(const QString& name);
    int getFileNumber();
private:
    filesystem::path directorypath;
    QStringList readFile(QFile& file);
};


#endif //DENOTE_FILEMANAGER_H
