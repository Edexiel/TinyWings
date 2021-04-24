#ifndef TINYWINGS_COMMON_HPP
#define TINYWINGS_COMMON_HPP

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION            100
#endif

#endif //TINYWINGS_COMMON_HPP
