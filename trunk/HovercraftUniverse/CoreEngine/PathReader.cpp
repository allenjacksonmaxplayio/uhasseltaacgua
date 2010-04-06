#include "PathReader.h"
#include <sstream>
#include <fstream>

namespace HovUni {
	std::vector<std::vector<float>> PathReader::parsePath(const std::string& filename) {
		std::ifstream ifs(filename.c_str());
		//Count nr of lines
		int size = 0;
		std::string s;
		while(getline(ifs, s)) {
			size++;
		}
		ifs.clear();
		ifs.seekg(0);

		std::vector<std::vector<float>> result;
		result.resize(size);
		for (int i = 0; i < size; ++i) {
			result[i].resize(4);
		}

		int index = 0;
		while (getline(ifs, s)) {
			std::istringstream iss(s);
			iss >> result[index][0]; //x
			iss >> result[index][1]; //y
			iss >> result[index][2]; //z
			iss >> result[index][3]; //radius
			index++;
		}

		return result;
	}
}