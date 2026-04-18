#include "conf_dialog.h"
#include "qtedit.h"

void Qtedit::testing(){
    textArea->setText("If you can read this text, the function works.");
}

ConfDialog::ConfDialog(QWidget* parent) : QDialog(parent)
{
    auto* fontTab = createFontTab();

    dialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | 
            QDialogButtonBox::Apply | QDialogButtonBox::Cancel | QDialogButtonBox::Help);

    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(fontTab);
    mainLayout->addWidget(dialogButtonBox);
}

QWidget* ConfDialog::createFontTab(){
    fontBox = new QFontComboBox;
    sizeBox = new QSpinBox;
    auto* layout = new QFormLayout;
    layout->addRow("Font family:", fontBox);
    layout->addRow("Font size:", sizeBox);

    auto* result = new QGroupBox;
    result->setTitle("Font");
    result->setLayout(layout);

    return result;
}
