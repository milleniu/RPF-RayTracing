#pragma once
#ifndef RPF_RAYTRACING_CORE_HIT_RECORD_H
#define RPF_RAYTRACING_CORE_HIT_RECORD_H

#include "core/include/common.h"
#include "core/include/material.h"

namespace ray_tracing
{
	namespace core
	{
		struct hit_record
		{
			float t{};
			float u{};
			float v{};
			point3 position{};
			vector3 normal{};
			std::shared_ptr<material_base> material_ptr;
			bool front_face{};

			void set_face_normal(const ray& r, vector3 outward_normal);
		};

		inline void hit_record::set_face_normal(const ray& r, const vector3 outward_normal)
		{
			front_face = dot(r.direction(), outward_normal) < 0;
			normal = front_face ? outward_normal : -outward_normal;
		}
	}
}

#endif
