#include "material/include/dielectric.h"
#include "core/include/random.h"
#include "core/include/hit_record.h"

bool ray_tracing::material::dielectric::scatter
(
	const core::ray& r,
	const core::hit_record& record,
	color& attenuation,
	core::ray& scattered
)
const
{
	attenuation = color{1.0, 1.0, 1.0};

	const auto refractive_index_normalized = record.front_face ? 1.F / refractive_index : refractive_index;
	const auto unit_direction = normalized(r.direction());
	const auto cos_theta = fminf(dot(-unit_direction, record.normal), 1.F);
	const auto sin_theta = boost::qvm::sqrt(1.F - cos_theta * cos_theta);

	if (refractive_index_normalized * sin_theta > 1.F )
	{
		const auto reflected = reflect(unit_direction, record.normal);
		scattered = core::ray(record.position, reflected);
		return true;
	}

	const auto reflect_probability = schlick_approximation(cos_theta, refractive_index_normalized);
	if (random::random_value<float>() < reflect_probability)
	{
		const auto reflected = reflect(unit_direction, record.normal);
		scattered = core::ray(record.position, reflected);
		return true;
	}

	const auto refracted = refract(unit_direction, record.normal, refractive_index_normalized);
	scattered = core::ray(record.position, refracted);
	return true;
}
