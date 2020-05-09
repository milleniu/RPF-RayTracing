#include "material/include/hemispheric.h"
#include "core/include/random.h"
#include "core/include/hit_record.h"

bool ray_tracing::material::hemispheric::scatter
(
	const core::ray& r,
	const core::hit_record& record,
	color& attenuation,
	core::ray& scattered
)
const
{
	const auto scatter_direction = random::random_in_hemisphere(record.normal);
	scattered = core::ray(record.position, scatter_direction);
	attenuation = albedo;
	return true;
}
