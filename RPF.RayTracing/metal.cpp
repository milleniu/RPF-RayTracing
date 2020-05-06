#include "metal.h"

bool ray_tracing::material::metal::scatter(const core::ray& r, const core::hit_record& record, color& attenuation, core::ray& scattered) const
{
	const auto reflected = reflect(normalized(r.direction()), record.normal);
	scattered = core::ray(record.position, reflected + fuzz * random_vector_in_unit_sphere());
	attenuation = albedo;
	return dot(scattered.direction(), record.normal) > 0;
}
