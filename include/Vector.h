#ifndef __VECTOR_DECLARATION__
#define __VECTOR_DECLARATION__

#include <iostream>
#include <cmath>
#include <vector>

typedef unsigned char uint8;

template <typename T>
class Vector2D
{
    public:
        T x, y;

        Vector2D();
        Vector2D(T a[2]);
        Vector2D(T a, T b);
        Vector2D(Vector2D const&) = default;
        ~Vector2D() = default;

        Vector2D& 	operator =(Vector2D const& a) = default;
        Vector2D   	operator +(Vector2D const& a);
        Vector2D 	operator -(Vector2D const& a);
        Vector2D& 	operator +=(Vector2D const& a);
        Vector2D& 	operator -=(Vector2D const& a);
        bool 		operator ==(Vector2D const& a);

    private:

};

template <typename T>
std::ostream&   operator <<(std::ostream& os, Vector2D<T> const& a);


template <typename T>
class Vector3D
{
    public:
        T x, y, z;

        Vector3D();
        Vector3D(T a[3]);
        Vector3D(T a, T b, T c); 
        Vector3D(Vector3D const&) = default;
        ~Vector3D() = default;

        Vector3D&   operator =(Vector3D const& a);
        Vector3D    operator +(Vector3D const& a); 
        Vector3D    operator -(Vector3D const& a); 
        Vector3D&   operator +=(Vector3D const& a); 
        Vector3D&   operator -=(Vector3D const& a);
        Vector3D    operator *(Vector3D const& a);
        Vector3D    operator *(T a);

        bool        operator ==(Vector3D const& a); 

        auto		convert() -> Vector3D;
	auto		direction(Vector3D origin, Vector3D destination) -> Vector3D;
	auto 		normalize() -> Vector3D;
	auto 		pow(T exp) -> Vector3D;
	auto		dot(Vector3D const& b) -> T;
	static auto	normalOnSphere(Vector3D intersect_point, Vector3D origin) -> Vector3D;
	static auto	normalOnTriangle(Vector3D a, Vector3D b, Vector3D c) -> Vector3D;
	static auto	normalOnModel(std::vector<float> verti_list, Vector3D<float> node_posi) -> Vector3D<float>;

	template <typename U>
	auto		cast(Vector3D<U> vec) -> Vector3D<T>;

    private:

};

template <typename T>
std::ostream&   operator <<(std::ostream& os, Vector3D<T> const& a);


template <typename T>
class Vector4D
{
    public:
        T x, y, z, w;

        Vector4D();
        Vector4D(T a[4]);
        Vector4D(T a, T b, T c, T d);
        Vector4D(Vector4D const&) = default;
        ~Vector4D() = default;

        Vector4D&   operator =(Vector4D const& a) = default;
        Vector4D    operator +(Vector4D const& a); 
        Vector4D    operator -(Vector4D const& a); 
        Vector4D&   operator +=(Vector4D const& a); 
        Vector4D&   operator -=(Vector4D const& a); 
        bool        operator ==(Vector4D const& a); 

    private:

};

template <typename T>
std::ostream&   operator <<(std::ostream& os, Vector4D<T> const& a);

#include "Vector.inl"

#endif
