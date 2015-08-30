#ifndef SELECTSECTIONDIALOG_H
#define SELECTSECTIONDIALOG_H

#include <QDialog>

namespace Ui {
class SelectSectionDialog;
}

class SelectSectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectSectionDialog(QWidget *parent = 0);
    void accept();
    ~SelectSectionDialog();
    void addsections(int);

private:
    Ui::SelectSectionDialog *ui;
    int total_sections;

signals:
    void sendSelectedSection(int);
};

#endif // SELECTSECTIONDIALOG_H
