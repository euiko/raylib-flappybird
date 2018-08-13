//
// Created by euiko on 8/13/18.
//

#include "CharacterController.h"


CharacterController::CharacterController(Character character, float graviationSpeed) {
    mCharacter = character;
    mGraviationSpeed = graviationSpeed;
}

CharacterController::~CharacterController() {}

Vector2 CharacterController::moveUp() {
    if(mCharacter.state != CHAR_STATE_UP)
        mElapsedTime = GetFrameTime();
    else
        mElapsedTime += GetFrameTime();
    mCharacter.state = CHAR_STATE_UP;
    mCharacter.speed = -(mGraviationSpeed * mElapsedTime)-5;
    mCharacter.location.y += mCharacter.speed;
    return mCharacter.location;
}

void CharacterController::rotate(float angle) {
    mCharacter.angle += angle;
}

Vector2 CharacterController::gravitationModifier() {
    if(mCharacter.state == CHAR_STATE_UP)
        mElapsedTime = GetFrameTime();
    else
        mElapsedTime += GetFrameTime();
    mCharacter.state = CHAR_STATE_DOWN;
    mCharacter.speed = mGraviationSpeed * mElapsedTime;
    mCharacter.location.y += mCharacter.speed;
    return mCharacter.location;
}

Vector2 CharacterController::drawCharacter() {
    Texture2D currentTexture;
    switch (mCharacter.state) {
        case CHAR_STATE_UP:
            currentTexture = mCharacter.textureUp;
            break;
        case CHAR_STATE_DOWN:
            currentTexture = mCharacter.textureDown;
            break;
        default:
            currentTexture = mCharacter.textureMid;
            break;
    }
    Rectangle currentRectangle = (Rectangle){mCharacter.location.x, mCharacter.location.y, mCharacter.rectangle.width, mCharacter.rectangle.height};
    DrawTexturePro(currentTexture, mCharacter.rectangle, currentRectangle, Vector2{0, 0}, 0, RAYWHITE);
}

Vector2 CharacterController::inputHandler() {
    if(IsKeyDown(KEY_SPACE)){
        moveUp();
    }else{
        if(mCharacter.state == CHAR_STATE_UP && mElapsedTime < 0.15f)
            moveUp();
        else
            gravitationModifier();
    }
//    std::cout << mCharacter.state << std::endl;
}

void CharacterController::onUpdate() {
    inputHandler();
    drawCharacter();
}
