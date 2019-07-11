#ifndef COMMANDTAB_H
#define COMMANDTAB_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QRegExp>

class CommandTab : public QWidget
{
    Q_OBJECT
public:
    CommandTab(QWidget *parent = nullptr);

private:
    QLabel *codeLabel;
    QLineEdit *codeEdit;
    QCheckBox *hexCheckBox;
    QPushButton *sendButton;

private:
    QRegExp regDec{"[1-9][0-9]{0,3}"};
    QRegExp regHex{"[A-Fa-f1-9][A-Fa-f0-9]{0,3}"};

private slots:
    void hexChanged(int state);
    void codeChanged();
    void sendCommand();
};

#endif // COMMANDTAB_H
