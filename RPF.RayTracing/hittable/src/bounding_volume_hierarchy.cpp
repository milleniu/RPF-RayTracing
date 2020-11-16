#include "hittable/include/bounding_volume_hierarchy.h"
#include "core/include/random.h"
#include <iostream>

ray_tracing::hittable::bounding_volume_hierarchy::bounding_volume_hierarchy
(
	hittable_list& list,
	const float t0,
	const float t1
)
	: bounding_volume_hierarchy(list.hittable_vector(), 0, list.hittable_vector().size(), t0, t1) {}

ray_tracing::hittable::bounding_volume_hierarchy::bounding_volume_hierarchy
(
	std::vector<std::shared_ptr<core::hittable_base>>& hittable_list,
	const size_t start,
	const size_t end,
	const float t0,
	const float t1
) : bbox_({})
{
	const auto axis = random::random_value<int>(0, 2);
	const auto comparer =
		axis == 0 ? detail::bbox_x_comparison
	  : axis == 1 ? detail::bbox_y_comparison
			      : detail::bbox_z_comparison;
	const auto object_span = end - start;

	if (object_span == 1)
	{
		left_ = right_ = hittable_list[start];
	}
	else if (object_span == 2)
	{
		if (comparer(hittable_list[start], hittable_list[start + 1]))
		{
			left_ = hittable_list[start];
			right_ = hittable_list[start + 1];
		}
		else
		{
			left_ = hittable_list[start + 1];
			right_ = hittable_list[start];
		}
	}
	else
	{
		std::sort(hittable_list.begin() + start, hittable_list.begin() + end, comparer);

		const auto mid = start + object_span / 2;
		left_ = std::make_shared<bounding_volume_hierarchy>(hittable_list, start, mid, t0, t1);
		right_ = std::make_shared<bounding_volume_hierarchy>(hittable_list, mid, end, t0, t1);
	}

	core::aabb left_bbox, right_bbox; // NOLINT(cppcoreguidelines-pro-type-member-init)

	if (!left_->bbox(t0, t1, left_bbox) | !right_->bbox(t0, t1, right_bbox))
		std::cerr << "bounding_volume_hierarchy :: no bounding box.\n";

	bbox_ = core::aabb::bbox(left_bbox, right_bbox);
}

bool ray_tracing::hittable::bounding_volume_hierarchy::hit
(
	const core::ray& r,
	const float t_min,
	const float t_max,
	core::hit_record& record
)
const
{
	if (!bbox_.hit(r, t_min, t_max)) return false;

	const auto left_hit = left_->hit(r, t_min, t_max, record);
	const auto right_hit = right_->hit(r, t_min, left_hit ? record.t : t_max, record);
	return left_hit || right_hit;
}

bool ray_tracing::hittable::bounding_volume_hierarchy::bbox
(
	const float t0,
	const float t1,
	core::aabb& computed_bbox
)
const
{
	computed_bbox = bbox_;
	return true;
}
