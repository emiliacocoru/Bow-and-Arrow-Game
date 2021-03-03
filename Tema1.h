#pragma once
#include "Classes.h"
#include <iostream>

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>
#include <vector>
#include <string>
#include <stdlib.h>     /* srand, rand */

#include "CreateTransform2D.h"
using namespace std;


class Tema1 : public SimpleScene
{
	public:
		Tema1();
		~Tema1();

		void Init() override;

	private:

		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

	protected:
		glm::mat3 modelMatrix, modelLine;
		float squareSide = 100;
		int numberOfLives = 3;
		float timeShowScore = 0;
		bool day = true;
		int score = 25;
		float timeBackground = 0;
		float timeNewElement = 0;

		float bonusHeartX, bonusHeartY;
		bool bonusHeartInGame = false;
		float timeBonusHeart = 0;
		bool collisionBonusHeart = false;

		std::vector<Balloon> thisBalloons;
		std::vector<Shuriken> thisShurikens;
		std::vector<BackGround> thisClouds;
		std::vector<BackGround> thisStars;
		string shurikenID = "shuriken";
		string balloonID = "balloon";
		string lineID = "line";
		string triangleID = "triangle";


		// shuriken
		int shurikenSize = 20;
		float shurikenAngle = 10;
		int numberOfShuriken = 0;
		bool arrowGo = false;
		int shurikenSpeed = 100;
		int newShurikens = 1;

		// balloons
		int balloonSize = 50;
		int numberOfBalloon = 0;
		float balloonAngle = 0;
		int balloonSpeed = 30;
		int newBalloons = 2;

		// spawn time
		float coolDown = 1.5;

		// bow
		int bowSize = 80;
		float bowX, bowY;
		float bowAngle = 0;

		// arrow
		int arrowSize = 40;
		float arrowX, arrowY;
		float arrowAngle = 0;
		bool arrowFlies = false;

		// power bar
		float barX, barY;
		float barScale = 0.01;
		int power = 0;

		bool mouse = false;
		bool colision = false;

		 // heart
		 float distanceHeart = 50;


		// functions

		// initializes the vectors
		void initStars(std::vector<BackGround> & stars) {
			BackGround newStar;
			newStar.setElements(400, 130, 0.9f, 0.9f);
			stars.push_back(newStar);
			newStar.setElements(200, 500, 0.8f, 0.8f);
			stars.push_back(newStar);
			newStar.setElements(1000, 710, 0.7f, 0.7f);
			stars.push_back(newStar);
			newStar.setElements(1200, 600, 0.9f, 0.9f);
			stars.push_back(newStar);
			newStar.setElements(1105, 350, 0.5f, 0.5f);
			stars.push_back(newStar);
			newStar.setElements(300, 600, 0.9f, 0.9f);
			stars.push_back(newStar);
			newStar.setElements(600, 780, 0.7f, 0.7f);
			stars.push_back(newStar);
			newStar.setElements(800, 450, 0.9f, 0.9f);
			stars.push_back(newStar);
			newStar.setElements(200, 389, 0.8f, 0.8f);
			stars.push_back(newStar);
			newStar.setElements(100, 30, 0.6f, 0.6f);
			stars.push_back(newStar);
			newStar.setElements(900, 100, 0.7f, 0.7f);
			stars.push_back(newStar);
			newStar.setElements(457, 370, 0.3f, 0.3f);
			stars.push_back(newStar);
			newStar.setElements(890, 555, 0.9f, 0.9f);
			stars.push_back(newStar);
			newStar.setElements(333, 444, 0.9f, 0.9f);
			stars.push_back(newStar);
			newStar.setElements(560, 120, 0.8f, 0.8f);
			stars.push_back(newStar);
			newStar.setElements(740, 240, 0.5f, 0.5f);
			stars.push_back(newStar);
			newStar.setElements(40, 730, 0.7f, 0.7f);
			stars.push_back(newStar);
			newStar.setElements(70, 640, 0.6f, 0.6f);
			stars.push_back(newStar);
			newStar.setElements(1200, 240, 0.8f, 0.8f);
			stars.push_back(newStar);
			newStar.setElements(560, 570, 0.6f, 0.6f);
			stars.push_back(newStar);
			newStar.setElements(860, 490, 0.7f, 0.7f);
			stars.push_back(newStar);
		}

