#ifndef UG_PANEL_H_
#define UG_PANEL_H_

#include <QObject>
#include <QWidget>

QT_FORWARD_DECLARE_CLASS(QPushButton)
QT_FORWARD_DECLARE_CLASS(QVBoxLayout)
QT_FORWARD_DECLARE_CLASS(QLabel)

class PanelWidget
    : public QWidget
{
    Q_OBJECT

public:
    explicit PanelWidget(QWidget* parent = nullptr);
    ~PanelWidget();

public Q_SLOTS:
    void OnRotationBtnClicked(bool value);
    void OnTORBtnClicked(bool value);
    void OnTOIRBtnClicked(bool value);
    void OnBORBtnClicked(bool value);
    void OnBOIRBtnClicked(bool value);
    void OnLRBtnClicked(bool value);
    void OnLIRBtnClicked(bool value);
    void OnRRBtnClicked(bool value);
    void OnRIRBtnClicked(bool value);
    void OnFRBtnClicked(bool value);
    void OnFIRBtnClicked(bool value);
    void OnBRBtnClicked(bool value);
    void OnBIRBtnClicked(bool value);
    void OnExitButtonClicked(bool value);
    void SetOk(bool value);

Q_SIGNALS:
    void SwitchRotation();
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
    void ExitApp();

private:
    static const char* OK;
    static const char* NOT_OK;

    QWidget* m_Base;
    QVBoxLayout* m_Layout;

    QPushButton* m_RotationButton;
    QPushButton* m_TO_Rot;
    QPushButton* m_TO_IRot;
    QPushButton* m_BO_Rot;
    QPushButton* m_BO_IRot;
    QPushButton* m_L_Rot;
    QPushButton* m_L_IRot;
    QPushButton* m_R_Rot;
    QPushButton* m_R_IRot;
    QPushButton* m_F_Rot;
    QPushButton* m_F_IRot;
    QPushButton* m_B_Rot;
    QPushButton* m_B_IRot;
    QPushButton* m_Exit;

    QLabel* m_Ok;
};

#endif // UG_PANEL_H_
