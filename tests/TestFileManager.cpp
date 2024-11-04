
#include "TestFileManager.h"

void TestFileManager::initTestCase() {
    manager=new FileManager("../tests/testsnotes");
}

void TestFileManager::testGetFileContent() {
    QString name="testfilecontent";
    QString text="La lista della spesa: carote,cipolle,pasta";
    manager->createNoteFile(new Note(name,text)); //Crea una nuova nota
    QStringList content=manager->getFileContent(name); //Ottieni il contenuto dell'ultima nota creata
    QCOMPARE(content[0],name); //Il nome della nota deve essere pari a "testfilecontent"
    QCOMPARE(content[3],text); //Il testo della nota deve essere pari a "La lista della spesa: carote,cipolle,pasta"
}

void TestFileManager::testCreateNoteFile() {
    QString name="testcreatenote";
    manager->createNoteFile(new Note(name,"elenco"));
    QCOMPARE(manager->getFileContent(name)[0],name); //Il nome dell'ultima nota creata deve essere pari a "testcreatenote"
}

void TestFileManager::testSaveFile() {
    QString name="testsavefile";
    QString text="La lista della spesa: carote,cipolle,pasta";
    Note* n=new Note(name,text); //Crea una nuova nota
    manager->createNoteFile(n); //Crea il file della nota
    QString changedtext="La lista della spesa: carote,cipolle,pasta,pane";
    n->setText(changedtext); //Modifica manualmente il testo della nota
    manager->saveFile(n);
    QCOMPARE(manager->getFileContent(name)[3], changedtext); //Il testo della nota deve essere pari a "La lista della spesa: carote,cipolle,pasta,pane"
}

void TestFileManager::testReadFileLoaded() {
    QString filepath=QString("testloadexternfile.txt");
    QString text="testo di prova per il caricamento di una nota tramite filesystem";
    QFile file(filepath); //creo un QFile associandolo dando il directorypath del file
    file.open(QIODevice::WriteOnly); //apro il file in modalità scrittura
    QTextStream writer(&file); //con QTextStream posso scrivere il contenuto
    writer<<text;//Scrivo il testo
    file.close();
    QStringList content= manager->readExternalFile(filepath); //Carica il file
    Note* n=new Note(content[0],false,false,content[1]);
    manager->createNoteFile(n); //Crea la nota
    content[0].replace(".txt", ""); //Elimino l'estensione .txt
    QCOMPARE(manager->getFileContent(content[0])[0],"testloadexternfile"); //Il nome della nota deve essere pari a "testloadexternfile"
    QCOMPARE(manager->getFileContent(content[0])[3],text); //Il testo della nota deve essere pari a "testo di prova per il caricamento di una nota tramite filesystem"
}

void TestFileManager::cleanupTestCase() {
    QStringList names;
    for (int i = 0; i < manager->getFileNumber(); ++i)
        names.push_back(manager->getFileContent(i)[0]);//Elimina tutte le note create
    for(QString name:names)
        manager->deleteNoteFile(name);
    delete manager;

}

