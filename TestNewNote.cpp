//
// Created by nicco on 31/07/2024.
//
#include "TestNewNote.h"
void TestNewNote::testEmptyName() {

    dialog=new NewNoteDialog;
    QLineEdit* input=dialog->getNoteTitleBox();
    QLabel* errorLabel=dialog->getErrorCreationLabel();
    QPushButton* newNoteButton=dialog->getNoteCreationButton();
    input->setText("");
    QTest::mouseClick(newNoteButton,Qt::LeftButton); //Todo: anche se QPushButton deriva da QWidget, c'è questo errore
    QVERIFY(errorLabel->isVisible());

}
QTEST_MAIN(TestNewNote)
//#include "TestNewNote.moc"
