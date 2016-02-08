#ifndef __SPHERE_DECLARATION__
#define __SPHERE_DECLARATION__

class Sphere
{
    public:
        Sphere() = default;
        ~Sphere() = default;

        Sphere(Sphere const&) = delete;
        Sphere(Sphere &&) = delete;
        auto operator=(Sphere const&) -> Sphere = delete;
        auto operator=(Sphere &&) -> Sphere = delete;

    private:
        
};

#endif //__SPHERE_DECLARATION__
