#pragma once
#include <QtWidgets>
#include "conf_dialog.h"

class Qtedit : public QMainWindow {
Q_OBJECT

private:
    QWidget* createTextArea();
    void createActions();
    void createMenus();
    void setSettings();

    // Menus
    QMenu* fileMenu;
    QMenu* editMenu;
    QMenu* helpMenu;

    // Actions
    // File Menu:
    QAction* newAct;
    QAction* openAct;
    QAction* saveAct;
    QAction* saveAsAct;

    // Edit Menu:
    QAction* prefAct;
    QAction* fontAct;

    // Help Menu:
    QAction* aboutQtAct;

    // Widgets
    QTextEdit* textArea;
    QFileDialog* fileDialog;

    // misc
    QString currentFile;
    QFile file;

    bool statusSavedFile;


protected:

public:
    explicit Qtedit();

    QSettings settings {QSettings::NativeFormat, QSettings::UserScope, "Qtedit", "Qtedit"};
    ConfDialog* conf;

private slots:

    //void loadConfig();
    //void saveConfig();

signals:

public slots:
    void testing();
    void openFile();
    void saveFile();
    void saveFileAs();


    void openPref();
};
