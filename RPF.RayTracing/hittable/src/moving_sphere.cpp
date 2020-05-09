#include "hittable/include/moving_sphere.h"

bool ray_tracing::hittable::moving_sphere::hit
(
	const core::ray& r,
	const float t_min,
	const float t_max,
	core::hit_record& record
)
const
{
	const auto center_offset = r.origin() - get_center(r.time());
	const auto a = mag_sqr(r.direction());
	const auto h = dot(r.direction(), center_offset);
	const auto c = mag_sqr(center_offset) - radius * radius;
	const auto discriminant = h * h - a * c;

	if (discriminant > 0)
	{
		const auto root = boost::qvm::sqrt(discriminant);
		auto t = (-h - root) / a;
		if( t > t_min && t < t_max)
		{
			record.t = t;
			record.position = r.evaluate(t);
			const auto outward_normal = (record.position - get_center(r.time())) / radius;
			record.set_face_normal(r, outward_normal);
			record.material_ptr = material;
			return true;
		}

		t = (-h + root) / a;
		if (t > t_min && t < t_max)
		{
			record.t = t;
			record.position = r.evaluate(t);
			const auto outward_normal = (record.position - get_center(r.time())) / radius;
			record.set_face_normal(r, outward_normal);
			record.material_ptr = material;
			return true;
		}
	}

	return false;
}


ray_tracing::point3 ray_tracing::hittable::moving_sphere::get_center(const float t) const
{
	if (t < movement_start) return origin;
	if (t > movement_end) return target;
	return origin + (t - movement_start) / (movement_end - movement_start) * (target - origin);
}
