//
// Created by nicco on 10/05/2024.
//

#include "NoteManager.h"
void NoteManager::createNewNote(QString &name) {
    Note n(name);
    notelist.push_back(n);
}
