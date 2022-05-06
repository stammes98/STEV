#ifndef STEV_H
#define STEV_H
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <math.h>

#define pi 3.14159265358979323846
#define PERCENTAGE(V, T) (100 - (((T - V) * 100) / T))

#define LATERAL_EXTREME_STABLE 0.14f
#define LATERAL_MODERATE_STABLE 0.165f
#define LATERAL_NEUTRAL 0.175f
#define LATERAL_MODERATE_UNSTABLE 0.325f
#define LATERAL_EXTREME_UNSTABLE 0.475f

#define VERTICAL_EXTREME_STABLE 0.015f
#define VERTICAL_MODERATE_STABLE 0.05f
#define VERTICAL_NEUTRAL 0.065f
#define VERTICAL_MODERATE_UNSTABLE 0.125f
#define VERTICAL_EXTREME_UNSTABLE 0.35f

float Q;
float u;
float H;

float sy;
float sz;

float Iy;
float Iz;

void print_progress(size_t count, size_t max);

float squared(float x);

float conc(float x, float y, float z);

float lineInt(float x, float y, float z);

int writeGrid(float xLower, float xUpper, float yLower, float yUpper, float zUpper, float step);

int initModel(float emissionRate, float windSpeed, float offset, float lateralIntensity, float verticalIntensity);



#endif
