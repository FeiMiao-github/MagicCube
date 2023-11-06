#ifndef UG_CUBE_H_
#define UG_CUBE_H_

#include <QMatrix4x4>
#include <QVector3D>
#include <QObject>
#include <QColor>

class Cube
    : public QObject
{
    Q_OBJECT

public:
    typedef struct 
    {
        float Point[3];
        float Color[3];
    } VertexData;

    static const unsigned Indeices[];
    static const unsigned IndexBufSize;

    static const QColor TopColor;
    static const QColor BottomColor;
    static const QColor FrontColor;
    static const QColor BackColor;
    static const QColor LeftColor;
    static const QColor RightColor;

    static const VertexData VertexBufData[];
    static const unsigned VertexBufSize;
    static const unsigned VertexStride = sizeof(VertexData);

    static const unsigned ElementSize;

    explicit Cube(QObject *parent = nullptr);
    ~Cube();

    void Transform(const QVector3D& transform);
    void Scale(const QVector3D& scale);
    void Rotation(const QVector3D& axis, float deg);

    const QMatrix4x4& Model() const;
    const QMatrix4x4& Model(const QMatrix4x4& model);

    const QVector4D& WorldPosition();

private:

    QMatrix4x4 m_Model;
    QVector4D m_WorldPos;
};

#endif // UG_CUBE_H_