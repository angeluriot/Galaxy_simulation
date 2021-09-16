#ifndef DIM_OBJECT_HPP
#define DIM_OBJECT_HPP

#include "dim/utils/libraries.hpp"
#include "dim/vectors/Vector3.hpp"
#include "dim/opengl/VertexBuffer.hpp"
#include "dim/objects/Material.hpp"
#include "dim/lights/Light.hpp"
#include "dim/opengl/Shader.hpp"
#include "dim/cameras/Camera.hpp"
#include "dim/windows/Scene.hpp"

namespace dim
{
	class Scene;
	class Window;
	class Shader;

	/**
	 * @brief This class represents a 3D object, it can be binded for optimization but it is not essential.
	 */
	class Object
	{
	private:

		Shader			shader;				// The shader used to display the object.
		VertexBuffer	vertex_buffer;		// The vertex buffer that stores the data of the object.
		Texture			texture;			// The texture of the object.
		glm::mat4		scaling_matrix;		// The matrix used to change the size of the object.
		glm::mat4		rotation_matrix;	// The matrix used to rotate the object.
		glm::mat4		translation_matrix;	// The matrix used to change the position of the object.
		glm::mat4		origin_matrix;		// The matrix used to change the origin point of the object.
		glm::mat4		model;				// The matrix that contains all the transformations data.
		float			thickness;			// The thickness of lines and points.
		bool			textured;			// True if the object is textured.
		mutable bool	binded;				// True if the object has been binded.

	public:

		Mesh			mesh;				// The mesh of the object (use the update_mesh function to apply the modifications).
		Material		material;			// The material of the object.

		/**
		 * @brief Construct a new object (not valid).
		 */
		Object();

		/**
		 * @brief Construct a new object from another.
		 *
		 * @param other the reference object
		 */
		Object(const Object& other);

		/**
		 * @brief Construct a new object.
		 *
		 * @param mesh the mesh of the object
		 * @param material the material of the object
		 */
		Object(const Mesh& mesh, const Material& material = Material(Color::white, 0.1f, 0.5f, 0.4f, 50.f));

		/**
		 * @brief Copy the data of another object.
		 *
		 * @param other the object to copy
		 * @return a reference to the object
		 */
		Object& operator=(const Object& other);

		/**
		 * @brief Initialize an already constructed object.
		 *
		 * @param mesh the mesh of the object
		 * @param material the material of the object
		 */
		void create(const Mesh& mesh, const Material& material = Material(Color::white, 0.1f, 0.5f, 0.4f, 50.f));

		/**
		 * @brief Change the shader (initially it is the default shader).
		 *
		 * @param shader_name the name of the new shader
		 */
		void set_shader(const std::string& shader_name);

		/**
		 * @brief Change the shader (initially it is the default shader).
		 *
		 * @param shader the new shader
		 */
		void set_shader(const Shader& shader);

		/**
		 * @brief Give the shader of the object.
		 *
		 * @return the shader of the object
		 */
		Shader get_shader() const;

		/**
		 * @brief Change the texture of the object.
		 *
		 * @param texture_name the name of the new texture
		 */
		void set_texture(const std::string& texture_name);

		/**
		 * @brief Change the texture of the object.
		 *
		 * @param texture the new texture
		 */
		void set_texture(const Texture& texture);

		/**
		 * @brief Remove the texture of the object.
		 */
		void remove_texture();

		/**
		 * @brief Give the texture of the object.
		 *
		 * @return the texture of the object
		 */
		Texture get_texture() const;

		/**
		 * @brief Change the mesh of the object and send the new mesh to the shader.
		 *
		 * @param mesh the new mesh
		 * @param data_sent the types of data to send (you can use the | operator)
		 */
		void set_mesh(const Mesh& mesh, dim::DataType data_sent = dim::DataType::All);

		/**
		 * @brief Send the mesh to the shader.
		 *
		 * @param data_sent the types of data to send (you can use the | operator)
		 */
		void update_mesh(dim::DataType data_sent = dim::DataType::All);

		/**
		 * @brief Change the size of the object.
		 *
		 * @param x the new X size
		 * @param y the new Y size
		 * @param z the new Z size
		 */
		void set_size(float x, float y, float z);

		/**
		 * @brief Change the size of the object.
		 *
		 * @param size the new size
		 */
		void set_size(const Vector3& size);

		/**
		 * @brief Change the rotation of the object.
		 *
		 * @param angle the new angle of rotation (in degrees)
		 * @param axis the new axis of rotation
		 */
		void set_rotation(float angle, const Vector3& axis);

		/**
		 * @brief Change the position of the object.
		 *
		 * @param x the new X position
		 * @param y the new Y position
		 * @param z the new Z position
		 */
		void set_position(float x, float y, float z);

		/**
		 * @brief Change the position of the object.
		 *
		 * @param position the new position
		 */
		void set_position(const Vector3& position);

		/**
		 * @brief Change the origin point of the object.
		 *
		 * @param x the new X origin point
		 * @param y the new Y origin point
		 * @param z the new Z origin point
		 */
		void set_origin(float x, float y, float z);

		/**
		 * @brief Change the origin point of the object.
		 *
		 * @param origin the new origin point
		 */
		void set_origin(const Vector3& origin);

		/**
		 * @brief Change the thickness of the borders of the object.
		 *
		 * @param thickness the new thickness of the borders
		 */
		void set_thickness(float thickness);

		/**
		 * @brief Scale the object.
		 *
		 * @param x the X scale
		 * @param y the Y scale
		 * @param z the Z scale
		 */
		void scale(float x, float y, float z);

		/**
		 * @brief Scale the object.
		 *
		 * @param scale the scale
		 */
		void scale(const Vector3& scale);

		/**
		 * @brief Rotate the object.
		 *
		 * @param angle the angle of rotation (in degrees)
		 * @param axis the axis of rotation
		 */
		void rotate(float angle, const Vector3& axis);

		/**
		 * @brief Move the object.
		 *
		 * @param x the X move
		 * @param y the Y move
		 * @param z the Z move
		 */
		void move(float x, float y, float z);

		/**
		 * @brief Move the object.
		 *
		 * @param move the move
		 */
		void move(const Vector3& move);

		/**
		 * @brief Give the size of the object.
		 *
		 * @return the size of the object
		 */
		Vector3 get_size() const;

		/**
		 * @brief Give the rotation of the object.
		 *
		 * @return the rotation matrix of the object
		 */
		glm::mat4 get_rotation() const;

		/**
		 * @brief Give the position of the object.
		 *
		 * @return the position of the object
		 */
		Vector3 get_position() const;

		/**
		 * @brief Give the origin point of the object.
		 *
		 * @return the origin point of the object
		 */
		Vector3 get_origin() const;

		/**
		 * @brief Give the thickness of the borders of the object.
		 *
		 * @return the thickness of the borders
		 */
		float get_thickness() const;

		/**
		 * @brief Bind the object (good for optimization but not not essential)
		 */
		void bind() const;

		/**
		 * @brief Unbind the object (good for optimization but not not essential)
		 */
		void unbind() const;

	private:

		/**
		 * @brief Display the object on the scene or the window.
		 *
		 * @param camera the camera of the scene or the window
		 * @param lights the lights in the scene or the window
		 * @param draw_type the way to draw the object (triangles, lines or points)
		 * @param scene_shader true if the scene or the window has a shader
		 */
		void draw(Camera* camera, const std::vector<Light*>& lights, DrawType draw_type, bool scene_shader) const;

	public:

		friend Scene;
		friend Window;
	};
}

#endif
