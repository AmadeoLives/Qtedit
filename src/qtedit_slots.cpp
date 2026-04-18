#include "qtedit.h"

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
        statusBar()->showMessage(tr("No changes needed."));
        return;
    }

    if (!file.exists()){
        currentFile = QFileDialog::getSaveFileName(this, "Save File", QDir::toNativeSeparators(QDir::homePath()));
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
    statusBar()->showMessage("File saved.");
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

    QString savedFile("File saved to" + currentFile + ".");
    statusBar()->showMessage(savedFile);
    file.close();
}

