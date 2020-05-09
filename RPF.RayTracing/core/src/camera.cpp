#include "core/include/camera.h"
#include "core/include/random.h"

ray_tracing::core::ray ray_tracing::core::camera::get_ray
(
	const float s,
	const float t,
	const float time
)
const
{
	const auto random_in_disk = lens_radius_ * random::random_vector_in_disk();
	const auto offset = u_ * random_in_disk.a[0] + v_ * random_in_disk.a[1];

	return
	{
		origin_ + offset,
		viewport_origin_ + s * viewport_width_ + t * viewport_height_ - origin_ - offset,
		time
	};
}
