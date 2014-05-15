#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QTextBrowser>
#include <QtGui>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QMessageBox>
#include "BF_debug_interp.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Ui::MainWindow *ui;
    QToolBar *toolbar;
    QTextEdit *textEdit;
    QMenu *fileMenu;
    QMenu *example;
    QAction *przyklad;
    QAction *przyklad2;
    QAction *fileMenuNew;
    QAction *fileMenuOpen;
    QAction *fileMenuSave;
    QAction *fileMenuSaveAs;
    QAction *fileMenuQuit;

    QMenu *editMenu;
    QAction *Undo;
    QAction *Redo;
    QAction *Cut;
    QAction *Copy;
    QAction *Paste;

    QMenu *buildMenu;
    QAction *Run;
    QAction *Stop;
    QAction *Debug;
    QAction *nextStep;
    QMenu *Settings;
    QAction *setMemLen;

    QMenu *convertMenu;
    QAction *toC;
    QAction *toJava;

    BF_debug_interp *braifuck;
    int memLen;
    void setMenuBar();
    void setToolBar();
    void setSingnals();
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setChar(char);
private slots:
    void sNew();
    void sOpen();
    void sSave();
    void sSaveAs();
    void sEg(QString);
    void sRun();
    void sDebug();
    void sStop();
    void sUndo();
    void sRedo();
    void sCut();
    void sPaste();
    void sCopy();
    void sSend();
    void sToC();
    void sToJava();
signals:
    void sig();
};

#endif // MAINWINDOW_H
