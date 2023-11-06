#include <QModbusTcpServer>
#include <QUrl>
#include "ug_modbustcp.h"

ModbusTcpServer::ModbusTcpServer(QObject *parent)
    : QModbusTcpServer(parent)
{
    QUrl url = QUrl::fromUserInput("127.0.0.1:5502");
    setConnectionParameter(ConnectionParameter::NetworkAddressParameter, url.host());
    setConnectionParameter(ConnectionParameter::NetworkPortParameter, url.port());
    setServerAddress(1);

    QModbusDataUnitMap reg;
    reg.insert(QModbusDataUnit::Coils, {
        QModbusDataUnit::Coils,
        static_cast<quint16>(COIL_ADDR::START),
        static_cast<quint16>(COIL_ADDR::MAX)
    });
    reg.insert(QModbusDataUnit::DiscreteInputs, {
        QModbusDataUnit::DiscreteInputs,
        static_cast<quint16>(DISCRETE_INPUT_ADDR::START),
        static_cast<quint16>(DISCRETE_INPUT_ADDR::MAX),
    });
    setMap(reg);

    connectDevice();
    qDebug() << "Modbus Tcp Server listenning: " << url.host().toInt() << ":" << url.port();

    connect(this, &QModbusServer::dataWritten, this, &ModbusTcpServer::UpdateWidgets);

    SetOk(true);
}

ModbusTcpServer::~ModbusTcpServer()
{
}

void ModbusTcpServer::UpdateWidgets(QModbusDataUnit::RegisterType table, int address, int size)
{
    for (int i = 0; i < size; i++)
    {
        quint16 value;
        quint16 addr;
        switch (table)
        {
        case QModbusDataUnit::RegisterType::Coils:
            addr = address + i;
            this->data(QModbusDataUnit::Coils, quint16(address + i), &value);
            if (value)
            {
                switch(static_cast<COIL_ADDR>(addr))
                {
                    case COIL_ADDR::TO_R:
                        emit TO_R();
                        break;
                    case COIL_ADDR::TO_IR:
                        emit TO_IR();
                        break;
                    case COIL_ADDR::BO_R:
                        emit BO_R();
                        break;
                    case COIL_ADDR::BO_IR:
                        emit BO_IR();
                        break;
                    case COIL_ADDR::L_R:
                        emit L_R();
                        break;
                    case COIL_ADDR::L_IR:
                        emit L_IR();
                        break;
                    case COIL_ADDR::R_R:
                        emit R_R();
                        break;
                    case COIL_ADDR::R_IR:
                        emit R_IR();
                        break;
                    case COIL_ADDR::F_R:
                        emit F_R();
                        break;
                    case COIL_ADDR::F_IR:
                        emit F_IR();
                        break;
                    case COIL_ADDR::B_R:
                        emit B_R();
                        break;
                    case COIL_ADDR::B_IR:
                        emit B_IR();
                        break;
                }
                this->setData(QModbusDataUnit::Coils, quint16(address + i), 0);
            }
            break;
        
        default:
            break;
        }
    }
}

void ModbusTcpServer::SetOk(bool flag)
{
    this->setData(QModbusDataUnit::DiscreteInputs, quint16(DISCRETE_INPUT_ADDR::OK), quint16(flag));
}