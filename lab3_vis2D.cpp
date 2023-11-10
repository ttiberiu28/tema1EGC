#include "lab_m1/lab3/lab3_vis2D.h"
#include <vector>
#include <iostream>
#include <math.h>
#include "lab_m1/lab3/transform2D.h"
#include "lab_m1/lab3/object2D.h"

using namespace std;
using namespace m1;

int theCounter = 0;

Lab3_Vis2D::Lab3_Vis2D()
{
}


Lab3_Vis2D::~Lab3_Vis2D()
{
}


void Lab3_Vis2D::Init()
{
    auto camera = GetSceneCamera();
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    oneTime = false;
    objFaceX = 0; objFaceY = 0;
    sign1 = 1;
    sign2 = 1;
    trIndexX = 0;
    trIndexY = 0;
    monsterAxisX = 0;
    monsterAxisY = 0;
    cxmonster = (float)(logicSpace.width / 2.f - 1.6 / 2.f) + 4.f;
    cymonster = (float)(logicSpace.height / 2.f - 1.6 / 2.f) - 4.f;
    heroAxisX =  (float)(logicSpace.width/2.f - 1.4f /2.f) + 0.5f;
    heroAxisY =  (float)(logicSpace.height/2.f - 1.4f /2.f);
    cxMap = (float)(logicSpace.width / 2.f - 24.f / 2.f);
    cyMap = (float)(logicSpace.height / 2.f - 24.f / 2.f);
    cxBullet = (float)(logicSpace.width / 2.f - 0.25f / 2.f);
    cyBullet = (float)(logicSpace.height / 2.f - 0.25f / 2.f);
    monsterSpeed = 3;
    okMonster = 1;
    playerAngle = 0;
    monsterAngle = 0;
    gameOver = 0;
    isShot = false;
        
    glm::ivec2 reso = window->GetResolution();
    logicSpace.x = 0, logicSpace.y = 0;
    logicSpace.width = 20.f;   // logic width
    logicSpace.height = (float((float) (reso.y * 20.f)) / reso.x);

    //dau mesh la 5 obiecte care formeaza corpul meu si le pozitionez in functie de centru
    //xAxis si yAxis ,reprezentand mijlocul viewspace-ului meu

    //(verde)
    lungimeLatura = 1.4f;
    xAxis = (logicSpace.width/2- lungimeLatura/2.f);
    yAxis = (logicSpace.height/2 - lungimeLatura/2.f);
    glm::vec3 cornerPlayer1 = glm::vec3(xAxis, yAxis, 0);
    Mesh* playerBody1 = object2D::CreateSquare("playerBody1", cornerPlayer1, lungimeLatura, glm::vec3(0.1f, 0.7f, 0.36f), true);
    AddMeshToList(playerBody1);
    
    //(rosu)
    lungimeLatura = 0.4f;
    xAxis = (logicSpace.width/2.f - lungimeLatura/2.f)  + 1.25f;
    yAxis = (logicSpace.height/2.f - lungimeLatura/2.f) + 0.3f;
    glm::vec3 cornerPlayer2 = glm::vec3(xAxis, yAxis , 0);
    Mesh* playerBody2 = object2D::CreateSquare("playerBody2", cornerPlayer2, lungimeLatura, glm::vec3(1.f, 0.2f, 0.3f), true);
    AddMeshToList(playerBody2);

    //(rosu)
    lungimeLatura = 0.4f;
    xAxis = (logicSpace.width/2.f - lungimeLatura/2.f)+ 1.25f;
    yAxis = (logicSpace.height/2.f - lungimeLatura/2.f) -0.3f;
    glm::vec3 cornerPlayer3 = glm::vec3(xAxis , yAxis , 0);
    Mesh* playerBody3 = object2D::CreateSquare("playerBody3", cornerPlayer3, lungimeLatura, glm::vec3(1.f, 0.2f, 0.3f), true);
    AddMeshToList(playerBody3);

    //glont
    lungimeLatura = 0.25f;
    xAxis = (logicSpace.width/2.f - lungimeLatura/2.f)+ 0.5f;
    yAxis = (logicSpace.height/2.f - lungimeLatura/2.f);
    glm::vec3 cornerPlayer4 = glm::vec3(xAxis , yAxis, 0);
    Mesh* playerBody4 = object2D::CreateSquare("playerBody4", cornerPlayer4, lungimeLatura, glm::vec3(1.f, 0.f, 0), true);//1.f, 0.f, 0
    AddMeshToList(playerBody4);
    
    //(verde inchis)
    lungimeLatura = 0.95f;
    xAxis = (logicSpace.width/2.f - lungimeLatura/2.f) + 0.7f;
    yAxis = (logicSpace.height/2.f - lungimeLatura/2.f);
    glm::vec3 cornerPlayer5 = glm::vec3(xAxis , yAxis, 0);
    Mesh* playerBody5 = object2D::CreateSquare("playerBody5", cornerPlayer5, lungimeLatura, glm::vec3(0.2f, 0.6f, 0.4f), true);
    AddMeshToList(playerBody5);
    
    //harta
    lungimeLatura = 24.f;
    xAxis = (logicSpace.width/2.f - lungimeLatura/2.f);
    yAxis = (logicSpace.height/2.f - lungimeLatura/2.f);
    glm::vec3 mapPosition = glm::vec3(xAxis, yAxis, 0);
    Mesh* theMap = object2D::CreateRectangle("theMap", mapPosition, lungimeLatura, glm::vec3(0.1f, 0, 0.5f), true);
    AddMeshToList(theMap);

    //monstrul
    lungimeLatura = 0.6f;
    xAxis = (logicSpace.width/2.f - lungimeLatura/2.f)+ 4.f;
    yAxis = (logicSpace.height/2.f - lungimeLatura/2.f)- 4.8f ;
    glm::vec3 cornerEn1 = glm::vec3(xAxis , yAxis  , 0);
    Mesh* en1 = object2D::CreateSquare("en1", cornerEn1, lungimeLatura, glm::vec3(1,0, 0), true);
    AddMeshToList(en1); 

    lungimeLatura = 1.6f;//baza
    xAxis = (logicSpace.width/2.f - lungimeLatura/2.f) +4.f;
    yAxis = (logicSpace.height/2.f - lungimeLatura/2.f)- 4.f;
     glm::vec3 cornerEn2 = glm::vec3(xAxis , yAxis , 0);
    Mesh* en2 = object2D::CreateSquare("en2", cornerEn2, lungimeLatura, glm::vec3(1,0, 0.8f), true);
    AddMeshToList(en2);

    lungimeLatura = 0.6f;
    xAxis = (logicSpace.width/2.f - lungimeLatura/2.f) +4.f;
    yAxis = (logicSpace.height/2.f - lungimeLatura/2.f)- 3.2f;
    glm::vec3 cornerEn3 = glm::vec3(xAxis, yAxis , 0);
    Mesh* en3 = object2D::CreateSquare("en3", cornerEn3, lungimeLatura, glm::vec3(1,0, 0), true);
    AddMeshToList(en3); 

    lungimeLatura = 0.6f;
    xAxis = (logicSpace.width/2.f - lungimeLatura/2.f)+ 3.2f;
    yAxis = (logicSpace.height/2.f - lungimeLatura/2.f)- 4.f;
    glm::vec3 cornerEn4 = glm::vec3(xAxis , yAxis , 0);
    Mesh* en4 = object2D::CreateSquare("en4", cornerEn4, lungimeLatura, glm::vec3(1,0, 0), true);
    AddMeshToList(en4);

    //healthBar
    lungimeLatura = 0.7f;
    xAxis = (logicSpace.width/2.f - lungimeLatura/2.f);
    yAxis = (logicSpace.height/2.f - lungimeLatura/2.f);
    glm::vec3 cornerHealth= glm::vec3(xAxis, yAxis, 0);
    Mesh* healthBar= object2D::CreateSquare("healthBar", cornerHealth, lungimeLatura, glm::vec3(0, 1.f, 0), true);
    AddMeshToList(healthBar);

    lungimeLatura = 0.7f;
    xAxis = (logicSpace.width/2.f - lungimeLatura/2.f);
    yAxis = (logicSpace.height/2.f - lungimeLatura/2.f);
    glm::vec3 cornerFullHealth = glm::vec3(xAxis , yAxis , 0);
    Mesh* fullHealth = object2D::CreateSquare("fullHealth", cornerFullHealth, lungimeLatura, glm::vec3(1,0, 0), false);
    AddMeshToList(fullHealth);


}


