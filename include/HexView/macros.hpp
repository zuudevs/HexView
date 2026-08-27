#pragma once

#ifndef NDEBUG
	#define NOEXCEPT
#else
	#define NOEXCEPT noexcept
#endif