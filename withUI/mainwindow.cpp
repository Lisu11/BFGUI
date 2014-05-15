#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setGeometry(100,100,1142,800);
    setMenuBar();
    setToolBar();
    //resizable(false);
    this->setFixedSize(this->width(),this->height());
    ui->textEdit->setText(QString(",>>,>,>,\n------------------------------------------------\n<------------------------------------------------\n[->++++++++++<]\n++++++++++>\n[\n\t[->+<<<<<.>>>>]\n\t<.>>\n\t[-<+>]\n\t<-\n]"));
    memLen = 256;
    braifuck = NULL;
    setSingnals();
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::sNew()
{

}

void MainWindow::sOpen()
{

}

void MainWindow::sSave()
{
}

void MainWindow::sSaveAs()
{

}


void MainWindow::sEg(QString name)
{

}

void MainWindow::sRun()
{
    ui->textBrowser->setText(QString(""));
    try{
        braifuck = new BF_debug_interp(this->ui->textEdit->toPlainText(),
                                   memLen, this->ui->textBrowser);
    } catch(std::string ex) {
        ui->textBrowser->setText("ERROR WRONG CODE");
        return;
    }
    braifuck->start(QThread::NormalPriority);
    Debug->setEnabled(false);
    Stop->setEnabled(true);
    Run->setEnabled(false);
    connect(braifuck, SIGNAL(finished()), this, SLOT(sStop()));
}

void MainWindow::sDebug()
{
    ui->textBrowser->setText(QString(""));
    try{
        braifuck = new BF_debug_interp(this->ui->textEdit->toPlainText(),
                                   memLen, this->ui->textBrowser);
    } catch(std::string ex) {
        ui->textBrowser->setText("ERROR WRONG CODE");
        return;
    }

    braifuck->setDebuggeMode(true);
    Debug->setEnabled(false);
    Run->setEnabled(false);
    Stop->setEnabled(true);
    nextStep->setEnabled(true);
    connect(nextStep, SIGNAL(triggered()), braifuck, SLOT( doNextInstruction()) );
}

void MainWindow::sStop()
{
    if(!(braifuck->isFinished())){
        braifuck->quit();
        ui->textBrowser->setText(ui->textBrowser->toPlainText()+QString("\nPROGRAM HAS BEEN STOPED"));
    } else {
        ui->textBrowser->setText(ui->textBrowser->toPlainText()+QString("\nPROGRAM ENDED SUCCESSFULLY"));
        disconnect(braifuck, SIGNAL(finished()), this, SLOT(sStop()));
        delete braifuck;
    }
    Stop->setEnabled(false);
    Run->setEnabled(true);
    Debug->setEnabled(true);
    nextStep->setEnabled(false);

    braifuck = NULL;

}


void MainWindow::sUndo()
{
    ui->textEdit->undo();
}

void MainWindow::sRedo()
{
    ui->textEdit->redo();
}

void MainWindow::sCut()
{
    ui->textEdit->cut();
}

void MainWindow::sPaste()
{
    ui->textEdit->paste();
}

void MainWindow::sCopy()
{
    ui->textEdit->copy();
}

void MainWindow::sSend()
{
    if(braifuck != NULL){
         //ui->textBrowser->setText(QString("nie jest nullem"));
        QString s = ui->lineEdit->text();
        for(int i=0; i < s.length(); i++)
            braifuck->addInput(s[i].toLatin1());

    }
    ui->lineEdit->setText(QString(""));
}

void MainWindow::sToC()
{

}

void MainWindow::sToJava()
{

}


