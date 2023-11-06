#include <QTransform>

#include "ug_magiccube.h"
#include "ug_cube.h"

const Cube::VertexData* MagicCube::Verteices = Cube::VertexBufData;
const unsigned* MagicCube::Indeices = Cube::Indeices;
const unsigned MagicCube::IndexBufSize = Cube::IndexBufSize;
const unsigned MagicCube::ElementSize = Cube::ElementSize;
const unsigned MagicCube::VertexBufSize = Cube::VertexBufSize;
const unsigned MagicCube::VertexStride = Cube::VertexStride;

MagicCube::MagicCube(QObject* parent)
    : QObject(parent),
      m_LastOk(true),
      m_RotationFlag(false),
      m_RotationSpeed(0.0),
      m_CurAnimeType(AnimationType::DUMMY),
      m_Degs(0.0),
      m_TargetDegs(0.0),
      m_msElapseTime(0)
{
    // qDebug() << "Allow MagicCube Object " << this;
    for (int i = 0; i < edgeCubeCount; i++)
    {
        m_CubeData3Array.append(QVector<QVector<long>>());
        for (int j = 0; j < edgeCubeCount; j++)
        {
            m_CubeData3Array[i].append(QVector<long>());
            for (int k = 0; k < edgeCubeCount; k++)
            {
                m_CubeData3Array[i][j].append(-1);
            }
        }
    }

    InitCubeDatas(edgeCubeCount);

    for (unsigned i = 0; i < CubeNum; i++)
    {
        Cube* m_Cube = new Cube(this);
        m_Cube->Transform(m_CubeDates[i].Transform);
        m_Cubes.push_back(m_Cube);
    }

    m_Model.setToIdentity();
    m_Model.rotate(30, QVector3D(1, 0, 0));
    // m_Model.rotate(30, QVector3D(0, 0, 1));
    m_Model.rotate(30, QVector3D(0, 1, 0));
}

MagicCube::~MagicCube()
{
    // qDebug() << "Release MagicCube Object " << this;
}

const QVector<Cube *>& MagicCube::Cubes() const
{
    return m_Cubes;
}

const QMatrix4x4 &MagicCube::Model() const
{
    return m_Model;
}

void MagicCube::RotateLeft(bool flag)
{
    FinishRotation();
    m_Degs = 0.0;
    m_TargetDegs = flag ? 90 : -90;
    m_CurAnimeType = AnimationType::L;
    m_LastOk = false;
    emit Ok(false);
}

void MagicCube::RotateRight(bool flag)
{
    FinishRotation();
    m_Degs = 0.0;
    m_TargetDegs = flag ? 90 : -90;
    m_CurAnimeType = AnimationType::R;
    m_LastOk = false;
    emit Ok(false);
}

void MagicCube::RotateTop(bool flag)
{
    FinishRotation();
    m_Degs = 0.0;
    m_TargetDegs = flag ? 90 : -90;
    m_CurAnimeType = AnimationType::TO;
    m_LastOk = false;
    emit Ok(false);
}

void MagicCube::RotateBottom(bool flag)
{
    FinishRotation();
    m_Degs = 0.0;
    m_TargetDegs = flag ? 90 : -90;
    m_CurAnimeType = AnimationType::BO;
    m_LastOk = false;
    emit Ok(false);
}

void MagicCube::RotateFront(bool flag)
{
    FinishRotation();
    m_Degs = 0.0;
    m_TargetDegs = flag ? 90 : -90;
    m_CurAnimeType = AnimationType::F;
    m_LastOk = false;
    emit Ok(false);
}

void MagicCube::RotateBack(bool flag)
{
    FinishRotation();
    m_Degs = 0.0;
    m_TargetDegs = flag ? 90 : -90;
    m_CurAnimeType = AnimationType::B;
    m_LastOk = false;
    emit Ok(false);
}

