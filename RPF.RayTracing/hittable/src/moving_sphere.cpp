#include "hittable/include/moving_sphere.h"
#include <utility>

ray_tracing::hittable::moving_sphere::moving_sphere
(
	const point3 origin,
	const point3 target,
	const float movement_start,
	const float movement_end,
	const float radius,
	std::shared_ptr<core::material_base> material
)
	: origin_(origin), target_(target),
	  movement_start_(movement_start), movement_end_(movement_end),
	  radius_(radius), material_(std::move(material)) {}


ray_tracing::point3 ray_tracing::hittable::moving_sphere::get_center(const float t) const
{
	if (t < movement_start_) return origin_;
	if (t > movement_end_) return target_;
	return origin_ + (t - movement_start_) / (movement_end_ - movement_start_) * (target_ - origin_);
}

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
	const auto c = mag_sqr(center_offset) - radius_ * radius_;
	const auto discriminant = h * h - a * c;

	if (discriminant > 0)
	{
		const auto root = boost::qvm::sqrt(discriminant);
		auto t = (-h - root) / a;
		if (t > t_min && t < t_max)
		{
			record.t = t;
			record.position = r.evaluate(t);
			const auto outward_normal = (record.position - get_center(r.time())) / radius_;
			record.set_face_normal(r, outward_normal);
			record.material_ptr = material_;
			return true;
		}

		t = (-h + root) / a;
		if (t > t_min && t < t_max)
		{
			record.t = t;
			record.position = r.evaluate(t);
			const auto outward_normal = (record.position - get_center(r.time())) / radius_;
			record.set_face_normal(r, outward_normal);
			record.material_ptr = material_;
			return true;
		}
	}

	return false;
}

bool ray_tracing::hittable::moving_sphere::bbox
(
	const float t0,
	const float t1,
	core::aabb& computed_bbox
)
const
{
	const core::aabb t0_bounds
	{
		get_center(t0) - vector3{ radius_, radius_, radius_ },
		get_center(t0) + vector3{ radius_, radius_, radius_ }
	};

	const core::aabb t1_bounds
	{
		get_center(t1) - vector3{ radius_, radius_, radius_ },
		get_center(t1) + vector3{ radius_, radius_, radius_ }
	};

	computed_bbox = core::aabb::bbox(t0_bounds, t1_bounds);
	return true;
}
