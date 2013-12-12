#include "math.h"
#include <stdlib.h>
#include <math.h>

#define DEG2RAD 0.0174532925
#define RAD2DEG 57.2957795

double Log2(double x) {
	return log(x) / log(2.0);
}

double DegSin(double degrees) {
	return sin(DEG2RAD * degrees);
}

double DegCos(double degrees) {
	return cos(DEG2RAD * degrees);
}

double DegTan(double degrees) {
	return tan(DEG2RAD * degrees);
}

double DegASin(double sin) {
	return asin(sin) * RAD2DEG;
}

double DegACos(double cos) {
	return acos(cos) * RAD2DEG;
}

double DegATan(double tan) {
	return atan(tan) * RAD2DEG;
}

double DegATan2(double y, double x) {
	return atan2(y, x) * RAD2DEG;
}

double WrapValue(double val, double mod) {
    if (mod == 0) return val;
    return val - mod*floor(val/mod);
}

double Angle(double x1, double y1, double x2, double y2) {
    return WrapValue(DegATan2(y1-y2, x2-x1), 360);
}

double Distance(double x1, double y1, double x2, double y2) {
	return sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
}

bool ValueInRange(double value, double min, double max) {
	return (value >= min) && (value <= max);
}

bool PointInRect(double x, double y, double rectx, double recty, double width, double height) {
	// TAREA: Implementar funcion
	return false;
}

void ClosestPointToRect(double x, double y, double rectx, double recty, double width, double height, double* outx, double* outy) {
	*outx = (x < rectx) ? rectx : (x > rectx+width) ? rectx+width : x;
	*outy = (y < recty) ? recty : (y > recty+height) ? recty+height : y;
}

bool RectsOverlap(double x1, double y1, double width1, double height1, double x2, double y2, double width2, double height2) {
	// TAREA: Implementar funcion
	return false;
}

void OverlappingRect(double x1, double y1, double width1, double height1, double x2, double y2, double width2, double height2, double* outx, double* outy, double* outwidth, double* outheight) {
	// TAREA: Implementar funcion
}

void TransformIsoCoords(double isoX, double isoY, double isoZ, double* screenX, double* screenY) {
	// TAREA: Implementar funcion
}

bool IsPOT(int x) {
    while (!(x & 1)) 
        x = x >> 1; 

    return x == 1;
}

double Abs(double x) {
    return (x > 0) ? x : x * -1;
}

bool IsBetweenOrEqual(double value, double min, double max) {
	return (min <= value) && (value <= max);  
}

int Random(int min, int max) {
    /*return rand() % max + min;*/
	if (max == min)
		return min;

	return (int)min + (max - min) * rand() / RAND_MAX;
}