void MagicCube::InitCubeDatas(int edgeCubeCount)
{
    Q_ASSERT(edgeCubeCount < 20 && edgeCubeCount > 0);

    QVector3D startPos;
    if (!edgeCubeCount % 2)
    {
        int halfEdgeCount = edgeCubeCount / 2;
        float dist = -(halfEdgeCount - 1) - 0.5;
        startPos = QVector3D(dist, dist, dist);
    }
    else
    {
        int halfEdgeCount = edgeCubeCount / 2;
        float dist = -halfEdgeCount;
        startPos = QVector3D(dist, dist, dist);
    }

    int i = 1, j = 1, k = 1;
    for (; i <= edgeCubeCount; i++)
    {
        QVector3D tmpPos= startPos;
        for (j = 1; j <= edgeCubeCount; j++)
        {
            for (k = 1; k <= edgeCubeCount; k++)
            {
                if (i == 1 || i == edgeCubeCount
                    || j == 1 || j == edgeCubeCount
                    || k == 1 || k == edgeCubeCount)
                {
                    m_CubeDates.append({tmpPos});
                    m_CubeData3Array[i-1][j-1][k-1] = m_CubeDates.size() - 1;
                }
                tmpPos.setZ(tmpPos.z() + 1.0);
            }
            tmpPos.setZ(startPos.z());
            tmpPos.setY(tmpPos.y() + 1.0);
        }
        tmpPos.setY(startPos.y());
        startPos.setX(startPos.x() + 1.0);
    }

    m_InitCubeData3Array = m_CubeData3Array;
}

void MagicCube::RotateDeg(const QVector<Cube *> &cubes, QVector3D axis, float deg)
{
    for (auto p = cubes.begin(); p != cubes.end(); p++)
    {
        (*p)->Rotation(axis, deg);
    }
}

QVector<Cube *> MagicCube::GetCubesByIdx(const QVector<long> &cubeIdx) const
{
    QVector<Cube *> ret;
    for (auto i: cubeIdx)
    {
        ret.append(m_Cubes[i]);
    }
    return ret;
}

QVector<long> MagicCube::GetCubeIdxByCond(const CondType &cond) const
{
    QVector<long> ret;
    for (int i = 0; i < edgeCubeCount; i++)
    {
        for (int j = 0; j < edgeCubeCount; j++)
        {
            for (int k = 0; k < edgeCubeCount; k++)
            {
                long idx = m_CubeData3Array[i][j][k];
                if (idx != -1 && cond(i, j, k))
                {
                    ret.push_back(idx);
                }
            }
        }
    }
    return ret;
}

