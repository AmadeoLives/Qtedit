#include "qtedit.h"
#include "conf_dialog.h"

int main(int argc, char* argv[]){
    QApplication root(argc, argv);
    auto* qtedit = new Qtedit;
    qtedit->conf = new ConfDialog(qtedit);

    QObject::connect(qtedit->conf->dialogButtonBox, &QDialogButtonBox::accepted, qtedit, &Qtedit::setFont);

    qtedit->show();

    root.setOrganizationName("Qtedit");
    root.setApplicationName("Qtedit");
    root.setApplicationDisplayName("Qtedit");

    return root.exec();
}
