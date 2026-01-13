#include <defaultmagnet.h>
#include <type_traits>

#ifndef CUBIC_MAGNET_
#define CUBIC_MAGNET_

class CubicMagnet : public Magnet
{
public:
	CubicMagnet (std::array<float, 3>& position, std::array<float, 3>& orientation, uint16_t side, float magnetization);
	// std::array<float, 3> field (std::array<float, 3>& position) override;

private:
	uint16_t m_side;
};

#endif // CUBIC_MAGNET_