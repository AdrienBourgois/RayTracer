#ifndef __VECTOR_DECLARATION__
#define __VECTOR_DECLARATION__

#include <iostream>

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
        Vector3D    operator *(float  a);
        bool        operator ==(Vector3D const& a); 

    private:

        //static_cast<float>(i)

            //if(std::is_same<T, float>::value)

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
