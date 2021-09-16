#include "dim/dimension3D.hpp"

namespace dim
{
	const Mesh	Mesh::circle_64			= Mesh::Circle(64);
	const Mesh	Mesh::empty_circle_64	= Mesh::EmptyCircle(64);
	const Mesh	Mesh::cone_64			= Mesh::Cone(64);
	const Mesh	Mesh::cube				= Mesh::Cube();
	const Mesh	Mesh::empty_cube		= Mesh::EmptyCube();
	const Mesh	Mesh::cylinder_64		= Mesh::Cylinder(64);
	const Mesh	Mesh::null				= Mesh();
	const Mesh	Mesh::sphere_64			= Mesh::Sphere(64, 64);
	const Mesh	Mesh::square			= Mesh::Square();
	const Mesh	Mesh::empty_square		= Mesh::EmptySquare();
	const Mesh	Mesh::screen			= Mesh::Screen();

	Mesh::Mesh()
	{
		draw_type = DrawType::Triangles;
		positions.clear();
		normals.clear();
		texcoords.clear();
	}

	Mesh& Mesh::operator+=(const Mesh& other)
	{
		for (auto& position : other.positions)
			positions.push_back(position);

		for (auto& normal : other.normals)
			normals.push_back(normal);

		for (auto& texcoord : other.texcoords)
			texcoords.push_back(texcoord);

		return *this;
	}

	Mesh& Mesh::operator*=(const glm::mat4& matrix)
	{
		for (auto& position : positions)
			position *= matrix;

		glm::mat3 normals_matrix = glm::transpose(glm::inverse(glm::mat3(matrix)));

		for (auto& normal : normals)
			normal = normalize(Vector3(normals_matrix * normal));

		return *this;
	}

	unsigned int Mesh::get_data_size() const
	{
		return static_cast<unsigned int>(positions.size() * sizeof(Vector3) + normals.size() * sizeof(Vector3) + texcoords.size() * sizeof(Vector2));
	}

	unsigned int Mesh::get_positions_size() const
	{
		return static_cast<unsigned int>(positions.size() * sizeof(Vector3));
	}

	unsigned int Mesh::get_normals_size() const
	{
		return static_cast<unsigned int>(normals.size() * sizeof(Vector3));
	}

	unsigned int Mesh::get_texcoords_size() const
	{
		return static_cast<unsigned int>(texcoords.size() * sizeof(Vector2));
	}

	unsigned int Mesh::get_nb_vertices() const
	{
		return static_cast<unsigned int>(positions.size());
	}

	void Mesh::clear()
	{
		positions.clear();
		normals.clear();
		texcoords.clear();
	}

	Mesh Mesh::Circle(unsigned int nb_edges)
	{
		Mesh mesh;
		mesh.draw_type = DrawType::Triangles;
		float nb = static_cast<float>(nb_edges);

		for (unsigned int i = 0; i < nb_edges; i++)
		{
			mesh.positions.push_back(Vector3(0.5f * cos(i * 2.f * pi / nb), 0.5f * sin(i * 2.f * pi / nb), 0.f));
			mesh.positions.push_back(Vector3(0.f, 0.f, 0.f));
			mesh.positions.push_back(Vector3(0.5f * cos((i + 1) * 2.f * pi / nb), 0.5f * sin((i + 1) * 2.f * pi / nb), 0.f));
		}

		for (auto& position : mesh.positions)
		{
			mesh.normals.push_back(Vector3(0.f, 0.f, 1.f));
			mesh.texcoords.push_back(Vector2(position.x + 0.5f, 0.5f - position.y));
		}

		return mesh;
	}

	Mesh Mesh::EmptyCircle(unsigned int nb_edges)
	{
		Mesh mesh;
		mesh.draw_type = DrawType::Lines;
		float nb = static_cast<float>(nb_edges);

		for (unsigned int i = 0; i < nb_edges; i++)
		{
			mesh.positions.push_back(Vector3(0.5f * cos(i * 2.f * pi / nb), 0.5f * sin(i * 2.f * pi / nb), 0.f));
			mesh.positions.push_back(Vector3(0.5f * cos((i + 1) * 2.f * pi / nb), 0.5f * sin((i + 1) * 2.f * pi / nb), 0.f));
		}

		for (auto& position : mesh.positions)
		{
			mesh.normals.push_back(Vector3(0.f, 0.f, 1.f));
			mesh.texcoords.push_back(Vector2(position.x + 0.5f, 0.5f - position.y));
		}

		return mesh;
	}