		void initClouds(std::vector<BackGround>& clouds) {
			BackGround newCloud;
			newCloud.setElements(500, 600, 1.5f, 0.5f);
			clouds.push_back(newCloud);
			newCloud.setElements(1000, 300, 2.0f, 0.6f);
			clouds.push_back(newCloud);
			newCloud.setElements(100, 100, 1.5f, 0.6f);
			clouds.push_back(newCloud);
		}

		void initBalloons(std::vector<Balloon>& balloons) {
			Balloon newBalloon;
			newBalloon.setCoordinates(-100, -100);
			balloons.push_back(newBalloon);
		}

		void initShuriken(std::vector<Shuriken>& shurikens){
			Shuriken newShuriken;
			newShuriken.setCoordinates(0, 0);
			shurikens.push_back(newShuriken);
		}

		// collision
		void collisionArrowBalloons(std::vector<Balloon>& balloons,int& numberOfBalloon,
			float arrowX, float arrowY, float arrowAngle, int arrowSize, int balloonSize,
			float resolutionX, float resolutionY, int& score) {

				std::vector<int> deletePositions;

				for (int i = 1; i <= numberOfBalloon; i++) {

					// if the balloon has not yet been hit by the arrow
					if (balloons[i].getStillInGame()) {
						// the coordinates of the arrowhead are calculated
						float arrowheadX = cos(arrowAngle) / (4 * arrowSize) + arrowX;
						float arrowheadY = sin(arrowAngle) * (arrowheadX - arrowX) + arrowY;

						float xArrowBalloon = balloons[i].getX() - arrowheadX;
						float yArrowBalloon = balloons[i].getY() - arrowheadY;

						float distanceArrowBalloon = sqrt(xArrowBalloon * xArrowBalloon
															+ yArrowBalloon * yArrowBalloon);
						// and a point-circle collision occurs
						if (distanceArrowBalloon <= balloonSize + 15) {
							balloons[i].setStillInGame(false);
							// if the balloon is hit
							// it does not disappear from the frame
							if (balloons[i].getColor() == "Red") {
								score += 10;
							} else {
								score -= 15;
							}
						}
					} else {
							// the balloon is scaled and rotated until it leaves the scene
							balloons[i].setScale(balloons[i].getScale() / 1.05);
					}

					if (balloons[i].getX() > resolutionX + 500
											|| balloons[i].getY() > resolutionY + 300) {
						balloons[i].setDead(true);
					}

					if (balloons[i].getDead()){
						deletePositions.push_back(i);
						numberOfBalloon--;
					}
					for (int i = 0; i < deletePositions.size(); i++) {
						balloons.erase(balloons.begin() + (deletePositions[i]));
						numberOfBalloon--;
					}
					deletePositions.clear();
				}
			}

			void collisionArrowShurikens(std::vector<Shuriken>& shurikens, int& numberOfShuriken,
									float arrowX, float arrowY, float arrowAngle, int shurikenSize, int&score) {

				std::vector<int> deletePositions;
				// the same principle as in the arrow-balloon collision appears here
				for (int i = 1; i <= numberOfShuriken; i++) {
	 		 		float arrowheadX = cos(arrowAngle) / (4 * arrowSize) + arrowX;
	 		 		float arrowheadY = sin(arrowAngle) * (arrowheadX - arrowX) + arrowY;

	 		 		float xArrowShuriken = shurikens[i].getX() - arrowheadX;
	 		 		float yArrowShuriken = shurikens[i].getY() - arrowheadY;


	 		 		float radiusShuriken = sqrt(shurikenSize * shurikenSize +
																								shurikenSize * shurikenSize);
	 		 		float distanceArrowShuriken = sqrt(xArrowShuriken * xArrowShuriken +
																		yArrowShuriken * yArrowShuriken);

	 		 		if (distanceArrowShuriken <= radiusShuriken) {
	 		 			deletePositions.push_back(i);
						score += 15;
	 		 		}
	 		 	}

 		 	for (int i = 0; i < deletePositions.size(); i++) {
 		 		shurikens.erase(shurikens.begin() + (deletePositions[i]));
 		 		numberOfShuriken--;
 		 	}

 		 	deletePositions.clear();
		}

