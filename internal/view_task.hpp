#pragma once

#include <string_view>
#include <view_config.hpp>

namespace zuu::hexview {

struct ViewTask {
	ViewConfig conf;
	std::string_view filepath;
};

} // namespace zuu::hexview