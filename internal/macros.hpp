#pragma once

#ifdef ENABLE_EXCEPTION
	#define NOEXCEPT
#else
	#define NOEXCEPT noexcept
#endif