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
	for_each(v.begin(), v.end(), [&](const Particle &p){
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
	mod = pow(mod,-0.037037);
	return std::make_pair(cos(arg) * mod, sin(arg) * mod);
}

void applyforce(std::vector<Particle> &v, double center_x, double center_y)
{
	std::pair<double, double> force;
	for_each(v.begin(), v.end(), [&](Particle &p){
			force = calculateforce(p.getxpos(), p.getypos(), center_x, center_y);
			p.applyforce(force.first, force.second);
			});
}

int main()
{
	int w_heigth=600, w_width=900;
	int nparticles=500;

	std::vector<Particle> vparticles(nparticles);
	vparticles.shrink_to_fit();
	initparticles(vparticles, w_width, w_heigth);

	sf::RenderWindow window(sf::VideoMode(w_width,w_heigth), "Particles");
	while(window.isOpen())
	{
		drawparticles(vparticles, window, [](const Particle &p){ return sf::Color::Black; });
		applyforce(vparticles, sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
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

		sf::Event event;
		while(window.pollEvent(event))
			if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) 
				window.close();
		window.display();
	}
	return 0;
}