// 2D visualization matrix
glm::mat3 Lab3_Vis2D::VisualizationTransf2D(const LogicSpace & logicSpace, const ViewportSpace & viewSpace)
{
    float sx, sy, tx, ty;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    tx = viewSpace.x - sx * logicSpace.x;
    ty = viewSpace.y - sy * logicSpace.y;

    return glm::transpose(glm::mat3(
        sx, 0.0f, tx,
        0.0f, sy, ty,
        0.0f, 0.0f, 1.0f));
}


glm::mat3 Lab3_Vis2D::VisualizationTransf2DUnif(const LogicSpace & logicSpace, const ViewportSpace & viewSpace)
{
    float sx, sy, tx, ty, smin;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    if (sx < sy)
        smin = sx;
    else
        smin = sy;
    tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
    ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

    return glm::transpose(glm::mat3(
        smin, 0.0f, tx,
        0.0f, smin, ty,
        0.0f, 0.0f, 1.0f));
}


void Lab3_Vis2D::SetViewportArea(const ViewportSpace & viewSpace, glm::vec3 colorColor, bool clear)
{
    glViewport(viewSpace.x, viewSpace.y, viewSpace.width * 2, viewSpace.height * 2);

    glEnable(GL_SCISSOR_TEST);
    glScissor(viewSpace.x, viewSpace.y, viewSpace.width * 2, viewSpace.height * 2);

    glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
    GetSceneCamera()->Update();
}


