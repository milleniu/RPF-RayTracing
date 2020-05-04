#include "color.h"

#include <iostream>

int main()
{
	const auto image_width = 256;
	const auto image_height = 256;

	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (auto j = image_height - 1; j >= 0; --j)
	{
		std::cerr << "\rScan lines remaining: " << j << std::flush;
		for (auto i = 0; i < image_width; ++i)
		{
			const color pixel_color
			(
				static_cast<float>(i) / (image_width - 1),
				static_cast<float>(j) / (image_height - 1),
				0.25F
			);

			write_color(std::cout, pixel_color);
		}
	}

	std::cerr << "\nDone.\n";
}
