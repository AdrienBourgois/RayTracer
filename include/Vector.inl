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
Vector3D<T> Vector3D<T>::operator *(float a)
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

