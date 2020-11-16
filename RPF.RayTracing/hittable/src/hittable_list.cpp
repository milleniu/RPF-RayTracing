#include "hittable/include/hittable_list.h"

ray_tracing::hittable::hittable_list::hittable_list(const std::shared_ptr<hittable_base>& hittable)
{
	add(hittable);
}

void ray_tracing::hittable::hittable_list::add(const std::shared_ptr<hittable_base>& hittable)
{
	hittable_vector_.push_back(hittable);
}

void ray_tracing::hittable::hittable_list::clear()
{
	hittable_vector_.clear();
}

bool ray_tracing::hittable::hittable_list::hit
(
	const core::ray& r,
	const float t_min,
	const float t_max,
	core::hit_record& record
)
const
{
	core::hit_record temp_record;
	auto hit = false;
	auto closest = t_max;

	for (const auto& hittable : hittable_vector_)
	{
		if (hittable->hit(r, t_min, closest, temp_record))
		{
			hit = true;
			closest = temp_record.t;
			record = temp_record;
		}
	}

	return hit;
}

bool ray_tracing::hittable::hittable_list::bbox
(
	const float t0,
	const float t1,
	core::aabb& computed_bbox
)
const
{
	if (hittable_vector_.empty()) return false;

	core::aabb temp_bbox; // NOLINT(cppcoreguidelines-pro-type-member-init)
	auto initial_bbox = true;

	for (const auto& hittable : hittable_vector_)
	{
		if (!hittable->bbox(t0, t1, temp_bbox)) return false;
		computed_bbox = initial_bbox ? temp_bbox : core::aabb::bbox(computed_bbox, temp_bbox);
		initial_bbox = false;
	}

	return true;
}
