#ifndef UG_OPENGLWIDGET_H_
#define UG_OPENGLWIDGET_H_

#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QTime>

class MagicCube;

QT_FORWARD_DECLARE_CLASS(Axis)

class OpenGLWidget: public QOpenGLWidget,
    protected QOpenGLExtraFunctions
{
    Q_OBJECT

    typedef struct
    {
        QOpenGLShaderProgram* Program;
        GLuint VBO;
        GLuint VAO;
        GLuint EBO;
        GLint ModelLocation;
        GLint ViewLocation;
        GLint ProjLocation;
    } AxisData;

public:
    explicit OpenGLWidget(QWidget *parent = nullptr);
    ~OpenGLWidget();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    void InitializeAxisGL();
    void PaintAxisGL();

    void InitializeCubeGL();
    void PaintCubeGL();

public Q_SLOTS:
    void OnTimerTimeOut();
    void OnSwithRotation();
    void OnTOR();
    void OnTOIR();
    void OnBOR();
    void OnBOIR();
    void OnLR();
    void OnLIR();
    void OnRR();
    void OnRIR();
    void OnFR();
    void OnFIR();
    void OnBR();
    void OnBIR();
    void OnOK(bool flag);

Q_SIGNALS:
    void Ok(bool flag);

private:
    GLuint m_VBO;
    GLuint m_VAO;
    GLuint m_EBO;
    GLint m_PosAttr;
    QVector<QVector2D> m_Pos;
    QOpenGLShaderProgram* m_Program;
    QVector<QMatrix4x4> m_Models;
    QMatrix4x4 m_Model, m_View, m_Proj;
    int m_ModelLocation, m_ViewLocation, m_ProjLocation;
    int m_MagicCubeModelLocation;

    GLuint m_W, m_H;
    QVector<QVector3D> m_CubePos;

    MagicCube* m_MagicCube;
    
    QTimer* m_Timer;

    double m_FPS;
    int m_ElapseTime;
    QTime m_LastTime;

    Axis* m_Axis;
    AxisData m_AxisData;
};

#endif // UG_OPENGLWIDGET_H_