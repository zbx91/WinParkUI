#include "mainwindow.h"
#include "ui_mainwindow.h"

extern QPlatformGlobal* g_pPlatformGlobal;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect( g_pPlatformGlobal, SIGNAL( ParseData( QString, QTcpSocket*, void* ) ),
             this, SLOT( HandleParseData( QString, QTcpSocket*, void* ) ) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    MyDataStructs::QEventMultiHash hash;
    QStringList lstTexts;

    lstTexts <<"Hello1��" << "Hello2\nTest" << "Hello3";
    g_pPlatformGlobal->GenerateLogHash( hash, lstTexts, QManipulateIniFile::LogDatabase );

    lstTexts.clear( );
    lstTexts <<"Hello11" << "Hello11" << "Hello33";
     g_pPlatformGlobal->GenerateLogHash( hash, lstTexts, QManipulateIniFile::LogNetwork );

    g_pPlatformGlobal->StartupLogWrite( g_pPlatformGlobal->GetThreadGenerator( ).GenerateLogThread( ), hash );
}

void MainWindow::on_pushButton_2_clicked()
{
    g_pPlatformGlobal->StartupThreadExit(
                g_pPlatformGlobal->GetThreadGenerator( ).GenerateLogThread( ), MyEnums::ThreadLogger );
}

void MainWindow::on_pushButton_3_clicked()
{
    g_pPlatformGlobal->BrowseLog( QManipulateIniFile::PlatformCentralLogClient );
}

void MainWindow::on_pushButton_4_clicked()
{
    g_pPlatformGlobal->TcpClientAllConnectOrDisconnect( true );
}

void MainWindow::on_pushButton_5_clicked()
{
   g_pPlatformGlobal->TcpClientAllConnectOrDisconnect( false );
}

void MainWindow::on_pushButton_6_clicked()
{
    QString strText = "Hello2\nTest�����";
    QByteArray byteData = g_pPlatformGlobal->GetCommonFunctionObj().GetTextCodec( )->fromUnicode( strText );

    g_pPlatformGlobal->TcpClientSendData2AllThreads( byteData );
}

void MainWindow::on_pushButton_7_clicked()
{
    g_pPlatformGlobal->CreateTcpClientThread( QManipulateIniFile::PlatformCentralClient );
}

void MainWindow::HandleParseData( QString strServer, QTcpSocket* pPeerSocket, void *pByteArray )
{
    QByteArray* pByteData = ( QByteArray* ) pByteArray;

    strServer += " : " + QString ( *pByteData ) + "\n";
    ui->textEdit->insertPlainText( strServer );

    delete pByteData;
}