#pragma once

#include <string>
#include <stdlib.h>     /* srand, rand */
#include <vector>
#include <include/glm.h>
#include <Core/GPU/Mesh.h>
#include <math.h>



class Balloon {
	private:
		float x;
		float y;
		float scale = 1;
		bool dead = false;
		bool stillInGame = true;
		std::string color;
		int speed;


	public:
		Balloon() {}
		~Balloon() {}


		void setCoordinates(float xBalloon, float yBalloon) {
			this->x = xBalloon;
			this->y = yBalloon;
		}

		void setColor(std::string colorBalloon) {
			this->color = colorBalloon;
		}

		float getX() {
			return this->x;
		}

		int getSpeed() {
			return speed;
		}

		void setSpeed(int s) {
			this->speed = s;
		}
		float getY() {
			return this->y;
		}

		void setX(float xBalloon) {
			this->x = xBalloon;
		}

		void setY(float yBalloon) {
			this->y = yBalloon;
		}

		bool getStillInGame() {
			return this->stillInGame;
		}

		void setStillInGame(bool thisGame) {
			this->stillInGame = thisGame;
		}

		float getScale() {
			return this->scale;
		}

		void setDead(bool thisGame) {
			this->dead = thisGame;
		}

		bool getDead() {
			return this->dead;
		}

		void setScale(float scaleThisFrame) {
			this->scale = scaleThisFrame;
		}

		std::string getColor(){
			return this->color;
		}
};


class BackGround {
	private:
		float x;
		float y;
		float scaleX;
		float scaleY;
	public:
		BackGround() {}
		~BackGround() {}

		void setElements(float x, float y, float scaleX, float scaleY) {
			this->x = x;
			this->y = y;
			this->scaleX = scaleX;
			this->scaleY = scaleY;
		}

		float getX() {
			return this->x;
		}

		float getY() {
			return this->y;
		}

		float getScaleX() {
			return this->scaleX;
		}

		float getScaleY() {
			return this->scaleY;
		}

		void setX(float xCloud) {
			this->x = xCloud;
		}

		void setY(float yCloud) {
			this->y = yCloud;
		}

		void setScaleX(float scaleXCloud) {
			this->x = scaleXCloud;
		}

		void setscaleY(float scaleYCloud) {
			this->y = scaleYCloud;
		}

};


class Shuriken {
	private:
		float x;
    float y;
    float scale = 1;
    bool dead = false;
    bool stillInGame = true;
		int speed;


	public:
		Shuriken() {}
		~Shuriken() {}


		void setCoordinates(float x, float y) {
			this->x = x;
			this->y = y;
		}

		int getSpeed() {
			return speed;
		}

		void setSpeed(int s) {
			this->speed = s;
		}

		float getX() {
			return this->x;
		}

		float getY() {
			return this->y;
		}

		void setX(float x) {
			this->x = x;
		}

		void setY(float y) {
			this->y = y;
		}

		bool getStillInGame() {
			return this->stillInGame;
		}

		void setStillInGame(bool thisGame) {
			this->stillInGame = thisGame;
		}

		float getScale() {
			return this->scale;
		}

		void setDead(bool thisGame) {
			this->dead = thisGame;
		}

		bool getDead() {
			return this->dead;
		}

		void setScale(float scaleThisFrame) {
			this->scale = scaleThisFrame;
		}
};
