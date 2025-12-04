#include <defaultmagnet.h>
#include <type_traits>

#ifndef CYLINDER_MAGNET_
#define CYLINDER_MAGNET_

class CylinderMagnet : public Magnet
{
public:
    CylinderMagnet (float x, float y, float z, uint16_t height, uint16_t radius, float magnetization);

private:
    uint16_t m_height, m_radius;
};

#endif // CYLINDER_MAGNET_