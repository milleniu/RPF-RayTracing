#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

#include <boost/math/tools/precision.hpp>

#include <iostream>

#include "random.h"

using namespace ray_tracing;
using namespace ray_tracing::hittable;
using namespace ray_tracing::core;

color ray_color(const ray& r, const hittable_base& world)
{
	hit_record record;
	if (world.hit(r, 0.F, boost::math::tools::max_value<float>(), record))
	{
		return (record.normal + color{1.F, 1.F, 1.F}) * 0.5F;
	}

	const auto unit_direction = unit_vector(r.direction());
	const auto t = 0.5F * (unit_direction.a[1] + 1.F);
	return color{1.F, 1.F, 1.F} * (1.F - t) + color{0.5F, 0.7F, 1.F} * t;
}

int main()
{
	try
	{
		const auto aspect_ratio = 16.F / 9.F;
		const auto image_width = 1080;
		const auto image_height = static_cast<int>(image_width / aspect_ratio);
		const auto samples = 100;

		std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

		const camera main_camera
		{
			{0.F, 0.F, 0.F},
			{4.F, 0.F, 0.F},
			{0.F, 2.25F, 0.F},
			{0.F, 0.F, 1.F}
		};

		hittable_list world;
		world.add(std::make_shared<sphere>(point3{0.F, 0.F, -1.F}, 0.5F));
		world.add(std::make_shared<sphere>(point3{0.F, -100.5F, -1.F}, 100.F));

		for (auto j = image_height - 1; j >= 0; --j)
		{
			std::cerr << "\rScan lines remaining: " << j << std::flush;
			for (auto i = 0; i < image_width; ++i)
			{
				color pixel_color{0.F, 0.F, 0.F};
				for (auto s = 0; s < samples; ++s)
				{
					const auto u = (i + random_float()) / (image_width - 1.F);
					const auto v = (j + random_float()) / (image_height - 1.F);
					const auto r = main_camera.get_ray(u, v);
					pixel_color += ray_color(r, world);
				}

				write_to(std::cout, pixel_color / samples);
			}
		}

		std::cerr << "\nDone.\n";
		return EXIT_SUCCESS;
	}
	catch (std::exception const& exception)
	{
		std::cerr << typeid(exception).name() << std::endl;
		return EXIT_FAILURE;
	}
}