	Mesh Mesh::Cone(unsigned int nb_latitudes)
	{
		Mesh mesh;
		mesh.draw_type = DrawType::Triangles;
		float nb = static_cast<float>(nb_latitudes);

		for (unsigned int i = 0; i < nb_latitudes; i++)
		{
			mesh.positions.push_back(Vector3(0.5f * cos((i + 1) * 2.f * pi / nb), -0.5f, 0.5f * sin((i + 1) * 2.f * pi / nb)));
			mesh.positions.push_back(Vector3(0.5f * cos(i * 2.f * pi / nb), -0.5f, 0.5f * sin(i * 2.f * pi / nb)));
			mesh.positions.push_back(Vector3(0.f, 0.5f, 0.f));

			mesh.normals.push_back(normalize(Vector3(mesh.positions[i * 3].x, 0.25f, mesh.positions[i * 3].z)));
			mesh.normals.push_back(normalize(Vector3(mesh.positions[i * 3 + 1].x, 0.25f, mesh.positions[i * 3 + 1].z)));
			mesh.normals.push_back((mesh.normals[i * 3] + mesh.normals[i * 3 + 1]) / 2.f);

			mesh.texcoords.push_back(Vector2((i + 1) / nb, 1.f));
			mesh.texcoords.push_back(Vector2(i / nb, 1.f));
			mesh.texcoords.push_back(Vector2((i + 0.5f) / nb, 0.f));
		}

		for (unsigned int i = 0; i < nb_latitudes; i++)
		{
			mesh.positions.push_back(Vector3(0.5f * cos(i * 2.f * pi / nb), -0.5f, 0.5f * sin(i * 2.f * pi / nb)));
			mesh.positions.push_back(Vector3(0.5f * cos((i + 1) * 2.f * pi / nb), -0.5f, 0.5f * sin((i + 1) * 2.f * pi / nb)));
			mesh.positions.push_back(Vector3(0.f, -0.5f, 0.f));

			mesh.normals.push_back(Vector3(0.f, -1.f, 0.f));
			mesh.normals.push_back(Vector3(0.f, -1.f, 0.f));
			mesh.normals.push_back(Vector3(0.f, -1.f, 0.f));

			mesh.texcoords.push_back(Vector2(mesh.positions[(nb_latitudes + i) * 3].x + 0.5f, 0.5f - mesh.positions[(nb_latitudes + i) * 3].z));
			mesh.texcoords.push_back(Vector2(mesh.positions[(nb_latitudes + i) * 3 + 1].x + 0.5f, 0.5f - mesh.positions[(nb_latitudes + i) * 3 + 1].z));
			mesh.texcoords.push_back(Vector2(mesh.positions[(nb_latitudes + i) * 3 + 2].x + 0.5f, 0.5f - mesh.positions[(nb_latitudes + i) * 3 + 2].z));
		}

		return mesh;
	}

