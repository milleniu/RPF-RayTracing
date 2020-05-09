#include "material/include/lambertian.h"
#include "core/include/random.h"
#include "core/include/hit_record.h"

ray_tracing::material::lambertian::lambertian(const color& a)
	: albedo_(a) {}

bool ray_tracing::material::lambertian::scatter
(
	const core::ray& r,
	const core::hit_record& record,
	color& attenuation,
	core::ray& scattered
)
const
{
	const auto scatter_direction = record.normal + random::random_unit_vector();
	scattered = core::ray(record.position, scatter_direction, r.time());
	attenuation = albedo_;
	return true;
}
