#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "Menu.hpp"
#include "Star.hpp"
#include "Block.hpp"
#include "Computer.hpp"
#include "Renderer.hpp"
#include <mutex>
#include <thread>
#include <atomic>

class Simulation
{
	public:

		static std::atomic<bool>	mesh_done;
		static std::mutex			reload;
		static float				step;
		static IntergrationMethod	intergration_method;
		static float				smoothing_length;
		static float				precision;
		static int					nb_stars;
		static float				galaxy_diameter;
		static float				galaxy_thickness;
		static float				stars_speed;
		static std::list<Star>		galaxy;
		static dim::FrameBuffer		input_texture;
		static dim::FrameBuffer		output_texture;
		static dim::ComputeShader	compute_shader;
		static dim::VertexBuffer	star_vbo;
		static dim::VertexBuffer	galaxy_vbo;
		static dim::VertexBuffer	blur_vbo;
		static dim::VertexBuffer	post_vbo;
		static dim::Mesh			mesh;
		static dim::FrameBuffer		galaxy_fbo_1;
		static dim::FrameBuffer		galaxy_fbo_2;
		static dim::FrameBuffer		blur_fbo_1;
		static dim::FrameBuffer		blur_fbo_2;
		static Block				main_block;

		static void restart();
		static void center_camera();
		static void menu_update();
		static void update();
		static void update_mesh();
		static void send_mesh();
		static void check_events(const sf::Event& sf_event);
		static void clear();
		static void draw();
};

#endif
