#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace CreateObject2D {

	Mesh* CreateRectangle(std::string name, glm::vec3 corner, float length, glm::vec3 color, bool fill = false);
	Mesh* CreateTriangle(std::string name, glm::vec3 corner, float length, glm::vec3 color);
	Mesh* CreateBow(std::string name, glm::vec3 corner, float length, glm::vec3 color);
	Mesh* CreateShuriken(std::string name, glm::vec3 corner, float miniLength, glm::vec3 color);
	Mesh* CreateBalloon(std::string name, glm::vec3 corner, float length, glm::vec3 color);
	Mesh* CreateArrowRectangle(std::string name, glm::vec3 corner, float length, glm::vec3 color);
	Mesh* CreateLine(std::string name, glm::vec3 corner, float length, glm::vec3 color);
	Mesh* CreateStar(std::string name, glm::vec3 corner, float length, glm::vec3 color);
}
