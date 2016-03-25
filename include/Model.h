#ifndef __MODEL_DECLARATION__
#define __MODEL_DECLARATION__

#include <vector>
#include <string>
#include <fstream>

struct Model_v
{
        float x;
        float y;
        float z;
};

struct Model_vt
{
        float x;
        float y;
};

struct Model_f
{
        unsigned int v1;
        unsigned int v2;
        unsigned int v3;

        unsigned int vt1;
        unsigned int vt2;
        unsigned int vt3;
};

class Model
{
public:
	Model() = default;
	~Model() = default;

	auto loadFile(std::string const& filename) -> void;
	auto getMesh() const& -> std::vector<float> {return this->mesh;}

private:
	auto getFileLength(std::ifstream& file) const& -> std::streampos;
	auto explodeString(std::string const& str, char delimiter) -> std::vector<std::string>;

	auto getModelFromFile(std::ifstream&) -> void;
	auto getCoordinates(std::string const&) -> void;
	auto setGLPointers() -> void;

	auto getVVT(std::string const&) -> void;
	auto getF(std::string const&) -> void;
	auto addVertexCoord(Model_f const&) -> void;
	auto addPoint(Model_v const&, Model_vt const&) -> void;

	std::vector<Model_v> mv;
	std::vector<Model_vt> mvt;
	std::vector<Model_f> mf;

	std::vector<float> mesh;
};

#endif