void MagicCube::UpdateCubeIdx()
{
    bool flag = m_TargetDegs > 0 ? true : false;
    switch (m_CurAnimeType)
    {
        case AnimationType::TO:
            if (flag)
            {
                long tmp1 = m_CubeData3Array[0][2][2];
                long tmp2 = m_CubeData3Array[0][2][1];
                m_CubeData3Array[0][2][2] = m_CubeData3Array[0][2][0];
                m_CubeData3Array[0][2][1] = m_CubeData3Array[1][2][0];
                m_CubeData3Array[0][2][0] = m_CubeData3Array[2][2][0];
                m_CubeData3Array[1][2][0] = m_CubeData3Array[2][2][1];
                m_CubeData3Array[2][2][0] = m_CubeData3Array[2][2][2];
                m_CubeData3Array[2][2][1] = m_CubeData3Array[1][2][2];
                m_CubeData3Array[2][2][2] = tmp1;
                m_CubeData3Array[1][2][2] = tmp2;
            }
            else
            {
                long tmp1 = m_CubeData3Array[2][2][2]; 
                long tmp2 = m_CubeData3Array[1][2][2];
                m_CubeData3Array[2][2][2] = m_CubeData3Array[2][2][0];
                m_CubeData3Array[1][2][2] = m_CubeData3Array[2][2][1];
                m_CubeData3Array[2][2][0] = m_CubeData3Array[0][2][0];
                m_CubeData3Array[2][2][1] = m_CubeData3Array[1][2][0];
                m_CubeData3Array[0][2][0] = m_CubeData3Array[0][2][2];
                m_CubeData3Array[1][2][0] = m_CubeData3Array[0][2][1];
                m_CubeData3Array[0][2][2] = tmp1;
                m_CubeData3Array[0][2][1] = tmp2;
            }
            break;
        case AnimationType::BO:
            if (flag)
            {
                long tmp1 = m_CubeData3Array[0][0][0];
                long tmp2 = m_CubeData3Array[0][0][1];
                m_CubeData3Array[0][0][0] = m_CubeData3Array[0][0][2];
                m_CubeData3Array[0][0][1] = m_CubeData3Array[1][0][2];
                m_CubeData3Array[0][0][2] = m_CubeData3Array[2][0][2];
                m_CubeData3Array[1][0][2] = m_CubeData3Array[2][0][1];
                m_CubeData3Array[2][0][2] = m_CubeData3Array[2][0][0];
                m_CubeData3Array[2][0][1] = m_CubeData3Array[1][0][0];
                m_CubeData3Array[2][0][0] = tmp1;
                m_CubeData3Array[1][0][0] = tmp2;
            }
            else
            {
                long tmp1 = m_CubeData3Array[2][0][0]; 
                long tmp2 = m_CubeData3Array[1][0][0];
                m_CubeData3Array[2][0][0] = m_CubeData3Array[2][0][2];
                m_CubeData3Array[1][0][0] = m_CubeData3Array[2][0][1];
                m_CubeData3Array[2][0][2] = m_CubeData3Array[0][0][2];
                m_CubeData3Array[2][0][1] = m_CubeData3Array[1][0][2];
                m_CubeData3Array[0][0][2] = m_CubeData3Array[0][0][0];
                m_CubeData3Array[1][0][2] = m_CubeData3Array[0][0][1];
                m_CubeData3Array[0][0][0] = tmp1;
                m_CubeData3Array[0][0][1] = tmp2;
            }
            break;
        case AnimationType::L:
            if (flag)
            {
                long tmp1 = m_CubeData3Array[0][2][0]; 
                long tmp2 = m_CubeData3Array[0][1][0];
                m_CubeData3Array[0][2][0] = m_CubeData3Array[0][0][0];
                m_CubeData3Array[0][1][0] = m_CubeData3Array[0][0][1];
                m_CubeData3Array[0][0][0] = m_CubeData3Array[0][0][2];
                m_CubeData3Array[0][0][1] = m_CubeData3Array[0][1][2];
                m_CubeData3Array[0][0][2] = m_CubeData3Array[0][2][2];
                m_CubeData3Array[0][1][2] = m_CubeData3Array[0][2][1];
                m_CubeData3Array[0][2][2] = tmp1;
                m_CubeData3Array[0][2][1] = tmp2;
            }
            else
            {
                long tmp1 = m_CubeData3Array[0][2][2];
                long tmp2 = m_CubeData3Array[0][2][1];
                m_CubeData3Array[0][2][2] = m_CubeData3Array[0][0][2];
                m_CubeData3Array[0][2][1] = m_CubeData3Array[0][1][2];
                m_CubeData3Array[0][0][2] = m_CubeData3Array[0][0][0];
                m_CubeData3Array[0][1][2] = m_CubeData3Array[0][0][1];
                m_CubeData3Array[0][0][0] = m_CubeData3Array[0][2][0];
                m_CubeData3Array[0][0][1] = m_CubeData3Array[0][1][0];
                m_CubeData3Array[0][2][0] = tmp1;
                m_CubeData3Array[0][1][0] = tmp2;
            }
            break;
        case AnimationType::R:
            if (flag)
            {
                long tmp1 = m_CubeData3Array[2][2][2]; 
                long tmp2 = m_CubeData3Array[2][1][2];
                m_CubeData3Array[2][2][2] = m_CubeData3Array[2][0][2];
                m_CubeData3Array[2][1][2] = m_CubeData3Array[2][0][1];
                m_CubeData3Array[2][0][2] = m_CubeData3Array[2][0][0];
                m_CubeData3Array[2][0][1] = m_CubeData3Array[2][1][0];
                m_CubeData3Array[2][0][0] = m_CubeData3Array[2][2][0];
                m_CubeData3Array[2][1][0] = m_CubeData3Array[2][2][1];
                m_CubeData3Array[2][2][0] = tmp1;
                m_CubeData3Array[2][2][1] = tmp2;
            }
            else
            {
                long tmp1 = m_CubeData3Array[2][2][0];
                long tmp2 = m_CubeData3Array[2][2][1];
                m_CubeData3Array[2][2][0] = m_CubeData3Array[2][0][0];
                m_CubeData3Array[2][2][1] = m_CubeData3Array[2][1][0];
                m_CubeData3Array[2][0][0] = m_CubeData3Array[2][0][2];
                m_CubeData3Array[2][1][0] = m_CubeData3Array[2][0][1];
                m_CubeData3Array[2][0][2] = m_CubeData3Array[2][2][2];
                m_CubeData3Array[2][0][1] = m_CubeData3Array[2][1][2];
                m_CubeData3Array[2][2][2] = tmp1;
                m_CubeData3Array[2][1][2] = tmp2;
            }
            break;
        case AnimationType::F:
            if (flag)
            {
                long tmp1 = m_CubeData3Array[2][2][2]; 
                long tmp2 = m_CubeData3Array[1][2][2];
                m_CubeData3Array[2][2][2] = m_CubeData3Array[2][0][2];
                m_CubeData3Array[1][2][2] = m_CubeData3Array[2][1][2];
                m_CubeData3Array[2][0][2] = m_CubeData3Array[0][0][2];
                m_CubeData3Array[2][1][2] = m_CubeData3Array[1][0][2];
                m_CubeData3Array[0][0][2] = m_CubeData3Array[0][2][2];
                m_CubeData3Array[1][0][2] = m_CubeData3Array[0][1][2];
                m_CubeData3Array[0][2][2] = tmp1;
                m_CubeData3Array[0][1][2] = tmp2;
            }
            else
            {
                long tmp1 = m_CubeData3Array[2][0][2];
                long tmp2 = m_CubeData3Array[0][1][2];
                m_CubeData3Array[2][0][2] = m_CubeData3Array[2][2][2];
                m_CubeData3Array[0][1][2] = m_CubeData3Array[1][0][2];
                m_CubeData3Array[2][2][2] = m_CubeData3Array[0][2][2];
                m_CubeData3Array[1][0][2] = m_CubeData3Array[2][1][2];
                m_CubeData3Array[0][2][2] = m_CubeData3Array[0][0][2];
                m_CubeData3Array[2][1][2] = m_CubeData3Array[1][2][2];
                m_CubeData3Array[0][0][2] = tmp1;
                m_CubeData3Array[1][2][2] = tmp2;
            }
            break;
        case AnimationType::B:
            if (flag)
            {
                long tmp1 = m_CubeData3Array[2][2][0]; 
                long tmp2 = m_CubeData3Array[1][2][0];
                m_CubeData3Array[2][2][0] = m_CubeData3Array[0][2][0];
                m_CubeData3Array[1][2][0] = m_CubeData3Array[0][1][0];
                m_CubeData3Array[0][2][0] = m_CubeData3Array[0][0][0];
                m_CubeData3Array[0][1][0] = m_CubeData3Array[1][0][0];
                m_CubeData3Array[0][0][0] = m_CubeData3Array[2][0][0];
                m_CubeData3Array[1][0][0] = m_CubeData3Array[2][1][0];
                m_CubeData3Array[2][0][0] = tmp1;
                m_CubeData3Array[2][1][0] = tmp2;
            }
            else
            {
                long tmp1 = m_CubeData3Array[2][0][0];
                long tmp2 = m_CubeData3Array[2][1][0];
                m_CubeData3Array[2][0][0] = m_CubeData3Array[0][0][0];
                m_CubeData3Array[2][1][0] = m_CubeData3Array[1][0][0];
                m_CubeData3Array[0][0][0] = m_CubeData3Array[0][2][0];
                m_CubeData3Array[1][0][0] = m_CubeData3Array[0][1][0];
                m_CubeData3Array[0][2][0] = m_CubeData3Array[2][2][0];
                m_CubeData3Array[0][1][0] = m_CubeData3Array[1][2][0];
                m_CubeData3Array[2][2][0] = tmp1;
                m_CubeData3Array[1][2][0] = tmp2;
            }
            break;
    }

    // CubeIdxCheck();
    bool ok = CheckIfOk();
    if (ok ^ m_LastOk)
    {
        qDebug() << "OK from " << m_LastOk << "->" << ok;
        emit Ok(ok);
    }
    m_LastOk = ok;
}

