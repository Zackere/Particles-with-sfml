#ifndef PARTICLE_H
#define PARTICLE_H
class Particle
{
	using kin_t = double; // kinetics type
	kin_t x_pos, y_pos;
	kin_t x_vel, y_vel;
public:
	Particle(kin_t x=0, kin_t y=0, kin_t xv=0, kin_t yv=0);

	kin_t getxpos() const { return x_pos; }
	kin_t getypos() const { return y_pos; }
	kin_t getxvel() const { return x_vel; }
	kin_t getyvel() const { return y_vel; }

	void applyforce(kin_t x_for, kin_t y_for, double dt);

};

#endif // PARTICLE_H
