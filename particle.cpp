#include "particle.h"

Particle::Particle(kin_t x, kin_t y, kin_t xv, kin_t yv):x_pos(x), y_pos(y), x_vel(xv), y_vel(yv)
{

}

void Particle::applyforce(kin_t x_for, kin_t y_for)
{
	this->x_vel += x_for;
	this->y_vel += y_for;
	this->x_pos += x_vel;
	this->y_pos += y_vel;
}
