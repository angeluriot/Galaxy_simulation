#ifndef COMPUTE_SHADER_HPP
#define COMPUTE_SHADER_HPP

#include "libraries.hpp"

/**
 * @brief The type of permissions of the compute shader data.
 */
enum class Permissions
{
	Read	= CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,	// The compute shader can only read the data.
	Write	= CL_MEM_WRITE_ONLY,						// The compute shader can only write on the data.
	All		= CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR	// The compute shader can do both.
};

/**
 * @brief A static class simplifying the use of OpenCL.
 */
class ComputeShader
{
public:

	static cl::Program		program;	// The program that will run on the device.
	static cl::Context		context;	// The context which holds the device.
	static cl::Device		device;		// The device where the kernel will run.
	static cl::CommandQueue	queue;		// The command queue of the kernel.

	/**
	 * @brief Find the default device.
	 *
	 * @return the device found
	 */
	static cl::Device get_default_device();

	/**
	 * @brief Compile the compute shader.
	 *
	 * @param path the path to the compute shader source code
	 */
	static void	init(const std::string& path);

	/**
	 * @brief Give a buffer from an array of data and its permissions.
	 *
	 * @tparam T the type of array
	 * @param data the array of data
	 * @param permissions its permissions
	 * @return the buffer
	 */
	template <typename T>
	static cl::Buffer Buffer(std::vector<T>& data, Permissions permissions = Permissions::All)
	{
		return cl::Buffer(context, static_cast<cl_mem_flags>(permissions), data.size() * sizeof(T), data.data());
	}

	/**
	 * @brief Give a buffer from data and its permissions.
	 *
	 * @tparam T the type of data
	 * @param data the data
	 * @param permissions its permissions
	 * @return the buffer
	 */
	template <typename T>
	static cl::Buffer Buffer(T& data, Permissions permissions = Permissions::All)
	{
		return cl::Buffer(context, static_cast<cl_mem_flags>(permissions), sizeof(T), &data);
	}

	/**
	 * @brief Launch a function of the compute shader.
	 *
	 * @param function the function to launch
	 * @param buffers the inputs
	 * @param global the global threads structure
	 * @param local the local threads structure
	 */
	static void launch(const std::string& function, const std::vector<cl::Buffer*>& buffers, const cl::NDRange& global, const cl::NDRange& local);

	/**
	 * @brief Launch a function of the compute shader.
	 *
	 * @param function the function to launch
	 * @param buffers the inputs
	 * @param global the global threads structure
	 */
	static void launch(const std::string& function, const std::vector<cl::Buffer*>& buffers, const cl::NDRange& global);

	/**
	 * @brief Update the given data array.
	 *
	 * @tparam T the type of array
	 * @param buffer the OpenCL buffer
	 * @param data the data array
	 */
	template <typename T>
	static void get_data(const cl::Buffer buffer, std::vector<T>& data)
	{
		queue.enqueueReadBuffer(buffer, CL_TRUE, 0, data.size() * sizeof(T), data.data());
	}

	/**
	 * @brief Update the given data.
	 *
	 * @tparam T the type of data
	 * @param buffer the OpenCL buffer
	 * @param data the data
	 */
	template <typename T>
	static void get_data(const cl::Buffer buffer, T& data)
	{
		queue.enqueueReadBuffer(buffer, CL_TRUE, 0, sizeof(T), &data);
	}
};

#endif
