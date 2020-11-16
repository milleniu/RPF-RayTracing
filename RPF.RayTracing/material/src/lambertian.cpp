#include "material/include/lambertian.h"
#include "core/include/random.h"
#include "core/include/hit_record.h"
#include "texture/include/solid_color.h"

ray_tracing::material::lambertian::lambertian(const color& a)
	: albedo_(std::make_shared<texture::solid_color>(a)) {}

ray_tracing::material::lambertian::lambertian(std::shared_ptr<core::texture> a)
	: albedo_(std::move(a)) {}

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
	attenuation = albedo_->value(record.u, record.v, record.position);
	return true;
}
