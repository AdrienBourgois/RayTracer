#ifndef __MATRIX_DECLARATION__
#define __MATRIX_DECLARATION__

#include <string>
#include <initializer_list>
#include <array>

#include "Vector.h"

struct Matrix4x4
{
    std::array<float, 16> val;
    
    Matrix4x4();
    Matrix4x4(std::initializer_list<float>);
    ~Matrix4x4() = default;
    
    auto operator  =(Matrix4x4 const&) -> Matrix4x4& = default;
    auto operator *(Matrix4x4 const&) const -> Matrix4x4;
    auto operator *=(Matrix4x4 const&) -> Matrix4x4;
 
    static auto translate(float,float,float) -> Matrix4x4;
    static auto translate(Vector3D<float> vec)->Matrix4x4;
    static auto scale(float,float,float) -> Matrix4x4;
    static auto scale(Vector3D<float> vec) -> Matrix4x4;
    static auto rotateX(float) -> Matrix4x4;
    static auto rotateY(float) -> Matrix4x4;
    static auto rotateZ(float) -> Matrix4x4;
    static auto rotate(Vector3D<float> vec) -> Matrix4x4;

    auto perspective(float,float,float,float) -> Matrix4x4;
    auto orthographic(float right, float left, float top, float bottom, float far, float near)->Matrix4x4;
    auto inverse() -> Matrix4x4;
    auto showMatrix() -> void;
    auto data() -> float*;

    auto getPosition() const -> Vector3D<float>;
    auto setPosition(Vector3D<float> vector) -> void;
    auto setPosition(float x, float y, float z) -> void;

    static Matrix4x4 identity;
};

#endif
