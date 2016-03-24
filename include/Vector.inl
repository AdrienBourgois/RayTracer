#include "MathCalc.h"

template <typename T>
Vector2D<T>::Vector2D()
{
	this->x = this->y = 0;
}

template <typename T>
Vector2D<T>::Vector2D(T a[2])
{
	this->x = a[0];
	this->y = a[1];
}

template <typename T>
Vector2D<T>::Vector2D(T a, T b)
{
	this->x = a;
	this->y = b;
}

template <typename T>
Vector2D<T> Vector2D<T>::operator +(Vector2D const& a)
{
    Vector2D<T> res;

	res.x = this->x + a.x;
	res.y = this->y + a.y;

	return res;
}

template <typename T>
Vector2D<T> Vector2D<T>::operator -(Vector2D const& a)
{
    Vector2D<T> res;

	res.x = this->x - a.x;
	res.y = this->y - a.y;
	
	return res;
}

template <typename T>
Vector2D<T>& Vector2D<T>::operator +=(Vector2D const& a)
{
	this->x = this->x + a.x;
	this->y = this->y + a.y;

	return *this;
}

template <typename T>
Vector2D<T>& Vector2D<T>::operator -=(Vector2D const& a)
{
	this->x = this->x - a.x;
	this->y = this->y - a.y;

	return *this;
}

template <typename T>
bool Vector2D<T>::operator ==(Vector2D const& a)
{
	if(this->x == a.x && this->y == a.y)
		return true;
	else
		return false;
}

template <typename T>
std::ostream& operator <<(std::ostream& os, Vector2D<T> const& a)
{
    os<<"( "<<a.x<<" ; "<<a.y<<" )";
    return os;
}




template <typename T>
Vector3D<T>::Vector3D()
{
    this->x = this->y = this->z = 0;
}

template <typename T>
Vector3D<T>::Vector3D(T a[3])
{
    this->x = a[0];
    this->y = a[1];
	this->z = a[2];
}

template <typename T>
Vector3D<T>::Vector3D(T a, T b, T c)
{
    this->x = a;
    this->y = b;
	this->z = c;
}

template <typename T>
Vector3D<T>& Vector3D<T>::operator =(Vector3D const& a)
{
    this->x = a.x;
    this->y = a.y;
    this->z = a.z;
    return *this;
}

template <typename T>
Vector3D<T> Vector3D<T>::operator +(Vector3D const& a)
{
    Vector3D<T> res;

    res.x = this->x + a.x;
    res.y = this->y + a.y;
	res.z = this->z + a.z;

    return res;
}

template <typename T>
Vector3D<T> Vector3D<T>::operator -(Vector3D const& a)
{
    Vector3D<T> res;
    res.x = this->x - a.x;
    res.y = this->y - a.y;
	res.z = this->z - a.z;    

    return res;
}

template <typename T>
Vector3D<T>& Vector3D<T>::operator +=(Vector3D const& a)
{
    this->x = this->x + a.x;
    this->y = this->y + a.y;
	this->z = this->z + a.z;

    return *this;
}

template <typename T>
Vector3D<T>& Vector3D<T>::operator -=(Vector3D const& a)
{
    this->x = this->x - a.x;
    this->y = this->y - a.y;
	this->z = this->z - a.z;
 
	return *this;
}

template <typename T>
Vector3D<T> Vector3D<T>::operator *(Vector3D const& a)
{
    Vector3D<T> res;

    res.x = (this->y * a.z) - (this->z * a.y);
    res.y = (this->z * a.x) - (this->x * a.z);
    res.z = (this->x * a.y) - (this->y * a.x);

    return res;
}

template <typename T>
Vector3D<T> Vector3D<T>::operator /(T a)
{
    Vector3D<T> res;

    res.x = this->x / a;
    res.y = this->y / a;
    res.z = this->z / a;

    return res;
}    

template <typename T>
Vector3D<T> Vector3D<T>::operator *(T a)
{
    Vector3D<T> res;

    res.x = this->x * a;
    res.y = this->y * a;
    res.z = this->z * a;

    return res;
}

template <typename T>
bool Vector3D<T>::operator ==(Vector3D const& a)
{
    if(this->x == a.x && this->y == a.y && this->z == a.z)
        return true;
    else
        return false;
}

template <typename T>
std::ostream& operator <<(std::ostream& os, Vector3D<T> const& a)
{
    os<<"( "<<a.x<<" ; "<<a.y<<" ; "<<a.z<<" )";
    return os;
}