void MainWindow::setMenuBar(){
    // menu Plik
   fileMenu = menuBar()->addMenu("&File");

       // menu Plik/Nowy
       fileMenuNew = new QAction (QIcon (":/images/new.png"),"&New",this);
       fileMenuNew -> setShortcut (QString ("Ctrl+N"));
       fileMenuNew -> setStatusTip ("Open new file");
       fileMenu -> addAction (fileMenuNew);

       // menu Plik/Otwórz
       fileMenuOpen = new QAction (QIcon (":/images/open.png"),"&Open",this);
       fileMenuOpen -> setShortcut (QString("Ctrl+O"));
       fileMenuOpen -> setStatusTip ("Open existing file");
       fileMenu -> addAction (fileMenuOpen);

       // menu Plik/Zapisz
       fileMenuSave = new QAction ("&Save",this);
       fileMenuSave -> setIcon (QIcon (":/images/save.png"));
       fileMenuSave -> setShortcut (QKeySequence::Save);
       fileMenuSave -> setStatusTip ("Save current state");
       fileMenu -> addAction (fileMenuSave);

       // menu Plik/Zapisz jako
       fileMenuSaveAs = new QAction ("Save As",this);
       fileMenuSaveAs -> setStatusTip ("Save file as..");
       fileMenu -> addAction (fileMenuSaveAs);

       example = new QMenu("Examples", fileMenu);
       fileMenu->addAction(example->menuAction());
       przyklad = new QAction("Przyklad1", this);
       przyklad2 = new QAction("Przyklad2", this);
       example->addAction(przyklad);
       example->addAction(przyklad2);
       fileMenu -> addSeparator ();  // separator

       // menu Plik/Wyjcie
       fileMenuQuit = new QAction ("Quit",this);
       fileMenuQuit -> setStatusTip ("Exit program");
       fileMenuQuit -> setShortcut (Qt::Key_F4 | Qt::AltModifier);
       fileMenu -> addAction (fileMenuQuit);

       editMenu = menuBar()->addMenu("&Edit");
       Undo = new QAction(QIcon(":/images/undo.png"),"&Undo",this);
       Undo->setShortcut(QString("Ctrl+Z"));
       editMenu->addAction(Undo);
       Redo = new QAction(QIcon(":/images/redo.png"),"&Redo",this);
       Redo->setShortcut(QString("Ctrl+Shift+Z"));
       editMenu->addAction(Redo);
       editMenu -> addSeparator ();  // separator

       Cut = new QAction(QIcon(":/images/cut.png"),"Cut",this);
       Cut->setShortcut(QString("Ctrl+X"));
       editMenu->addAction(Cut);

       Copy = new QAction(QIcon(":/images/copy.png"),"&Copy",this);
       Copy->setShortcut(QString("Ctrl+C"));
       editMenu->addAction(Copy);

       Paste = new QAction(QIcon(":/images/paste.png"),"Paste",this);
       Paste->setShortcut(QString("Ctrl+V"));
       editMenu->addAction(Paste);

       buildMenu = menuBar()->addMenu("Build");
       Run = new QAction(QIcon(":/images/run.png"), "Run", this);
       buildMenu->addAction(Run);

       Stop = new QAction(QIcon(":/images/stop.png"), "Stop", this);
       buildMenu->addAction(Stop);
        Stop->setEnabled(false);
       Debug = new QAction(QIcon(":/images/debug.png"), "Debug", this);
       buildMenu->addAction(Debug);

       nextStep = new QAction(QIcon(":/images/next.png"), "Next Instruction", this);
       buildMenu->addAction(nextStep);
       nextStep->setEnabled(false);

       convertMenu = menuBar()->addMenu("Conver");
       toC = new QAction("To C", this);
       toJava = new QAction("To Java", this);
       convertMenu->addAction(toC);
       convertMenu->addAction(toJava);
}
void MainWindow::setToolBar(){
    toolbar = new QToolBar(this);
    toolbar->addAction(Run);
    toolbar->addAction(Stop);
    toolbar->addAction(Debug);
    toolbar->addAction(nextStep);

    addToolBar(Qt::TopToolBarArea, toolbar);
}

void MainWindow::setSingnals()
{
    connect(fileMenuNew, SIGNAL(triggered()), this, SLOT( sNew() ));
    connect(fileMenuOpen, SIGNAL(triggered()), this, SLOT( sOpen() ));
    connect(fileMenuSave, SIGNAL(triggered()), this, SLOT( sSave() ));
    connect(fileMenuQuit, SIGNAL(triggered()), qApp, SLOT(quit() ));
    connect(fileMenuSaveAs, SIGNAL(triggered()), this, SLOT( sSaveAs() ));
    connect(this->ui->send_button, SIGNAL(clicked()), this, SLOT(sSend()));
    //connect(przyklad, SIGNAL(triggered()), this, SLOT( sEg((QString)"przyklad") ));
    connect(Run, SIGNAL(triggered()), this, SLOT( sRun() ));
    connect(Debug, SIGNAL(triggered()), this, SLOT( sDebug() ));
    connect(Stop, SIGNAL(triggered()), this, SLOT( sStop() ));

    connect(Undo, SIGNAL(triggered()), this, SLOT( sUndo() ));
    connect(Redo, SIGNAL(triggered()), this, SLOT( sRedo() ));

    connect(Copy, SIGNAL(triggered()), this, SLOT(sCopy()));
    connect(Cut, SIGNAL(triggered()), this, SLOT(sCut()));
    connect(Paste, SIGNAL(triggered()), this, SLOT(sPaste()));
    connect(toC, SIGNAL(triggered()), this, SLOT(sToC()));
    connect(toJava, SIGNAL(triggered()), this, SLOT(sToJava()));

}
