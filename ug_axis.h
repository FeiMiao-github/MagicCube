#ifndef UG_AXIS_H_
#define UG_AXIS_H_

#include <QObject>

class Axis
    : public QObject
{
    Q_OBJECT

public:
    static constexpr unsigned XINDEX = 0;
    static constexpr unsigned YINDEX = 1;
    static constexpr unsigned ZINDEX = 2;
    static constexpr float Len = 100;
    static constexpr float VertexBuf[][3] = {
        {-Len, 0, 0},
        {Len, 0, 0},
        {0, -Len, 0},
        {0, Len, 0},
        {0, 0, -Len},
        {0, 0, Len}
    };
    static constexpr unsigned VertexBufSize = sizeof(VertexBuf);

    static constexpr unsigned IndexBuf[][2] = {
        {0, 1},
        {2, 3},
        {4, 5}
    };
    static constexpr unsigned IndexBufSize = sizeof(IndexBuf);
    static constexpr unsigned IndexStride = 3 * sizeof(float);

    static constexpr unsigned ElementSize = 6;

    explicit Axis(QObject *parent = nullptr);
    ~Axis();
};

#endif // UG_AXIS_H_
