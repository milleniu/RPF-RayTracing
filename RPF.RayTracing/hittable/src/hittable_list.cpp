#include "hittable/include/hittable_list.h"

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
