#include <iostream>
#include <sstream>

#include "Model.h"

auto Model::loadFile(std::string const& filename) -> void
{
	std::ifstream file;
	file.open("./assets/" + filename, std::ios::binary);

	if (!file.is_open())
	{
		std::cerr << "Cannot open model : file does not exist" << std::endl;
		return;
	}

	this->getModelFromFile(file);
	file.close();
}

auto Model::getFileLength(std::ifstream& file) const& -> std::streampos
{
	file.seekg(0, std::ios::end);
        auto file_len = file.tellg();
        file.seekg(0,std::ios::beg);

	return file_len;
}

auto Model::explodeString(std::string const& str, char delimiter) -> std::vector<std::string>
{
	std::vector<std::string> string_array;
	std::istringstream iss(str);
	std::string buffer;

	while(std::getline(iss, buffer, delimiter))
	{
		string_array.push_back(buffer);
	}

	return string_array;
}

auto Model::getModelFromFile(std::ifstream& file) -> void
{
        auto file_len = this->getFileLength(file);
        int cur_pos = 0;

        std::string line;

        while(cur_pos < file_len)
        {
                std::getline(file,line);
                this->getCoordinates(line);
                cur_pos = (int)file.tellg();
        }

	this->setGLPointers();
}

auto Model::getCoordinates(std::string const& line) -> void
{
        switch(line[0])
        {
                case 'v':
                        this->getVVT(line);
                break;

                case 'f':
                        this->getF(line);
                break;
        }
}

auto Model::setGLPointers() -> void
{
	std::vector<Model_f>::iterator first = this->mf.begin();
	std::vector<Model_f>::iterator last = this->mf.end();

	for (; first != last; ++first)
	{
		this->addVertexCoord(*first);
	}
}

auto Model::getVVT(std::string const& line) -> void
{
        std::vector<std::string> str_array = this->explodeString(line, ' ');
        std::vector<std::string>::iterator first = str_array.begin();
        std::vector<std::string>::iterator last = str_array.end();

        if (first != last)
        {
                switch(line[1])
                {
                        case ' ':
                        {
                                Model_v _mv;
				
                                _mv.x = std::stof(str_array[1]);
                                _mv.y = std::stof(str_array[2]);
                                _mv.z = std::stof(str_array[3]);
				
                                this->mv.push_back(_mv);

                        }
                        break;

                        case 't':
                        {
                                Model_vt _mvt;
                                _mvt.x = stof(str_array[1]);
                                _mvt.y = stof(str_array[2]);

                                this->mvt.push_back(_mvt);
                        }
                        break;

                        default: break;
                }
        }
}

auto Model::getF(std::string const& line) -> void
{
        if (line[1] != ' ')
                return;

        std::vector<std::string> str_array = this->explodeString(line, ' ');
        std::vector<std::string>::iterator first = str_array.begin();
        std::vector<std::string>::iterator last = str_array.end();

        if( first != last )
        {
                std::vector<std::string> f1 = this->explodeString( str_array[1], '/');
                std::vector<std::string> f2 = this->explodeString( str_array[2], '/');
                std::vector<std::string> f3 = this->explodeString( str_array[3], '/');

                Model_f _mf;
                _mf.v1 = std::stoi(f1[0]);
                _mf.v2 = std::stoi(f2[0]);
                _mf.v3 = std::stoi(f3[0]);

                _mf.vt1 = std::stoi(f1[1]);
                _mf.vt2 = std::stoi(f2[1]);
                _mf.vt3 = std::stoi(f3[1]);

                this->mf.push_back(_mf);
        }

}

auto Model::addVertexCoord(Model_f const& _mf) -> void
{
	Model_v v1 = this->mv[_mf.v1 - 1];
	Model_v v2 = this->mv[_mf.v2 - 1];
	Model_v v3 = this->mv[_mf.v3 - 1];

	Model_vt vt1 = this->mvt[_mf.vt1 - 1];
	Model_vt vt2 = this->mvt[_mf.vt2 - 1];
	Model_vt vt3 = this->mvt[_mf.vt3 - 1];

	this->addPoint(v1, vt1);
	this->addPoint(v2, vt2);
	this->addPoint(v3, vt3);
}

auto Model::addPoint(Model_v const& _mv, Model_vt const& _mvt) -> void
{
	this->mesh.push_back(_mv.x);
	this->mesh.push_back(_mv.y);
	this->mesh.push_back(_mv.z);
	(void)_mvt;
}
