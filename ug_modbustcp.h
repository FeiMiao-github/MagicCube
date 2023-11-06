#ifndef UG_MODBUS_TCP_H_
#define UG_MODBUS_TCP_H_

#include <QModbusTcpServer>

class ModbusTcpServer:
    public QModbusTcpServer
{
    Q_OBJECT
private:
    enum class COIL_ADDR: quint16 {
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

    enum class DISCRETE_INPUT_ADDR: quint16 {
        START = 0,
        OK = 0,
        MAX = 1
    };
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

public:
    ModbusTcpServer(QObject* parent = nullptr);
    ~ModbusTcpServer() override;   

public slots:
    void UpdateWidgets(QModbusDataUnit::RegisterType table, int address, int size);
};

#endif // UG_MODBUS_TCP_H_