		void collisionBowShuriken(std::vector<Shuriken>& shurikens, int& numberOfShuriken,
											int& numberOfLives, float bowX, float bowY, int shurikenSize,
											int bowSize) {

			std::vector<int> deletePositions;

			for(int i = 1; i <= numberOfShuriken; i++) {
				// circle-circle collision
				float xBowShuriken = bowX - shurikens[i].getX();
				float yBowShuriken = bowY - shurikens[i].getY();

				float distanceBowShuriken = sqrt((xBowShuriken * xBowShuriken)
																			+ (yBowShuriken * yBowShuriken));

				if (distanceBowShuriken <= bowSize + shurikenSize) {
					deletePositions.push_back(i);
					std::cout << "You lost a life because of the shuriken!" << endl;
					numberOfLives--;
				}
			}

			for (int i = 0; i < deletePositions.size(); i++) {
				shurikens.erase(shurikens.begin() + (deletePositions[i]));
				numberOfShuriken--;
			}

			deletePositions.clear();

		}

		void collisionArrowBonusHeart(float bonusHeartX, float bonusHeartY,
															float arrowX, float arrowY, int& numberOfLives,
															bool& collisionBonusHeart) {
			// the same principle as in the arrow-balloon collision appears here
				float arrowheadX = (4 * arrowSize) / cos(arrowAngle) + arrowX;
				float arrowheadY = sin(arrowAngle) * (arrowheadX - arrowX) + arrowY;

				float xArrowBonusHeart = bonusHeartX - arrowheadX;
				float yArrowBonusHeart = bonusHeartY - arrowheadY;

				float distanceArrowBonusHeart = sqrt(xArrowBonusHeart * xArrowBonusHeart +
																	yArrowBonusHeart * yArrowBonusHeart);

				if (distanceArrowBonusHeart <= 30) {
					if (numberOfLives < 4) {
						numberOfLives++;
					}
					std::cout<<"You have gained a new life." << endl;
					collisionBonusHeart = true;
				}
			}

		// shuriken
		void createShurikenMatrix(std::vector<Shuriken>& shurikens, glm::mat3& modelMatrix,
												int position, float deltaTimeSeconds, float shurikenAngle) {
		modelMatrix = glm::mat3(1);
		shurikens[position].setX(shurikens[position].getX() - shurikens[position].getSpeed() * deltaTimeSeconds);
		modelMatrix *= CreateTransform2D::Translate(shurikens[position].getX(),
																									shurikens[position].getY());
		modelMatrix *= CreateTransform2D::Rotate(shurikenAngle);

		}

		// arrow
		void createArrowMatrix(glm::mat3& modelMatrix, float arrowX,
																						float arrowY, float arrowAngle) {
			modelMatrix = glm::mat3(1);
			modelMatrix *= CreateTransform2D::Translate(arrowX , arrowY);
		 	modelMatrix *= CreateTransform2D::Rotate(arrowAngle);
		}

		// bow
		void createBowMatrix(glm::mat3& modelMatrix, float bowX, float bowY, float bowAngle) {
			modelMatrix = glm::mat3(1);
			modelMatrix *= CreateTransform2D::Translate(bowX, bowY);
		 	modelMatrix *= CreateTransform2D::Rotate(bowAngle - 1.57); // radians(-90) = -1.57;
		}

		// bar
		// maxScale = 1.1
		// minScale = 0.01
		// 0.1 - 0.3 - 0.5 - 0.7 - 0.9 - 1.1
		void createBarMatrix(glm::mat3& modelMatrix, float bowX, float barY, float barScale) {
			modelMatrix = glm::mat3(1);
			modelMatrix *= CreateTransform2D::Translate(bowX - 40, barY);
			modelMatrix *= CreateTransform2D::Scale(barScale, 1);
		}

		void createFrameMatrix(glm::mat3& modelMatrix, float bowX, float barY) {
			modelMatrix = glm::mat3(1);
			modelMatrix *= CreateTransform2D::Translate(bowX - 42, barY + 5);
		}

		void createBalloonMatrix(std::vector<Balloon> &balloons, glm::mat3& modelMatrix,
														int position, float deltaTimeSeconds,float balloonAngle) {
			 modelMatrix = glm::mat3(1);
			 balloons[position].setY(balloons[position].getY() + balloons[position].getSpeed() * deltaTimeSeconds);

				if (balloons[position].getStillInGame() == false) {
					balloons[position].setX(balloons[position].getX() + 100 * deltaTimeSeconds);
					balloons[position].setY(balloons[position].getY() + 100 * deltaTimeSeconds);
				}
				modelMatrix *= CreateTransform2D::Translate(balloons[position].getX(),
																									balloons[position].getY());

				if (balloons[position].getStillInGame() == false) {
					modelMatrix *= CreateTransform2D::Rotate(balloonAngle);
					modelMatrix *= CreateTransform2D::Scale(balloons[position].getScale(),
																								balloons[position].getScale());
				}

		}

