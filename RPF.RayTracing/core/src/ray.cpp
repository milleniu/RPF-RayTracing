#include "core/include/ray.h"

ray_tracing::core::ray::ray(const point3& origin, const vector3& direction, const float time)
	: origin_(origin), direction_(direction), time_(time) {}

ray_tracing::point3 ray_tracing::core::ray::evaluate(const float t) const
{
	return origin_ + t * direction_;
}
