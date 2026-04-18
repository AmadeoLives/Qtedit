#include "confs.h"

Confs::Confs(Format format, Scope scope, QString org, QString app)
    : QSettings(format, scope, org, app)
{
    beginGroup("textArea");
    value("fontFamily", "monospace");
    value("fontSize", 67);
    endGroup();
}
