#include "ug_cube.h"

const unsigned Cube::Indeices[] = {
    0, 1, 2, 0, 2, 3,
    4, 5, 6, 4, 6, 7,
    8, 9, 10, 8, 10, 11,
    12, 13, 14, 12, 14, 15,
    16, 17, 18, 16, 18, 19,
    20, 21, 22, 20, 22, 23,
};
const unsigned Cube::IndexBufSize = sizeof(Cube::Indeices);
const unsigned Cube::ElementSize = sizeof(Cube::Indeices) / sizeof(unsigned);

const QColor Cube::TopColor = QColor("blue");
const QColor Cube::BottomColor = QColor("white");
const QColor Cube::FrontColor = QColor("green");
const QColor Cube::BackColor = QColor("yellow");
const QColor Cube::LeftColor = QColor("red");
const QColor Cube::RightColor = QColor("orange");

#define BOTTOM_COLOR Cube::BottomColor.redF(), Cube::BottomColor.greenF(), Cube::BottomColor.blueF()
#define TOP_COLOR Cube::TopColor.redF(), Cube::TopColor.greenF(), Cube::TopColor.blueF()
#define FRONT_COLOR Cube::FrontColor.redF(), Cube::FrontColor.greenF(), Cube::FrontColor.blueF()
#define BACK_COLOR Cube::BackColor.redF(), Cube::BackColor.greenF(), Cube::BackColor.blueF()
#define LEFT_COLOR Cube::LeftColor.redF(), Cube::LeftColor.greenF(), Cube::LeftColor.blueF()
#define RIGHT_COLOR Cube::RightColor.redF(), Cube::RightColor.greenF(), Cube::RightColor.blueF()

#define HALF_EDGE_LENGTH 0.45
#define LEFT_TOP_BACK -HALF_EDGE_LENGTH, HALF_EDGE_LENGTH, -HALF_EDGE_LENGTH
#define LEFT_TOP_FRONT -HALF_EDGE_LENGTH, HALF_EDGE_LENGTH, HALF_EDGE_LENGTH
#define LEFT_BOTTOM_BACK -HALF_EDGE_LENGTH, -HALF_EDGE_LENGTH, -HALF_EDGE_LENGTH
#define LEFT_BOTTOM_FRONT -HALF_EDGE_LENGTH, -HALF_EDGE_LENGTH, HALF_EDGE_LENGTH
#define RIGHT_TOP_BACK HALF_EDGE_LENGTH, HALF_EDGE_LENGTH, -HALF_EDGE_LENGTH
#define RIGHT_TOP_FRONT HALF_EDGE_LENGTH, HALF_EDGE_LENGTH, HALF_EDGE_LENGTH
#define RIGHT_BOTTOM_BACK HALF_EDGE_LENGTH, -HALF_EDGE_LENGTH, -HALF_EDGE_LENGTH
#define RIGHT_BOTTOM_FRONT HALF_EDGE_LENGTH, -HALF_EDGE_LENGTH, HALF_EDGE_LENGTH

const Cube::VertexData Cube::VertexBufData[] = {
    {LEFT_BOTTOM_BACK, LEFT_COLOR},
    {LEFT_BOTTOM_FRONT, LEFT_COLOR},
    {LEFT_TOP_FRONT, LEFT_COLOR},
    {LEFT_TOP_BACK, LEFT_COLOR},

    {RIGHT_BOTTOM_FRONT, RIGHT_COLOR},
    {RIGHT_BOTTOM_BACK, RIGHT_COLOR},
    {RIGHT_TOP_BACK, RIGHT_COLOR},
    {RIGHT_TOP_FRONT, RIGHT_COLOR},

    {LEFT_BOTTOM_BACK, BACK_COLOR},
    {RIGHT_BOTTOM_BACK, BACK_COLOR},
    {RIGHT_TOP_BACK, BACK_COLOR},
    {LEFT_TOP_BACK, BACK_COLOR},

    {LEFT_BOTTOM_FRONT, FRONT_COLOR},
    {RIGHT_BOTTOM_FRONT, FRONT_COLOR},
    {RIGHT_TOP_FRONT, FRONT_COLOR},
    {LEFT_TOP_FRONT, FRONT_COLOR},

    {LEFT_TOP_FRONT, TOP_COLOR},
    {RIGHT_TOP_FRONT, TOP_COLOR},
    {RIGHT_TOP_BACK, TOP_COLOR},
    {LEFT_TOP_BACK, TOP_COLOR},

    {LEFT_BOTTOM_FRONT, BOTTOM_COLOR},
    {RIGHT_BOTTOM_FRONT, BOTTOM_COLOR},
    {RIGHT_BOTTOM_BACK, BOTTOM_COLOR},
    {LEFT_BOTTOM_BACK, BOTTOM_COLOR},
};
const unsigned Cube::VertexBufSize = sizeof(Cube::VertexBufData);

Cube::Cube(QObject *parent)
    : QObject(parent)
{
    // qDebug() << "Alloc Cube Object " << this;
    m_Model.setToIdentity();
}

Cube::~Cube()
{
    // qDebug() << "Release Cube Object " << this;
}

void Cube::Transform(const QVector3D& transform)
{
    QMatrix4x4 trans;
    trans.setToIdentity();
    trans.translate(transform);
    m_Model = trans * m_Model;
}

void Cube::Scale(const QVector3D &scale)
{
    QMatrix4x4 scaleMat;
    scaleMat.setToIdentity();
    scaleMat.scale(scale);
    m_Model = scaleMat * m_Model;
}

void Cube::Rotation(const QVector3D &axis, float deg)
{
    QMatrix4x4 rotMat;
    rotMat.setToIdentity();
    rotMat.rotate(deg, axis);
    m_Model = rotMat * m_Model;
}

const QMatrix4x4 &Cube::Model() const
{
    return m_Model;
}

const QVector4D& Cube::WorldPosition()
{
    m_WorldPos = m_Model * QVector4D(0, 0, 0, 1);
    return m_WorldPos;
}
