#include "commandtab.h"
#include <QRegExpValidator>
#include <QString>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

CommandTab::CommandTab(QWidget *parent)
    :QWidget(parent)
{
    codeLabel = new QLabel(tr("Command &Code:"));
    codeEdit = new QLineEdit();
    codeLabel->setBuddy(codeEdit);
    hexCheckBox = new QCheckBox(tr("Hex"));
    sendButton = new QPushButton(tr("Send"));
    sendButton->setDefault(true);
    sendButton->setEnabled(false);

    codeEdit->setValidator(new QRegExpValidator(regDec, this));
    connect(hexCheckBox, SIGNAL(stateChanged(int)), this, SLOT(hexChanged(int)));
    connect(codeEdit, SIGNAL(textChanged(const QString&)), this, SLOT(codeChanged()));
    connect(sendButton, SIGNAL(clicked()), this, SLOT(sendCommand()));

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addWidget(codeLabel);
    leftLayout->addStretch(1);
    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(codeEdit);
    rightLayout->addWidget(hexCheckBox);
    rightLayout->addWidget(sendButton);
//    QVBoxLayout *stretchLayout = new QVBoxLayout;
//    stretchLayout->addStretch(1);
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
//    mainLayout->addLayout(stretchLayout);
    mainLayout->addStretch(1);

    setLayout(mainLayout);
}

void CommandTab::hexChanged(int state)
{
    if(state == Qt::Unchecked)
        codeEdit->setValidator(new QRegExpValidator(regDec, this));
    else
        codeEdit->setValidator(new QRegExpValidator(regHex, this));
}

void CommandTab::codeChanged()
{
    sendButton->setEnabled(codeEdit->hasAcceptableInput());
}

void CommandTab::sendCommand()
{
    bool ok;
    unsigned short code = (hexCheckBox->checkState() == Qt::Unchecked)?
                codeEdit->text().toUShort(&ok) :
                codeEdit->text().toUShort(&ok, 16);

    QMessageBox::information(this,
                             "Send Command Code",
                             QString("Command Code: %1").arg(code),
                             QMessageBox::Ok);
}
