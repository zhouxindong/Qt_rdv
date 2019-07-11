#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "rdv_core.h"

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QToolBar;
class QLabel;
class QTreeWidget;
class QListWidget;
class QTabWidget;
class QSplitter;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    HJYD_GSA::rdv_conf conf;

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();

    void createTabs();
    void createCental();

private slots:
    void connect();
    void disconnect();
    void refresh();
    void options();
    void about();

    void setConnected(bool connected);

private:
    QMenu *systemMenu;
    QMenu *helpMenu;

    QAction *connectAction;
    QAction *disconnectAction;
    QAction *refreshAction;
    QAction *optionsAction;
    QAction *exitAction;

    QAction *aboutAction;
    QAction *aboutQtAction;

    QToolBar *systemToolBar;

private:
    QLabel *vdrConfLabel;

private:
    QTreeWidget *treeWidget;
    QListWidget *listWidget;
    QTabWidget *tabWidget;

    QSplitter *rightSplitter;
    QSplitter *mainSplitter;
};

#endif // MAINWINDOW_H
