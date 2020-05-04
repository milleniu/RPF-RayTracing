#pragma once

#include "common.h"

#include <iostream>

inline void write_to(std::ostream &out, const color pixel_color)
{
	out << static_cast<int>(255.999 * pixel_color.a[0]) << ' '
		<< static_cast<int>(255.999 * pixel_color.a[1]) << ' '
		<< static_cast<int>(255.999 * pixel_color.a[2]) << '\n';
}
