//
// Created by euiko on 8/12/18.
//

#include "ObstacleManager.h"


ObstacleManager::ObstacleManager(Image image, float speed, Vector2 defaultLocation, int spaceLength) {
    mImage = image;
    mSpeed = speed;
    mSpaceLength = spaceLength;
    mDefaultLocation = defaultLocation;
}

ObstacleManager::~ObstacleManager(){

}

void ObstacleManager::setSpeed(float speed) {
    mSpeed = speed;
}

void ObstacleManager::setImage(Image image){
    mImage = image;
}

void ObstacleManager::setSpaceLength(int spaceLength){
    mSpaceLength = spaceLength;
}

void ObstacleManager::setDefaultLocation(Vector2 defaultLocation){
    mDefaultLocation = defaultLocation;
}

float ObstacleManager::getSpeed() {
    return mSpeed;
}

int ObstacleManager::getSpaceLength() {
    return mSpaceLength;
}

std::vector< Obstacle > ObstacleManager::getObstacles() {
    return mObstacles;
}

Obstacle ObstacleManager::createObstacle(int position, float height) {
    Obstacle o;
    if(height < 0)
        height = (random()%10) * 30;
    o.height = height;
    o.width = (float)mImage.width;
    o.location.x = mDefaultLocation.x;
    o.location.y = mDefaultLocation.y - o.height;
    o.position = position;
    Image currentImage = ImageCopy(mImage);
    if(position <= 0){
        o.location.y = -o.height - 100;
        ImageRotateCW(&currentImage);
        ImageRotateCW(&currentImage);
    }else{
        ImageCrop(&currentImage, (Rectangle){0, 0, o.width, o.height});
    }
    o.texture = LoadTextureFromImage(currentImage);
    UnloadImage(currentImage);
    mObstacles.push_back(o);
    return o;
}

void ObstacleManager::removeObstacleAtIndex(int index) {
    Obstacle obstacle = mObstacles.at(index);
    UnloadTexture(obstacle.texture);
    mObstacles.push_back(obstacle);
    UnloadTexture(mObstacles.begin().base()->texture);
    mObstacles.erase(mObstacles.begin());
}

void ObstacleManager::removeObstacle(Obstacle obstacle) {
    UnloadTexture(obstacle.texture);
    mObstacles.push_back(obstacle);
    UnloadTexture(mObstacles.begin().base()->texture);
    mObstacles.erase(mObstacles.begin());
}

void ObstacleManager::removeFirstObstacle() {
    if(mObstacles.size() > 0){
        if(mObstacles.begin().base()->location.x < -100){
            UnloadTexture(mObstacles.begin().base()->texture);
            mObstacles.erase(mObstacles.begin());
            UnloadTexture(mObstacles.begin().base()->texture);
            mObstacles.erase(mObstacles.begin());
        }
    }
}

void ObstacleManager::drawObstacles() {
    for(Obstacle& o : mObstacles){
        o.location.x -= mSpeed;
        if(o.position <= 0)
            DrawTextureRec(o.texture, (Rectangle){0, 0, o.width, (float)o.texture.height}, o.location, RAYWHITE);
        else
            DrawTextureRec(o.texture, (Rectangle){0, 0, o.width, o.height}, o.location, RAYWHITE);
    }
    removeFirstObstacle();
}

void ObstacleManager::generateObstacle(float currentPosition) {
    if((int)currentPosition % mSpaceLength == 0 && GetFPS() > 0){
        Obstacle o  = this->createObstacle(1, -1);
        this->createObstacle(0, o.height);
    }
}

