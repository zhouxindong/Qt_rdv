#include "optionsdialog.h"
#include <QMessageBox>

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

    extension = new ExtensionWidget(conf, this);
    connect(extension, SIGNAL(visibleChanged(bool)), this, SLOT(extensionVisible(bool)));
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

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addLayout(vdrOptionsLayout);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(extension);

    setLayout(mainLayout);
}

void OptionsDialog::extensionVisible(bool visible)
{
    visible ? moreButton->setText(lessStr) :
              moreButton->setText(moreStr);
}
