#ifndef VTG_R24B__VISIBILITY_CONTROL_H_
#define VTG_R24B__VISIBILITY_CONTROL_H_
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define VTG_R24B_EXPORT __attribute__ ((dllexport))
    #define VTG_R24B_IMPORT __attribute__ ((dllimport))
  #else
    #define VTG_R24B_EXPORT __declspec(dllexport)
    #define VTG_R24B_IMPORT __declspec(dllimport)
  #endif
  #ifdef VTG_R24B_BUILDING_LIBRARY
    #define VTG_R24B_PUBLIC VTG_R24B_EXPORT
  #else
    #define VTG_R24B_PUBLIC VTG_R24B_IMPORT
  #endif
  #define VTG_R24B_PUBLIC_TYPE VTG_R24B_PUBLIC
  #define VTG_R24B_LOCAL
#else
  #define VTG_R24B_EXPORT __attribute__ ((visibility("default")))
  #define VTG_R24B_IMPORT
  #if __GNUC__ >= 4
    #define VTG_R24B_PUBLIC __attribute__ ((visibility("default")))
    #define VTG_R24B_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define VTG_R24B_PUBLIC
    #define VTG_R24B_LOCAL
  #endif
  #define VTG_R24B_PUBLIC_TYPE
#endif
#endif  // VTG_R24B__VISIBILITY_CONTROL_H_
// Generated 11-Dec-2025 18:45:45
// Copyright 2019-2020 The MathWorks, Inc.