	Mesh Mesh::Cube()
	{
		Mesh mesh;
		mesh.draw_type = DrawType::Triangles;

		mesh.positions =
		{
			//Back
			Vector3(-0.5f,  0.5f, -0.5f),
			Vector3( 0.5f,  0.5f, -0.5f),
			Vector3(-0.5f, -0.5f, -0.5f),
			Vector3( 0.5f,  0.5f, -0.5f),
			Vector3( 0.5f, -0.5f, -0.5f),
			Vector3(-0.5f, -0.5f, -0.5f),

			//Front
			Vector3( 0.5f,  0.5f,  0.5f),
			Vector3(-0.5f,  0.5f,  0.5f),
			Vector3(-0.5f, -0.5f,  0.5f),
			Vector3( 0.5f, -0.5f,  0.5f),
			Vector3( 0.5f,  0.5f,  0.5f),
			Vector3(-0.5f, -0.5f,  0.5f),

			//Left
			Vector3(-0.5f,  0.5f,  0.5f),
			Vector3(-0.5f,  0.5f, -0.5f),
			Vector3(-0.5f, -0.5f,  0.5f),
			Vector3(-0.5f,  0.5f, -0.5f),
			Vector3(-0.5f, -0.5f, -0.5f),
			Vector3(-0.5f, -0.5f,  0.5f),

			//Right
			Vector3(0.5f,  0.5f, -0.5f),
			Vector3(0.5f,  0.5f,  0.5f),
			Vector3(0.5f, -0.5f,  0.5f),
			Vector3(0.5f, -0.5f, -0.5f),
			Vector3(0.5f,  0.5f, -0.5f),
			Vector3(0.5f, -0.5f,  0.5f),

			//Top
			Vector3( 0.5f,  0.5f, -0.5f),
			Vector3(-0.5f,  0.5f, -0.5f),
			Vector3(-0.5f,  0.5f,  0.5f),
			Vector3( 0.5f,  0.5f, -0.5f),
			Vector3(-0.5f,  0.5f,  0.5f),
			Vector3( 0.5f,  0.5f,  0.5f),

			//Bottom
			Vector3( 0.5f, -0.5f, -0.5f),
			Vector3(-0.5f, -0.5f,  0.5f),
			Vector3(-0.5f, -0.5f, -0.5f),
			Vector3( 0.5f, -0.5f, -0.5f),
			Vector3( 0.5f, -0.5f,  0.5f),
			Vector3(-0.5f, -0.5f,  0.5f)
		};

		mesh.normals =
		{
			//Back
			Vector3(0.f, 0.f, -1.f),
			Vector3(0.f, 0.f, -1.f),
			Vector3(0.f, 0.f, -1.f),
			Vector3(0.f, 0.f, -1.f),
			Vector3(0.f, 0.f, -1.f),
			Vector3(0.f, 0.f, -1.f),

			//Front
			Vector3(0.f, 0.f, 1.f),
			Vector3(0.f, 0.f, 1.f),
			Vector3(0.f, 0.f, 1.f),
			Vector3(0.f, 0.f, 1.f),
			Vector3(0.f, 0.f, 1.f),
			Vector3(0.f, 0.f, 1.f),

			//Left
			Vector3(-1.f, 0.f, 0.f),
			Vector3(-1.f, 0.f, 0.f),
			Vector3(-1.f, 0.f, 0.f),
			Vector3(-1.f, 0.f, 0.f),
			Vector3(-1.f, 0.f, 0.f),
			Vector3(-1.f, 0.f, 0.f),

			//Right
			Vector3(1.f, 0.f, 0.f),
			Vector3(1.f, 0.f, 0.f),
			Vector3(1.f, 0.f, 0.f),
			Vector3(1.f, 0.f, 0.f),
			Vector3(1.f, 0.f, 0.f),
			Vector3(1.f, 0.f, 0.f),

			//Top
			Vector3(0.f, 1.f, 0.f),
			Vector3(0.f, 1.f, 0.f),
			Vector3(0.f, 1.f, 0.f),
			Vector3(0.f, 1.f, 0.f),
			Vector3(0.f, 1.f, 0.f),
			Vector3(0.f, 1.f, 0.f),

			//Bottom
			Vector3(0.f, -1.f, 0.f),
			Vector3(0.f, -1.f, 0.f),
			Vector3(0.f, -1.f, 0.f),
			Vector3(0.f, -1.f, 0.f),
			Vector3(0.f, -1.f, 0.f),
			Vector3(0.f, -1.f, 0.f)
		};

		mesh.texcoords =
		{
			//Back
			Vector2(1.f, 0.f),
			Vector2(0.f, 0.f),
			Vector2(1.f, 1.f),
			Vector2(0.f, 0.f),
			Vector2(0.f, 1.f),
			Vector2(1.f, 1.f),

			//Front
			Vector2(1.f, 0.f),
			Vector2(0.f, 0.f),
			Vector2(0.f, 1.f),
			Vector2(1.f, 1.f),
			Vector2(1.f, 0.f),
			Vector2(0.f, 1.f),

			//Left
			Vector2(1.f, 0.f),
			Vector2(0.f, 0.f),
			Vector2(1.f, 1.f),
			Vector2(0.f, 0.f),
			Vector2(0.f, 1.f),
			Vector2(1.f, 1.f),

			//Right
			Vector2(1.f, 0.f),
			Vector2(0.f, 0.f),
			Vector2(0.f, 1.f),
			Vector2(1.f, 1.f),
			Vector2(1.f, 0.f),
			Vector2(0.f, 1.f),

			//Top
			Vector2(1.f, 0.f),
			Vector2(0.f, 0.f),
			Vector2(0.f, 1.f),
			Vector2(1.f, 0.f),
			Vector2(0.f, 1.f),
			Vector2(1.f, 1.f),

			//Bottom
			Vector2(0.f, 0.f),
			Vector2(1.f, 1.f),
			Vector2(1.f, 0.f),
			Vector2(0.f, 0.f),
			Vector2(0.f, 1.f),
			Vector2(1.f, 1.f)
		};

		return mesh;
	}

