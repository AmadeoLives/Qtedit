#include "qtedit.h"
#include "conf_dialog.h"

void Qtedit::openPref(){
    conf->fontBox->setCurrentFont(confs.fontFamily);
    conf->sizeBox->setValue(confs.fontSize);
    conf->show();
}

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

    auto fontFamily = confs.value("textArea/fontFamily").toString();
    auto fontSize = confs.value("textArea/fontSize").toInt();
    textArea->setFont(QFont(fontFamily, fontSize));

    return textArea;
}
