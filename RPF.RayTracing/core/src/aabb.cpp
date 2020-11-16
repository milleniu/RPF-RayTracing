#include "core/include/aabb.h"

ray_tracing::core::aabb::aabb(const point3& a, const point3& b)
	: min_(a), max_(b) {}

bool ray_tracing::core::aabb::hit(const ray& r, float t_min, float t_max) const
{
	for (auto i = 0; i < 3; ++i)
	{
		const auto inverted_direction = 1.F / r.direction().a[i];
		auto t0 = (min().a[i] - r.origin().a[i]) * inverted_direction;
		auto t1 = (max().a[i] - r.origin().a[i]) * inverted_direction;
		if (inverted_direction < 0.F) std::swap(t0, t1);

		t_min = t0 > t_min ? t0 : t_min;
		t_max = t1 < t_max ? t1 : t_max;

		if (t_max <= t_min) return false;
	}

	return true;
}

ray_tracing::core::aabb ray_tracing::core::aabb::bbox(aabb a, aabb b)
{
	const point3 min =
	{
		fminf (a.min_.a[0], b.min_.a[0]),
		fminf(a.min_.a[1], b.min_.a[1]),
		fminf(a.min_.a[2], b.min_.a[2])
	};

	const point3 max =
	{
		fmaxf(a.max_.a[0], b.max_.a[0]),
		fmaxf(a.max_.a[1], b.max_.a[1]),
		fmaxf(a.max_.a[2], b.max_.a[2])
	};

	return {min, max};
}
