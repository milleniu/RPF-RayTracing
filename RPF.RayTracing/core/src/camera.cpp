#include "core/include/camera.h"
#include "core/include/random.h"

ray_tracing::core::camera::camera
(
	const point3 position,
	const point3 target,
	const float field_of_view,
	const float aspect_ratio,
	const float aperture,
	const float focus_distance
)
	: origin_({}), viewport_width_({}), viewport_height_({}), viewport_origin_({}), u_({}), v_({}), w_({})
{
	origin_ = position;
	lens_radius_ = aperture / 2.F;

	const auto theta = degrees_to_radians(field_of_view);
	const auto half_height = boost::qvm::tan(theta / 2);
	const auto half_width = aspect_ratio * half_height;

	const auto vector_up = vector3{0.F, 1.F, 0.F};
	w_ = normalized(position - target);
	u_ = normalized(cross(vector_up, w_));
	v_ = cross(w_, u_);

	viewport_origin_ = origin_
		- half_width * focus_distance * u_
		- half_height * focus_distance * v_
		- focus_distance * w_;

	viewport_width_ = 2 * half_width * focus_distance * u_;
	viewport_height_ = 2 * half_height * focus_distance * v_;
}


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
