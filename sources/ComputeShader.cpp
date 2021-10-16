#include "ComputeShader.hpp"

cl::Program			ComputeShader::program;
cl::Context			ComputeShader::context;
cl::Device			ComputeShader::device;
cl::CommandQueue	ComputeShader::queue;

cl::Device ComputeShader::get_default_device()
{
	// Search for all the OpenCL platforms available and check if there are any.

	std::vector<cl::Platform> platforms;
	cl::Platform::get(&platforms);

	if (platforms.empty())
	{
		std::cerr << "No platforms found!" << std::endl;
		exit(1);
	}

	// Search for all the devices on the first platform and check if there are any available.

	auto platform = platforms.front();
	std::vector<cl::Device> devices;
	platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);

	if (devices.empty())
	{
		std::cerr << "No devices found!" << std::endl;
		exit(1);
	}

	// Return the first device found.
	return devices.front();
}

void ComputeShader::init(const std::string& path)
{
	// Select the first available device.
	device = get_default_device();

	// Read OpenCL kernel file as a string.
	std::ifstream kernel_file(path);
	std::string src(std::istreambuf_iterator<char>(kernel_file), (std::istreambuf_iterator<char>()));

	// Compile kernel program which will run on the device.
	cl::Program::Sources sources(1, std::make_pair(src.c_str(), src.length() + 1));
	context = cl::Context(device);
	program = cl::Program(context, sources);

	auto err = program.build();
	if(err != CL_BUILD_SUCCESS)
	{
		std::cerr << "Error!\nBuild Status: " << program.getBuildInfo<CL_PROGRAM_BUILD_STATUS>(device)
			<< "\nBuild Log:\t " << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device) << std::endl;
		exit(1);
	}

	//std::vector<::size_t> maxWorkItems;
	//maxWorkItems = device.getInfo<CL_DEVICE_MAX_WORK_ITEM_SIZES>();
	//std::cout << maxWorkItems[0] << " " << maxWorkItems[1] << " " << maxWorkItems[2] << std::endl;
}

void ComputeShader::launch(const std::string& function, const std::vector<cl::Buffer*>& buffers, const cl::NDRange& global, const cl::NDRange& local)
{
	cl::Kernel kernel(program, function.data());

	for (int i = 0; i < buffers.size(); i++)
		kernel.setArg(i, *(buffers[i]));

	queue = cl::CommandQueue(context, device);
	queue.enqueueNDRangeKernel(kernel, cl::NullRange, global, local);
}

void ComputeShader::launch(const std::string& function, const std::vector<cl::Buffer*>& buffers, const cl::NDRange& global)
{
	cl::Kernel kernel(program, function.data());

	for (int i = 0; i < buffers.size(); i++)
		kernel.setArg(i, *(buffers[i]));

	queue = cl::CommandQueue(context, device);
	queue.enqueueNDRangeKernel(kernel, cl::NullRange, global);
}
