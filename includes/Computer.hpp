#ifndef COMPUTATION_HPP
#define COMPUTATION_HPP

#include "libraries.hpp"

class Computer
{
public:

	static dim::Vector2int		textures_size;
	static dim::ComputeShader	init_positions;
	static dim::ComputeShader	init_speeds;
	static dim::ComputeShader	interactions;
	static dim::ComputeShader	integration;
	static dim::FrameBuffer		positions;
	static dim::FrameBuffer		speeds;
	static dim::FrameBuffer		accelerations;

	static void init();
	static void update_accelerations();
	static void update_speeds();
	static void update_positions();
	static void compute();
};

#endif