void MagicCube::UpdateCubeRotation()
{
    bool animFinish = false;
    float delta = m_RotationSpeed * m_msElapseTime / 1000;
    int sign = m_TargetDegs > 0 ? 1 : -1;
    delta = sign * delta;

    if (m_CurAnimeType != AnimationType::DUMMY)
    {
        if (qAbs(delta + m_Degs) > qAbs(m_TargetDegs))
        {
            delta = m_TargetDegs - m_Degs;
            animFinish = true;
        }
        m_Degs += delta;
        // qDebug() << "Rotation " << delta << "====" << m_Degs << "====" << m_TargetDegs;
    }

    switch (m_CurAnimeType)
    {
        case AnimationType::DUMMY:
            return;
        case AnimationType::TO:
            RotateTop(delta);
            break;
        case AnimationType::BO:
            RotateBottom(delta);
            break;
        case AnimationType::L:
            RotateLeft(delta);
            break;
        case AnimationType::R:
            RotateRight(delta);
            break;
        case AnimationType::F:
            RotateFront(delta);
            break;
        case AnimationType::B:
            RotateBack(delta);
            break;
    }

    if (animFinish)
    {
        UpdateCubeIdx();
        m_Degs = 0;
        m_TargetDegs = 0;
        m_CurAnimeType = AnimationType::DUMMY;
    }
}

