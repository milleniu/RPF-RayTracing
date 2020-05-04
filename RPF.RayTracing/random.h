#pragma once

#include "common.h"

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real.hpp>

boost::random::mt19937 rng;

inline float random_float()
{
	return boost::random::uniform_real_distribution<float>()(rng);
}

inline float random_float(const float min, const float max)
{
	return boost::random::uniform_real_distribution<float>(min, max)(rng);
}
