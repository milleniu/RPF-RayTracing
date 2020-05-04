﻿#include "hittable_list.h"

void hittable_list::add(const std::shared_ptr<hittable>& hittable)
{
	hittable_vector_.push_back(hittable);
}

void hittable_list::clear()
{
	hittable_vector_.clear();
}

bool hittable_list::hit
(
	const ray& r,
	const float t_min,
	const float t_max,
	hit_record& record
)
const
{
	hit_record temp_record;
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