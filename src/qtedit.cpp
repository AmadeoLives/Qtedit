#include "qtedit.h"
#include "conf_dialog.h"

// Slots

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

void Qtedit::openPref(){
    conf->show();
}

// Constructor
Qtedit::Qtedit(){
    createActions();
    createMenus();

    resize(QGuiApplication::primaryScreen()->availableGeometry().size() * 0.5);

    auto* textArea = createTextArea();
    statusBar()->showMessage("Nice.");

    setCentralWidget(textArea);
}

// Member functions
void Qtedit::createActions(){
    // File Menu Actions
    newAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::DocumentNew), tr("&New"));
    openAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::DocumentOpen), tr("&Open"));
    openAct->setShortcut(QKeySequence::Open);
    connect(openAct, &QAction::triggered, this, &Qtedit::openFile);

    saveAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::DocumentSave), tr("&Save"));
    saveAct->setShortcuts(QKeySequence::Save);

    saveAsAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::DocumentSave), tr("&Save as..."));
    saveAsAct->setShortcuts(QKeySequence::SaveAs);

    // Edit Menu Actions
    prefAct = new QAction(tr("&Preferences..."));
    connect(prefAct, &QAction::triggered, this, &Qtedit::openPref);

    // Help Menu Actions
    aboutQtAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::HelpAbout), tr("About Qt..."));
    connect(aboutQtAct, &QAction::triggered, this, &QApplication::aboutQt);
}

void Qtedit::createMenus(){
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(prefAct);

    helpMenu = menuBar()->addMenu(tr("&Help")); 
    helpMenu->addAction(aboutQtAct);
}

QWidget* Qtedit::createTextArea(){
    textArea = new QTextEdit;
    connect(saveAct, &QAction::triggered, this, &Qtedit::saveFile);
    connect(saveAsAct, &QAction::triggered, this, &Qtedit::saveFileAs);
    connect(textArea, &QTextEdit::textChanged, this, [this](){ statusSavedFile = false; });

    auto fontFamily = settings.value("textArea/fontFamily", "Arial").toString();
    auto fontSize = settings.value("textArea/fontSize", 78).toInt();
    textArea->setFont(QFont(fontFamily, fontSize));

    return textArea;
}
