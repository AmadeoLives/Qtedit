#include "qtedit.h"

void Qtedit::newFile(){
    auto* confirmDialog = new QMessageBox;
    confirmDialog->setText("The file has been modified.");
    confirmDialog->setInformativeText("Do you want to save your changes or discard them?");
    confirmDialog->setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    confirmDialog->setDefaultButton(QMessageBox::Save);
    confirmDialog->setIcon(QMessageBox::Warning);

    if (statusSavedFile == false) {
        int ret = confirmDialog->exec();

        switch (ret) {
            case QMessageBox::Save:
                Qtedit::saveFileAs();
                return;
            case QMessageBox::Discard:
                textArea->clear();
                statusBar()->showMessage("New file created.", 2000);
                statusSavedFile = true;
                return;
            case QMessageBox::Cancel:
                confirmDialog->close();
                return;
            default:
                QApplication::exit();
                return;
        }
    } 
    else {
        textArea->clear();
        statusBar()->showMessage("New file created.", 2000);
        statusSavedFile = true;
    }
}

void Qtedit::openFile(){
    currentFile = QFileDialog::getOpenFileName(this, "Open File", QDir::currentPath());
    file.setFileName(currentFile);
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }
    QTextStream in { &file };
    QString text;
    QString content = in.readAll();
    textArea->setText(content);
    file.close();
}

void Qtedit::saveFile(){
    if (statusSavedFile){
        statusBar()->showMessage(tr("No changes needed."), 2000);
        return;
    }

    if (!file.exists()){
        currentFile = QFileDialog::getSaveFileName(this, tr("Save File"), QDir::toNativeSeparators(QDir::homePath()));
    }
    qDebug() << currentFile;

    if (!file.isOpen()){
        file.setFileName(currentFile);

        if(!file.open(QIODevice::WriteOnly)){
            return;
        }
    }

    QTextStream out { &file };
    out << textArea->document()->toPlainText();
    file.close();
    statusSavedFile = true;
    statusBar()->showMessage("File saved.", 2000);
    statusBar()->setSizeGripEnabled(false);
}

void Qtedit::saveFileAs(){
    currentFile = QFileDialog::getSaveFileName(this, "Save File", QDir::toNativeSeparators(QDir::homePath())); 
    qDebug() << currentFile;
    file.setFileName(currentFile);
    if (!file.open(QIODevice::WriteOnly)) {
        return;
    }

    QTextStream out { &file };
    out << textArea->document()->toPlainText();
    file.close();

    QString savedFile("File saved to " + currentFile + ".");
    statusBar()->showMessage(savedFile);
    file.close();
}

