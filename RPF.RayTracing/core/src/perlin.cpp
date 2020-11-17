#include "core/include/perlin.h"

ray_tracing::core::perlin::perlin()
{
	random_vectors_ = new vector3[point_count];

	for (auto i = 0; i < point_count; ++i)
		random_vectors_[i] = normalized(random::random_vector(-1, 1));
		
	perm_x_ = perlin_generated_perm();
	perm_y_ = perlin_generated_perm();
	perm_z_ = perlin_generated_perm();
}

ray_tracing::core::perlin::~perlin()
{
	delete[] random_vectors_;
	delete[] perm_x_;
	delete[] perm_y_;
	delete[] perm_z_;
}

float ray_tracing::core::perlin::noise(const point3& p) const
{
	const auto u = p.a[0] - floorf(p.a[0]);
	const auto v = p.a[1] - floorf(p.a[1]);
	const auto w = p.a[2] - floorf(p.a[2]);
	const auto i = static_cast<int>(floorf(p.a[0]));
	const auto j = static_cast<int>(floorf(p.a[1]));
	const auto k = static_cast<int>(floorf(p.a[2]));
	vector3 c[2][2][2];

	for (auto di = 0; di < 2; ++di)
		for (auto dj = 0; dj < 2; ++dj)
			for (auto dk = 0; dk < 2; ++dk)
				c[di][dj][dk] = random_vectors_[
					perm_x_[(i + di) & 255] ^
					perm_y_[(j + dj) & 255] ^
					perm_z_[(k + dk) & 255]
				];

	return perlin_interpolation(c, u, v, w);
}

float ray_tracing::core::perlin::turbulence(const point3& p, const int depth) const
{
	auto accumulator = 0.F;
	auto temp_p = p;
	auto weight = 1.F;

	for (auto i = 0; i < depth; ++i)
	{
		accumulator += weight * noise(temp_p);
		weight *= 0.5F;
		temp_p *= 2;
	}

	return fabsf(accumulator);
}


inline int* ray_tracing::core::perlin::perlin_generated_perm()
{
	auto* const p = new int[point_count];
	for (auto i = 0; i < point_count; ++i)
		p[i] = i;

	permute(p, point_count);

	return p;
}

inline void ray_tracing::core::perlin::permute(int* p, const int n)
{
	for (auto i = n - 1; i > 0; i--)
	{
		const auto target = random::random_value<int>(0, i);
		const auto temp = p[i];
		p[i] = p[target];
		p[target] = temp;
	}
}

float ray_tracing::core::perlin::perlin_interpolation(vector3 c[2][2][2], const float u, const float v, const float w)
{
	const auto uu = u * u * (3 - 2 * u);
	const auto vv = v * v * (3 - 2 * v);
	const auto ww = w * w * (3 - 2 * w);
	auto accumulator = 0.F;

	for (auto i = 0; i < 2; ++i)
		for (auto j = 0; j < 2; ++j)
			for (auto k = 0; k < 2; ++k)
			{
				const auto weight_vector = vector3{ u - i, v - j, w - k };
				accumulator +=
					(static_cast<float>(i) * uu + static_cast<float>((1 - i)) * (1 - uu)) *
					(static_cast<float>(j) * vv + static_cast<float>((1 - j)) * (1 - vv)) *
					(static_cast<float>(k) * ww + static_cast<float>((1 - k)) * (1 - ww)) *
					dot( c[i][j][k], weight_vector );
			}

	return accumulator;
}
