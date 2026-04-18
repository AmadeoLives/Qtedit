#pragma once
#include <QtWidgets>
#include <QDialog>

class ConfDialog : public QDialog {
Q_OBJECT

private:
    QTabWidget* tab;
    QWidget* createFontTab();

    QFontComboBox* fontBox;
    QSpinBox* sizeBox;

public:
    explicit ConfDialog(QWidget* parent = nullptr);
    QDialogButtonBox* dialogButtonBox;

private slots:

signals:

public slots:
signals:
    void accepted();
};
