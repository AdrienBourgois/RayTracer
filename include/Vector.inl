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
Vector2D<T>& Vector2D<T>::operator +(Vector2D const& a)
{
	this->x = this->x + a.x;
	this->y = this->y + a.y;

	return *this;
}

template <typename T>
Vector2D<T>& Vector2D<T>::operator -(Vector2D const& a)
{
	this->x = this->x - a.x;
	this->y = this->y - a.y;
	
	return *this;
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
Vector3D<T>& Vector3D<T>::operator +(Vector3D const& a)
{
    this->x = this->x + a.x;
    this->y = this->y + a.y;
	this->z = this->z + a.z;

    return *this;
}

template <typename T>
Vector3D<T>& Vector3D<T>::operator -(Vector3D const& a)
{
    this->x = this->x - a.x;
    this->y = this->y - a.y;
	this->z = this->z - a.z;    

    return *this;
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
bool Vector3D<T>::operator ==(Vector3D const& a)
{
    if(this->x == a.x && this->y == a.y && this->z == a.z)
        return true;
    else
        return false;
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
Vector4D<T>& Vector4D<T>::operator +(Vector4D const& a)
{
    this->x = this->x + a.x;
    this->y = this->y + a.y;
    this->z = this->z + a.z;
	this->w = this->w + a.w;

    return *this;
}

template <typename T>
Vector4D<T>& Vector4D<T>::operator -(Vector4D const& a)
{
    this->x = this->x - a.x;
    this->y = this->y - a.y;
    this->z = this->z - a.z;
	this->w = this->w - a.w;

    return *this;
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
