#include <QGridLayout>
#include <QOpenGLWidget>
#include <QPushButton>
#include <QGuiApplication>
#include <QModbusTcpServer>

#include "ug_mainwindow.h"
#include "ug_openglwidget.h"
#include "ug_panel.h"
#include "ug_config.h"
#include "ug_modbustcp.h"
#include "ug_httpserver.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_CentralWidget = new QWidget(this);
    m_OpenGLWidget = new OpenGLWidget(m_CentralWidget);
    setCentralWidget(m_CentralWidget);
    setFixedSize(WINDOW_W, WINDOW_H);
    setWindowFlags(Qt::FramelessWindowHint);

    m_PanelWidget = new PanelWidget(m_CentralWidget);
    connect(m_PanelWidget, SIGNAL(SwitchRotation()), m_OpenGLWidget, SLOT(OnSwithRotation()));
    connect(m_PanelWidget, SIGNAL(TO_R()), m_OpenGLWidget, SLOT(OnTOR()));
    connect(m_PanelWidget, SIGNAL(TO_IR()), m_OpenGLWidget, SLOT(OnTOIR()));
    connect(m_PanelWidget, SIGNAL(BO_R()), m_OpenGLWidget, SLOT(OnBOR()));
    connect(m_PanelWidget, SIGNAL(BO_IR()), m_OpenGLWidget, SLOT(OnBOIR()));
    connect(m_PanelWidget, SIGNAL(L_R()), m_OpenGLWidget, SLOT(OnLR()));
    connect(m_PanelWidget, SIGNAL(L_IR()), m_OpenGLWidget, SLOT(OnLIR()));
    connect(m_PanelWidget, SIGNAL(R_R()), m_OpenGLWidget, SLOT(OnRR()));
    connect(m_PanelWidget, SIGNAL(R_IR()), m_OpenGLWidget, SLOT(OnRIR()));
    connect(m_PanelWidget, SIGNAL(F_R()), m_OpenGLWidget, SLOT(OnFR()));
    connect(m_PanelWidget, SIGNAL(F_IR()), m_OpenGLWidget, SLOT(OnFIR()));
    connect(m_PanelWidget, SIGNAL(B_R()), m_OpenGLWidget, SLOT(OnBR()));
    connect(m_PanelWidget, SIGNAL(B_IR()), m_OpenGLWidget, SLOT(OnBIR()));
    connect(m_PanelWidget, SIGNAL(ExitApp()), this, SLOT(ExitApp()));

    m_ModbusTcpServer = new ModbusTcpServer(this);
    connect(m_ModbusTcpServer, SIGNAL(TO_R()), m_OpenGLWidget, SLOT(OnTOR()));
    connect(m_ModbusTcpServer, SIGNAL(TO_IR()), m_OpenGLWidget, SLOT(OnTOIR()));
    connect(m_ModbusTcpServer, SIGNAL(BO_R()), m_OpenGLWidget, SLOT(OnBOR()));
    connect(m_ModbusTcpServer, SIGNAL(BO_IR()), m_OpenGLWidget, SLOT(OnBOIR()));
    connect(m_ModbusTcpServer, SIGNAL(L_R()), m_OpenGLWidget, SLOT(OnLR()));
    connect(m_ModbusTcpServer, SIGNAL(L_IR()), m_OpenGLWidget, SLOT(OnLIR()));
    connect(m_ModbusTcpServer, SIGNAL(R_R()), m_OpenGLWidget, SLOT(OnRR()));
    connect(m_ModbusTcpServer, SIGNAL(R_IR()), m_OpenGLWidget, SLOT(OnRIR()));
    connect(m_ModbusTcpServer, SIGNAL(F_R()), m_OpenGLWidget, SLOT(OnFR()));
    connect(m_ModbusTcpServer, SIGNAL(F_IR()), m_OpenGLWidget, SLOT(OnFIR()));
    connect(m_ModbusTcpServer, SIGNAL(B_R()), m_OpenGLWidget, SLOT(OnBR()));
    connect(m_ModbusTcpServer, SIGNAL(B_IR()), m_OpenGLWidget, SLOT(OnBIR()));

    m_HttpServer = new HttpServer(this);
    connect(m_HttpServer, SIGNAL(TO_R()), m_OpenGLWidget, SLOT(OnTOR()));
    connect(m_HttpServer, SIGNAL(TO_IR()), m_OpenGLWidget, SLOT(OnTOIR()));
    connect(m_HttpServer, SIGNAL(BO_R()), m_OpenGLWidget, SLOT(OnBOR()));
    connect(m_HttpServer, SIGNAL(BO_IR()), m_OpenGLWidget, SLOT(OnBOIR()));
    connect(m_HttpServer, SIGNAL(L_R()), m_OpenGLWidget, SLOT(OnLR()));
    connect(m_HttpServer, SIGNAL(L_IR()), m_OpenGLWidget, SLOT(OnLIR()));
    connect(m_HttpServer, SIGNAL(R_R()), m_OpenGLWidget, SLOT(OnRR()));
    connect(m_HttpServer, SIGNAL(R_IR()), m_OpenGLWidget, SLOT(OnRIR()));
    connect(m_HttpServer, SIGNAL(F_R()), m_OpenGLWidget, SLOT(OnFR()));
    connect(m_HttpServer, SIGNAL(F_IR()), m_OpenGLWidget, SLOT(OnFIR()));
    connect(m_HttpServer, SIGNAL(B_R()), m_OpenGLWidget, SLOT(OnBR()));
    connect(m_HttpServer, SIGNAL(B_IR()), m_OpenGLWidget, SLOT(OnBIR()));

    connect(m_OpenGLWidget, SIGNAL(Ok(bool)), m_ModbusTcpServer, SLOT(SetOk(bool)));
    connect(m_OpenGLWidget, SIGNAL(Ok(bool)), m_PanelWidget, SLOT(SetOk(bool)));
    connect(m_OpenGLWidget, SIGNAL(Ok(bool)), m_HttpServer, SLOT(SetOk(bool)));
}

void MainWindow::ExitApp()
{
    qDebug() << "===== EXIT =====";
    QGuiApplication::quit();
}

MainWindow::~MainWindow()
{
}
