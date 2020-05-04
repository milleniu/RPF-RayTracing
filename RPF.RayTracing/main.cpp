#include "vector3.h"
#include "color.h"
#include "ray.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

#include <iostream>


color ray_color(const ray& r, const hittable& world)
{
	hit_record record;
	if (world.hit(r, 0.F, std::numeric_limits<float>::infinity(), record))
	{
		return (record.normal + color(1.F, 1.F, 1.F)) * 0.5F;
	}

	const auto unit_direction = unit_vector(r.direction());
	const auto t = 0.5F * (unit_direction.y() + 1.F);
	return color(1.F, 1.F, 1.F) * (1.F - t) + color(0.5F, 0.7F, 1.F) * t;
}

int main()
{
	try
	{
		const auto aspect_ratio = 16.F / 9.F;
		const auto image_width = 1080;
		const auto image_height = static_cast<int>(image_width / aspect_ratio);

		std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

		const point3 origin(0.F, 0.F, 0.F);
		const vector3 viewport_horizontal(4.F, 0.F, 0.F);
		const vector3 viewport_vertical(0.F, 2.25F, 0.F);
		const auto viewport_origin = origin - viewport_horizontal / 2 - viewport_vertical / 2 - vector3(0, 0, 1);

		hittable_list world;
		world.add(std::make_shared<sphere>(point3(0.F, 0.F, -1.F), 0.5F));
		world.add(std::make_shared<sphere>(point3(0.F, -100.5F, -1.F), 100.F));
		
		for (auto j = image_height - 1; j >= 0; --j)
		{
			std::cerr << "\rScan lines remaining: " << j << std::flush;
			for (auto i = 0; i < image_width; ++i)
			{
				const auto u = static_cast<float>(i) / (image_width - 1.F);
				const auto v = static_cast<float>(j) / (image_height - 1.F);

				const ray r(origin, viewport_origin + viewport_horizontal * u + viewport_vertical * v);
				const auto pixel_color = ray_color(r, world);

				write_to(std::cout, pixel_color);
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
