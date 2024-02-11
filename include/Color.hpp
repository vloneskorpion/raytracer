#pragma once

#include "Vec3.hpp"

#include <iostream>

using Color = Vec3;

void writeColor(std::ostream& out, Color pixelColor, int samplesPerPixel);
