//
// Created by euiko on 8/12/18.
//

#include <raylib.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

#ifndef LEARN_01_OBSTACLEMANAGER_H
#define LEARN_01_OBSTACLEMANAGER_H

typedef struct Obstacle {
    Vector2 location;
    float height;
    float width;
    Texture2D texture;
    int position;
} Obstacle;


class ObstacleManager {
private:
    Image mImage;
    Vector2 mDefaultLocation;
    float mSpeed;
    int mSpaceLength;
    std::vector< Obstacle > mObstacles;

public:
    ObstacleManager (Image image, float speed, Vector2 defaultLocation, int spaceLength = 5);
    ~ObstacleManager();
    void setDefaultLocation(Vector2 defaultLocation);
    void setImage(Image image);
    void setSpeed(float speed);
    void setSpaceLength(int spaceLength);
    float getSpeed();
    int getSpaceLength();
    std::vector< Obstacle > getObstacles();
    Obstacle createObstacle(int position, float height = -1);
    void removeFirstObstacle();
    void removeObstacleAtIndex(int index);
    void removeObstacle(Obstacle obstacle);
    void drawObstacles();
    void generateObstacle(float currentPosition);
};


#endif //LEARN_01_OBSTACLEMANAGER_H
