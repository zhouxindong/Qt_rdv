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

class OptionsDialog : public QDialog
{
public:
    OptionsDialog(HJYD_GSA::rdv_conf &conf, QWidget *parent = nullptr);

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
    QLabel *cmdLabel;
    QLineEdit *cmdEdit;
    QLabel *stepLabel;
    QLineEdit *stepEdit;
    QLabel *loadLabel;
    QLineEdit *loadEdit;
    QLabel *initLabel;
    QLineEdit *initEdit;
    QLabel *startLabel;
    QLineEdit *startEdit;
    QLabel *freezeLabel;
    QLineEdit *freezeEdit;
    QLabel *unfreezeLabel;
    QLineEdit *unfreezeEdit;
    QLabel *speedLabel;
    QLineEdit *speedEdit;
    QLabel *finishLabel;
    QLineEdit *finishEdit;
    QWidget *extension;
    QDialogButtonBox *buttonBox;
    QGridLayout *cmdLayout;
    QVBoxLayout *mainLayout;
};

#endif // OPTIONSDIALOG_H