void Lab3_Vis2D::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void Lab3_Vis2D::Update(float deltaTimeSeconds)
{   
    glm::ivec2 reso = window->GetResolution();
    viewSpace = ViewportSpace(0 , 0, reso.x , reso.y);
    SetViewportArea(viewSpace, glm::vec3(0), true);

    if (window->KeyHold(GLFW_KEY_W)) {
        if(35 > trIndexY ){
            logicSpace.y += deltaTimeSeconds * 3.6f;
            trIndexY += deltaTimeSeconds * 3.6f;
        }
    }

    if (window->KeyHold(GLFW_KEY_A)) {
        if(-11 < trIndexX){
            logicSpace.x -= deltaTimeSeconds * 3.6f;
            trIndexX -= deltaTimeSeconds * 3.6f;
        }
    }
    
    if (window->KeyHold(GLFW_KEY_S)) {
        if(-11 < trIndexY){
            logicSpace.y -= deltaTimeSeconds * 3.6f;
            trIndexY -= deltaTimeSeconds * 3.6f;
        }
    }
           
    if (window->KeyHold(GLFW_KEY_D)) {
        if(11 > trIndexX){
            logicSpace.x += deltaTimeSeconds *3.6f;
            trIndexX += deltaTimeSeconds * 3.6f;
        }
    }
    

    //o matrice pt health-bar
    healthMatrix = glm::mat3(1);
    healthMatrix = healthMatrix * VisualizationTransf2D(logicSpace, viewSpace);

    if (oneTime == true) {
        if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {

            oneTime = false;
            angle = playerAngle;
        }
    }

    if (okMonster) {
       if (abs(monsterAxisX + cxmonster - trIndexX - heroAxisX) < 0.5f && abs(monsterAxisY + cymonster - trIndexY - heroAxisY) < 0.5f) {
            okMonster = 0;

            for(int i = 0 ; i < 10; ++i){

                if ((rand() % 2 == 0)){
                    sign1 = 1;
                    sign2 = 1;
                }
                else{
                    sign1 = -1;
                    sign2 = -1;
                }
            }

            if ((sign2 > 0) && (rand() % 2 == 0)) sign2 *= 2;

            monsterAxisX = (float)((sign1) * (rand() % 10)) + (sign1)*logicSpace.x;
            monsterAxisY = (float)((sign2) * (rand() % 11)) + (sign2)*logicSpace.y;
            okMonster = 1;

            theCounter += 1;
        }
    }
          monsterAxisX -= monsterSpeed * deltaTimeSeconds * cos(monsterAngle);
          monsterAxisY -= monsterSpeed * deltaTimeSeconds * sin(monsterAngle);

    if (!isShot && window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
        isShot = true;
        angle = playerAngle;
    }
    else {
        if (isShot) {
            if(angle == 3.1415/2)
        {
            objFaceY -= 25 * deltaTimeSeconds;//viteza glont
            objFaceX = 0;
        }
        else
        if (cos(angle) > 0) {
            objFaceX += 25 * deltaTimeSeconds;
            objFaceY = tan(angle) * objFaceX;
        }
        else
            if (cos(angle) < 0) {
                objFaceX -= 25 * deltaTimeSeconds;
                objFaceY = tan(angle) * objFaceX;
            }
        }
    }

    if ((objFaceX > 10 || objFaceX < -10 || objFaceY > 10 || objFaceY < - 10)) {//raza de actiune glont
        objFaceX = 0;
        objFaceY = 0;
        isShot = false;
    }

    //1.se randeaza inamicul
    monsterMatrix = glm::mat3(1);
    monsterMatrix = monsterMatrix * VisualizationTransf2D(logicSpace, viewSpace);

    DrawMonster(monsterMatrix);
    //2. se randeaza player-ul si componentele(view-portul)
    visMatrix = glm::mat3(1);
    visMatrix = visMatrix * VisualizationTransf2D(logicSpace, viewSpace);
    DrawFrogComponents(visMatrix);
    
    //se randeaza harta
    lakeMatrix = glm::mat3(1);
    lakeMatrix = lakeMatrix * VisualizationTransf2D(logicSpace, viewSpace);
    DrawMap(lakeMatrix);
    //matrice pt inamics

}