	Mesh Mesh::EmptyCube()
	{
		Mesh mesh;
		mesh.draw_type = DrawType::Lines;

		mesh.positions =
		{
			//Back
			Vector3( 0.5f, -0.5f, -0.5f),
			Vector3( 0.5f,  0.5f, -0.5f),
			Vector3(-0.5f, -0.5f, -0.5f),
			Vector3(-0.5f,  0.5f, -0.5f),

			//Front
			Vector3( 0.5f, -0.5f,  0.5f),
			Vector3( 0.5f,  0.5f,  0.5f),
			Vector3(-0.5f, -0.5f,  0.5f),
			Vector3(-0.5f,  0.5f,  0.5f),

			//Top
			Vector3(-0.5f,  0.5f, -0.5f),
			Vector3(-0.5f,  0.5f,  0.5f),
			Vector3(-0.5f,  0.5f, -0.5f),
			Vector3( 0.5f,  0.5f, -0.5f),
			Vector3( 0.5f,  0.5f,  0.5f),
			Vector3(-0.5f,  0.5f,  0.5f),
			Vector3( 0.5f,  0.5f,  0.5f),
			Vector3( 0.5f,  0.5f, -0.5f),

			//Bottom
			Vector3(-0.5f, -0.5f, -0.5f),
			Vector3(-0.5f, -0.5f,  0.5f),
			Vector3(-0.5f, -0.5f, -0.5f),
			Vector3( 0.5f, -0.5f, -0.5f),
			Vector3( 0.5f, -0.5f,  0.5f),
			Vector3(-0.5f, -0.5f,  0.5f),
			Vector3( 0.5f, -0.5f,  0.5f),
			Vector3( 0.5f, -0.5f, -0.5f)
		};

		mesh.normals =
		{
			//Back
			Vector3(1.f, 0.f, 0.f),
			Vector3(1.f, 0.f, 0.f),
			Vector3(1.f, 0.f, 0.f),
			Vector3(1.f, 0.f, 0.f),

			//Front
			Vector3(1.f, 0.f, 0.f),
			Vector3(1.f, 0.f, 0.f),
			Vector3(1.f, 0.f, 0.f),
			Vector3(1.f, 0.f, 0.f),

			//Top
			Vector3(1.f, 0.f, 0.f),
			Vector3(1.f, 0.f, 0.f),
			Vector3(1.f, 0.f, 0.f),
			Vector3(1.f, 0.f, 0.f),
			Vector3(1.f, 0.f, 0.f),
			Vector3(1.f, 0.f, 0.f),
			Vector3(1.f, 0.f, 0.f),
			Vector3(1.f, 0.f, 0.f),

			//Bottom
			Vector3(1.f, 0.f, 0.f),
			Vector3(1.f, 0.f, 0.f),
			Vector3(1.f, 0.f, 0.f),
			Vector3(1.f, 0.f, 0.f),
			Vector3(1.f, 0.f, 0.f),
			Vector3(1.f, 0.f, 0.f),
			Vector3(1.f, 0.f, 0.f),
			Vector3(1.f, 0.f, 0.f)
		};

		mesh.texcoords =
		{
			//Back
			Vector2(0.f, 0.f),
			Vector2(0.f, 0.f),
			Vector2(0.f, 0.f),
			Vector2(0.f, 0.f),

			//Front
			Vector2(0.f, 0.f),
			Vector2(0.f, 0.f),
			Vector2(0.f, 0.f),
			Vector2(0.f, 0.f),

			//Top
			Vector2(0.f, 0.f),
			Vector2(0.f, 0.f),
			Vector2(0.f, 0.f),
			Vector2(0.f, 0.f),
			Vector2(0.f, 0.f),
			Vector2(0.f, 0.f),
			Vector2(0.f, 0.f),
			Vector2(0.f, 0.f),

			//Bottom
			Vector2(0.f, 0.f),
			Vector2(0.f, 0.f),
			Vector2(0.f, 0.f),
			Vector2(0.f, 0.f),
			Vector2(0.f, 0.f),
			Vector2(0.f, 0.f),
			Vector2(0.f, 0.f),
			Vector2(0.f, 0.f)
		};

		return mesh;
	}

