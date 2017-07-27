#include "ModelLoader.h"
#include <fstream>
#include <string>
#include "FileUtils.h"
#include "System/Log.h"
#include "Math/Vector4.h"
#include <sstream>

using namespace std;
using namespace s3dge;

bool ModelUtils::ReadObjDataFromFile(cstring filepath, vector<Mesh*>& meshVector)
{
	if (!FileUtils::CheckFileExists(filepath))
	{
		LOG_ERROR("Failed to open model at \"", filepath, "\"");
		return false;
	}

	ifstream in(filepath, ios::in);

	std::vector<Vector4> vertices;
	std::vector<uint> elements;

	string line;

	while (getline(in, line))
	{
		if (line.substr(0, 2) == "v ")
		{
			istringstream s(line.substr(2));
			Vector4 v;
			s >> v.x;
			s >> v.y;
			s >> v.z;
			v.w = 1.0f;
			vertices.push_back(v);

			continue;
		}

		if (line.substr(0, 2) == "f ")
		{
			istringstream s(line.substr(2));
			uint a, b, c;
			s >> a; 
			s >> b; 
			s >> c;
			a--; 
			b--; 
			c--;
			elements.push_back(a); 
			elements.push_back(b); 
			elements.push_back(c);

			continue;
		}

	}
}
