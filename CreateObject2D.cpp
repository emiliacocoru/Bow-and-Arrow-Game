#include "CreateObject2D.h"

#include <Core/Engine.h>

// line
Mesh* CreateObject2D::CreateLine(std::string name, glm::vec3 corner, float size, glm::vec3 color) {
	std::vector<VertexFormat> vertices = {
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(- size / 3, - size, 0), color),
		VertexFormat(corner + glm::vec3(+ size / 3, - size - size / 3, 0), color),
		VertexFormat(corner + glm::vec3(- size / 3, -2 * size , 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3};

	square->SetDrawMode(GL_LINE_STRIP);

	square->InitFromData(vertices, indices);
	return square;
}

// bar rectangle
Mesh* CreateObject2D::CreateRectangle(std::string name, glm::vec3 corner, float size, glm::vec3 color, bool fill) {
	std::vector<VertexFormat> vertices = {
		VertexFormat(corner + glm::vec3(0, -size / 3, 0), color),
		VertexFormat(corner + glm::vec3(size, -size / 3, 0), color),
		VertexFormat(corner + glm::vec3(size, -size / 2, 0), color),
		VertexFormat(corner + glm::vec3(0, -size / 2, 0), color),
	};

	Mesh* rectangle = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3};

	if (!fill) {
		rectangle->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		indices.push_back(0);
		indices.push_back(2);
	}

	rectangle->InitFromData(vertices, indices);
	return rectangle;
}


Mesh* CreateObject2D::CreateTriangle(std::string name, glm::vec3 middle, float size, glm::vec3 color) {
	std::vector<VertexFormat> vertices = {
		VertexFormat(middle + glm::vec3(+ 3 * size, - size / 2, 0), color),
		VertexFormat(middle + glm::vec3(+ 3 * size, + size / 2, 0), color),
		VertexFormat(middle + glm::vec3(+ 4 * size, 0, 0), color),
	};

	Mesh* triangle = new Mesh(name);
	std::vector<unsigned short> indices = {0, 2, 1};

	triangle->InitFromData(vertices, indices);
	return triangle;
}


Mesh* CreateObject2D::CreateArrowRectangle(std::string name, glm::vec3 middle, float size, glm::vec3 color) {

	std::vector<VertexFormat> vertices = {
		VertexFormat(middle + glm::vec3(0, - size / 7, 0), color),
		VertexFormat(middle + glm::vec3(+ 3 * size,  - size / 7, 0), color),
		VertexFormat(middle + glm::vec3(+ 3 * size, size / 7, 0), color),
		VertexFormat(middle + glm::vec3(0, +size / 7, 0), color),

	};

	Mesh* triangle = new Mesh(name);
	std::vector<unsigned short> indicesRectangle = { 0, 1, 2,
																										0, 2, 3};
	triangle->InitFromData(vertices, indicesRectangle);
	return triangle;
}

Mesh* CreateObject2D::CreateBow(std::string name, glm::vec3 middle, float size, glm::vec3 color) {
	float angle = 9.78;
	int a = 0;
	int b = 0;
	std::vector<VertexFormat> verticesBow = {};

	for(int i = 0; i < 1000; i++) {
		verticesBow.push_back(VertexFormat(middle + glm::vec3(a,b, 0), color));
		angle += 0.2;
		a = size * cos(angle);
		b = size * sin(angle);
	}

	Mesh* bow = new Mesh(name);
	std::vector<unsigned short> indicesBow = {};

	for (int i = 6; i <= 22; i++) {
		indicesBow.push_back(i);
	}

	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable (GL_BLEND);

	glEnable (GL_LINE_SMOOTH);
	glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);

	glLineWidth(7.f);
	bow->SetDrawMode(GL_LINE_LOOP);

	bow->InitFromData(verticesBow, indicesBow);
	return bow;

}

