#ifndef UG_MAGICCUBE_H_
#define UG_MAGICCUBE_H_

#include <QVector>
#include <QObject>
#include <functional>

#include "ug_cube.h"

class MagicCube
    : public QObject
{
    Q_OBJECT
private:
    typedef struct 
    {
        QVector3D Transform;
    } CubeData;

    enum class AnimationType {
        TO,
        BO,
        L,
        R,
        F,
        B,
        DUMMY
    };

Q_SIGNALS:
    void Ok(bool flag);

public:
    explicit MagicCube(QObject* parent = nullptr);
    ~MagicCube();

    MagicCube(const MagicCube&) = delete;
    MagicCube& operator=(const MagicCube&) = delete;

    static const Cube::VertexData* Verteices;
    static const unsigned VertexBufSize;
    static const unsigned VertexStride;
    static const unsigned* Indeices;
    static const unsigned IndexBufSize;
    static const unsigned ElementSize;
    static constexpr unsigned CubeNum = 26;
    static constexpr int edgeCubeCount = 3;
 
    void Update(int msElapseTime);
    void SwitchRotation();
    void SetRotationSpeed(const float speed);

    const QVector<Cube*>& Cubes() const;
    const QMatrix4x4& Model() const;

    void RotateLeft(bool flag);
    void RotateRight(bool flag);
    void RotateTop(bool flag);
    void RotateBottom(bool flag);
    void RotateFront(bool flag);
    void RotateBack(bool flag);

private:
    void RotateLeft(float deg = 90.0);
    void RotateRight(float deg = 90.0);
    void RotateTop(float deg = 90.0);
    void RotateBottom(float deg = 90.0);
    void RotateFront(float deg = 90.0);
    void RotateBack(float deg = 90.0);

    using CondType = std::function<bool(long i, long j, long k)>;

    void InitCubeDatas(int edgeCubeCount = 3);
    void RotateDeg(const QVector<Cube*>& cubes, QVector3D axis, float deg = 90.0f);

    QVector<Cube*> GetCubesByIdx(const QVector<long>& cubeIdx) const;
    QVector<long> GetCubeIdxByCond(const CondType& cond) const;
    void UpdateCubeIdx();
    void UpdateCubeRotation();
    void FinishRotation();

    void CubeIdxCheck();
    bool CheckIfOk() const;

private:
    QVector<CubeData> m_CubeDates;
    QVector<QVector<QVector<long>>> m_CubeData3Array;
    QVector<QVector<QVector<long>>> m_InitCubeData3Array;
    bool m_LastOk;

    QMatrix4x4 m_Model;

    QVector<Cube*> m_Cubes;

    bool m_RotationFlag;
    float m_RotationSpeed;

    AnimationType m_CurAnimeType;
    float m_Degs;
    float m_TargetDegs;
    int m_msElapseTime;
};

#endif // UG_MAGICCUBE_H_