		void createTriangleBalloonMatrix(glm::mat3& modelMatrix, int balloonSize) {
			modelMatrix *= CreateTransform2D::Translate(0, - 3.6 * balloonSize);
			modelMatrix *= CreateTransform2D::Rotate(3.14 / 2);
		}

		void createLineBalloonMatrix(glm::mat3& modelLine, int balloonSize) {
			modelLine *= CreateTransform2D::Translate(0, - balloonSize);
		}


		void createLeftPartHeartMatrix(glm::mat3& modelMatrix, int distanceHeart,
								float bowY, float bowSize, float squareSide, int position) {
			modelMatrix = glm::mat3(1);
			modelMatrix *= CreateTransform2D::Translate(-10 + position * distanceHeart,
																				bowY - bowSize - (2.5 * squareSide) / 3);
			modelMatrix *= CreateTransform2D::Rotate(-1);
			modelMatrix *= CreateTransform2D::Scale(0.25, 0.1);
		}

		void createRightPartHeartMatrix(glm::mat3& modelMatrix, int distanceHeart,
								float bowY, float bowSize, float squareSide, int position){
			modelMatrix = glm::mat3(1);
			modelMatrix *= CreateTransform2D::Translate(4 + position * distanceHeart,
																		bowY - bowSize - (2.5 * squareSide) / 3);
			modelMatrix *= CreateTransform2D::Rotate(1);
			modelMatrix *= CreateTransform2D::Scale(0.25, 0.1);
		}

		void createRightPartBonusHeart(glm::mat3& modelMatrix, float bonusHeartX, int bonusHeartY) {
			modelMatrix = glm::mat3(1);
			modelMatrix *= CreateTransform2D::Translate(bonusHeartX, bonusHeartY);
			modelMatrix *= CreateTransform2D::Rotate(-1);
			modelMatrix *= CreateTransform2D::Scale(0.25, 0.1);
		}

		void createLeftPartBonusHeart(glm::mat3& modelMatrix, float bonusHeartX, int bonusHeartY) {
			modelMatrix = glm::mat3(1);
			modelMatrix *= CreateTransform2D::Translate(14 + bonusHeartX, bonusHeartY);
			modelMatrix *= CreateTransform2D::Rotate(1);
			modelMatrix *= CreateTransform2D::Scale(0.25, 0.1);
		}

		void createInitialCloudMatrix(glm::mat3& modelMatrix, std::vector<BackGround> clouds, int position) {
			modelMatrix = glm::mat3(1);
			modelMatrix *= CreateTransform2D::Translate(clouds[position].getX(), clouds[position].getY());
			modelMatrix *= CreateTransform2D::Scale(clouds[position].getScaleX(), clouds[position].getScaleY());
		}


		// creates new elements to appear on the scene
		void createNewElements(std::vector<Shuriken>& shurikens, std::vector<Balloon>& balloons, float& coolDown,
													int& numberOfBalloon, int& numberOfShuriken, int resolutionX, int resolutionY,
													int shurikenSpeed, int balloonSpeed, int newShurikens, int newBalloons) {

			// creates balloons
			for (int i = 0; i < newBalloons; i++) {
				int color = rand() % 2;
				float xBalloon = rand() % resolutionX + 350;
				float yBalloon = - rand() % 300;
				int speedBalloon = rand() % 50 + balloonSpeed;

				Balloon newBalloon;
				newBalloon.setCoordinates(xBalloon, yBalloon);
				newBalloon.setScale(1.f);
				newBalloon.setSpeed(speedBalloon);

				if (color == 1) {
					newBalloon.setColor("Red");

				} else {
					newBalloon.setColor("Yellow");
				}

				balloons.push_back(newBalloon);
				numberOfBalloon++;
			}

			// creates shurikens
			for (int i = 0; i < newShurikens; i++) {
				Shuriken newShuriken;
				float yShuriken = rand() % resolutionY;
				float xShuriken = rand() % 500 + resolutionX;
				int speed = rand() % 100 + shurikenSpeed;

				newShuriken.setCoordinates(xShuriken, yShuriken);
				newShuriken.setSpeed(speed);
				shurikens.push_back(newShuriken);

				numberOfShuriken++;
			}
			// new elements appear every 2 seconds
			coolDown = 0;
		}


};
