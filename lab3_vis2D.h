#pragma once

#include "components/simple_scene.h"


namespace m1
{
    class Lab3_Vis2D : public gfxc::SimpleScene
    {
     public:
        struct ViewportSpace
        {
            ViewportSpace() : x(0), y(0), width(1), height(1) {}
            ViewportSpace(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        struct LogicSpace
        {
            LogicSpace() : x(0), y(0), width(1), height(1) {}
            LogicSpace(float x, float y, float width, float height)
                : x(x), y(y), width(width), height(height) {}
            float x;
            float y;
            float width;
            float height;
        };

     public:
        Lab3_Vis2D();
        ~Lab3_Vis2D();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void DrawFrogComponents(glm::mat3 visMatrix);
        void DrawPlayer(glm::mat3 visMatrix, int theCounter);
        void DrawBullet(glm::mat3 visMatrix);
        void DrawMap(glm::mat3 visMatrix);
        void DrawHealthBar(glm::mat3 visMatrix, int theCounter);
        void DrawMonster(glm::mat3 visMatrix);

        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;

     
        glm::mat3 VisualizationTransf2D(const LogicSpace &logicSpace, const ViewportSpace &viewSpace);
        glm::mat3 VisualizationTransf2DUnif(const LogicSpace &logicSpace, const ViewportSpace &viewSpace);

        void SetViewportArea(const ViewportSpace &viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);

     protected:
        float lungimeLatura;
        ViewportSpace viewSpace;
        LogicSpace logicSpace;
        glm::mat3 playerMatrix, visMatrix, lakeMatrix, monsterMatrix, healthMatrix;
        GLfloat playerAngle,monsterAngle, angle;
        GLfloat trIndexX;
        GLfloat trIndexY;
        GLfloat objFaceX, objFaceY;
        float xAxis, yAxis;
        bool oneTime, isShot;
        float monsterAxisX, monsterAxisY;
        float monsterSpeed;
        int okMonster, sign1,sign2, score;
        float cxmonster, cymonster ,heroAxisX, heroAxisY,cxMap, cyMap, cxBullet, cyBullet;
        int gameOver;
    };
} 
