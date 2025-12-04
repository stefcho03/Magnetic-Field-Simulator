#include <magnetinterface.h>

#ifndef MAGNETS_INCLUDE_DEFAULTMAGNET_
#define MAGNETS_INCLUDE_DEFAULTMAGNET_

class Magnet : public MagnetInterface
{
public:
    Magnet (float x, float y, float z, float magnetization);
    void move (float x, float y, float z) override;
    std::array<float, 3>& position () override;
    float magnetization () override;
    ~Magnet () = default;

protected:
    std::array<float, 3> m_position;
    float m_magnetization;
};

#endif // MAGNETS_INCLUDE_DEFAULTMAGNET_