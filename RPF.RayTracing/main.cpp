#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "hemispheric.h"
#include "lambertian.h"
#include "random.h"
#include "metal.h"
#include "dielectric.h"

#include <boost/math/tools/precision.hpp>

#include <iostream>

using namespace ray_tracing;
using namespace ray_tracing::hittable;
using namespace ray_tracing::core;

hittable_list get_world()
{
	hittable_list world;
	
	world.add(std::make_shared<sphere>
		(
			point3{0.F, 0.F, -1.F},
			0.5F,
			std::make_shared<material::lambertian>(color{0.1F, 0.2F, 0.5F})
		)
	);

	world.add(std::make_shared<sphere>
		(
			point3{0.F, -100.5F, -1.F},
			100.F,
			std::make_shared<material::lambertian>(color{0.8F, 0.8F, 0.F})
		)
	);

	world.add(std::make_shared<sphere>
		(
			point3{1.F, 0.F, -1.F},
			0.5F,
			std::make_shared<material::metal>(color{0.8F, 0.6F, 0.2F}, 0.F)
		)
	);

	world.add(std::make_shared<sphere>
		(
			point3{ -1.F, 0.F, -1.F },
			0.5F,
			std::make_shared<material::dielectric>(1.5F)
		)
	);

	world.add(std::make_shared<sphere>
		(
			point3{ -1.F, 0.F, -1.F },
			-0.45F,
			std::make_shared<material::dielectric>(1.5F)
		)
	);

	return world;
}

int main()
{
	try
	{
		const auto aspect_ratio = 16.F / 9.F;
		const auto image_width = 1200;
		const auto image_height = static_cast<int>(image_width / aspect_ratio);
		const auto samples = 50;
		const auto max_depth = 50;

		std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

		const auto world = get_world();

		const point3 camera_position{-2.F, 2.F, 1.F};
		const point3 camera_target{0.F, 0.F, -1.F};
		const float field_of_view = 20;
		const float aperture = 2;
		
		const auto focus_distance = mag(camera_target - camera_position);
		
		const camera main_camera{camera_position, camera_target, field_of_view, aspect_ratio, aperture, focus_distance};

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
					pixel_color += evaluate_ray_color(r, world, max_depth);
				}

				write_color_to(std::cout, pixel_color / samples);
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