Mesh* CreateObject2D::CreateShuriken(std::string name, glm::vec3 middle, float minisize, glm::vec3 color) {

	std::vector<VertexFormat> verticesShuriken = {
		// left-bottom triangle
		VertexFormat(middle + glm::vec3(+ minisize / 9, 0, 0), color),
		VertexFormat(middle + glm::vec3(- minisize, - minisize, 0), color),
		VertexFormat(middle + glm::vec3(- minisize, 0, 0), color),

		// left-top triangle
		VertexFormat(middle + glm::vec3(0, -minisize / 9, 0), color),
		VertexFormat(middle + glm::vec3(0, minisize, 0), color),
		VertexFormat(middle + glm::vec3(-minisize, + minisize, 0), color),

		// rigth-bottom triangle
		VertexFormat(middle + glm::vec3(- minisize / 9, 0, 0), color),
		VertexFormat(middle + glm::vec3(minisize, 0, 0), color),
		VertexFormat(middle + glm::vec3(+ minisize, + minisize, 0), color),

		// right-top triangle
		VertexFormat(middle + glm::vec3(0, + minisize / 9, 0), color),
		VertexFormat(middle + glm::vec3(0, - minisize , 0), color),
		VertexFormat(middle + glm::vec3(+minisize, -minisize, 0), color),

	};

	Mesh* shuriken = new Mesh(name);
	std::vector<unsigned short> indicesLBTriangle = { 0, 2, 1 };
	std::vector<unsigned short> indicesLTTriangle = { 3, 4, 5 };
	std::vector<unsigned short> indicesRTTriangle = { 6, 7, 8 };
	std::vector<unsigned short> indicesRBTriangle = { 9, 10, 11 };

	std::vector<unsigned short> indicesShuriken = {};

	indicesShuriken.insert(indicesShuriken.end(), indicesLBTriangle.begin(), indicesLBTriangle.end());
	indicesShuriken.insert(indicesShuriken.end(), indicesLTTriangle.begin(), indicesLTTriangle.end());
	indicesShuriken.insert(indicesShuriken.end(), indicesRTTriangle.begin(), indicesRTTriangle.end());
	indicesShuriken.insert(indicesShuriken.end(), indicesRBTriangle.begin(), indicesRBTriangle.end());

	shuriken->InitFromData(verticesShuriken, indicesShuriken);
	return shuriken;
}

Mesh* CreateObject2D::CreateBalloon(std::string name, glm::vec3 middle, float size, glm::vec3 color){
	float angle = 0;
	float a = 0;
	float b = size;
	int balloon = size;
	std::vector<VertexFormat> verticesBalloon = {};

	for(int i = 0; i < 100; i++) {
		verticesBalloon.push_back(VertexFormat(middle + glm::vec3(a,b, 0), color));

		angle += 0.2;
		a = size / 1.3 * cos(angle);
		b = size * sin(angle);
	}

	Mesh* bow = new Mesh(name);
	std::vector<unsigned short> indicesBalloon = {};

	for (int i = 0; i <= 99; i++) {
		indicesBalloon.push_back(0);
		indicesBalloon.push_back(i);
		indicesBalloon.push_back(i + 1);
	}

	bow->InitFromData(verticesBalloon, indicesBalloon);
	return bow;
}

Mesh* CreateObject2D::CreateStar(std::string name, glm::vec3 middle, float size, glm::vec3 color){
	std::vector<VertexFormat> verticesStar = {
		// first triangle
		VertexFormat(middle, color),
		VertexFormat(middle + glm::vec3(+ size, 0 , 0), color),
		VertexFormat(middle + glm::vec3(+ size / 2, - size, 0), color),
		// second triangle
		VertexFormat(middle + glm::vec3(+ size / 2, + size / 3, 0), color),
		VertexFormat(middle + glm::vec3(0, - 2 * size / 3, 0), color),
		VertexFormat(middle + glm::vec3(+ size , - 2 * size / 3, 0), color),
	};

	std::vector<unsigned short> indicesStar = {0, 1, 2, 3, 4, 5};

	Mesh* star = new Mesh(name);
	star->InitFromData(verticesStar, indicesStar);
	return star;

}