void Lab3_Vis2D::DrawFrogComponents(glm::mat3 visMatrix){
    DrawPlayer(visMatrix, theCounter);
    DrawHealthBar(visMatrix, theCounter);
    DrawBullet(visMatrix);
}

void Lab3_Vis2D::DrawPlayer(glm::mat3 visMatrix, int theCounter){
    //compontentele care formeaza o broasca
    //toate se vor roti in functie de unghiul calculat
    //toate se rotesc in functie de cea mai mare componenta
    //tot in functie de cea mai mare componenta calculez si unghiul
    //si anume , patratul  
    playerMatrix = visMatrix * transform2D::Translate(logicSpace.x, logicSpace.y);
    playerMatrix = playerMatrix * transform2D::Translate(logicSpace.width / 2, logicSpace.height / 2);
    playerMatrix = playerMatrix * transform2D::Rotate(playerAngle);
    playerMatrix = playerMatrix * transform2D::Translate(- logicSpace.width / 2, - logicSpace.height / 2);
    RenderMesh2D(meshes["playerBody2"], shaders["VertexColor"], playerMatrix);

    playerMatrix = visMatrix * transform2D::Translate(logicSpace.x, logicSpace.y);
    playerMatrix = playerMatrix * transform2D::Translate(logicSpace.width / 2, logicSpace.height / 2);
    playerMatrix = playerMatrix * transform2D::Rotate(playerAngle);
    playerMatrix = playerMatrix * transform2D::Translate(- logicSpace.width / 2, - logicSpace.height / 2);
    RenderMesh2D(meshes["playerBody3"], shaders["VertexColor"], playerMatrix);

    playerMatrix = visMatrix * transform2D::Translate(logicSpace.x, logicSpace.y);
    playerMatrix = playerMatrix * transform2D::Translate(logicSpace.width / 2, logicSpace.height / 2);
    playerMatrix = playerMatrix * transform2D::Rotate(playerAngle);
    playerMatrix = playerMatrix * transform2D::Translate(- logicSpace.width / 2, - logicSpace.height / 2);
    RenderMesh2D(meshes["playerBody5"], shaders["VertexColor"], playerMatrix);

    //baza jucatorului
    playerMatrix = visMatrix * transform2D::Translate(logicSpace.x, logicSpace.y);
    playerMatrix = playerMatrix * transform2D::Translate(logicSpace.width / 2,  logicSpace.height / 2);
    playerMatrix = playerMatrix * transform2D::Rotate(playerAngle);
    playerMatrix = playerMatrix * transform2D::Translate(- logicSpace.width / 2, - logicSpace.height / 2);
    RenderMesh2D(meshes["playerBody1"], shaders["VertexColor"], playerMatrix);

}

