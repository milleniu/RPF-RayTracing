#include "core/include/color.h"
#include "core/include/camera.h"
#include "core/include/random.h"
#include "hittable/include/hittable_list.h"
#include "hittable/include/sphere.h"
#include "hittable/include/moving_sphere.h"
#include "hittable/include/bounding_volume_hierarchy.h"
#include "material/include/lambertian.h"
#include "material/include/metal.h"
#include "material/include/dielectric.h"
#include "texture/include/checker.h"
#include "texture/include/noise.h"

#include <boost/math/tools/precision.hpp>

#include <iostream>

using namespace ray_tracing;

hittable::hittable_list get_world(float t0, float t1)
{
	hittable::hittable_list world;

	world.add
	(
		std::make_shared<hittable::sphere>
		(
			point3{ 0.F, -1000.F, 0.F },
			1000.F,
			std::make_shared<material::lambertian>
			(
				std::make_shared<texture::checker>
				(
					color{ 0.2F, 0.3F, 0.1F },
					color{ 0.9F, 0.9F, 0.9F }
					)
				)
			)
	);

	hittable::hittable_list spheres;
	for (auto a = -11; a < 11; ++a)
	{
		hittable::hittable_list slice;

		for (auto b = -11; b < 11; ++b)
		{
			const auto material = random::random_value<float>();
			const auto position = point3{
				a + 0.9F * random::random_value<float>(),
				0.2F,
				b + 0.9F * random::random_value<float>()
			};

			if (mag(position - vector3{ 4.F, 0.2F, 0.F }) > 0.9F)
			{
				if (material < 0.8F)
				{
					const auto albedo = random::random_vector() * random::random_vector();
					const auto destination = position + vector3{ 0.F, random::random_value(0.F, 0.5F), 0.F };

					slice.add
					(
						std::make_shared<hittable::moving_sphere>
						(
							position,
							destination,
							0.F,
							1.F,
							0.2F,
							std::make_shared<material::lambertian>(albedo)
							)
					);
				}
				else if (material < 0.95F)
				{
					const auto albedo = random::random_vector(.5F, 1);
					const auto fuzz = random::random_value<float>(0, .5F);
					slice.add
					(
						std::make_shared<hittable::sphere>
						(
							position,
							0.2F,
							std::make_shared<material::metal>(albedo, fuzz)
							)
					);
				}
				else
				{
					slice.add
					(
						std::make_shared<hittable::sphere>
						(
							position,
							0.2F,
							std::make_shared<material::dielectric>(1.5F)
							)
					);
				}
			}
		}

		spheres.add
		(
			std::make_shared<hittable::bounding_volume_hierarchy>
			(
				slice,
				t0,
				t1
				)
		);
	}

	world.add
	(
		std::make_shared<hittable::bounding_volume_hierarchy>
		(
			spheres,
			t0,
			t1
			)
	);

	world.add
	(
		std::make_shared<hittable::sphere>
		(
			point3{ 0.F, 1.F, 0.F },
			1.F,
			std::make_shared<material::dielectric>(1.5F)
			)
	);

	world.add
	(
		std::make_shared<hittable::sphere>
		(
			point3{ -4.F, 1.F, 0.F },
			1.F,
			std::make_shared<material::lambertian>(color{ .4F, .2F, .1F })
			)
	);

	world.add
	(
		std::make_shared<hittable::sphere>
		(
			point3{ 4.F, 1.F, 0.F },
			1.F,
			std::make_shared<material::metal>(color{ .7F, .6F, .5F }, 0.F)
			)
	);

	return world;
}

hittable::hittable_list two_spheres()
{
	hittable::hittable_list world;

	const auto checker = std::make_shared<texture::checker>
	(
		color{ 0.2F, 0.3F, 0.1F },
		color{ 0.9F, 0.9F, 0.9F }
	);

	world.add
	(
		std::make_shared<hittable::sphere>
		(
			point3{ 0.F, -10.F, 0.F },
			10.F,
			std::make_shared<material::lambertian>(checker)
		)
	);

	world.add
	(
		std::make_shared<hittable::sphere>
		(
			point3{ 0.F, 10.F, 0.F },
			10.F,
			std::make_shared<material::lambertian>(checker)
		)
	);

	return world;
}

hittable::hittable_list two_perlin_spheres()
{
	hittable::hittable_list world;

	const auto perlin = std::make_shared<texture::noise>(4.F);

	world.add
	(
		std::make_shared<hittable::sphere>
		(
			point3{ 0.F, -1000.F, 0.F },
			1000.F,
			std::make_shared<material::lambertian>(perlin)
		)
	);

	world.add
	(
		std::make_shared<hittable::sphere>
		(
			point3{ 0.F, 2.F, 0.F },
			2.F,
			std::make_shared<material::lambertian>(perlin)
		)
	);

	return world;
}

int main()
{
	try
	{
		const auto aspect_ratio = 16.F / 9.F;
		const auto image_width = 1080;
		const auto image_height = static_cast<int>(image_width / aspect_ratio);
		const auto samples = 100;
		const auto max_depth = 50;

		std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

		const auto focus_distance = 10.F;
		const auto time_min = 0.F;
		const auto time_max = 1.F;

		hittable::hittable_list world;
		point3 camera_position;
		point3 camera_target;
		float field_of_view;
		float aperture;

		switch (0)
		{
		case 1:
			world = get_world(time_min, time_max);
			camera_position = { 13.F, 2.F, 3.F };
			camera_target = { 0.F, 0.F, 0.F };
			field_of_view = 20.F;
			aperture = 0.1F;
			break;

		case 2:
			world = two_spheres();
			camera_position = { 13.F, 2.F, 3.F };
			camera_target = { 0.F, 0.F, 0.F };
			field_of_view = 20.F;
			aperture = 0.F;
			break;

		default:
		case 3:
			world = two_perlin_spheres();
			camera_position = { 13.F, 2.F, 3.F };
			camera_target = { 0.F, 0.F, 0.F };
			field_of_view = 20.F;
			aperture = 0.F;
			break;
		}

		const core::camera main_camera{
			camera_position,
			camera_target,
			field_of_view,
			aspect_ratio,
			aperture,
			focus_distance
		};

		for (auto j = image_height - 1; j >= 0; --j)
		{
			std::cerr << "\rScan lines remaining: " << j << std::flush;
			for (auto i = 0; i < image_width; ++i)
			{
				color pixel_color{ 0.F, 0.F, 0.F };
				for (auto s = 0; s < samples; ++s)
				{
					const auto u = (i + random::random_value<float>()) / (image_width - 1.F);
					const auto v = (j + random::random_value<float>()) / (image_height - 1.F);
					const auto r = main_camera.get_ray(u, v, random::random_value(time_min, time_max));
					pixel_color += evaluate_ray_color(r, world, max_depth);
				}

				core::write_color_to(std::cout, pixel_color / samples);
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
