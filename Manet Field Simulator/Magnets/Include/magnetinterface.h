#include <array>

#ifndef MAGNETS_INCLUDE_MAGNETINTERFACE_
#define MAGNETS_INCLUDE_MAGNETINTERFACE_

class MagnetInterface
{
public:
    virtual void move (float x, float y, float z) = 0;
    virtual std::array<float, 3>& position () = 0;
    virtual float magnetization () = 0;
    virtual ~MagnetInterface () = default;
};

#endif // MAGNETS_INCLUDE_MAGNETINTERFACE_
