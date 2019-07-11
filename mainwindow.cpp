#include "mainwindow.h"
#include <QCloseEvent>
#include <QAction>
#include <QApplication>
#include <QMessageBox>
#include <QMenuBar>
#include <QToolBar>
#include <QLabel>
#include <QStatusBar>
#include "commandtab.h"
#include <QTreeWidget>
#include <QListWidget>
#include <QSplitter>
#include "optionsdialog.h"

MainWindow::MainWindow()
{
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    createTabs();
    createCental();

    setWindowIcon(QIcon(":/images/main.png"));
    setWindowTitle("rdv - a Easy vdr @ HJYD corp");
    resize(1024, 768);

    setConnected(false);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
}

void MainWindow::createActions()
{
    connectAction = new QAction(tr("&Connect"), this);
    connectAction->setIcon(QIcon(":/images/connect.png"));
    connectAction->setShortcut(tr("Ctrl+C"));
    connectAction->setStatusTip(tr("Connect to VDR Server"));
    QObject::connect(connectAction, SIGNAL(triggered()), this, SLOT(connect()));

    disconnectAction = new QAction(tr("&Disconnect"), this);
    disconnectAction->setIcon(QIcon(":/images/disconnect.png"));
    disconnectAction->setShortcut(tr("Ctrl+D"));
    disconnectAction->setStatusTip(tr("Disconnect from VDR Server"));
    QObject::connect(disconnectAction, SIGNAL(triggered()), this, SLOT(disconnect()));

    refreshAction = new QAction(tr("&Refresh"), this);
    refreshAction->setIcon(QIcon(":/images/refresh.png"));
    refreshAction->setShortcut(tr("Ctrl+R"));
    refreshAction->setStatusTip(tr("Refresh VDR Server"));
    QObject::connect(refreshAction, SIGNAL(triggered()), this, SLOT(refresh()));

    optionsAction = new QAction(tr("&Options..."), this);
    optionsAction->setIcon(QIcon(":/images/options.png"));
    optionsAction->setShortcut(tr("Ctrl+O"));
    optionsAction->setStatusTip(tr("Show options used for VDR"));
    QObject::connect(optionsAction, SIGNAL(triggered()), this, SLOT(options()));

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setIcon(QIcon(":/images/exit.png"));
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the application"));
    QObject::connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setIcon(QIcon(":/images/about.png"));
    aboutAction->setStatusTip(tr("Show the application's About box"));
    QObject::connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAction = new QAction(tr("About Q&t"), this);
    aboutQtAction->setIcon(QIcon(":/images/aboutqt.png"));
    aboutQtAction->setStatusTip(tr("Show the Qt library's About box"));
    QObject::connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus()
{
    systemMenu = menuBar()->addMenu(tr("&System"));
    systemMenu->addAction(connectAction);
    systemMenu->addAction(disconnectAction);
    systemMenu->addSeparator();
    systemMenu->addAction(refreshAction);
    systemMenu->addAction(optionsAction);
    systemMenu->addSeparator();
    systemMenu->addAction(exitAction);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);
}

void MainWindow::createToolBars()
{
    systemToolBar = addToolBar(tr("&System"));
    systemToolBar->addAction(connectAction);
    systemToolBar->addAction(disconnectAction);
    systemToolBar->addSeparator();
    systemToolBar->addAction(refreshAction);
    systemToolBar->addAction(optionsAction);
}

void MainWindow::createStatusBar()
{
    vdrConfLabel = new QLabel(tr("Ready"));
    statusBar()->addWidget(vdrConfLabel, 1);
}

void MainWindow::createTabs()
{
    tabWidget = new QTabWidget;
    tabWidget->setTabPosition(QTabWidget::South);
    tabWidget->addTab(new CommandTab(), tr("Command"));
}

void MainWindow::createCental()
{
    treeWidget = new QTreeWidget;
    treeWidget->setColumnCount(1);
    treeWidget->setHeaderLabel("Unknown Server");

    listWidget = new QListWidget;

    rightSplitter = new QSplitter(Qt::Vertical);
    rightSplitter->addWidget(listWidget);
    rightSplitter->addWidget(tabWidget);
    rightSplitter->setStretchFactor(1, 1);
    rightSplitter->setStretchFactor(0, 3);
    rightSplitter->setHandleWidth(2);

    mainSplitter = new QSplitter(Qt::Horizontal);
    mainSplitter->addWidget(treeWidget);
    mainSplitter->addWidget(rightSplitter);
    mainSplitter->setStretchFactor(0, 1);
    mainSplitter->setStretchFactor(1, 3);
    mainSplitter->setHandleWidth(3);

    setCentralWidget(mainSplitter);
}

void MainWindow::connect()
{
    QMessageBox::information(this, tr("action"), tr("connect() called"), QMessageBox::Ok);
}

void MainWindow::disconnect()
{
    QMessageBox::information(this, tr("action"), tr("disconnect() called"), QMessageBox::Ok);
}

void MainWindow::refresh()
{
    QMessageBox::information(this, tr("action"), tr("refresh() called"), QMessageBox::Ok);
}

void MainWindow::options()
{       
//    QMessageBox::information(this, tr("action"), tr("options() called"), QMessageBox::Ok);
    OptionsDialog *dialog = new OptionsDialog(conf, this);
    dialog->exec();
    delete dialog;
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About rdv_demo"),
            tr("<h2>rdv_demo 0.11</h2>"
               "<p>Copyright &copy; 2019 HJYD Inc."
               "<p>This application is used to show how to use"
               " the rdv api (a Easy vdr) to build your own application."
               "<p>If you encount any question, contact me: 13611050407@139.com"
               "<p>Enjoy yourself. :)"));
}

void MainWindow::setConnected(bool connected)
{
    connectAction->setEnabled(!connected);
    disconnectAction->setEnabled(connected);
}
