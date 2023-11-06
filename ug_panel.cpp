#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

#include "ug_panel.h"

const char* PanelWidget::OK = "STATUS: OK";
const char* PanelWidget::NOT_OK = "STATUS: NG";

PanelWidget::PanelWidget(QWidget *parent)
    : QWidget(parent)
{
    // qDebug() << "Alloc PanelWidget " << this;

    setStyleSheet("background-color: gray");

    m_Layout = new QVBoxLayout(this);

    m_RotationButton = new QPushButton("Start Rotation", this);
    m_Layout->addWidget(m_RotationButton);

    connect(m_RotationButton, SIGNAL(clicked(bool)), this, SLOT(OnRotationBtnClicked(bool)));

    QVector<std::pair<const char*, const char*>> buttons;
    buttons.append(std::make_pair("TO_R", SLOT(OnTORBtnClicked(bool))));
    buttons.append(std::make_pair("TO_IR", SLOT(OnTOIRBtnClicked(bool))));
    buttons.append(std::make_pair("BO_R", SLOT(OnBORBtnClicked(bool))));
    buttons.append(std::make_pair("BO_IR", SLOT(OnBOIRBtnClicked(bool))));
    buttons.append(std::make_pair("L_R", SLOT(OnLRBtnClicked(bool))));
    buttons.append(std::make_pair("L_IR", SLOT(OnLIRBtnClicked(bool))));
    buttons.append(std::make_pair("R_R", SLOT(OnRRBtnClicked(bool))));
    buttons.append(std::make_pair("R_IR", SLOT(OnRIRBtnClicked(bool))));
    buttons.append(std::make_pair("F_R", SLOT(OnFRBtnClicked(bool))));
    buttons.append(std::make_pair("F_IR", SLOT(OnFIRBtnClicked(bool))));
    buttons.append(std::make_pair("B_R", SLOT(OnBRBtnClicked(bool))));
    buttons.append(std::make_pair("B_IR", SLOT(OnBIRBtnClicked(bool))));
    for (auto &pair: buttons)
    {
        QPushButton* button = new QPushButton(pair.first, this);
        m_Layout->addWidget(button);
        connect(button, SIGNAL(clicked(bool)), this, pair.second);
    }

    m_Exit = new QPushButton("Exit", this);
    m_Layout->addWidget(m_Exit);
    connect(m_Exit, SIGNAL(clicked(bool)), this, SLOT(OnExitButtonClicked(bool)));

    m_Ok = new QLabel(OK, this);
    m_Layout->addWidget(m_Ok);
}

PanelWidget::~PanelWidget()
{
    // qDebug() << "Release PanelWidget " << this;
}

void PanelWidget::OnTORBtnClicked(bool value)
{
    emit TO_R();
}

void PanelWidget::OnTOIRBtnClicked(bool value)
{
    emit TO_IR();
}

void PanelWidget::OnBORBtnClicked(bool value)
{
    emit BO_R();
}

void PanelWidget::OnBOIRBtnClicked(bool value)
{
    emit BO_IR();
}

void PanelWidget::OnLRBtnClicked(bool value)
{
    emit L_R();
}

void PanelWidget::OnLIRBtnClicked(bool value)
{
    emit L_IR();
}

void PanelWidget::OnRRBtnClicked(bool value)
{
    emit R_R();
}

void PanelWidget::OnRIRBtnClicked(bool value)
{
    emit R_IR();
}

void PanelWidget::OnFRBtnClicked(bool value)
{
    emit F_R();
}

void PanelWidget::OnFIRBtnClicked(bool value)
{
    emit F_IR();
}

void PanelWidget::OnBRBtnClicked(bool value)
{
    emit B_R();
}

void PanelWidget::OnBIRBtnClicked(bool value)
{
    emit B_IR();
}

void PanelWidget::OnExitButtonClicked(bool value)
{
    emit ExitApp();
}

void PanelWidget::SetOk(bool value)
{
    if (value)
    {
        m_Ok->setText(OK);
    }
    else
    {
        m_Ok->setText(NOT_OK);
    }
}

void PanelWidget::OnRotationBtnClicked(bool value)
{
    // qDebug() << "Rotation Button Clicked ... " << value;
    emit SwitchRotation();
}

