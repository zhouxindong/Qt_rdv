#include "extensionwidget.h"
#include <QShowEvent>

ExtensionWidget::ExtensionWidget(HJYD_GSA::rdv_conf &conf, QWidget *parent)
    :QWidget (parent)
{
    cmdLabel = new QLabel(QString::fromLocal8Bit("指令数据名:"));
    cmdEdit = new QLineEdit(QString::fromLocal8Bit(conf.config_s(conf._XML_CTL_CMD).c_str()));
    cmdEdit->setReadOnly(true);

    stepLabel = new QLabel(QString::fromLocal8Bit("步长数据名:"));
    stepEdit = new QLineEdit(QString::fromLocal8Bit(conf.config_s(conf._XML_CTL_SPEED).c_str()));
    stepEdit->setReadOnly(true);

    loadLabel = new QLabel(QString::fromLocal8Bit("资源加载："));
    loadEdit = new QLineEdit(QString::number(conf.config_u16(conf._XML_CMD_LOAD)));
    loadEdit->setReadOnly(true);

    initLabel = new QLabel(QString::fromLocal8Bit("初始化:"));
    initEdit = new QLineEdit(QString::number(conf.config_u16(conf._XML_CMD_INIT)));
    initEdit->setReadOnly(true);

    startLabel = new QLabel(QString::fromLocal8Bit("仿真开始:"));
    startEdit = new QLineEdit(QString::number(conf.config_u16(conf._XML_CMD_START)));
    startEdit->setReadOnly(true);

    freezeLabel = new QLabel(QString::fromLocal8Bit("仿真暂停:"));
    freezeEdit = new QLineEdit(QString::number(conf.config_u16(conf._XML_CMD_FREEZE)));
    freezeEdit->setReadOnly(true);

    unfreezeLabel = new QLabel(QString::fromLocal8Bit("仿真继续:"));
    unfreezeEdit = new QLineEdit(QString::number(conf.config_u16(conf._XML_CMD_UNFREEZE)));
    unfreezeEdit->setReadOnly(true);

    speedLabel = new QLabel(QString::fromLocal8Bit("调整步长:"));
    speedEdit = new QLineEdit(QString::number(conf.config_u16(conf._XML_CMD_SPEED)));
    speedEdit->setReadOnly(true);

    finishLabel = new QLabel(QString::fromLocal8Bit("仿真结束:"));
    finishEdit = new QLineEdit(QString::number(conf.config_u16(conf._XML_CMD_FINISH)));
    finishEdit->setReadOnly(true);

    cmdLayout = new QGridLayout;
    cmdLayout->setMargin(0);
    cmdLayout->addWidget(cmdLabel, 0, 0);
    cmdLayout->addWidget(cmdEdit, 0, 1);
    cmdLayout->addWidget(stepLabel, 1, 0);
    cmdLayout->addWidget(stepEdit, 1, 1);
    cmdLayout->addWidget(loadLabel, 2, 0);
    cmdLayout->addWidget(loadEdit, 2, 1);
    cmdLayout->addWidget(initLabel, 3, 0);
    cmdLayout->addWidget(initEdit, 3, 1);
    cmdLayout->addWidget(startLabel, 4, 0);
    cmdLayout->addWidget(startEdit, 4, 1);
    cmdLayout->addWidget(freezeLabel, 5, 0);
    cmdLayout->addWidget(freezeEdit, 5, 1);
    cmdLayout->addWidget(unfreezeLabel, 6, 0);
    cmdLayout->addWidget(unfreezeEdit, 6, 1);
    cmdLayout->addWidget(speedLabel, 7, 0);
    cmdLayout->addWidget(speedEdit, 7, 1);
    cmdLayout->addWidget(finishLabel, 8, 0);
    cmdLayout->addWidget(finishEdit, 8, 1);

    setLayout(cmdLayout);
}

void ExtensionWidget::showEvent(QShowEvent */*event*/)
{
    emit visibleChanged(true);
}

void ExtensionWidget::hideEvent(QHideEvent */*event*/)
{
    emit visibleChanged(false);
}
