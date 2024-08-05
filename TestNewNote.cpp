//
// Created by nicco on 31/07/2024.
//
#include "TestNewNote.h"
#include <QWidget>
#include <QSignalSpy>
void TestNewNote::testEmptyName() {

    dialog=new NewNoteDialog;
    QLineEdit* input=dialog->getNoteTitleBox();
    QLabel* errorlabel=dialog->getErrorCreationLabel();

    QWidget* newnotebutton= reinterpret_cast<QWidget *>(dialog->getNoteCreationButton());
    /*
    QWidget* newnotebutton=dialog->getNoteCreationButton();
     Todo: preferirei questa versione (riga 14) rispetto all'istruzione prededente (riga 12),
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
    dialog=new NewNoteDialog;
    QLineEdit* input=dialog->getNoteTitleBox();
    QLabel* errorlabel=dialog->getErrorCreationLabel();
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
     Prendiamo il primo (first)perché ci aspettiamo che ce ne sia uno solo
     spy.takeFirst() restituisce una lista di QVariant, ovvero un tipo che
     può essere string, int, o altri tipi di dati. Ogni argomento di spy (ovvero ogni segnale emesso
     da dialog) è quindi una lista di QVariant e quindi una lista di dati
    */

    QCOMPARE(signalsdialog.at(0).toString(),input->text());
    /*
     Con sinalsdialog.at(0) prendiamo il primo QVariant (e l'unico) che è proprio il nome
     della nuova nota e lo compariamo al nome inserito nella simulazione precedente
    */
}

QTEST_MAIN(TestNewNote)
//#include "TestNewNote.moc"
