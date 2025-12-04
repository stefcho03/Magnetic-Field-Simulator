#include <defaultmagnet.h>
#include <type_traits>

#ifndef CUBIC_MAGNET_
#define CUBIC_MAGNET_

class CubicMagnet : public Magnet
{
public:
    CubicMagnet (float x, float y, float z, uint16_t side, float magnetization);

private:
    uint16_t m_side;
};

#endif // CUBIC_MAGNET_