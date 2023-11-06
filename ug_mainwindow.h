#ifndef UG_MAINWINDOW_H_
#define UG_MAINWINDOW_H_

#include <QMainWindow>

QT_FORWARD_DECLARE_CLASS(QGridLayout)
QT_FORWARD_DECLARE_CLASS(OpenGLWidget)
QT_FORWARD_DECLARE_CLASS(PanelWidget)
QT_FORWARD_DECLARE_CLASS(ModbusTcpServer)
QT_FORWARD_DECLARE_CLASS(HttpServer)

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

public Q_SLOTS:
    void ExitApp();

private:
    QWidget* m_CentralWidget;
    OpenGLWidget* m_OpenGLWidget;
    PanelWidget* m_PanelWidget;
    ModbusTcpServer* m_ModbusTcpServer;
    HttpServer* m_HttpServer;
};
#endif // UG_MAINWINDOW_H_
