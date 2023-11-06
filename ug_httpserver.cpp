#include <QHttpServer>
#include <QJsonObject>
#include "ug_httpserver.h"

HttpServer::HttpServer(QObject* parent)
    : QObject(parent),
      m_Ok(true)
{
    m_HttpServer = new QHttpServer(this);

    m_HttpServer->route("/", []() { return "Hello World"; });
    m_HttpServer->route("/query", [this]() {
        return QJsonObject{{{"State", m_Ok}}};
    });
    m_HttpServer->route("/write/<arg>", [this] (const quint16& id) {
        switch(static_cast<WRITE_ID>(id))
        {
            case WRITE_ID::TO_R:
                emit TO_R();
                break;
            case WRITE_ID::TO_IR:
                emit TO_IR();
                break;
            case WRITE_ID::BO_R:
                emit BO_R();
                break;
            case WRITE_ID::BO_IR:
                emit BO_IR();
                break;
            case WRITE_ID::L_R:
                emit L_R();
                break;
            case WRITE_ID::L_IR:
                emit L_IR();
                break;
            case WRITE_ID::R_R:
                emit R_R();
                break;
            case WRITE_ID::R_IR:
                emit R_IR();
                break;
            case WRITE_ID::F_R:
                emit F_R();
                break;
            case WRITE_ID::F_IR:
                emit F_IR();
                break;
            case WRITE_ID::B_R:
                emit B_R();
                break;
            case WRITE_ID::B_IR:
                emit B_IR();
                break;
        }
        return QJsonObject{{{"id", id}}};
    });
    m_HttpServer->listen(QHostAddress::Any, 5080);

}

HttpServer::~HttpServer() {}

void HttpServer::SetOk(bool flag)
{
    m_Ok = flag;
}