template <typename T>
auto Vector3D<T>::direction(Vector3D origin, Vector3D destination) -> Vector3D<T>
{
	Vector3D<T> vector;
	
	return vector = destination - origin;
}

template <typename T>
auto Vector3D<T>::normalize() -> Vector3D<T>
{
	float length = (float)sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	Vector3D<T> vector;
	vector.x = this->x / length;
	vector.y = this->y / length;
	vector.z = this->z / length;

	return vector;
}

template <typename T>
auto Vector3D<T>::pow(T exp) -> Vector3D<T>
{
	Vector3D<T> vector;

	vector.x = std::pow(this->x, exp);
	vector.y = std::pow(this->y, exp);
	vector.z = std::pow(this->z, exp);

	return vector;	
}

template <typename T>
auto Vector3D<T>::dot(Vector3D const& b) -> T
{
	T res = 0;
	
	return res = this->x * b.x + this->y * b.y + this->z * b.z;
}

template <typename T>
auto normalOnSphere(Vector3D<T> intersect_point, Vector3D<T> sphere_origin) -> Vector3D<T>
{
	return (intersect_point - sphere_origin).normalize();
}

template <typename T>
auto normalOnTriangle(Vector3D<T> a, Vector3D<T> b, Vector3D<T> c) -> Vector3D<T>
{
	Vector3D<T> U = b - a;
	Vector3D<T> V = c - a;

	Vector3D<T> normal = U * V;
	return normal;
}

template <typename T, typename U>
auto normalOnModel(std::vector<T> verti_list, Vector3D<T> node_posi, U triangle_posi) -> Vector3D<T>
{
        Vector3D<T> normal;

	Vector3D<T> a = Vector3D<T>(verti_list[triangle_posi], verti_list[triangle_posi+1], verti_list[triangle_posi+2]) + node_posi;
        Vector3D<T> b = Vector3D<T>(verti_list[triangle_posi+3], verti_list[triangle_posi+4], verti_list[triangle_posi+5]) + node_posi;
        Vector3D<T> c = Vector3D<T>(verti_list[triangle_posi+6], verti_list[triangle_posi+7], verti_list[triangle_posi+8]) + node_posi;
	
	normal = normalOnTriangle(a, b, c);

        return normal.normalize();
}

template <typename T> template <typename U>
auto Vector3D<T>::cast(Vector3D<U> vec) -> Vector3D<T>
{
	Vector3D<T> vector;
	
	vector.x = static_cast<T> (vec.x);
	vector.y = static_cast<T> (vec.y);
	vector.z = static_cast<T> (vec.z);
	
	return vector;
}

template <typename T>
Vector4D<T>::Vector4D()
{
    this->x = this->y = this->z = this->w = 0;
}

template <typename T>
Vector4D<T>::Vector4D(T a[4])
{
    this->x = a[0];
    this->y = a[1];
    this->z = a[2];
	this->w = a[3];
}

template <typename T>
Vector4D<T>::Vector4D(T a, T b, T c, T d)
{
    this->x = a;
    this->y = b;
    this->z = c;
	this->w = d;
}

template <typename T>
Vector4D<T> Vector4D<T>::operator +(Vector4D const& a)
{
    Vector4D<T> res;

    res.x = this->x + a.x;
    res.y = this->y + a.y;
    res.z = this->z + a.z;
	res.w = this->w + a.w;

    return res;
}

template <typename T>
Vector4D<T> Vector4D<T>::operator -(Vector4D const& a)
{
    Vector4D<T> res;

    res.x = this->x - a.x;
    res.y = this->y - a.y;
    res.z = this->z - a.z;
	res.w = this->w - a.w;

    return res;
}

template <typename T>
Vector4D<T>& Vector4D<T>::operator +=(Vector4D const& a)
{
    this->x = this->x + a.x;
    this->y = this->y + a.y;
    this->z = this->z + a.z;
	this->w = this->w + a.w;

    return *this;
}

template <typename T>
Vector4D<T>& Vector4D<T>::operator -=(Vector4D const& a)
{
    this->x = this->x - a.x;
    this->y = this->y - a.y;
    this->z = this->z - a.z;
	this->w = this->w - a.w;

    return *this;
}

template <typename T>
bool Vector4D<T>::operator ==(Vector4D const& a)
{
    if(this->x == a.x && this->y == a.y && this->z == a.z && this->w == a.w)
        return true;
    else
        return false;
}

template <typename T>
std::ostream& operator <<(std::ostream& os, Vector4D<T> const& a)
{
    os<<"( "<<a.x<<" ; "<<a.y<<" ; "<<a.z<<" ; "<<a.w<<" )";
    return os;
}

