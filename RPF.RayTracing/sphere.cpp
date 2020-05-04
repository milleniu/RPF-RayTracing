#include "sphere.h"

bool sphere::hit
(
	const ray& r,
	const float t_min,
	const float t_max,
	hit_record& record
)
const
{
	const auto center_offset = r.origin() - center;
	const auto a = r.direction().length_squared();
	const auto h = dot(r.direction(), center_offset);
	const auto c = center_offset.length_squared() - radius * radius;
	const auto discriminant = h * h - a * c;

	if (discriminant > 0)
	{
		const auto root = sqrt(discriminant);
		auto t = (-h - root) / a;
		if (t > t_min && t < t_max)
		{
			record.t = t;
			record.position = r.evaluate(record.t);
			const auto outward_normal = (record.position - center) / radius;
			record.set_face_normal(r, outward_normal);
			return true;
		}

		t = (-h + root) / a;
		if (t > t_min && t < t_max)
		{
			record.t = t;
			record.position = r.evaluate(record.t);
			const auto outward_normal = (record.position - center) / radius;
			record.set_face_normal(r, outward_normal);
			return true;
		}
	}

	return false;
}
