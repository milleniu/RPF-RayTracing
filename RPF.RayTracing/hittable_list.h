#pragma once

#include "hittable.h"
#include <memory>
#include <vector>

class hittable_list final : public hittable
{
public:
	hittable_list() = default;
	explicit hittable_list(const std::shared_ptr<hittable>& hittable) { add(hittable); }

	void add(const std::shared_ptr<hittable>& hittable);
	void clear();

	bool hit(const ray& r, float t_min, float t_max, hit_record& record) const override;

private:
	std::vector<std::shared_ptr<hittable>> hittable_vector_;
};
