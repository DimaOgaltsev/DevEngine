#ifndef DEV_MATH_H
#define DEV_MATH_H

#include <math.h>

namespace dev
{
  #define PI      3.14159265358979323846f
  #define PI_2    1.57079632679489661923f
  #define PI_4    0.78539816339744830962f
  #define Radian  57.2957795130823208768f
  #define Degree  0.01745329251994329577f

  #define ToRadian( degree ) ((degree) * (0.01745329251994329577f))
  #define ToDegree( radian ) ((radian) * (57.2957795130823208768f))

}

#endif