#include "texture/include/image.h"

#include <boost/gil/extension/io/jpeg.hpp>

ray_tracing::texture::image::image(const std::string& filename)
{
	try
	{
		read_image(filename, data_, boost::gil::jpeg_tag());
	}
	catch (std::exception const& exception)
	{
		std::cerr 
			<< "ERROR: Could not load texture image file '"
			<< filename
			<< "'.\n"
			<< exception.what()
			<< std::endl;
	}
}

ray_tracing::color ray_tracing::texture::image::value(float u, float v, const point3& p) const
{
	if (data_._view.empty())
		return color{ 1, 0, 1 };
	
	u = clamp(u, 0.F, 1.F);
	v = 1.F - clamp(v, 0.F, 1.F);

	auto i = static_cast<int>(u * static_cast<float>(data_.width()));
	auto j = static_cast<int>(v * static_cast<float>(data_.height()));

	if (i >= data_.width()) i = data_.width() - 1;
	if (j >= data_.height()) j = data_.height() - 1;

	const auto pixel = data_._view.at(i, j)[0];
	const auto r = static_cast<int>(get_color(pixel, boost::gil::red_t()));
	const auto g = static_cast<int>(get_color(pixel, boost::gil::green_t()));
	const auto b = static_cast<int>(get_color(pixel, boost::gil::blue_t()));

	const auto color_scale = 1.F / 255.F;
	return color{ color_scale * r, color_scale * g, color_scale * b };
}
