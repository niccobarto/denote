//
// Created by nicco on 31/07/2024.
//
#include "TestNewNote.h"
#include <QWidget>
#include <QSignalSpy>
void TestNewNote::testEmptyName() {

    dialog=new NewNoteDialog();
    QLineEdit* input=dialog->getNoteTitleBox();
    QLabel* errorlabel=dialog->getErrorCreationLabel();

    QWidget* newnotebutton= reinterpret_cast<QWidget *>(dialog->getNoteCreationButton());
    /*
    QWidget* newnotebutton=dialog->getNoteCreationButton();
     Todo: preferirei questa versione (riga 15) rispetto all'istruzione prededente (riga 13),
         ma nonostante QPushButton derivi da QWidget, viene dato un errore
         "Cannot initialize a variable of type 'QWidget *' with an rvalue of type 'QPushButton *'.
         La soluzione adottata nella riga 12 era consigliata ma non da me capita
    */
     //SIMULAZIONE
    input->clear();
    QTest::mouseClick(newnotebutton,Qt::LeftButton); //simula il click del mouse
    //FINE SIMULAZIONE
    QVERIFY(errorlabel->isVisible());

}

void TestNewNote::testNoteCreation() {
    dialog=new NewNoteDialog(base);
    QLineEdit* input=dialog->getNoteTitleBox();
    QWidget* newnotebutton= reinterpret_cast<QWidget *>(dialog->getNoteCreationButton()); //Todo: stesse considerazioni del Todo precedente
    QSignalSpy spy(dialog,&NewNoteDialog::noteConfirmed); //oggetto essenziale per la gestione dei segnali nei test

    //SIMULAZIONE
    input->setText("Nota");
    QTest::mouseClick(newnotebutton,Qt::LeftButton);
    //FINE SIMULAZIONE
    //QVERIFY(spy.isValid());
    QVERIFY(spy.count()==1); //verifica che il segnale "noteConfirmed" sia stato emesso una volta
    QList<QVariant> signalsdialog=spy.takeFirst();
    /*
     Prendiamo il primo (first) perché ci aspettiamo che ce ne sia uno solo
     spy.takeFirst() restituisce una lista di QVariant, ovvero un tipo che
     può essere string, int, o altri tipi di dati. Ogni argomento di spy (ovvero ogni segnale emesso
     da dialog) è quindi una lista di QVariant e quindi una lista di dati
    */

    //Verifico che il segnale emesso contenga come parametro una QString uguale (nel testo) al nome deciso
    QCOMPARE(signalsdialog.at(0).toString(),input->text());
    /*
     Con sinalsdialog.at(0) prendiamo il primo QVariant (e l'unico) che è proprio il nome
     della nuova nota e lo compariamo al nome inserito nella simulazione precedente
    */


    /*
      ORA VERIFICHIAMO CHE LA NOTA INSERITA NELLA LISTA SIA CON IL NOME INSERITO.

      preso questa decisione perché non riuscito a gestire la simulazione della scelta del nome
      utilizzando direttamente il NewNoteDialog che si genererebbe al click del button "newnotebutton"
     */

    //connessione slot creatioNote a NewNoteDialog fantoccio
    connect(dialog, &NewNoteDialog::noteConfirmed, base, &BaseWindow::createNote);

    /*
    segue la corrispettiva operazione compiuta nello slot NewNoteDialog::noteCreationButtonClicked(),
     ignorando il controllo sulla presenza del nome poiché in questo test lo diamo per scontato
    */
     emit dialog->noteConfirmed(signalsdialog.at(0).toString());
    list<Note*> notes=base->getNotes();
    bool found=false;
    for(Note* n:notes){
        if(n->getName()==signalsdialog.at(0).toString())
            found=true;
    }
    QVERIFY(found);
}

void TestNewNote::initTestCase() {
    base=new BaseWindow();
}

#include "TestNewNote.moc"
//QTEST_MAIN(TestNewNote)

