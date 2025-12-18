#define _USE_MATH_DEFINES

#ifndef MAGNETS_INCLUDE_DEFAULTMAGNET_
#define MAGNETS_INCLUDE_DEFAULTMAGNET_

#include <magnetinterface.h>
#include <math.h>

static constexpr float mu0 = 4.0f * M_PI * 1e-7f;

class Magnet : public MagnetInterface
{
public:
    Magnet (std::array<float, 3> position, std::array<float, 3> orientation, float magnetization);
    void move (float x, float y, float z) override;
    void rotate (float degrees, std::array<float, 3> axis) override;
    void rotate (float degrees, std::array<float, 3> axis, std::array<float, 3> anchor) override;
    std::array<float, 3>& orientation () override;
    std::array<float, 3>& position () override;
    std::array<float, 3> field (std::array<float, 3> position) override;
    float magnetization () override;
    ~Magnet () = default;

protected:
    std::array<float, 3> m_position, m_orientation;
    float m_magnetization, m_farFieldThreshold;
};

#endif // MAGNETS_INCLUDE_DEFAULTMAGNET_