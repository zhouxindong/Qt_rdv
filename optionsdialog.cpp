#include "optionsdialog.h"

OptionsDialog::OptionsDialog(HJYD_GSA::rdv_conf &conf, QWidget *parent)
    :QDialog (parent)
{
    setWindowIcon(QIcon(tr(":/images/options.png")));
    setWindowTitle(tr("Options - config_element_id.xml"));

    vdrRegionLabel = new QLabel(tr("VDR Region:"));
    vdrRegionEdit = new QLineEdit(QString::number(conf.config_u8(conf._XML_VDR_REGION)));
    vdrRegionEdit->setReadOnly(true);

    vdrIdLabel = new QLabel(tr("VDR ID:"));
    vdrIdEdit = new QLineEdit(QString::number(conf.config_u16(conf._XML_VDR_ID)));
    vdrIdEdit->setReadOnly(true);

    groupIpLabel = new QLabel(tr("VDR Group IP:"));
    groupIpEdit = new QLineEdit(QString(conf.config_s(conf._XML_VDR_GROUP_IP).c_str()));
    groupIpEdit->setReadOnly(true);

    groupPortLabel = new QLabel(tr("VDR Group Port:"));
    groupPortEdit = new QLineEdit(QString::number(conf.config_u16(conf._XML_VDR_GROUP_PORT)));
    groupPortEdit->setReadOnly(true);

    localIpLabel = new QLabel(tr("VDR Local IP:"));
    localIpEdit = new QLineEdit(QString(conf.config_s(conf._XML_VDR_LOCAL_IP).c_str()));
    localIpEdit->setReadOnly(true);

    localPortLabel = new QLabel(tr("VDR Local Port:"));
    localPortEdit = new QLineEdit(QString::number(conf.config_u16(conf._XML_VDR_LOCAL_PORT)));
    localPortEdit->setReadOnly(true);

    vdrOptionsLayout = new QGridLayout;
    vdrOptionsLayout->addWidget(vdrRegionLabel, 0, 0);
    vdrOptionsLayout->addWidget(vdrRegionEdit, 0, 1);
    vdrOptionsLayout->addWidget(vdrIdLabel, 1, 0);
    vdrOptionsLayout->addWidget(vdrIdEdit, 1, 1);
    vdrOptionsLayout->addWidget(groupIpLabel, 2, 0);
    vdrOptionsLayout->addWidget(groupIpEdit, 2, 1);
    vdrOptionsLayout->addWidget(groupPortLabel, 3, 0);
    vdrOptionsLayout->addWidget(groupPortEdit, 3, 1);
    vdrOptionsLayout->addWidget(localIpLabel, 4, 0);
    vdrOptionsLayout->addWidget(localIpEdit, 4, 1);
    vdrOptionsLayout->addWidget(localPortLabel, 5, 0);
    vdrOptionsLayout->addWidget(localPortEdit, 5, 1);

    moreButton = new QPushButton(moreStr);
    moreButton->setCheckable(true);
    moreButton->setAutoDefault(false);
    closeButton = new QPushButton(tr("Close"));
    closeButton->setDefault(true);

    extension = new QWidget;
    extension->setVisible(false);

    buttonBox = new QDialogButtonBox(Qt::Horizontal);
    buttonBox->addButton(moreButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(closeButton, QDialogButtonBox::AcceptRole);
    connect(moreButton, &QAbstractButton::toggled, extension, &QWidget::setVisible);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch();
    buttonLayout->addWidget(moreButton);
    buttonLayout->addWidget(closeButton);

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

    extension->setLayout(cmdLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addLayout(vdrOptionsLayout);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(extension);

    setLayout(mainLayout);
}
