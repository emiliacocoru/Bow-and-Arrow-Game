#include "Tema1.h"
#include "Classes.h"
//#include "Utilities.h"
#include <vector>
#include <iostream>
#include <string>
#include <math.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include <Core/Engine.h>
#include "CreateTransform2D.h"
#include "CreateObject2D.h"

using namespace std;

Tema1::Tema1() {}

Tema1::~Tema1() {}

void Tema1::Init() {
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);
	glm::vec3 corner = glm::vec3(0, 0, 0);


	// inițializare
	initBalloons(thisBalloons);
 	initClouds(thisClouds);
	initStars(thisStars);
	initShuriken(thisShurikens);

	bowY = resolution.y / 2;
	bowX = 80;
	barY = bowY - bowSize;
	arrowX = 60;
	arrowY = resolution.y / 2;

	// ARROW
	AddMeshToList(CreateObject2D::CreateTriangle("triangleArrow", corner, arrowSize, glm::vec3(0, 0, 0)));
	AddMeshToList(CreateObject2D::CreateArrowRectangle("rectangleArrow", corner, arrowSize, glm::vec3(0, 0, 0)));

	// SHURIKEN
	AddMeshToList(CreateObject2D::CreateShuriken(shurikenID, corner, shurikenSize, glm::vec3(0, 0, 0)));

	// BAR
	AddMeshToList(CreateObject2D::CreateRectangle("bar", corner, squareSide, glm::vec3(1, 0, 0), true));
	AddMeshToList(CreateObject2D::CreateRectangle("frame", corner, squareSide + 14, glm::vec3(0, 0, 0), true));


	// BALLOONS
	// Red
	AddMeshToList(CreateObject2D::CreateBalloon("balloonRed", corner, 50, glm::vec3(1, 0, 0)));
	AddMeshToList(CreateObject2D::CreateLine("lineRed", corner, 20, glm::vec3(1,0,0)));
	AddMeshToList(CreateObject2D::CreateTriangle("triangleRed", corner, arrowSize, glm::vec3(1, 0, 0)));

	// Yellow
	AddMeshToList(CreateObject2D::CreateBalloon("balloonYellow", corner, 50, glm::vec3(1, 1, 0)));
	AddMeshToList(CreateObject2D::CreateLine("lineYellow", corner, 20, glm::vec3(1, 1, 0)));
	AddMeshToList(CreateObject2D::CreateTriangle("triangleYellow", corner, arrowSize, glm::vec3(1, 1, 0)));


	// CLOUD
	AddMeshToList(CreateObject2D::CreateBalloon("cloud", corner, 100, glm::vec3(1, 1, 1)));

	// HEART
	AddMeshToList(CreateObject2D::CreateBalloon("heart", corner, 100, glm::vec3(0.9, 0, 0)));

	// STAR
	AddMeshToList(CreateObject2D::CreateStar("star", corner, 50, glm::vec3(0.9, 1, 0.4)));
	// BOW
	AddMeshToList(CreateObject2D::CreateBow("bow", corner, bowSize, glm::vec3(0, 0, 0)));

}

void Tema1::FrameStart() {}

