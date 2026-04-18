#pragma once
#include <QSettings>

class Confs : public QSettings {
Q_OBJECT
private:

public:
    Confs(Format format, Scope scope, QString org, QString app);

    QString fontFamily = value("textArea/fontFamily").toString();
    int fontSize = value("textArea/fontSize").toInt();
};
