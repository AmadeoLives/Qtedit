#pragma once
#include <QtWidgets>
#include <QDialog>

class ConfDialog : public QDialog {
Q_OBJECT

private:
    QTabWidget* tab;
    QWidget* createFontTab();

public:
    explicit ConfDialog(QWidget* parent = nullptr);
    QDialogButtonBox* dialogButtonBox;

    QFontComboBox* fontBox;
    QSpinBox* sizeBox;

private slots:

signals:

public slots:
signals:
};