void MagicCube::FinishRotation()
{
    if (m_CurAnimeType == AnimationType::DUMMY)
    {
        return;
    }

    int sign = m_TargetDegs > 0 ? 1 : -1;
    float delta = m_TargetDegs - m_Degs;

    switch (m_CurAnimeType)
    {
        case AnimationType::DUMMY:
            return;
        case AnimationType::TO:
            RotateTop(delta);
            break;
        case AnimationType::BO:
            RotateBottom(delta);
            break;
        case AnimationType::L:
            RotateLeft(delta);
            break;
        case AnimationType::R:
            RotateRight(delta);
            break;
        case AnimationType::F:
            RotateFront(delta);
            break;
        case AnimationType::B:
            RotateBack(delta);
            break;
    }

    UpdateCubeIdx();
    m_CurAnimeType = AnimationType::DUMMY;
}

void MagicCube::CubeIdxCheck()
{
    for (int i = 0; i < edgeCubeCount; i++)
    {
        for (int j = 0; j < edgeCubeCount; j++)
        {
            for (int k = 0; k < edgeCubeCount; k++)
            {
                if (m_CubeData3Array[i][j][k] != -1)
                {
                    qDebug() << i << "-" << j << "-" << k << ":" << m_Cubes[m_CubeData3Array[i][j][k]]->WorldPosition();
                }

                if (i == 0 && qAbs(m_Cubes[m_CubeData3Array[i][j][k]]->WorldPosition().x() + 1) > 0.1)
                {
                    QDebug(QtMsgType::QtFatalMsg) << "ERROR!";
                }
                
                if (i == 2 && qAbs(m_Cubes[m_CubeData3Array[i][j][k]]->WorldPosition().x() - 1) > 0.1)
                {
                    QDebug(QtMsgType::QtFatalMsg) << "ERROR!";
                }

                if (j == 2 && qAbs(m_Cubes[m_CubeData3Array[i][j][k]]->WorldPosition().y() - 1) > 0.1)
                {
                    QDebug(QtMsgType::QtFatalMsg) << "ERROR!";
                }

                if (j == 0 && qAbs(m_Cubes[m_CubeData3Array[i][j][k]]->WorldPosition().y() + 1) > 0.1)
                {
                    QDebug(QtMsgType::QtFatalMsg) << "ERROR!";
                }

                if (k == 0 && qAbs(m_Cubes[m_CubeData3Array[i][j][k]]->WorldPosition().z() + 1) > 0.1)
                {
                    QDebug(QtMsgType::QtFatalMsg) << "ERROR!";
                }

                if (k == 2 && qAbs(m_Cubes[m_CubeData3Array[i][j][k]]->WorldPosition().z() - 1) > 0.1)
                {
                    QDebug(QtMsgType::QtFatalMsg) << "ERROR!";
                }
            }
        }
    }
}

