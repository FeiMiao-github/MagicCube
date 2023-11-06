#ifndef UG_HTTPSERVER_H_
#define UG_HTTPSERVER_H_

#include <QHttpServer>

class HttpServer
    : public QObject
{
    Q_OBJECT

    enum class WRITE_ID: quint16 {
        START = 0,
        TO_R = 0,
        TO_IR = 1,
        BO_R = 2,
        BO_IR = 3,
        L_R = 4,
        L_IR = 5,
        R_R = 6,
        R_IR = 7,
        F_R = 8,
        F_IR = 9,
        B_R = 10,
        B_IR = 11,
        MAX = 12,
    };

public:
    HttpServer(QObject* parent = nullptr);
    ~HttpServer() override;

Q_SIGNALS:
    void TO_R();
    void TO_IR();
    void BO_R();
    void BO_IR();
    void L_R();
    void L_IR();
    void R_R();
    void R_IR();
    void F_R();
    void F_IR();
    void B_R();
    void B_IR();

public Q_SLOTS:
    void SetOk(bool flag);

private:
    QHttpServer* m_HttpServer;
    bool m_Ok;
};

#endif // UG_HTTPSERVER_H_