void Lab3_Vis2D::DrawMonster(glm::mat3 visMatrix){
    monsterMatrix = visMatrix * transform2D::Translate(monsterAxisX,monsterAxisY);
    //creez inamicul
    RenderMesh2D(meshes["en1"], shaders["VertexColor"],monsterMatrix);
    RenderMesh2D(meshes["en3"], shaders["VertexColor"],monsterMatrix);
    RenderMesh2D(meshes["en4"], shaders["VertexColor"],monsterMatrix);
    RenderMesh2D(meshes["en2"], shaders["VertexColor"],monsterMatrix);
}

void Lab3_Vis2D::DrawHealthBar(glm::mat3 visMatrix, int theCounter){

    //1hp
    playerMatrix = visMatrix * transform2D::Translate(logicSpace.x, logicSpace.y);
    playerMatrix = playerMatrix * transform2D::Translate(4,5);
    
    if(theCounter >= 5){
        playerMatrix = playerMatrix * transform2D::Translate(-1.1f,2);//scad pana unde tre sa ajung - 4hp

        if(theCounter == 5 && gameOver == 0){
            printf("GAME OVER!!!\n");
            gameOver++;
        }
    }

    RenderMesh2D(meshes["healthBar"], shaders["VertexColor"], playerMatrix);

    //2hp
    // playerMatrix = visMatrix * transform2D::Translate(logicSpace.x, logicSpace.y);
    playerMatrix = playerMatrix * transform2D::Translate(1.1f,0);

    if(theCounter >= 4){
        playerMatrix = playerMatrix * transform2D::Translate(-1.1f,2);//scad pana unde tre sa ajung - 4hp
    }
    
    RenderMesh2D(meshes["healthBar"], shaders["VertexColor"], playerMatrix); 

    //3hp
    // playerMatrix = visMatrix * transform2D::Translate(logicSpace.x, logicSpace.y);
    playerMatrix = playerMatrix * transform2D::Translate(1.1f,0);
    
    if(theCounter >= 3){
        playerMatrix = playerMatrix * transform2D::Translate(-1.1f,2);//-3hp
    }
    RenderMesh2D(meshes["healthBar"], shaders["VertexColor"], playerMatrix);

    //4hp
    // playerMatrix = visMatrix * transform2D::Translate(logicSpace.x, logicSpace.y);
    playerMatrix = playerMatrix * transform2D::Translate(1.1f,0);

    if(theCounter >= 2){
          playerMatrix = playerMatrix * transform2D::Translate(-1.1f,2);//-2hp
    }
    RenderMesh2D(meshes["healthBar"], shaders["VertexColor"], playerMatrix);

    //5hp
    // playerMatrix = visMatrix * transform2D::Translate(logicSpace.x, logicSpace.y); 

    playerMatrix = playerMatrix * transform2D::Translate(1.1f,0);

    if(theCounter >= 1){//pentru fiecare atingere a monstrului pierd 1 hp
        playerMatrix = playerMatrix * transform2D::Translate(-4.4f,2);//-1hp
    }
  
    RenderMesh2D(meshes["healthBar"], shaders["VertexColor"], playerMatrix);


     ///5 patrate care reprezinta full-hpul
    playerMatrix = visMatrix * transform2D::Translate(logicSpace.x, logicSpace.y);
    playerMatrix = playerMatrix * transform2D::Translate(4,5);
    RenderMesh2D(meshes["fullHealth"], shaders["VertexColor"], playerMatrix);

    playerMatrix = visMatrix * transform2D::Translate(logicSpace.x, logicSpace.y);
    playerMatrix = playerMatrix * transform2D::Translate(5.1f,5);
    RenderMesh2D(meshes["fullHealth"], shaders["VertexColor"], playerMatrix); 

    playerMatrix = visMatrix * transform2D::Translate(logicSpace.x, logicSpace.y);
    playerMatrix = playerMatrix * transform2D::Translate(6.2f,5);
    RenderMesh2D(meshes["fullHealth"], shaders["VertexColor"], playerMatrix);

    playerMatrix = visMatrix * transform2D::Translate(logicSpace.x, logicSpace.y);
    playerMatrix = playerMatrix * transform2D::Translate(7.3f,5);
    RenderMesh2D(meshes["fullHealth"], shaders["VertexColor"], playerMatrix);

    playerMatrix = visMatrix * transform2D::Translate(logicSpace.x, logicSpace.y);
    playerMatrix = playerMatrix * transform2D::Translate(8.4f,5);
    RenderMesh2D(meshes["fullHealth"], shaders["VertexColor"], playerMatrix);



}
void Lab3_Vis2D::DrawBullet(glm::mat3 visMatrix)
{
    //proiectil
    playerMatrix = visMatrix * transform2D::Translate(trIndexX, trIndexY);
    playerMatrix = playerMatrix * transform2D::Translate(objFaceX, objFaceY);
    playerMatrix = playerMatrix * transform2D::Translate(logicSpace.width / 2, logicSpace.height / 2);
    playerMatrix = playerMatrix * transform2D::Rotate(angle);
    playerMatrix = playerMatrix * transform2D::Translate(- logicSpace.width / 2,- logicSpace.height /2);
    RenderMesh2D(meshes["playerBody4"], shaders["VertexColor"], playerMatrix);
}

