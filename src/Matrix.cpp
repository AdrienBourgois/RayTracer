#include <cmath>
#include <sstream>
#include <iostream>
#include "Matrix.h"

Matrix4x4::Matrix4x4()
{
    *this = Matrix4x4::identity;
}

Matrix4x4::Matrix4x4(std::initializer_list<float> init_list)
{
    *this = Matrix4x4::identity;
    unsigned int count = 0;
    if (init_list.size() <= 16)
        for (auto x : init_list)
        {
            val[count] = x;
            ++count;
        }
}

float cotan(float x)
{
    return (1.f / std::tan(x));
}

Matrix4x4 Matrix4x4::identity =
{
    1.f, 0.f, 0.f, 0.f,
    0.f, 1.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f
};

auto Matrix4x4::perspective(float angle, float aspect, float near, float far) -> Matrix4x4
{

    float f = cotan(angle / 2);
    float z2 = (far + near) / (near - far);
    float z3 = (2 * far * near) / (near - far);

    this->val[0] = (f / aspect);
    this->val[5] = f;
    this->val[10] = z2;
    this->val[11] = z3;
    this->val[14] = -1.f;

    return *this;
}

auto Matrix4x4::orthographic(float right, float left, float top, float bottom, float far, float near) -> Matrix4x4
{
    val[0] = (2.0f/(right - left));
    val[3] = -(right + left) / (right - left);
    val[5] = (2.0f/(top - bottom));
    val[7] = -(top + bottom) / (top - bottom);
    val[10] = (-2.0f/(far - near));
    val[11] = -(far+near) / (far - near);
	val[15] = 1.0f;

    return *this;
}

auto Matrix4x4::translate(float x, float y, float z) -> Matrix4x4
{
    return
    {
        1.f, 0.f, 0.f, x,
        0.f, 1.f, 0.f, y,
        0.f, 0.f, 1.f, z,
        0.f, 0.f, 0.f, 1.f
    };
}

auto Matrix4x4::translate(Vector3D<float> vector3) -> Matrix4x4
{
    return
    {
        1.f, 0.f, 0.f, vector3.x,
        0.f, 1.f, 0.f, vector3.y,
        0.f, 0.f, 1.f, vector3.z,
        0.f, 0.f, 0.f, 1.f 
    };
}

auto Matrix4x4::scale(float x, float y, float z) -> Matrix4x4
{
    return
    {
        x, 0.f, 0.f, 0.f,
        0.f, y, 0.f, 0.f,
        0.f, 0.f, z, 0.f,
        0.f, 0.f, 0.f, 1.f
    };
}

auto Matrix4x4::scale(Vector3D<float> vec) -> Matrix4x4
{
	 return
    {   
        vec.x, 0.f, 0.f, 0.f,
        0.f, vec.y, 0.f, 0.f,
        0.f, 0.f, vec.z, 0.f,
        0.f, 0.f, 0.f, 1.f 
    };
}

auto Matrix4x4::rotateX(float angle) -> Matrix4x4
{
    return
    {
        1.f, 0.f, 0.f, 0.f,
        0.f, std::cos(angle), -std::sin(angle), 0.f,
        0.f, std::sin(angle), std::cos(angle), 0.f,
        0.f, 0.f, 0.f, 1.f
    };
}

auto Matrix4x4::rotateY(float angle) -> Matrix4x4
{
    return
    {
        std::cos(angle), 0.f, std::sin(angle), 0.f,
        0.f, 1.f, 0.f, 0.f,
        -std::sin(angle), 0.f, std::cos(angle), 0.f,
        0.f, 0.f, 0.f, 1.f
    };
}

auto Matrix4x4::rotateZ(float angle) -> Matrix4x4
{
    return 
    {
        std::cos(angle), -std::sin(angle), 0.f, 0.f,
        std::sin(angle), std::cos(angle), 0.f, 0.f,
        0.f, 0.f, 1.f, 0.f,
        0.f, 0.f, 0.f, 1.f
    };
}

auto Matrix4x4::rotate(Vector3D<float> vec) -> Matrix4x4
{
	Matrix4x4 result = Matrix4x4::identity;
	result *= rotateY(vec.y);
	result *= rotateX(vec.x);
	result *= rotateZ(vec.z);
	
	return result;
}

auto Matrix4x4::inverse() -> Matrix4x4
{
    Matrix4x4 res = *this;

    for (int i = 3; i < 12; i += 4)
        res.val[i] *= -1;

    std::swap(res.val[1], res.val[4]);
    std::swap(res.val[2], res.val[8]);
    std::swap(res.val[6], res.val[9]);

    return res;
}

auto Matrix4x4::operator * (Matrix4x4 const& mat) const -> Matrix4x4
{
    Matrix4x4 res =
    {
        0.f, 0.f, 0.f, 0.f,
        0.f, 0.f, 0.f, 0.f,
        0.f, 0.f, 0.f, 0.f,
        0.f, 0.f, 0.f, 0.f
    };

    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            for(int k = 0; k < 4; ++k)
                res.val[(4*i) + j] += this->val[(4*i) + k] * mat.val[(4*k) + j];

    return res;
}

auto Matrix4x4::operator *= (Matrix4x4 const& mat) -> Matrix4x4
{
    *this = *this * mat;
    return *this;
}

auto Matrix4x4::getPosition() const -> Vector3D<float>
{
    float position[3];
    position[0] = val[3];
    position[1] = val[7];
    position[2] = val[11];
    return Vector3D<float>(position);
}

auto Matrix4x4::setPosition(Vector3D<float> vector) -> void
{
	val[3] = vector.x;
	val[7] = vector.y;
	val[11] = vector.z;
}

auto Matrix4x4::setPosition(float x, float y, float z) -> void
{
	val[3] = x;
	val[7] = y;
	val[11] =z;
}

auto Matrix4x4::showMatrix() -> void
{

    std::cout<< " <----------------------------------->"<<std::endl;
    std::cout<< "    | " << val[0] << ".f,  " << val[1] << ".f,  " << val[2] << ".f,  " << val[3] << ".f, |" << std::endl;
    std::cout<< "    | " << val[4] << ".f,  " << val[5] << ".f,  " << val[6] << ".f,  " << val[7] << ".f, |" << std::endl;
    std::cout<< "    | " << val[8] << ".f,  " << val[9] << ".f,  " << val[10] << ".f,  " << val[11] << ".f, |" << std::endl;
    std::cout<< "    | " << val[12] << ".f,  " << val[13] << ".f,  " << val[14] << ".f,  " << val[15] << ".f, |" <<std::endl;
    std::cout<< " <----------------------------------->"<<std::endl;
}

auto Matrix4x4::data() -> float*
{
    return val.data();
}
