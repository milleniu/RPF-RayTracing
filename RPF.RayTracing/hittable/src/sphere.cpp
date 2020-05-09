#include "hittable/include/sphere.h"

bool ray_tracing::hittable::sphere::hit
(
	const core::ray& r,
	const float t_min,
	const float t_max,
	core::hit_record& record
)
const
{
	const auto center_offset = r.origin() - center;
	const auto a = mag_sqr(r.direction());
	const auto h = dot(r.direction(), center_offset);
	const auto c = mag_sqr(center_offset) - radius * radius;
	const auto discriminant = h * h - a * c;

	if (discriminant > 0)
	{
		const auto root = boost::qvm::sqrt(discriminant);
		auto t = (-h - root) / a;
		if (t > t_min && t < t_max)
		{
			record.t = t;
			record.position = r.evaluate(record.t);
			const auto outward_normal = (record.position - center) / radius;
			record.set_face_normal(r, outward_normal);
			record.material_ptr = material;
			return true;
		}

		t = (-h + root) / a;
		if (t > t_min && t < t_max)
		{
			record.t = t;
			record.position = r.evaluate(record.t);
			const auto outward_normal = (record.position - center) / radius;
			record.set_face_normal(r, outward_normal);
			record.material_ptr = material;
			return true;
		}
	}

	return false;
}