	Mesh Mesh::Cylinder(unsigned int nb_latitudes)
	{
		Mesh mesh;
		mesh.draw_type = DrawType::Triangles;
		float nb = static_cast<float>(nb_latitudes);

		for (unsigned int i = 0; i < nb_latitudes; i++)
		{
			mesh.positions.push_back(Vector3(0.5f * cos((i + 1) * 2.f * pi / nb), -0.5f, 0.5f * sin((i + 1) * 2.f * pi / nb)));
			mesh.positions.push_back(Vector3(0.5f * cos(i * 2.f * pi / nb), -0.5f, 0.5f * sin(i * 2.f * pi / nb)));
			mesh.positions.push_back(Vector3(0.5f * cos(i * 2.f * pi / nb), 0.5f, 0.5f * sin(i * 2.f * pi / nb)));

			mesh.positions.push_back(Vector3(0.5f * cos(i * 2.f * pi / nb), 0.5f, 0.5f * sin(i * 2.f * pi / nb)));
			mesh.positions.push_back(Vector3(0.5f * cos((i + 1) * 2.f * pi / nb), 0.5f, 0.5f * sin((i + 1) * 2.f * pi / nb)));
			mesh.positions.push_back(Vector3(0.5f * cos((i + 1) * 2.f * pi / nb), -0.5f, 0.5f * sin((i + 1) * 2.f * pi / nb)));

			mesh.texcoords.push_back(Vector2((i + 1) / nb, 1.f));
			mesh.texcoords.push_back(Vector2(i / nb, 1.f));
			mesh.texcoords.push_back(Vector2(i / nb, 0.f));

			mesh.texcoords.push_back(Vector2(i / nb, 0.f));
			mesh.texcoords.push_back(Vector2((i + 1) / nb, 0.f));
			mesh.texcoords.push_back(Vector2((i + 1) / nb, 1.f));
		}

		for (auto& position : mesh.positions)
			mesh.normals.push_back(normalize(Vector3(position.x, 0.f, position.z)));

		for (unsigned int i = 0; i < nb_latitudes; i++)
		{
			mesh.positions.push_back(Vector3(0.5f * cos(i * 2.f * pi / nb), -0.5f, 0.5f * sin(i * 2.f * pi / nb)));
			mesh.positions.push_back(Vector3(0.5f * cos((i + 1) * 2.f * pi / nb), -0.5f, 0.5f * sin((i + 1) * 2.f * pi / nb)));
			mesh.positions.push_back(Vector3(0.f, -0.5f, 0.f));

			mesh.normals.push_back(Vector3(0.f, -1.f, 0.f));
			mesh.normals.push_back(Vector3(0.f, -1.f, 0.f));
			mesh.normals.push_back(Vector3(0.f, -1.f, 0.f));

			mesh.texcoords.push_back(Vector2(mesh.positions[nb_latitudes * 6 + i * 3].x + 0.5f, 0.5f - mesh.positions[nb_latitudes * 6 + i * 3].z));
			mesh.texcoords.push_back(Vector2(mesh.positions[nb_latitudes * 6 + i * 3 + 1].x + 0.5f, 0.5f - mesh.positions[nb_latitudes * 6 + i * 3 + 1].z));
			mesh.texcoords.push_back(Vector2(mesh.positions[nb_latitudes * 6 + i * 3 + 2].x + 0.5f, 0.5f - mesh.positions[nb_latitudes * 6 + i * 3 + 2].z));
		}

		for (unsigned int i = 0; i < nb_latitudes; i++)
		{
			mesh.positions.push_back(Vector3(0.5f * cos((i + 1) * 2.f * pi / nb), 0.5f, 0.5f * sin((i + 1) * 2.f * pi / nb)));
			mesh.positions.push_back(Vector3(0.5f * cos(i * 2.f * pi / nb), 0.5f, 0.5f * sin(i * 2.f * pi / nb)));
			mesh.positions.push_back(Vector3(0.f, 0.5f, 0.f));

			mesh.normals.push_back(Vector3(0.f, 1.f, 0.f));
			mesh.normals.push_back(Vector3(0.f, 1.f, 0.f));
			mesh.normals.push_back(Vector3(0.f, 1.f, 0.f));

			mesh.texcoords.push_back(Vector2(mesh.positions[nb_latitudes * 9 + i * 3].x + 0.5f, 0.5f - mesh.positions[nb_latitudes * 9 + i * 3].z));
			mesh.texcoords.push_back(Vector2(mesh.positions[nb_latitudes * 9 + i * 3 + 1].x + 0.5f, 0.5f - mesh.positions[nb_latitudes * 9 + i * 3 + 1].z));
			mesh.texcoords.push_back(Vector2(mesh.positions[nb_latitudes * 9 + i * 3 + 2].x + 0.5f, 0.5f - mesh.positions[nb_latitudes * 9 + i * 3 + 2].z));
		}

		return mesh;
	}

