#ifndef DIM_DIMENSION3D_HPP
#define DIM_DIMENSION3D_HPP

#include "dim/utils/libraries.hpp"
#include "dim/objects/Mesh.hpp"
#include "dim/lights/Light.hpp"
#include "dim/lights/AmbientLight.hpp"
#include "dim/lights/DirectionalLight.hpp"
#include "dim/lights/PointLight.hpp"
#include "dim/objects/Material.hpp"
#include "dim/objects/Object.hpp"
#include "dim/opengl/Shader.hpp"
#include "dim/opengl/Texture.hpp"
#include "dim/vectors/Vector2.hpp"
#include "dim/vectors/Vector3.hpp"
#include "dim/vectors/Vector4.hpp"
#include "dim/vectors/Vector2int.hpp"
#include "dim/vectors/Vector3int.hpp"
#include "dim/vectors/Vector4int.hpp"
#include "dim/vectors/vectors.hpp"
#include "dim/opengl/VertexBuffer.hpp"
#include "dim/windows/Window.hpp"
#include "dim/cameras/Camera.hpp"
#include "dim/utils/utils.hpp"
#include "dim/opengl/FrameBuffer.hpp"
#include "dim/windows/Scene.hpp"
#include "dim/utils/Color.hpp"
#include "dim/controllers/Controller.hpp"
#include "dim/controllers/OrbitController.hpp"
#include "dim/controllers/FlyController.hpp"
#include "dim/controllers/DragController.hpp"
#include "dim/cameras/Camera2D.hpp"
#include "dim/cameras/OrthographicCamera.hpp"
#include "dim/cameras/PerspectiveCamera.hpp"

namespace dim
{
	/**
	 * @brief Initialize the OpenGL library.
	 */
	void init_opengl();

	/**
	 * @brief Initialize the ImGui library.
	 */
	void init_imgui();

	/**
	 * @brief Initialize the Dimension3D library.
	 */
	void init();

	/**
	 * @brief Shut down the Dimension3D library.
	 */
	void shut_down();
}

#endif
