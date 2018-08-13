//
// Created by euiko on 8/13/18.
//

#ifndef LEARN_01_CHARACTERCONTROLLER_H
#define LEARN_01_CHARACTERCONTROLLER_H

#include <raylib.h>
#include <iostream>

const int CHAR_STATE_UP = 1;
const int CHAR_STATE_MID = 0;
const int CHAR_STATE_DOWN = -1;

typedef struct Character {
    Vector2 location;
    float angle;
    float speed;
    Texture2D textureMid;
    Texture2D textureUp;
    Texture2D textureDown;
    Rectangle rectangle;
    int state;

} Character;

class CharacterController {
private:
    Character mCharacter;
    float mGraviationSpeed;
    float mElapsedTime;
    void rotate(float angle);
    Vector2 gravitationModifier();
public:
    CharacterController(Character character, float graviationSpeed);
    ~CharacterController();
    Vector2 moveUp();
    Vector2 drawCharacter();
    Vector2 inputHandler();
    void onUpdate();
};


#endif //LEARN_01_CHARACTERCONTROLLER_H