bool MagicCube::CheckIfOk() const
{
    for (int i = 0; i < edgeCubeCount; i++)
    {
        for (int j = 0; j < edgeCubeCount; j++)
        {
            for (int k = 0; k < edgeCubeCount; k++)
            {
                if (m_CubeData3Array[i][j][k] != m_InitCubeData3Array[i][j][k])
                {
                    return false;
                }
            }
        }
    }
    return true;
}

void MagicCube::SwitchRotation()
{
    qDebug() << "RotationFlag " << m_RotationFlag << "->" << !m_RotationFlag;
    m_RotationFlag = !m_RotationFlag;
}

void MagicCube::SetRotationSpeed(const float speed)
{
    m_RotationSpeed = speed;
}

void MagicCube::RotateLeft(float deg)
{
    QVector<long> leftCubeIdx = GetCubeIdxByCond([](long i, long j, long k) -> bool {
        return i == 0;
    });

    QVector<Cube*> cubes = GetCubesByIdx(leftCubeIdx);
    RotateDeg(cubes, QVector3D(1, 0, 0), deg);
}

void MagicCube::RotateRight(float deg)
{
    QVector<long> cubeIdx = GetCubeIdxByCond([](long i, long j, long k) -> bool {
        return i == 2;
    });

    QVector<Cube*> cubes = GetCubesByIdx(cubeIdx);
    RotateDeg(cubes, QVector3D(-1, 0, 0), deg);
}

void MagicCube::RotateTop(float deg)
{
    QVector<long> cubeIdx = GetCubeIdxByCond([](long i, long j, long k) -> bool {
        return j == 2;
    });
    QVector<Cube*> cubes = GetCubesByIdx(cubeIdx);
    RotateDeg(cubes, QVector3D(0, 1, 0), deg);
}

void MagicCube:: RotateBottom(float deg)
{
    QVector<long> cubeIdx = GetCubeIdxByCond([](long i, long j, long k) -> bool {
        return j == 0;
    });
    QVector<Cube*> cubes = GetCubesByIdx(cubeIdx);
    RotateDeg(cubes, QVector3D(0, -1, 0), deg);
}

void MagicCube::RotateFront(float deg)
{
    QVector<long> cubeIdx = GetCubeIdxByCond([](long i, long j, long k) -> bool {
        return k == 2;
    });
    QVector<Cube*> cubes = GetCubesByIdx(cubeIdx);
    RotateDeg(cubes, QVector3D(0, 0, 1), deg);
}

void MagicCube::RotateBack(float deg)
{
    QVector<long> cubeIdx = GetCubeIdxByCond([](long i, long j, long k) -> bool {
        return k == 0;
    });
    QVector<Cube*> cubes = GetCubesByIdx(cubeIdx);
    RotateDeg(cubes, QVector3D(0, 0, -1), deg);
}

void MagicCube::Update(int msElapseTime)
{
    static const int X_AXIS = 0;
    static const int Y_AXIS = 1;
    static const int Z_AXIS = 2;

    static const QVector3D AXIS[3] = {
        QVector3D{1, 0, 0},
        QVector3D{0, 1, 0},
        QVector3D{0, 0, 1},
    };

    static double deg = 0.0;
    static int idx = 0;

    static double limit = 30;
    
    double delta = m_RotationSpeed * msElapseTime / 1000;
    m_msElapseTime = msElapseTime;

    if (m_RotationFlag)
    {
        deg += delta;
        if (deg > limit)
        {
            delta = delta + limit - deg;
        }

        QMatrix4x4 rotMat;
        rotMat.setToIdentity();
        rotMat.rotate(delta, AXIS[idx]);
        m_Model = rotMat * m_Model;

        // qDebug() << (m_Cubes[0]->Model() * QVector4D(0, 0, 0, 1));

        if (deg >= limit)
        {
            idx = rand() % 3;
            limit = rand() % 30 + 3;
            deg = 0;
        }
    }

    UpdateCubeRotation();
}
