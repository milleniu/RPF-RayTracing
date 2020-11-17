#pragma once
#ifndef RPF_RAYTRACING_CORE_PERLIN_H
#define RPF_RAYTRACING_CORE_PERLIN_H

#include "core/include/common.h"
#include "core/include/random.h"

namespace ray_tracing
{
	namespace core
	{
		class perlin final {
		public:
			perlin();
			~perlin();

			float noise(const point3& p) const;
			float turbulence(const point3& p, int depth = 7) const;

		private:
			static const int point_count = 256;

			vector3* random_vectors_;
			int* perm_x_;
			int* perm_y_;
			int* perm_z_;

			static int* perlin_generated_perm();
			static void permute(int* p, int n);
			static float perlin_interpolation(vector3 c[2][2][2], float u, float v, float w);
		};
	}
}

#endif
