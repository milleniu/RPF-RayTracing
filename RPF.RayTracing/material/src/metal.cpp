#include "material//include/metal.h"
#include "core/include/random.h"
#include "core/include/hit_record.h"

ray_tracing::material::metal::metal(const color& a, const float fuzz)
	: albedo_(a), fuzz_(fuzz < 1 && fuzz >= 0 ? fuzz : 1) {}

bool ray_tracing::material::metal::scatter
(
	const core::ray& r,
	const core::hit_record& record,
	color& attenuation,
	core::ray& scattered
)
const
{
	const auto reflected = reflect(normalized(r.direction()), record.normal);
	scattered = core::ray(record.position, reflected + fuzz_ * random::random_vector_in_unit_sphere(), r.time());
	attenuation = albedo_;
	return dot(scattered.direction(), record.normal) > 0;
}
