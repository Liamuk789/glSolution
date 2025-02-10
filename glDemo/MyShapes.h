#pragma once

void drawTriangle();
void drawPolygon(int _x, int _y, int _sides, float _radius);
void drawStar(float _atX, float _atY, float _innerRadius, float _outerRadius, int _points);
void drawTank(float _atX, float _atY, float _orientation);
void drawOcto(float _atX, float _atY, float _radius, float _points);
void drawOverLap();
void drawSemiCircle();


float randomFloat(float max);
void movePoly();