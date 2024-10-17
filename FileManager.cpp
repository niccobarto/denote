//
// Created by nicco on 12/10/2024.
//

#include "FileManager.h"



QStringList FileManager::getFileContent(int filenumber) {

}

void FileManager::createNoteFile(const Note* n) {

}

void FileManager::saveFile(const QString &name, const QString &text, bool fav, bool blo) {

}

void FileManager::saveFile(const QString &name, bool f, bool b) {

}

void FileManager::loadNote(const QString& filepath) {

}

void FileManager::renameFile(const QString &name) {

}

void FileManager::deleteNoteFile(const QString &name) {

}

int FileManager::getFileNumber() {
    int number_of_files = 0;
    for (auto const & file : std::filesystem::directory_iterator(directorypath))
        number_of_files++;
    return number_of_files;
}
