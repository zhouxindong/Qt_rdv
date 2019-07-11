#ifndef EXTENSIONWIDGET_H
#define EXTENSIONWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include "rdv_conf.h"

class ExtensionWidget : public QWidget
{
    Q_OBJECT
public:
    ExtensionWidget(HJYD_GSA::rdv_conf &conf, QWidget *parent = nullptr);

signals:
    void visibleChanged(bool visibled);

protected:
    void showEvent(QShowEvent *event) override;
    void hideEvent(QHideEvent *event) override;

private:
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

    QGridLayout *cmdLayout;
};

#endif // EXTENSIONWIDGET_H
