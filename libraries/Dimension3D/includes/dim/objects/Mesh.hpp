#ifndef DIM_MESH_HPP
#define DIM_MESH_HPP

#include "dim/utils/libraries.hpp"
#include "dim/utils/utils.hpp"
#include "dim/vectors/Vector2.hpp"
#include "dim/vectors/Vector3.hpp"
#include "dim/vectors/Vector4.hpp"
#include "dim/opengl/Shader.hpp"

namespace dim
{
	class VertexBuffer;
	class Mesh;
	class Scene;
	class Window;
	enum class DrawType;

	/**
	 * @brief Merge two meshes.
	 *
	 * @param mesh_1 the first mesh
	 * @param mesh_2 the second mesh
	 * @return the merged mesh
	 */
	Mesh operator+(const Mesh& mesh_1, const Mesh& mesh_2);

	/**
	 * @brief Apply a transformation matrix to a mesh.
	 *
	 * @param matrix the transformation matrix
	 * @param mesh the mesh to transform
	 * @return the transformed mesh
	 */
	Mesh operator*(const glm::mat4& matrix, const Mesh& mesh);

	/**
	 * @brief Apply a transformation matrix to a mesh.
	 *
	 * @param mesh the mesh to transform
	 * @param matrix the transformation matrix
	 * @return the transformed mesh
	 */
	Mesh operator*(const Mesh& mesh, const glm::mat4& matrix);

	/**
	 * @brief This class represents a 3D model with all the data necessary for the
	 * correct display of the shape : positions, normals and texture coordinates.
	 */
	class Mesh
	{
	private:

		DrawType				draw_type;			// The way to draw the mesh (triangles, lines or points).

	public:

		std::vector<Vector3>	positions;			// The positions data of the mesh.
		std::vector<Vector3>	normals;			// The normals data of the mesh.
		std::vector<Vector2>	texcoords;			// The texture coordinates data of the mesh.

		static const Mesh		circle_64;			// A circle with 64 edges.
		static const Mesh		empty_circle_64;	// An empty circle with 64 edges.
		static const Mesh		cone_64;			// A cone with 64 latitudes.
		static const Mesh		cube;				// A cube.
		static const Mesh		empty_cube;			// An empty cube.
		static const Mesh		cylinder_64;		// A cylinder with 64 latitudes.
		static const Mesh		null;				// An empty mesh.
		static const Mesh		sphere_64;			// A sphere with 64 latitudes and longitudes.
		static const Mesh		square;				// A square.
		static const Mesh		empty_square;		// An empty square.
		static const Mesh		screen;				// A shape that takes all the screen for post processing shaders.

		/**
		 * @brief Construct a new empty mesh.
		 */
		Mesh();

		/**
		 * @brief Construct a new mesh from another.
		 *
		 * @param other the reference mesh
		 */
		Mesh(const Mesh& other) = default;

		/**
		 * @brief Copy the data of another mesh.
		 *
		 * @param other the mesh to copy
		 * @return a reference to the mesh
		 */
		Mesh& operator=(const Mesh& other) = default;

		/**
		 * @brief Merge with another mesh.
		 *
		 * @param other the mesh to merge with
		 * @return a reference to the mesh
		 */
		Mesh& operator+=(const Mesh& other);

		/**
		 * @brief Apply a transformation matrix to the mesh.
		 *
		 * @param matrix the transformation matrix
		 * @return a reference to the mesh
		 */
		Mesh& operator*=(const glm::mat4& matrix);

		/**
		 * @brief Give the size of all the mesh data.
		 *
		 * @return the size of all the mesh data
		 */
		unsigned int get_data_size() const;

		/**
		 * @brief Give the size of the positions data.
		 *
		 * @return the size of the positions data
		 */
		unsigned int get_positions_size() const;

		/**
		 * @brief Give the size of the normals data.
		 *
		 * @return the size of the normals data
		 */
		unsigned int get_normals_size() const;

		/**
		 * @brief Give the size of the texcoords data.
		 *
		 * @return the size of the texcoords data
		 */
		unsigned int get_texcoords_size() const;

		/**
		 * @brief Give the number of vertices in the mesh.
		 *
		 * @return the number of vertices in the mesh
		 */
		unsigned int get_nb_vertices() const;

		/**
		 * @brief Empty the mesh.
		 */
		void clear();

		/**
		 * @brief Construct a new circle mesh.
		 *
		 * @param nb_edges the number of edges
		 * @return the new circle mesh
		 */
		static Mesh Circle(unsigned int nb_edges);

		/**
		 * @brief Construct a new empty circle mesh.
		 *
		 * @param nb_edges the number of edges
		 * @return the new empty circle mesh
		 */
		static Mesh EmptyCircle(unsigned int nb_edges);

		/**
		 * @brief Construct a new cone mesh.
		 *
		 * @param nb_latitudes the number of latitudes
		 * @return the new cone mesh
		 */
		static Mesh Cone(unsigned int nb_latitudes);

		/**
		 * @brief Construct a new cube mesh.
		 *
		 * @return the a new cube mesh
		 */
		static Mesh Cube();

		/**
		 * @brief Construct a new empty cube mesh.
		 *
		 * @return the a new empty cube mesh
		 */
		static Mesh EmptyCube();

		/**
		 * @brief Construct a new cylinder mesh.
		 *
		 * @param nb_latitudes the number of latitudes
		 * @return the new cylinder mesh
		 */
		static Mesh Cylinder(unsigned int nb_latitudes);

		/**
		 * @brief Construct a new sphere mesh.
		 *
		 * @param nb_latitudes the number of latitudes
		 * @param nb_longitudes the number of longitudes
		 * @return the new sphere mesh
		 */
		static Mesh Sphere(unsigned int nb_latitudes, unsigned int nb_longitudes);

		/**
		 * @brief Construct a new square mesh.
		 *
		 * @return the new square mesh
		 */
		static Mesh Square();

		/**
		 * @brief Construct a new empty square mesh.
		 *
		 * @return the new empty square mesh
		 */
		static Mesh EmptySquare();

		/**
		 * @brief Construct a shape that takes all the screen for post processing shaders.
		 *
		 * @return the screen shape
		 */
		static Mesh Screen();

		friend Scene;
		friend Window;
		friend Mesh operator+(const Mesh& mesh_1, const Mesh& mesh_2);
		friend Mesh operator*(const glm::mat4& matrix, const Mesh& mesh);
		friend Mesh operator*(const Mesh& mesh, const glm::mat4& matrix);
	};
}

#endif
