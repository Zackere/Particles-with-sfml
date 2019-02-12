#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <math.h>
#include <random>
#include <functional>

#include "particle.h"

void initparticles(std::vector<Particle> &v, int width, int heigth)
{
	std::random_device rd;
	std::mt19937 g(rd());
	int *positions = new int[width * heigth];
	for(int i=0; i< width * heigth; i++)
		positions[i] = i;
	std::random_shuffle(positions, positions + width * heigth);
	for(int i=0; i<(int)v.size(); i++)
		v[i] = Particle(positions[i]%width, positions[i]/width, 0.f, 0.f);
	delete[] positions;
}

void drawparticles(const std::vector<Particle> &v, sf::RenderWindow &w, std::function<sf::Color(const Particle&)> colorf)
{
	sf::CircleShape shape(1.f);
	for_each(v.begin(), v.end(), [&shape, &w, &colorf](const Particle &p){
			shape.setFillColor(colorf(p));
			shape.setPosition(p.getxpos(), p.getypos());
			w.draw(shape);
			});
}

std::pair<double, double> calculateforce(double x, double y, double center_x, double center_y)
{
	double rx = center_x - x;
	double ry = center_y - y;
	double mod = rx*rx + ry*ry;
	double arg = 2 * atan(ry/(rx + sqrt(mod)));
	mod = pow(mod,0.373737) * 4;
	return std::make_pair(cos(arg) * mod, sin(arg) * mod);
}

void applyforce(std::vector<Particle> &v, double center_x, double center_y, double dt)
{
	std::pair<double, double> force;
	for_each(v.begin(), v.end(), [&dt, &center_x, &center_y, &force](Particle &p){
			force = calculateforce(p.getxpos(), p.getypos(), center_x, center_y);
			p.applyforce(force.first, force.second, dt);
			});
}

int main()
{
	int w_heigth=900, w_width=1400;
	int nparticles=10000;
	sf::Clock clock;
	sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
	std::vector<Particle> vparticles(nparticles);
	vparticles.shrink_to_fit();
	initparticles(vparticles, w_width, w_heigth);
	sf::RenderWindow window(sf::VideoMode(w_width,w_heigth), "Particles", sf::Style::Default, settings);

	clock.restart();
	while(window.isOpen())
	{
		applyforce(vparticles, sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, clock.restart().asSeconds());
		window.clear();
		drawparticles(vparticles, window, [&window](const Particle &p){
				double rx = sf::Mouse::getPosition(window).x - p.getxpos();
				double ry = sf::Mouse::getPosition(window).y - p.getypos();
				double r = sqrt(rx*rx + ry*ry);
				double b = 0;
				if(r > 255)
				{
					b = r - 255;
					b = (b>255?255:b);
					r = 255;
				}
				return sf::Color(255,r,b); });
		window.display();
		sf::Event event;
		while(window.pollEvent(event))
			if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				window.close();
	}
	return 0;
}
