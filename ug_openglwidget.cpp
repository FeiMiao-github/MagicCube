#include <QFlags>
#include <QTimer>

#include "ug_openglwidget.h"
#include "ug_magiccube.h"
#include "ug_axis.h"
#include "ug_config.h"

OpenGLWidget::OpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      m_Program(nullptr),
      m_FPS(72),
      m_ElapseTime(0)
{
    m_W = WINDOW_W;
    m_H = WINDOW_H;
    setFixedSize(m_W, m_H);

    m_MagicCube = new MagicCube(this);
    m_MagicCube->SetRotationSpeed(20.0);
    connect(m_MagicCube, SIGNAL(Ok(bool)), this, SLOT(OnOK(bool)));

    m_Timer = new QTimer(this);
    m_Timer->setInterval(1.0 / m_FPS);

    m_View.setToIdentity();
    m_View.translate(0, 0, -10);

    m_Proj.setToIdentity();
    m_Proj.perspective(45.0f, (float)m_W * 1.0f / m_H, 0.1f, 100.0f);

    m_Axis = new Axis(this);

    connect(m_Timer, SIGNAL(timeout()), this, SLOT(OnTimerTimeOut()));
    m_Timer->start();

    m_LastTime = QTime::currentTime();
}

void OpenGLWidget::InitializeAxisGL()
{
    m_AxisData.Program = new QOpenGLShaderProgram(this);
    m_AxisData.Program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/axis_shader.vert");
    m_AxisData.Program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/axis_shader.frag");
    m_AxisData.Program->link();

    m_AxisData.ModelLocation = m_AxisData.Program->uniformLocation("ug_Model");
    m_AxisData.ViewLocation = m_AxisData.Program->uniformLocation("ug_View");
    m_AxisData.ProjLocation = m_AxisData.Program->uniformLocation("ug_Proj");

    glGenVertexArrays(1, &m_AxisData.VAO);
    glGenBuffers(1, &m_AxisData.VBO);
    glGenBuffers(1, &m_AxisData.EBO);

    glBindVertexArray(m_AxisData.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_AxisData.VBO);
    glBufferData(GL_ARRAY_BUFFER, Axis::VertexBufSize, Axis::VertexBuf, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_AxisData.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Axis::IndexBufSize, Axis::IndexBuf, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, Axis::IndexStride, NULL);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void OpenGLWidget::PaintAxisGL()
{
    m_AxisData.Program->bind();
    m_AxisData.Program->setUniformValue(m_AxisData.ViewLocation, m_View);
    m_AxisData.Program->setUniformValue(m_AxisData.ProjLocation, m_Proj);
    QMatrix4x4 Identify;
    Identify.setToIdentity();
    m_AxisData.Program->setUniformValue(m_AxisData.ModelLocation, Identify);

    glBindVertexArray(m_AxisData.VAO);

    glDrawElements(GL_LINES, Axis::ElementSize, GL_UNSIGNED_INT, NULL);
}

void OpenGLWidget::InitializeCubeGL()
{
    m_Program = new QOpenGLShaderProgram(this);
    m_Program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shader.vert");
    m_Program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shader.frag");

    m_Program->link();

    m_ModelLocation = m_Program->uniformLocation("ug_Model");
    m_ViewLocation = m_Program->uniformLocation("ug_View");
    m_ProjLocation = m_Program->uniformLocation("ug_Proj");
    m_MagicCubeModelLocation = m_Program->uniformLocation("ug_magiccube_Model");

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, MagicCube::VertexBufSize, MagicCube::Verteices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, MagicCube::IndexBufSize, MagicCube::Indeices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, MagicCube::VertexStride, NULL);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, MagicCube::VertexStride, reinterpret_cast<void*>(3 * sizeof(float)));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void OpenGLWidget::PaintCubeGL()
{
    m_Program->bind();
    m_Program->setUniformValue(m_ViewLocation, m_View);
    m_Program->setUniformValue(m_ProjLocation, m_Proj);
    m_Program->setUniformValue(m_MagicCubeModelLocation, m_MagicCube->Model());
    glBindVertexArray(m_VAO);

    auto& cubes = m_MagicCube->Cubes();
    for (auto p = cubes.cbegin(); p!= cubes.cend(); p++)
    {
        m_Program->setUniformValue(m_ModelLocation, (*p)->Model());
        glDrawElements(GL_TRIANGLES, MagicCube::ElementSize, GL_UNSIGNED_INT, NULL);
    }
}

void OpenGLWidget::OnSwithRotation()
{
    Q_ASSERT(m_MagicCube != nullptr);
    m_MagicCube->SwitchRotation();
}

void OpenGLWidget::OnTOR()
{
    qDebug() << __FUNCTION__ << " run !";
    m_MagicCube->RotateTop(false);
}

void OpenGLWidget::OnTOIR()
{
    qDebug() << __FUNCTION__ << " run !";
    m_MagicCube->RotateTop(true);
}

void OpenGLWidget::OnBOR()
{
    qDebug() << __FUNCTION__ << " run !";
    m_MagicCube->RotateBottom(false);
}

void OpenGLWidget::OnBOIR()
{
    qDebug() << __FUNCTION__ << " run !";
    m_MagicCube->RotateBottom(true);
}

void OpenGLWidget::OnLR()
{
    qDebug() << __FUNCTION__ << " run !";
    m_MagicCube->RotateLeft(false);
}

void OpenGLWidget::OnLIR()
{
    qDebug() << __FUNCTION__ << " run !";
    m_MagicCube->RotateLeft(true);
}

void OpenGLWidget::OnRR()
{
    qDebug() << __FUNCTION__ << " run !";
    m_MagicCube->RotateRight(true);
}

void OpenGLWidget::OnRIR()
{
    qDebug() << __FUNCTION__ << " run !";
    m_MagicCube->RotateRight(false);
}

void OpenGLWidget::OnFR()
{
    qDebug() << __FUNCTION__ << " run !";
    m_MagicCube->RotateFront(true);
}

void OpenGLWidget::OnFIR()
{
    qDebug() << __FUNCTION__ << " run !";
    m_MagicCube->RotateFront(false);
}

void OpenGLWidget::OnBR()
{
    qDebug() << __FUNCTION__ << " run !";
    m_MagicCube->RotateBack(false);
}

void OpenGLWidget::OnBIR()
{
    qDebug() << __FUNCTION__ << " run !";
    m_MagicCube->RotateBack(true);
}

void OpenGLWidget::OnOK(bool flag)
{
    emit Ok(flag);
}

OpenGLWidget::~OpenGLWidget()
{
}

void OpenGLWidget::initializeGL()
{
    // qDebug() << __FUNCTION__ << ":" << __LINE__;

    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);

    InitializeCubeGL();
    InitializeAxisGL();
}

void OpenGLWidget::resizeGL(int w, int h)
{
    // qDebug() << __FUNCTION__ << ":" << __LINE__ << "(" << w << "," << h << ")";

    glClearColor(.5, .5, .5, 1);
    glViewport(0, 0, w, h);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLWidget::paintGL()
{
    static int count = 0;
    QTime time = QTime::currentTime();
    m_ElapseTime = m_LastTime.msecsTo(time);
    m_LastTime = time;
    // qDebug() << "Delta Time: " << m_ElapseTime;
    // qDebug() << "paint GL..." << count << "...";

    m_MagicCube->Update(m_ElapseTime);

    PaintCubeGL();
    PaintAxisGL();

    count ++;
}

void OpenGLWidget::OnTimerTimeOut()
{
    // qDebug() << "Timeout ...";
    update();
}