	Mesh Mesh::Sphere(unsigned int nb_latitudes, unsigned int nb_longitudes)
	{
		Mesh mesh;
		mesh.draw_type = DrawType::Triangles;
		float nb_y = static_cast<float>(nb_latitudes);
		float nb_x = static_cast<float>(nb_longitudes);

		for (unsigned int x = 0; x < nb_longitudes; x++)
			for (unsigned int y = 0; y < nb_latitudes; y++)
			{
				mesh.positions.push_back(Vector3::Spherical(0.5f, (x + 1) * 2.f * pi / nb_x, y * pi / nb_y));
				mesh.positions.push_back(Vector3::Spherical(0.5f, x * 2.f * pi / nb_x, y * pi / nb_y));
				mesh.positions.push_back(Vector3::Spherical(0.5f, x * 2.f * pi / nb_x, (y + 1) * pi / nb_y));

				mesh.positions.push_back(Vector3::Spherical(0.5f, (x + 1) * 2.f * pi / nb_x, y * pi / nb_y));
				mesh.positions.push_back(Vector3::Spherical(0.5f, x * 2.f * pi / nb_x, (y + 1) * pi / nb_y));
				mesh.positions.push_back(Vector3::Spherical(0.5f, (x + 1) * 2.f * pi / nb_x, (y + 1) * pi / nb_y));

				mesh.texcoords.push_back(Vector2((x + 1) / nb_x, y / nb_y));
				mesh.texcoords.push_back(Vector2(x / nb_x, y / nb_y));
				mesh.texcoords.push_back(Vector2(x / nb_x, (y + 1) / nb_y));

				mesh.texcoords.push_back(Vector2((x + 1) / nb_x, y / nb_y));
				mesh.texcoords.push_back(Vector2(x / nb_x, (y + 1) / nb_y));
				mesh.texcoords.push_back(Vector2((x + 1) / nb_x, (y + 1) / nb_y));
			}

		for (auto& position : mesh.positions)
			mesh.normals.push_back(normalize(position));

		return mesh;
	}

	Mesh Mesh::Square()
	{
		Mesh mesh;
		mesh.draw_type = DrawType::Triangles;

		mesh.positions =
		{
			Vector3( 0.5f,  0.5f,  0.f),
			Vector3(-0.5f,  0.5f,  0.f),
			Vector3(-0.5f, -0.5f,  0.f),
			Vector3( 0.5f, -0.5f,  0.f),
			Vector3( 0.5f,  0.5f,  0.f),
			Vector3(-0.5f, -0.5f,  0.f)
		};

		mesh.normals =
		{
			Vector3(0.f, 0.f, 1.f),
			Vector3(0.f, 0.f, 1.f),
			Vector3(0.f, 0.f, 1.f),
			Vector3(0.f, 0.f, 1.f),
			Vector3(0.f, 0.f, 1.f),
			Vector3(0.f, 0.f, 1.f)
		};

		mesh.texcoords =
		{
			Vector2(1.f, 0.f),
			Vector2(0.f, 0.f),
			Vector2(0.f, 1.f),
			Vector2(1.f, 1.f),
			Vector2(1.f, 0.f),
			Vector2(0.f, 1.f)
		};

		return mesh;
	}

