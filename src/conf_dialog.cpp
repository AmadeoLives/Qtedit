#include "conf_dialog.h"
#include "qtedit.h"

void Qtedit::setFont(){
    confs.setValue("textArea/fontFamily", conf->fontBox->currentFont().family());
    confs.setValue("textArea/fontSize", conf->sizeBox->value());
    auto fontFamily = confs.value("textArea/fontFamily").toString();
    auto fontSize = confs.value("textArea/fontSize").toInt();
    textArea->setFont(QFont(fontFamily, fontSize));
}

ConfDialog::ConfDialog(QWidget* parent) : QDialog(parent)
{
    auto* fontTab = createFontTab();

    dialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | 
            QDialogButtonBox::Apply | QDialogButtonBox::Cancel | QDialogButtonBox::Help);
    connect(dialogButtonBox, &QDialogButtonBox::rejected, this, &QDialog::close);

    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(fontTab);
    mainLayout->addWidget(dialogButtonBox);
}

QWidget* ConfDialog::createFontTab(){
    fontBox = new QFontComboBox;
    sizeBox = new QSpinBox;

    //fontBox->setFontFilters(QFontComboBox::MonospacedFonts);

    auto* layout = new QFormLayout;

    layout->addRow("Font family:", fontBox);
    layout->addRow("Font size:", sizeBox);

    auto* result = new QGroupBox;
    result->setTitle("Font");
    result->setLayout(layout);

    return result;
}
