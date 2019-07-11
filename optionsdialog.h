#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>
#include "rdv_conf.h"
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QIcon>
#include <QPushButton>
#include <QHBoxLayout>
#include "extensionwidget.h"

class OptionsDialog : public QDialog
{
    Q_OBJECT
public:
    OptionsDialog(HJYD_GSA::rdv_conf &conf, QWidget *parent = nullptr);

private slots:
    void extensionVisible(bool visible);

private:
    QString moreStr = "More >>";
    QString lessStr = "Less <<";

private:
    QLabel *vdrRegionLabel;
    QLineEdit *vdrRegionEdit;
    QLabel *vdrIdLabel;
    QLineEdit *vdrIdEdit;
    QLabel *groupIpLabel;
    QLineEdit *groupIpEdit;
    QLabel *groupPortLabel;
    QLineEdit *groupPortEdit;
    QLabel *localIpLabel;
    QLineEdit *localIpEdit;
    QLabel *localPortLabel;
    QLineEdit *localPortEdit;

    QGridLayout *vdrOptionsLayout;
    QPushButton *moreButton;
    QPushButton *closeButton;

    ExtensionWidget *extension;
    QDialogButtonBox *buttonBox;

    QVBoxLayout *mainLayout;
};

#endif // OPTIONSDIALOG_H