void Tema1::Update(float deltaTimeSeconds) {

	glm::ivec2 resolution = window->GetResolution();

	// choose the background color after two seconds
	timeBackground += 2 * deltaTimeSeconds;
	if (timeBackground > 20) {
		if (day == true) {
			day = false;
		} else {
			day = true;
		}
		timeBackground = 0;
		balloonSpeed += 20;
		shurikenSpeed += 50;

	}

	// set the background color
	if (day == true) {
		glClearColor(0.8, 0.9, 1, 1);
	} else {
		glClearColor(0, 0.1, 0.3, 1);
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, resolution.x, resolution.y);


	// draw arrow
	createArrowMatrix(modelMatrix, arrowX, arrowY, arrowAngle);
	RenderMesh2D(meshes["triangleArrow"], shaders["VertexColor"], modelMatrix);
	RenderMesh2D(meshes["rectangleArrow"], shaders["VertexColor"], modelMatrix);

	// draw bow
	createBowMatrix(modelMatrix, bowX, bowY, bowAngle);
	RenderMesh2D(meshes["bow"], shaders["VertexColor"], modelMatrix);

	// draw bar
	createBarMatrix(modelMatrix, bowX, barY, barScale);
	RenderMesh2D(meshes["bar"], shaders["VertexColor"], modelMatrix);

	//draw frame bar
	createFrameMatrix(modelMatrix, bowX, barY);
	RenderMesh2D(meshes["frame"], shaders["VertexColor"], modelMatrix);

	// arrow-shuriken collision
	collisionArrowShurikens(thisShurikens, numberOfShuriken, arrowX,
															arrowY, arrowAngle,shurikenSize, score);

	// bow-shuriken collision
	collisionBowShuriken(thisShurikens, numberOfShuriken, numberOfLives, bowX,
													bowY, shurikenSize, bowSize);

	// draw shuriken
	for (int i = 1; i <= numberOfShuriken; i++) {
		createShurikenMatrix(thisShurikens, modelMatrix, i, deltaTimeSeconds, shurikenAngle);
		RenderMesh2D(meshes[shurikenID], shaders["VertexColor"], modelMatrix);
	}

	shurikenAngle += 15 * deltaTimeSeconds;

	// balloons collision
	collisionArrowBalloons(thisBalloons, numberOfBalloon, arrowX, arrowY, arrowAngle,
														arrowSize, balloonSize, resolution.x, resolution.y, score);

	// draw ballons
	for (int i = 1; i <= numberOfBalloon; i++) {
		createBalloonMatrix(thisBalloons, modelMatrix, i, deltaTimeSeconds, balloonAngle);
		modelLine = modelMatrix;
		RenderMesh2D(meshes[balloonID + thisBalloons[i].getColor()], shaders["VertexColor"], modelMatrix);
		createTriangleBalloonMatrix(modelMatrix, balloonSize);
		RenderMesh2D(meshes[triangleID + thisBalloons[i].getColor()], shaders["VertexColor"], modelMatrix);
		createLineBalloonMatrix(modelLine, balloonSize);
		RenderMesh2D(meshes[lineID + thisBalloons[i].getColor()], shaders["VertexColor"], modelLine);
	}

	balloonAngle += 20 * deltaTimeSeconds;


	// create new elements
	coolDown += deltaTimeSeconds;
	timeNewElement += deltaTimeSeconds;

	if (timeNewElement >= 20) {
		if (newShurikens < 5) {
			newShurikens++;
		}
		if (newBalloons < 5) {
			newBalloons++;
		}
		timeNewElement = 0;
	}

	if (coolDown >= 2) {
			createNewElements(thisShurikens, thisBalloons, coolDown, numberOfBalloon,
													numberOfShuriken, resolution.x, resolution.y,
													shurikenSpeed, balloonSpeed, newShurikens, newBalloons);
	}

	// arrow speed
	if (mouse == true && arrowFlies == false) {
		// change the firing power as long as the mouse is held down
		// and the arrow is not in the air
		if (power < 4000 * deltaTimeSeconds) {
			power += 150 * deltaTimeSeconds;
			barScale += 0.03;
		}
	} else {
		arrowFlies = true;
		if (arrowX < resolution.x) {
			// changes the arrow coordinates according to the firing power
			arrowX += power * cos(arrowAngle);
			arrowY += power * sin(arrowAngle);
		} else {
			// the arrow returns to the initial position
			power = 0;
			barScale = 0.01;
			arrowX = 60;
			arrowY = bowY;
			arrowFlies = false;
		}
	}
	// the arrow returns to the initial position
	if (arrowY > resolution.y || arrowY < 0) {
		arrowX = 60;
		arrowY = bowY;
		power = 0;
		barScale = 0.01;
		arrowFlies = false;
	}

	// when the arrow is in the initial position
	// its angle changes with that of the bow
	if (arrowX == 60) {
		arrowAngle = bowAngle - 1.57;
		arrowY = bowY;
		arrowFlies = false;
	}

	// the game ends when all lives are lost
	if (numberOfLives == 0) {
		std::cout << "Game Over!" << endl;
		std::cout << "Your final score is " << score << "." << endl;
		exit(1);
	}

	// if the score is negative
	// a life is lost and the score is reset to an initial value
	if (score < 0) {
		numberOfLives--;
		cout << "Your score was negative. You lost a life." << endl;
		score = 25;
	}

	// shows the score every 5 seconds
	timeShowScore += deltaTimeSeconds;
	if (timeShowScore > 5) {
		std::cout << "Your score is " << score << "." << endl;
		timeShowScore = 0;
	}


	// bonus heart
	// appears and disappears every two seconds
	timeBonusHeart += deltaTimeSeconds;
	if (timeBonusHeart > 2) {
		if (bonusHeartInGame) {
			bonusHeartInGame = false;
		} else {
			bonusHeartInGame = true;
			bonusHeartX = rand() % resolution.x + 300;
			bonusHeartY = rand() % resolution.y;
			collisionBonusHeart = false;
		}
		timeBonusHeart = 0;
	}

	// if a collision occurs
	// lives will increase
	// the player can have a maximum of four lives
	if (bonusHeartInGame && collisionBonusHeart == false) {
		collisionArrowBonusHeart(bonusHeartX, bonusHeartY, arrowX, arrowY, numberOfLives, collisionBonusHeart);
	}

	if (bonusHeartInGame && collisionBonusHeart == false) {
		createRightPartBonusHeart(modelMatrix, bonusHeartX, bonusHeartY);
		RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);
		createLeftPartBonusHeart(modelMatrix, bonusHeartX, bonusHeartY);
		RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);
	}

	// draw hearts
	for (int i = 1; i <= numberOfLives; i++) {
		createLeftPartHeartMatrix(modelMatrix, distanceHeart, bowY, bowSize, squareSide, i);
		RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);
		createRightPartHeartMatrix(modelMatrix, distanceHeart, bowY, bowSize, squareSide, i);
		RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);
	}


	if (day) {
		// draw clouds
		for (int i = 0 ; i < 3; i++) {
			createInitialCloudMatrix(modelMatrix, thisClouds, i);
			RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);
			modelMatrix *= CreateTransform2D::Translate(-70,-50);
			RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);
			modelMatrix *= CreateTransform2D::Translate(20, -70);
			RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);
			modelMatrix *= CreateTransform2D::Translate(70, -10);
			RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);
		}
	} else {
		// draw starts
		for (int i = 0; i < thisStars.size(); i++) {
			modelMatrix = glm::mat3(1);
			modelMatrix *= CreateTransform2D::Translate(thisStars[i].getX(), thisStars[i].getY());
			modelMatrix *= CreateTransform2D::Scale(thisStars[i].getScaleX(), thisStars[i].getScaleY());
			RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);
		}
	}
}

void Tema1::FrameEnd() {}

void Tema1::OnInputUpdate(float deltaTime, int mods) {

	glm::ivec2 resolution = window->GetResolution();

	if (window->KeyHold(GLFW_KEY_W)) {
		if (bowY + bowSize + 250 * deltaTime < resolution.y) {
			bowY += 250 * deltaTime;
			barY += 250 * deltaTime;
		}
	}
	if (window->KeyHold(GLFW_KEY_S)) {
		if (barY - (squareSide + 10) - 250 * deltaTime  > 0) {
			bowY -= 250 * deltaTime;
			barY -= 250 * deltaTime;
		}
	}
	if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
		mouse = true;
	} else {
		mouse = false;
	}

}

void Tema1::OnKeyPress(int key, int mods) {}

void Tema1::OnKeyRelease(int key, int mods) {}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {

	glm::ivec2 resolution = window->GetResolution();
	float x = mouseX - (bowSize / 2 + bowX);
	float y = mouseY - (resolution.y - bowY);
	bowAngle = atan2(x, y);

}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {}

void Tema1::OnWindowResize(int width, int height) {}