	Mesh Mesh::EmptySquare()
	{
		Mesh mesh;
		mesh.draw_type = DrawType::Lines;

		mesh.positions =
		{
			Vector3( 0.5f,  0.5f,  0.f),
			Vector3(-0.5f,  0.5f,  0.f),
			Vector3(-0.5f,  0.5f,  0.f),
			Vector3(-0.5f, -0.5f,  0.f),
			Vector3(-0.5f, -0.5f,  0.f),
			Vector3( 0.5f, -0.5f,  0.f),
			Vector3( 0.5f, -0.5f,  0.f),
			Vector3( 0.5f,  0.5f,  0.f)
		};

		mesh.normals =
		{
			Vector3(0.f, 0.f, 1.f),
			Vector3(0.f, 0.f, 1.f),
			Vector3(0.f, 0.f, 1.f),
			Vector3(0.f, 0.f, 1.f),
			Vector3(0.f, 0.f, 1.f),
			Vector3(0.f, 0.f, 1.f),
			Vector3(0.f, 0.f, 1.f),
			Vector3(0.f, 0.f, 1.f)
		};

		mesh.texcoords =
		{
			Vector2(1.f, 0.f),
			Vector2(0.f, 0.f),
			Vector2(0.f, 0.f),
			Vector2(0.f, 1.f),
			Vector2(0.f, 1.f),
			Vector2(1.f, 1.f),
			Vector2(1.f, 1.f),
			Vector2(1.f, 0.f)
		};

		return mesh;
	}

	Mesh Mesh::Screen()
	{
		Mesh mesh;
		mesh.draw_type = DrawType::Triangles;

		mesh.positions =
		{
			Vector3( 1.f,  1.f,  0.f),
			Vector3(-1.f,  1.f,  0.f),
			Vector3(-1.f, -1.f,  0.f),
			Vector3( 1.f, -1.f,  0.f),
			Vector3( 1.f,  1.f,  0.f),
			Vector3(-1.f, -1.f,  0.f)
		};

		mesh.normals =
		{
			Vector3(0.f, 0.f, -1.f),
			Vector3(0.f, 0.f, -1.f),
			Vector3(0.f, 0.f, -1.f),
			Vector3(0.f, 0.f, -1.f),
			Vector3(0.f, 0.f, -1.f),
			Vector3(0.f, 0.f, -1.f)
		};

		mesh.texcoords =
		{
			Vector2(1.f, 1.f),
			Vector2(0.f, 1.f),
			Vector2(0.f, 0.f),
			Vector2(1.f, 0.f),
			Vector2(1.f, 1.f),
			Vector2(0.f, 0.f)
		};

		return mesh;
	}

	Mesh operator+(const Mesh& mesh_1, const Mesh& mesh_2)
	{
		Mesh mesh;
		mesh.draw_type = mesh_1.draw_type;

		for (auto& position : mesh_1.positions)
			mesh.positions.push_back(position);

		for (auto& normal : mesh_1.normals)
			mesh.normals.push_back(normal);

		for (auto& texcoord : mesh_1.texcoords)
			mesh.texcoords.push_back(texcoord);

		for (auto& position : mesh_2.positions)
			mesh.positions.push_back(position);

		for (auto& normal : mesh_2.normals)
			mesh.normals.push_back(normal);

		for (auto& texcoord : mesh_2.texcoords)
			mesh.texcoords.push_back(texcoord);

		return mesh;
	}

	Mesh operator*(const glm::mat4& matrix, const Mesh& mesh)
	{
		Mesh result;
		result.draw_type = mesh.draw_type;

		for (auto& position : mesh.positions)
			result.positions.push_back(Vector3(matrix * position));

		glm::mat3 normals_matrix = glm::transpose(glm::inverse(glm::mat3(matrix)));

		for (auto& normal : mesh.normals)
			result.normals.push_back(normalize(Vector3(normals_matrix * normal)));

		result.texcoords = mesh.texcoords;

		return result;
	}

	Mesh operator*(const Mesh& mesh, const glm::mat4& matrix)
	{
		Mesh result = matrix * mesh;
		return result;
	}
}
