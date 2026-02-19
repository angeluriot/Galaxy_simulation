// Convert a 4D vector to a 3D vector.
float3 convert_3(float4 vector)
{
    return (float3)(vector.x, vector.y, vector.z);
}

// Convert a 3D vector to a 4D vector.
float4 convert_4(float3 vector)
{
    return (float4)(vector.x, vector.y, vector.z, 0);
}

// Give the squared norm of the vector.
float norm_2(float3 vector)
{
    return pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2);
}

// Give the squared distance between to points.
float distance_2(float3 point_1, float3 point_2)
{
    return norm_2(point_2 - point_1);
}

// Handle the interactions between the stars.
__kernel void interactions(__global float4* positions, __global float4* accelerations,
    __global float* interaction_rate, __global float* smoothing_length, __global float* black_hole_mass, __global int* types,
    __global float* negative_attraction_constant, __global float* repulsion_constant)
{
    int index = get_global_id(0);
    float3 acc = (float3)(0, 0, 0);
    int type = types[index];

    for (int i = 0; i < *interaction_rate * get_global_size(0); i++)
    {
        if (i != index)
        {
            float3 vector = convert_3(positions[i]) - convert_3(positions[index]);
            int other_type = types[i];
            float sign;

            if (type == other_type)
            {
                sign = (type == -1) ? *negative_attraction_constant : 1.0f; // Use negative_attraction_constant for negative stars
            }
            else
            {
                sign = -*repulsion_constant; // Use repulsion_constant for different types repulsing each other
            }

            acc += sign * (normalize(vector) / (norm_2(vector) + *smoothing_length)) / *interaction_rate;
        }
    }

    acc += (*black_hole_mass * normalize(-convert_3(positions[index]))) / (norm_2(convert_3(positions[index])) + *smoothing_length);
    accelerations[index] = convert_4(acc);
}

// Make the integrations to update the position of the stars.
__kernel void integration(__global float3* positions, __global float3* speeds, __global float3* accelerations, __global float* step)
{
	int index = get_global_id(0);
	speeds[index] += *step * accelerations[index];
	positions[index] += *step * speeds[index];
}