void Lab3_Vis2D::DrawMap(glm::mat3 visMatrix){
    //scalez si translatez peretii in functie de harta
    //pentru a obtine harta dorita

    lakeMatrix = visMatrix * transform2D::Scale(0.15f,0.05f);
    lakeMatrix = lakeMatrix * transform2D::Translate(100.f,22.f);//fixed
    RenderMesh2D(meshes["theMap"], shaders["Simple"], lakeMatrix);

    lakeMatrix = visMatrix * transform2D::Scale(0.3f,0.2f);
    lakeMatrix = lakeMatrix * transform2D::Translate(22.f,90.f);//fixed
    RenderMesh2D(meshes["theMap"], shaders["Simple"], lakeMatrix); 

    lakeMatrix = visMatrix * transform2D::Scale(0.5f,0.05f);
    lakeMatrix = lakeMatrix * transform2D::Translate(0.f,-5.f);//fixed
    RenderMesh2D(meshes["theMap"], shaders["Simple"], lakeMatrix);

    lakeMatrix = visMatrix * transform2D::Scale(0.5f,0.1f);
    lakeMatrix = lakeMatrix * transform2D::Translate(20.f,84.f);//fixed
    RenderMesh2D(meshes["theMap"], shaders["Simple"], lakeMatrix);

    lakeMatrix = visMatrix * transform2D::Scale(0.1f,0.5f);
    lakeMatrix = lakeMatrix * transform2D::Translate(0.f,20.f);//fixed
    RenderMesh2D(meshes["theMap"], shaders["Simple"], lakeMatrix);

    lakeMatrix = visMatrix * transform2D::Scale(0.5f,0.05f);
    lakeMatrix = lakeMatrix * transform2D::Translate(20.f,640.f);//fixed
    RenderMesh2D(meshes["theMap"], shaders["Simple"], lakeMatrix);


    //baza hartii
    RenderMesh2D(meshes["theMap"], shaders["VertexColor"], visMatrix);

}

void Lab3_Vis2D::FrameEnd(){
    //cand se pierd cele 5 vieti se face ecranul negru 
    if(theCounter >= 5){
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}

void Lab3_Vis2D::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY){   

    glm::ivec2 reso = window->GetResolution();
    //calculez unghiul pt player
    //
    playerAngle = atan2(reso.y - mouseY - ((reso.y) / logicSpace.height * 2 *2.8125f) - trIndexY, mouseX - ((reso.x) / logicSpace.width * 2 * 5.f) - trIndexX);
    monsterAngle = atan2(cymonster + monsterAxisY - heroAxisY - trIndexY, cxmonster + monsterAxisX - heroAxisX  - trIndexX);
}



