// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../sdk.hpp"

vector vector::transform(matrix3x4_t trans)
{
	return { dot(trans[0]) + trans[0][3], dot(trans[1]) + trans[1][3], dot(trans[2]) + trans[2][3] };
}