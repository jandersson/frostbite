#ifndef HIGHLIGHTADDDIALOG_H
#define HIGHLIGHTADDDIALOG_H

#include <QDialog>
#include <QtGui>

#include <highlighttexttab.h>
#include <highlightsettings.h>
#include <highlightsettingsentry.h>

class HighlightTextTab;

namespace Ui {
    class HighlightAddDialog;
}

class HighlightAddDialog : public QDialog {
    Q_OBJECT

public:
    explicit HighlightAddDialog(HighlightTextTab *textTab, QWidget *parent = 0);
    ~HighlightAddDialog();

    QComboBox* getGroupSelect();

private:
    Ui::HighlightAddDialog *ui;
    HighlightTextTab *textTab;
    HighlightSettings *settings;

private slots:
    void okPressed();
    void cancelPressed();
};

#endif // HIGHLIGHTADDDIALOG_H