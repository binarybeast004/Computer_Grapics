#include <iostream>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <utility>
#include <math.h>
using namespace std;
struct Color
{
    int r;
    int g;
    int b;
};

struct Scene
{
    string scene;
    Color skyTop;
    Color skyBottom;
    Color frontMountain;
    Color rearMountain;
    Color lightShadow;
    Color darkShadow;
    Color River;
    Color ground; // 9
    Color houseWallShadowed;
    Color houseWallSide;
    Color houseRoof;
    Color houseWindows;
    Color houseDoor;
    Color treeLeft;
    Color treeRight;
    Color treeBase;
    Color riverMark;
    Color groundMark;
    Color tentRoof;
    Color tentRoofdark;
    Color tentFront;
    Color tentRope;
    Color boatSails;
    Color boatMast;
    Color boatBody;
};
float X = 550, Y = 30;
float boatX = 0;
int factor = 1;
unsigned long long lastFrameTime = 0;
float cloudX = 0;
float cloud2X = 500;
float cloud3X = 1000;
float cloud4X = 200;
float angle = 0;

Scene day = {
    "day",
    {147, 236, 244},
    {243, 240, 189},
    {87, 78, 74}, // fr
    {43, 43, 270}, // back
    {43, 43, 270}, //
    {43, 43, 270},
    {154, 242, 255},
    {46, 189, 143}, // 9

    {130, 130, 120},
    {187, 78, 56},
    {188, 187, 156},
    {255,203,21},
    {75,52,42}, //14

    {2, 110, 123},
    {2, 148, 138},
    {70, 38, 17},
    {99, 228, 234},
    {119, 217, 185},//19

    {231, 144, 34},
    {220, 121, 45},
    {254, 161, 35},
    {0, 0, 0},//23

    {255, 255, 255},
    {135, 196, 240},
    {1, 63, 86} //26
};

Scene night =
    {
        "night",
        {60, 41, 102},
        {99, 106, 188},
        {35, 26, 104},
        {66, 58, 163},
        {145, 143, 207},
        {57, 54, 161},
        {96, 106, 88},
        {57, 54, 161}, // 9

        {45, 38, 110},
        {46, 39, 122},
        {66, 58, 163},
        {255, 203, 21},
        {130,130,120}, // 14

        {42, 33, 110},
        {66, 58, 162},
        {0, 0, 0},
        {2, 30, 68},
        {12, 4, 93}, // 19

        {66, 58, 163},
        {27, 21, 84},
        {35, 26, 104},
        {11, 0, 26},

        {188, 187, 156},
        {0, 0, 0},
        {87,78,74}

};

Scene currentScene = day;

void quad(float x1, float x2, float y1, float y2, Color color, float Tx = 0, float Ty = 0, float s = 1)
{
    glColor3ub(color.r, color.g, color.b);
    glBegin(GL_QUADS);
    glVertex2f(s * x1 + Tx, s * y1 + Ty);
    glVertex2f(s * x2 + Tx, s * y1 + Ty);
    glVertex2f(s * x2 + Tx, s * y2 + Ty);
    glVertex2f(s * x1 + Tx, s * y2 + Ty);
    glEnd();
}
void circle(float x, float y, float radius, float height, Color color)
{
    int triangleAmount = 360;
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(color.r, color.g, color.b);
    glVertex2f(x, y); // center of circle
    for (int i = 0; i <= 360; i++)
        glVertex2f(x + (radius * cos(i * 2 * 3.1416 / triangleAmount)), y + (height * sin(i * 2 * 3.1416 / triangleAmount)));
    glEnd();
}
void quad(vector<pair<float, float>> coord, Color color = {255, 255, 255}, float Tx = 0, float Ty = 0, float s = 1)
{
    glColor3ub(color.r, color.g, color.b);
    glBegin(GL_QUADS);
    for (int i = 0; i < coord.size(); i++)
        glVertex2d(Tx + s * coord[i].first, Ty + s * coord[i].second);
    glEnd();
}
void triangle(vector<pair<float, float>> coord, Color color = {255, 255, 255}, float Tx = 0, float Ty = 0, float s = 1)
{
    glColor3ub(color.r, color.g, color.b);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < coord.size(); i++)
        glVertex2d(Tx + s * coord[i].first, Ty + s * coord[i].second);
    glEnd();
}
void polygon(vector<pair<float, float>> coord, Color color = {255, 255, 255}, float Tx = 0, float Ty = 0, float s = 1)
{
    glColor3ub(color.r, color.g, color.b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < coord.size(); i++)
        glVertex2d(Tx + s * coord[i].first, Ty + s * coord[i].second);
    glEnd();
}

void tree(float Tx, float Ty, float s = 1, Color treeleft = {2, 110, 123}, Color treeRight = {2, 148, 138}, Color treeBase = {70, 38, 17})
{
    //left
    polygon({{Tx + s * 0, Ty + s * 48.57}, {Tx + s * -39.01, Ty + s * 48.57}, {Tx + s * -34.88, Ty + s * 75.17}, {Tx + s * -24.92, Ty + s * 61.88}, {Tx + s * -33.42, Ty + s * 84.56}, {Tx + s * -31.06, Ty + s * 99.78}, {Tx + s * -15.47, Ty + s * 66.84}, {Tx + s * -30.11, Ty + s * 105.9}, {Tx + s * -27.82, Ty + s * 120.62}, {Tx + s * -19.83, Ty + s * 103.74}, {Tx + s * -27.33, Ty + s * 123.76}, {Tx + s * -19.55, Ty + s * 173.84}, {Tx + s * -0.71, Ty + s * 149.68}, {Tx + s * -16.68, Ty + s * 192.3}, {Tx + s * -12.7, Ty + s * 217.93}, {Tx + s * -5.3, Ty + s * 208.05}, {Tx + s * -11.62, Ty + s * 224.91}, {Tx + s * -9.11, Ty + s * 241.04}, {Tx + s * -0.71, Ty + s * 226}, {Tx + s * -8.3, Ty + s * 246.25}, {Tx + s * 0, Ty + s * 299.76}}, treeleft);
    //right
    polygon({{Tx + s * 0, Ty + s * 48.57}, {Tx + s * 39.04, Ty + s * 48.57}, {Tx + s * 31.32, Ty + s * 98.28}, {Tx + s * 12.13, Ty + s * 79.1}, {Tx + s * 28.64, Ty + s * 115.48}, {Tx + s * 22.52, Ty + s * 154.9}, {Tx + s * 12.13, Ty + s * 144.51}, {Tx + s * 21.93, Ty + s * 158.73}, {Tx + s * 14.78, Ty + s * 204.74}, {Tx + s * 7.39, Ty + s * 197.36}, {Tx + s * 13.75, Ty + s * 211.36}, {Tx + s * 0, Ty + s * 299.76}}, treeRight);
    //base
    triangle({{Tx + s * 4.59, Ty + s * -0.03}, {Tx + s * -0.71, Ty + s * 219.82}, {Tx + s * -10.07, Ty + s * 0.02}, {Tx + s * -0.89, Ty + s * 46.87}, {Tx + s * -25.93, Ty + s * 98.64}, {Tx + s * -0.89, Ty + s * 61.32}, {Tx + s * -0.71, Ty + s * 64.41}, {Tx + s * 16.71, Ty + s * 100.43}, {Tx + s * -0.71, Ty + s * 74.46}, {Tx + s * -0.71, Ty + s * 86.87}, {Tx + s * 16.71, Ty + s * 122.89}, {Tx + s * -0.89, Ty + s * 96.67}, {Tx + s * -0.89, Ty + s * 109.64}, {Tx + s * -18.48, Ty + s * 146.01}, {Tx + s * -0.89, Ty + s * 119.79}, {Tx + s * -0.71, Ty + s * 148.71}, {Tx + s * 11.97, Ty + s * 175.2}, {Tx + s * -0.71, Ty + s * 156.29}, {Tx + s * -0.89, Ty + s * 169.09}, {Tx + s * -12.39, Ty + s * 192.88}, {Tx + s * -0.89, Ty + s * 175.73}, {Tx + s * -0.89, Ty + s * 132.44}, {Tx + s * -12.39, Ty + s * 156.22}, {Tx + s * -0.71, Ty + s * 138.82}}, treeBase);
}


void windMill(float Tx, float Ty, Color houseWallSide = {255, 254, 255}, Color houseRoof = {255, 197, 78}, Color houseWindows = {37, 105, 118}, Color houseDoor = {18, 105, 132})
{
    //main body
    glColor3ub(houseWallSide.r, houseWallSide.g, houseWallSide.b);
    glBegin(GL_QUADS);
    glVertex2f(Tx + 0, Ty + 0);
    glVertex2f(Tx + 56.43, Ty + -0.05);
    glVertex2f(Tx + 51.41, Ty + 70.25);
    glVertex2f(Tx + 4.73, Ty + 70.25);
    //throat
    glColor3ub(125, 130, 100);
    glBegin(GL_QUADS);
    glVertex2f(Tx + 7.3, Ty + 70.25);
    glVertex2f(Tx + 49.04, Ty + 70.25);
    glVertex2f(Tx + 49.04, Ty + 76.52);
    glVertex2f(Tx + 7.3, Ty + 76.52);
    //door
    glColor3ub(houseDoor.r, houseDoor.g, houseDoor.b);
    glBegin(GL_QUADS);
    glVertex2f(Tx + 22.34, Ty + -0.02);
    glVertex2f(Tx + 33.36, Ty + -0.03);
    glVertex2f(Tx + 33.36, Ty + 18.94);
    glVertex2f(Tx + 22.34, Ty + 18.94);
    //window
    glColor3ub(houseWindows.r, houseWindows.g, houseWindows.b);
    glBegin(GL_QUADS);
    glVertex2f(Tx + 25.21, Ty + 29.74);
    glVertex2f(Tx + 30.9, Ty + 29.74);
    glVertex2f(Tx + 30.91, Ty + 40.45);
    glVertex2f(Tx + 25.21, Ty + 40.45);
    glVertex2f(Tx + 25.17, Ty + 51.55);
    glVertex2f(Tx + 30.87, Ty + 51.55);
    glVertex2f(Tx + 30.88, Ty + 62.26);
    glVertex2f(Tx + 25.17, Ty + 62.26);
    glEnd();
    //roof
    glColor3ub(houseRoof.r, houseRoof.g, houseRoof.b);
    glBegin(GL_TRIANGLES);
    glVertex2f(Tx + -0.52, Ty + 76.52);
    glVertex2f(Tx + 57, Ty + 76.52);
    glVertex2f(Tx + 28.42, Ty + 91.33);
    glEnd();

    //fan
    glPushMatrix();
    glTranslatef(Tx+28.5, Tx+203, 0);
    glRotatef(0, 0, 0, 1);
    quad({{18.16, 11.27}, {41.18, 34.23}, {34.19, 41.19}, {11.17, 18.23}, {-11.37, 18.23}, {-34.4, 41.19}, {-41.38, 34.23}, {-18.36, 11.27}, {-18.36, -11.22}, {-41.38, -34.18}, {-34.4, -41.14}, {-11.37, -18.18}, {11.17, -18.18}, {34.19, -41.14}, {41.18, -34.18}, {18.16, -11.22}, {22.22, -23.16}, {23.15, -22.23}, {1.24, -0.39}, {0.31, -1.31}, {-1.44, -0.39}, {-23.35, -22.23}, {-22.42, -23.16}, {-0.52, -1.31}, {-0.52, 1.36}, {-22.42, 23.21}, {-23.35, 22.28}, {-1.44, 0.44}, {1.24, 0.44}, {23.15, 22.28}, {22.22, 23.21}, {0.31, 1.36}}, currentScene.houseDoor);
    glPopMatrix();
    circle(Tx+28.5, Ty+73.5, 3.8, 3.8, currentScene.houseDoor);
    glEnd();
}
void tent(float init_x = 0, float init_y = 0, float m = 1, Color tentRoof = {231, 144, 34}, Color tentRoofdark = {220, 121, 45}, Color tentFront = {254, 161, 35}, Color tentRope = {106, 90, 73})
{
    polygon({{init_x + m * 133.68, init_y + 209.63}, {init_x + m * 259.04, init_y + 48.56}, {init_x + m * 338.81, init_y + 90.11}, {init_x + m * 244.79, init_y + 207.92}}, currentScene.tentRoof);
    polygon({{init_x + m * 106.9, init_y + 171.5}, {init_x + m * 259.04, init_y + 48.56}, {init_x + m * 133.68, init_y + 209.63}}, currentScene.tentRoofdark);
    polygon({{init_x + m * 106.9, init_y + 171.5}, {init_x + m * 35.39, init_y + 69.68}, {init_x + m * 48.76, init_y + 74.43}, {init_x + m * 112.63, init_y + 166.87}}, currentScene.tentRoof);
    polygon({{init_x + m * 35.39, init_y + 69.68}, {init_x + m * 46.37, init_y + 65.9}, {init_x + m * 61.53, init_y + 28.05}, {init_x + m * 65.69, init_y + 28.29}, {init_x + m * 48.76, init_y + 74.43}}, currentScene.tentRoof);
    polygon({{init_x + m * 65.69, init_y + 28.29}, {init_x + m * 235.44, init_y + 15.1}, {init_x + m * 243.29, init_y + 61.29}, {init_x + m * 112.72, init_y + 167}, {init_x + m * 48.76, init_y + 74.43}}, currentScene.tentFront);
    polygon({{init_x + m * 129.34, init_y + 24.23}, {init_x + m * 133.46, init_y + 141.46}, {init_x + m * 135.84, init_y + 139.65}, {init_x + m * 137.52, init_y + 23.71}}, currentScene.tentRoofdark);
    polygon({{init_x + m * 243.29, init_y + 61.29}, {init_x + m * 235.44, init_y + 15.1}, {init_x + m * 314.05, init_y + 53.57}, {init_x + m * 317.81, init_y + 79.15}, {init_x + m * 259.04, init_y + 48.56}}, currentScene.tentRoofdark);
    triangle({{init_x + m * 361.32, init_y + 79.37}, {init_x + m * 368.56, init_y + 79.37}, {init_x + m * 365.2, init_y + 57.39}, {init_x + m * 292.93, init_y + 26.69}, {init_x + m * 300.17, init_y + 26.69}, {init_x + m * 296.86, init_y + 2.61}, {init_x + m * 2.67, init_y + 53.7}, {init_x + m * 9.91, init_y + 53.7}, {init_x + m * 6.59, init_y + 29.62}}, currentScene.tentRope);
    quad({{init_x + m * 36.47, init_y + 69.31}, {init_x + m * 2.54, init_y + 44.22}, {init_x + m * 3.54, init_y + 42.45}, {init_x + m * 37.5, init_y + 68.95}, {init_x + m * 260.36, init_y + 49.25}, {init_x + m * 300.9, init_y + 18.44}, {init_x + m * 301.29, init_y + 19.75}, {init_x + m * 261.43, init_y + 49.8}, {init_x + m * 337.36, init_y + 89.35}, {init_x + m * 368.73, init_y + 70.34}, {init_x + m * 368.98, init_y + 72.55}, {init_x + m * 338.4, init_y + 89.89}, {init_x + m * 337.36, init_y + 89.35}}, currentScene.tentRope);
    glFlush();
}
void boat(float Tx = 0, float Ty = 0, float m = 1, Color boatSails = {58, 59, 95}, Color boatMast = {10, 24, 32}, Color boatBody = {98, 41, 61})
{
    polygon({{Tx + m * 0.34, Ty + 14.87}, {Tx + m * 128.31, Ty + 14.87}, {Tx + m * 138.12, Ty + 20.12}, {Tx + m * 138.12, Ty + 8.16}, {Tx + m * 137.79, Ty + 6.26}, {Tx + m * 136.91, Ty + 3.95}, {Tx + m * 135.59, Ty + 2.48}, {Tx + m * 134.24, Ty + 1.43}, {Tx + m * 132.48, Ty + 0.87}, {Tx + m * 129.5, Ty + 0.38}, {Tx + m * 126.76, Ty + 0.11}, {Tx + m * 4.1, Ty + 0.11}, {Tx + m * 0.34, Ty + 14.87}}, boatBody);
    triangle({{Tx + m * 62.27, Ty + 121.69}, {Tx + m * 2.06, Ty + 27.62}, {Tx + m * 62.27, Ty + 27.62}}, boatSails);
    triangle({{Tx + m * 62.82, Ty + 163.64}, {Tx + m * 66.01, Ty + 14.48}, {Tx + m * 121.62, Ty + 47.07}}, boatSails);
    triangle({{Tx + m * 62.82, Ty + 163.64}, {Tx + m * 44.85, Ty + 160.68}, {Tx + m * 62.8, Ty + 154.21}}, boatMast);
    triangle({{Tx + m * 62.82, Ty + 163.64}, {Tx + m * 62.49, Ty + 13.76}, {Tx + m * 66.02, Ty + 13.79}}, boatMast);
}

void cloud1(float Tx, float Ty, float s)
{
    //cloud
    circle(Tx + s * 16, Ty + s * 20, 15, 15, {211, 210, 231});
    circle(Tx + s * 29, Ty + s * 31, 9, 9, {211, 210, 231});
    circle(Tx + s * 58, Ty + s * 30, 27, 27, {211, 210, 231});
    circle(Tx + s * 85, Ty + s * 21, 20, 20, {211, 210, 231});
    quad({{17, 23}, {85, 23}, {85, 1}, {17, 5}}, {211, 210, 231}, Tx, Ty, s);
}
void cloud2(float Tx, float Ty, float s)
{
    //cloud
    circle(Tx + s * 13, Ty + s * 16, 7, 7, {211, 210, 231});
    circle(Tx + s * 24, Ty + s * 24, 9, 9, {211, 210, 231});
    circle(Tx + s * 40, Ty + s * 32, 12, 12, {211, 210, 231});
    circle(Tx + s * 54, Ty + s * 36, 7, 7, {211, 210, 231});
    circle(Tx + s * 74, Ty + s * 40, 16, 16, {211, 210, 231});
    circle(Tx + s * 95, Ty + s * 40, 10, 10, {211, 210, 231});
    circle(Tx + s * 108, Ty + s * 34, 6, 6, {211, 210, 231});
    circle(Tx + s * 122, Ty + s * 31, 10, 10, {211, 210, 231});
    circle(Tx + s * 132, Ty + s * 25, 10, 10, {211, 210, 231});
    circle(Tx + s * 144, Ty + s * 16, 6, 6, {211, 210, 231});
    quad({{12, 18}, {146, 18}, {146, 11}, {11, 10}}, {211, 210, 231}, Tx, Ty, s);
    quad({{20, 32}, {138, 32}, {138, 17}, {20, 17}}, {211, 210, 231}, Tx, Ty, s);
}
void cloud3(float Tx, float Ty, float s)
{
    circle(Tx + s * 23, Ty + s * 33, 21, 21, {211, 210, 231});
    circle(Tx + s * 50, Ty + s * 49, 20, 20, {211, 210, 231});
    circle(Tx + s * 80, Ty + s * 43, 14, 14, {211, 210, 231});
    circle(Tx + s * 90, Ty + s * 32, 17, 17, {211, 210, 231});
    circle(Tx + s * 68, Ty + s * 23, 21, 21, {211, 210, 231});
    circle(Tx + s * 43, Ty + s * 17, 17, 17, {211, 210, 231});
    circle(Tx + s * 23, Ty + s * 33, 22, 22, {211, 210, 231});
}

void rearMountain() {
    polygon({{387, 500}, {387, 760}, {348.32, 765.88}, {320.46, 774.31}, {299.96, 789.06}, {286.54, 781.83}, {243.2, 807.31}, {216.28, 788.02}, {206.29, 788.98}, {149.44, 766.41}, {116.31, 735.41}, {80.72, 735.49}, {42.76, 721.31}, {0, 712.6}, {0, 500}}, currentScene.rearMountain);
    polygon({{690.42, 519.21}, {690.42, 757.24}, {709.64, 766.25}, {728.84, 762.53}, {745.91, 779.31}, {774.19, 797.69}, {787.32, 790.72}, {808.37, 807.38}, {863.74, 769.09}, {876.16, 776.44}, {901.02, 771.37}, {916.09, 757.99}, {945.28, 782.72}, {1002.54, 737.36}, {1024.48, 745.68}, {1024.48, 745.68}, {1084.4, 712.8}, {1096.1, 718.64}, {1125.06, 692.17}, {1166.05, 675.09}, {1195.96, 677.25}, {1230.89, 688.87}, {1267.07, 688.85}, {1300.48, 715.54}, {1357.64, 735.28}, {1366.68, 734.21}, {1393.75, 751.33}, {1437.43, 729.19}, {1450.75, 735.32}, {1471.2, 722.3}, {1498.42, 715.01}, {1537.89, 710.47}, {1537.89, 515.63}}, currentScene.rearMountain);
    polygon({{1841.53, 515.63}, {1841.53, 707.41}, {1860.76, 715.26}, {1879.12, 712.43}, {1920, 736.81}, {1920, 515.63}}, currentScene.rearMountain);
    // shadow
    polygon({{11.49, 678.1}, {19.58, 706.16}, {54.84, 710.9}, {80.56, 730.61}, {96.73, 730.61}, {79.28, 693.96}, {41.78, 693.96}}, currentScene.lightShadow);
    polygon({{122.62, 730.92}, {138.09, 710.48}, {121.89, 692.85}, {95.14, 680.23}, {116.84, 700.82}}, currentScene.lightShadow);
    polygon({{171.57, 733.51}, {181.76, 751.26}, {204.37, 760}, {222.91, 783.13}, {241.67, 798.35}, {235.72, 782.12}, {216.45, 760.23}, {209.28, 749.34}, {190.2, 742.87}}, currentScene.lightShadow);
    polygon({{254.59, 742.59}, {276.38, 773.33}, {298.97, 781.39}, {340.33, 753.78}, {305.12, 761.74}, {278.5, 753.88}}, currentScene.lightShadow);
    polygon({{722.66, 754.34}, {737.85, 760.17}, {746.01, 778.78}, {772.29, 787.05}, {774.3, 791.78}, {776.62, 791.78}, {780.94, 786.75}, {773.8, 776.79}, {743.9, 754.06}}, currentScene.lightShadow);
    polygon({{748.31, 750.64}, {773.17, 766.73}, {787.36, 783.03}, {805.08, 792.08}, {810.42, 803.68}, {812.94, 786.07}, {792.51, 775.31}, {773.28, 753.79}}, currentScene.lightShadow);
    polygon({{799.01, 733.56}, {824.29, 749.65}, {829.6, 761.87}, {818.49, 791.95}, {839.74, 776.03}, {847.63, 761.87}, {844.08, 748.68}, {823.8, 733.88}, {810.12, 709.75}}, currentScene.lightShadow);
    polygon({{826.87, 726.14}, {855.2, 744.8}, {860.19, 755.25}, {868.56, 766.51}, {882.41, 773.11}, {886.75, 767.8}, {884.02, 760.08}, {865.99, 744.15}}, currentScene.lightShadow);
    polygon({{887.55, 726.72}, {900.81, 739.31}, {928.96, 745.57}, {944.45, 773.63}, {944.45, 754.45}, {955.21, 735.99}, {910.93, 725.84}, {888.55, 708.56}}, currentScene.lightShadow);
    polygon({{953.05, 765.26}, {978.86, 749}, {996.53, 724.32}, {978.66, 716.79}, {962.69, 752.21}}, currentScene.lightShadow);
    polygon({{1024.67, 741.68}, {1031.81, 733.2}, {1075.98, 706.34}, {1092.04, 706.34}, {1075.48, 686.78}, {1080.7, 699.82}, {1061.13, 708.74}, {1049.29, 698.62}, {1040.96, 673.75}, {1048.7, 708.47}, {1043.79, 719.68}, {1026.57, 728.28}}, currentScene.lightShadow);
    polygon({{1161.99, 639.32}, {1168.97, 662.37}, {1204.85, 667.32}, {1231.12, 684.63}, {1247.26, 684.63}, {1229.74, 652.72}, {1191.9, 652.72}}, currentScene.lightShadow);
    polygon({{1246.26, 641.17}, {1267.16, 658.06}, {1272.76, 684.83}, {1288.76, 667.15}, {1272.76, 651.96}}, currentScene.lightShadow);
    polygon({{1321.54, 686.76}, {1331.03, 701.6}, {1354.75, 709.58}, {1371.94, 728.45}, {1392.22, 743.33}, {1386.03, 728.76}, {1368.55, 711.68}, {1359.44, 700.66}, {1339.93, 695.07}}, currentScene.lightShadow);
    polygon({{1404.71, 694.4}, {1426.86, 721.35}, {1449.47, 728.41}, {1490.54, 704.48}, {1455.47, 711.37}, {1429.99, 704.98}}, currentScene.lightShadow);
    polygon({{1872.1, 705.02}, {1888.57, 709.91}, {1894.26, 721.28}, {1899.86, 724.97}, {1914.33, 728.26}, {1914.33, 718.19}, {1894.46, 704.82}}, currentScene.lightShadow);


}
void frontMountain() {
    polygon({{1166.00, 500.00}, {1166.00, 535.11}, {1205.15, 550.08}, {1238.54, 603.29}, {1398.15, 667.96}, {1436.34, 647.9}, {1460.13, 671.01}, {1525.59, 691.51}, {1532.36, 708.08}, {1568.29, 729.59}, {1589.46, 750.52}, {1674.12, 807.22}, {1718.64, 764.92}, {1734.57, 770.37}, {1760.1, 747.91}, {1782.62, 753.8}, {1829.14, 722.66}, {1850.61, 696.52}, {1859.94, 702.7}, {1920, 685.85}, {1920, 515.63}}, currentScene.frontMountain);
    polygon({{0, 500}, {2.25, 551.5}, {38.98, 551.5}, {88.79, 636.1}, {248.5, 710.75}, {285.99, 688.18}, {309.44, 714.25}, {374.34, 737.76}, {382.35, 757.46}, {416.33, 781.97}, {438.72, 806.81}, {523.28, 872.26}, {569.27, 823.59}, {584.07, 829.74}, {609.17, 804.24}, {631.7, 810.58}, {678.52, 774.51}, {700.18, 743.9}, {709.57, 751.36}, {788.14, 724.27}, {811.41, 701.83}, {826.72, 711.39}, {828.6, 710.54}, {829.72, 711.5}, {831.99, 709.63}, {879.22, 698.09}, {920.12, 686.66}, {954.98, 674.09}, {965.89, 668.04}, {970.37, 664.47}, {970.37, 662.34}, {984.1, 650.66}, {1155.36, 539.05}, {1155.36, 531.11}, {1166.00, 535.11}, {1166.00, 500.00}}, currentScene.frontMountain);

    // dark shadow
    polygon({{619.24, 773.49}, {602.89, 804.89}, {582.32, 825.45}, {592.06, 797.14}, {586.37, 756.92}, {605.15, 711.93}, {670.36, 708.44}, {680.78, 736.14}}, currentScene.darkShadow);
    polygon({{751.13, 680.29}, {751.13, 637.15}, {760.02, 665.57}, {794.56, 705.92}, {767.87, 724.05}, {731.3, 733.44}, {750.6, 717.2}, {745.27, 697.91}, {716.57, 663.65}, {721.93, 631.82}}, currentScene.darkShadow);
    polygon({{863.7, 637.08}, {877.96, 657.5}, {868.25, 670.43}, {853.88, 635.1}, {865.3, 603.36}}, currentScene.darkShadow);
    polygon({{1742.57, 742.96}, {1733.18, 765.39}, {1753.4, 748.31}, {1770.02, 721.36}, {1832.11, 689.25}, {1820.34, 665.02}, {1754.65, 668}, {1736.93, 708.73}}, currentScene.darkShadow);
    polygon({{1901.39, 673.68}, {1880.29, 687.21}, {1914.96, 682.09}, {1914.96, 633.64}, {1910.08, 627.23}, {1902.11, 602.16}, {1902.11, 641.15}, {1871.3, 598.16}, {1867.67, 628.14}, {1896.04, 655.89}}, currentScene.darkShadow);

    //white shadow
    polygon({{113.98, 642.79}, {187.49, 658.08}, {196.28, 643.04}, {216.6, 672.12}, {250.22, 700.95}}, currentScene.lightShadow);
    polygon({{248.78, 654.13}, {295.36, 666.09}, {304.93, 689.57}, {334.53, 718.67}, {315.28, 682.62}, {326.44, 675.99}, {297.81, 658.53}, {280.66, 643.18}, {271.44, 653.85}}, currentScene.lightShadow);
    polygon({{339.4, 697.73}, {408.53, 746.64}, {408.53, 766.11}, {445.68, 799.68}, {523.27, 863.99}, {521.49, 828.32}, {509.37, 818.32}, {505.81, 795.64}, {511.95, 789.34}, {509.69, 781.11}, {512.43, 764.97}, {507.25, 749.74}, {485.28, 722.3}, {447.16, 696.47}, {484.8, 742.15}, {494.97, 766.04}, {493.69, 780.83}, {478.92, 767.96}, {466.61, 774.27}, {448.24, 753.07}, {450.77, 783.16}, {442.94, 776.35}, {438.77, 749.86}, {404.04, 727.75}}, currentScene.lightShadow);
    polygon({{693.89, 723.32}, {709.73, 750.66}, {714.85, 710.13}, {674.42, 672.78}, {617.87, 661.35}, {673.41, 698.1}}, currentScene.lightShadow);
    polygon({{800.4, 693.88}, {830.08, 710.32}, {839.36, 697.75}, {864.04, 687.22}, {852.21, 665.65}, {822.92, 665.65}, {754.56, 628.15}, {754.98, 629.06}}, currentScene.lightShadow);
    polygon({{1366.49, 632.83}, {1400.82, 658.44}, {1265.79, 609.02}, {1338.05, 621.31}, {1347.27, 608.25}}, currentScene.lightShadow);
    polygon({{1446.3, 628.78}, {1455.74, 648.77}, {1485.21, 674.73}, {1465.68, 643.06}, {1477.05, 636.98}, {1447.6, 621.94}, {1430.95, 608.35}, {1421.82, 618.11}, {1399.65, 618.11}}, currentScene.lightShadow);
    polygon({{1593.52, 724.2}, {1601.2, 729.48}, {1598.8, 703.74}, {1617.36, 722.12}, {1630.48, 717.33}, {1644.23, 727.72}, {1645.8, 715.07}, {1635.9, 695.18}, {1597.28, 654.83}, {1636.15, 677.21}, {1662.7, 706.77}, {1662.7, 717.26}, {1660.13, 728.58}, {1662.13, 736.47}, {1656.43, 741.07}, {1659.81, 760.15}, {1672.2, 769.64}, {1673.35, 800.63}, {1558.39, 714.94}, {1558.39, 698.37}, {1489.85, 656.22}, {1553.36, 681.48}, {1589.2, 701.78}}, currentScene.lightShadow);
    polygon({{1824.07, 656.76}, {1842.68, 675.87}, {1860.02, 700.84}, {1865.38, 666.7}, {1823.81, 633.57}, {1767.96, 624.9}}, currentScene.lightShadow);

}
void landOntheOtherSide() {
    polygon({ {0, 400}, {500, 400}, {550, 425}, {1150, 425}, {1200, 450}, {1920, 475}, {1920, 515}, {0, 515} }, {92, 83, 72});
}
void landOntheOtherSideNight() {
    polygon({ {0, 400}, {500, 400}, {550, 425}, {1150, 425}, {1200, 450}, {1920, 475}, {1920, 515}, {0, 515} }, {90, 89, 145});
}
void river() {
    glBegin(GL_POLYGON);
        glColor3ub(66, 162, 179);
        glVertex2f(0, 275);
        glVertex2f(1920, 275);
        glColor3ub(171, 203, 209);
        glVertex2f(1920, 475);
        glVertex2f(0, 475);
    glEnd();
    // polygon({ {0, 275}, {1920, 275}, {1920, 475}, {0, 475} }, {207,233,240});
}
void river2() {
    //polygon({ {700, 275},{750, 200}, {850, 150},{900,50}, {1000 , 0},{1150,0},{1050,50},{950,150},{900,200} ,{900,225},{940,260},{1300, 275}, {0, 275} }, {207,233,240});
    glBegin(GL_POLYGON);
        glColor3ub(66, 162, 179);
        glVertex2f(700, 275);
        glVertex2f(750, 200);
        glVertex2f(850, 150);

        glVertex2f(900,50);
        glVertex2f(1000 , 0);
        glVertex2f(1150,0);
        glVertex2f(1050,50);

        glVertex2f(950,150);
        glVertex2f(900,200);

        glVertex2f(900,225);
        glVertex2f(940,260);
        glVertex2f(1300, 275);
        glVertex2f(0, 275);


    glEnd();
}
void banyanTree(float Tx, float Ty, float s = 1, Color t = {0, 0, 0}, Color treeBase = {70, 38, 17}) {
    int x = Tx, y = Ty;
    circle(100, 200, 30, 30, {t.r, t.g, t.b});
    circle(70, 215, 30, 30, {t.r, t.g, t.b});
    circle(40, 240, 30, 30, {t.r, t.g, t.b});
    circle(30, 270, 40, 35, {t.r, t.g, t.b});
    circle(40, 290, 40, 35, {t.r, t.g, t.b});
    circle(50, 320, 40, 35, {t.r, t.g, t.b});
    circle(85, 350, 40, 35, {t.r, t.g, t.b});
    circle(120, 355, 40, 45, {t.r, t.g, t.b});
    circle(170, 350, 40, 45, {t.r, t.g, t.b});
    circle(200, 320, 40, 45, {t.r, t.g, t.b});
    circle(220, 280, 40, 25, {t.r, t.g, t.b});
    circle(200, 250, 40, 30, {t.r, t.g, t.b});
    circle(180, 210, 40, 30, {t.r, t.g, t.b});
    circle(150, 210, 30, 50, {t.r, t.g, t.b});

    circle(120, 280, 70, 70, {t.r, t.g, t.b});


    triangle({{Tx + s * 4.59, Ty + s * -0.03}, {Tx + s * -0.71, Ty + s * 219.82}, {Tx + s * -10.07, Ty + s * 0.02}, {Tx + s * -0.89, Ty + s * 46.87}, {Tx + s * -25.93, Ty + s * 98.64}, {Tx + s * -0.89, Ty + s * 61.32}, {Tx + s * -0.71, Ty + s * 64.41}, {Tx + s * 16.71, Ty + s * 100.43}, {Tx + s * -0.71, Ty + s * 74.46}, {Tx + s * -0.71, Ty + s * 86.87}, {Tx + s * 16.71, Ty + s * 122.89}, {Tx + s * -0.89, Ty + s * 96.67}, {Tx + s * -0.89, Ty + s * 109.64}, {Tx + s * -18.48, Ty + s * 146.01}, {Tx + s * -0.89, Ty + s * 119.79}, {Tx + s * -0.71, Ty + s * 148.71}, {Tx + s * 11.97, Ty + s * 175.2}, {Tx + s * -0.71, Ty + s * 156.29}, {Tx + s * -0.89, Ty + s * 169.09}, {Tx + s * -12.39, Ty + s * 192.88}, {Tx + s * -0.89, Ty + s * 175.73}, {Tx + s * -0.89, Ty + s * 132.44}, {Tx + s * -12.39, Ty + s * 156.22}, {Tx + s * -0.71, Ty + s * 138.82}}, treeBase);

}


void house1(float x, float y, int m = 1, Color houseWallShadowed = {15, 151, 161}, Color houseWallSide = {255, 254, 255}, Color houseRoof = {255, 201, 84}, Color houseWindows = {24, 105, 126})
{
    polygon({{x + m * 0, y + 0}, {x + m * 40.07, y + 0}, {x + m * 40.14, y + 26.27}, {x + m * 19.84, y + 48.1}, {x + m * -0.04, y + 26.06}}, houseWallShadowed);

    //sidewall
    quad({{x + m * 40.07, y + 0}, {x + m * 141.26, y + 0}, {x + m * 141.06, y + 26.27}, {x + m * 40.14, y + 26.27}}, houseWallSide);

    //roof
    quad({{x + m * 19.84, y + 48.1}, {x + m * 40.14, y + 26.27}, {x + m * 141.06, y + 26.27}, {x + m * 121.52, y + 48.26}}, houseRoof);

    //window
    quad({{x + m * 6.65, y + 7.08}, {x + m * 10.83, y + 7.08}, {x + m * 10.83, y + 19.13}, {x + m * 6.65, y + 19.13}, {x + m * 17.82, y + 7.15}, {x + m * 22, y + 7.15}, {x + m * 22, y + 19.2}, {x + m * 17.82, y + 19.2}, {x + m * 29.36, y + 6.98}, {x + m * 33.54, y + 6.98}, {x + m * 33.54, y + 19.03}, {x + m * 29.36, y + 19.03}, {x + m * 46.23, y + 14.96}, {x + m * 50.83, y + 14.96}, {x + m * 50.83, y + 19.01}, {x + m * 46.23, y + 19.01}, {x + m * 60.35, y + 15.09}, {x + m * 64.94, y + 15.09}, {x + m * 64.94, y + 19.13}, {x + m * 60.35, y + 19.13}, {x + m * 74.39, y + 14.88}, {x + m * 78.99, y + 14.88}, {x + m * 78.99, y + 18.92}, {x + m * 74.39, y + 18.92}, {x + m * 88.43, y + 14.88}, {x + m * 93.03, y + 14.88}, {x + m * 93.03, y + 18.92}, {x + m * 88.43, y + 18.92}, {x + m * 102.53, y + 15.09}, {x + m * 107.12, y + 15.09}, {x + m * 107.12, y + 19.13}, {x + m * 102.53, y + 19.13}, {x + m * 116.46, y + 14.91}, {x + m * 121.06, y + 14.91}, {x + m * 121.06, y + 18.96}, {x + m * 116.46, y + 18.96}, {x + m * 130.73, y + 14.91}, {x + m * 135.33, y + 14.91}, {x + m * 135.33, y + 18.95}, {x + m * 130.73, y + 18.95}}, houseWindows);
}
void house2(float x, float y, int m = 1, Color houseWallShawdowed = {20, 147, 166}, Color houseWallSide = {255, 254, 255}, Color houseRoof = {255, 197, 77}, Color houseWindows = {17, 97, 124}, Color houseDoor = {20, 93, 128})
{
    //polygon
    polygon({{x + m * 0, y + 0}, {x + m * 40.34, y + 0}, {x + m * 40.34, y + 51.78}, {x + m * 19.91, y + 74.55}, {x + m * 0.26, y + 52.67}}, houseWallShawdowed);

    //side wall
    quad({{x + m * 40.34, y + 0}, {x + m * 101.25, y + 0}, {x + m * 101.22, y + 52.29}, {x + m * 40.34, y + 51.78}}, houseWallSide);

    //roof
    quad({{x + m * 19.91, y + 74.55}, {x + m * 40.34, y + 51.78}, {x + m * 101.22, y + 52.29}, {x + m * 81.25, y + 74.62}}, houseRoof);

    //windows
    quad({{x + m * 5.71, y + 33.74}, {x + m * 15.4, y + 33.74}, {x + m * 15.4, y + 45.7}, {x + m * 5.71, y + 45.7}, {x + m * 24.99, y + 33.5}, {x + m * 34.68, y + 33.5}, {x + m * 34.68, y + 45.46}, {x + m * 24.99, y + 45.46}, {x + m * 5.78, y + 10.08}, {x + m * 15.47, y + 10.08}, {x + m * 15.47, y + 22.04}, {x + m * 5.78, y + 22.04}, {x + m * 24.81, y + 10.08}, {x + m * 34.5, y + 10.08}, {x + m * 34.5, y + 22.04}, {x + m * 24.81, y + 22.04}}, houseWindows);

    quad({{x + m * 46.73, y + 9.84}, {x + m * 56.41, y + 9.84}, {x + m * 56.41, y + 21.8}, {x + m * 46.73, y + 21.8}, {x + m * 46.73, y + 33.65}, {x + m * 56.58, y + 33.65}, {x + m * 56.58, y + 45.61}, {x + m * 46.9, y + 45.61}, {x + m * 65.8, y + 33.41}, {x + m * 75.55, y + 33.41}, {x + m * 75.55, y + 45.37}, {x + m * 65.87, y + 45.37}, {x + m * 84.75, y + 33.29}, {x + m * 94.44, y + 33.29}, {x + m * 94.44, y + 45.25}, {x + m * 84.75, y + 45.25}, {x + m * 84.88, y + 10.09}, {x + m * 94.56, y + 10.09}, {x + m * 94.56, y + 22.05}, {x + m * 84.88, y + 22.05}}, houseWindows);

    //door
    quad({{x + m * 65.8, y + 0.08}, {x + m * 75.48, y + 0.11}, {x + m * 75.48, y + 21.85}, {x + m * 65.8, y + 21.85}}, houseDoor);

    //chimney left
    quad({{x + m * 44.27, y + 66.72}, {x + m * 48.7, y + 61.97}, {x + m * 48.7, y + 78.82}, {x + m * 44.27, y + 78.82}}, currentScene.houseWallSide);

    //chimney front
    quad({{x + m * 48.7, y + 61.97}, {x + m * 55.23, y + 61.97}, {x + m * 55.23, y + 78.8}, {x + m * 48.7, y + 78.82}}, currentScene.houseWallShadowed);
}
void nearGround() {
    polygon({ {0, 0}, {1920, 0}, {1920, 275}, {0, 275} }, {130, 117, 101});
}
void nearGroundNight() {
    polygon({ {0, 0}, {1920, 0}, {1920, 275}, {0, 275} }, {90, 89, 145});
}
void display()
{
    //sky
    glBegin(GL_QUADS);
    glColor3ub(currentScene.skyBottom.r, currentScene.skyBottom.g, currentScene.skyBottom.b);
    glVertex2f(0, 660);
    glVertex2f(1920, 660);
    glColor3ub(currentScene.skyTop.r, currentScene.skyTop.g, currentScene.skyTop.b);
    glVertex2f(1920, 1080);
    glVertex2f(0, 1080);
    glEnd();

    if (currentScene.scene == "night") {
        circle(1200, 900, 50, 50, {166, 137, 36}); //moon
    }


    if (currentScene.scene == "day") {
        circle(1169, 715, 100, 100, {255, 196, 62}); //sun
        landOntheOtherSide();
        nearGround();
    }

    rearMountain();
    frontMountain();

    cloud1(cloudX, 950, 1);
    cloud2(cloud2X, 900, 1);
    cloud3(cloud3X, 850, 1);
    cloud3(cloud4X, 800, 1);

    river();
    river2();
    landOntheOtherSide();
    if (currentScene.scene == "night") {
        //circle(1200, 900, 50, 50, {166, 137, 36}); //moon
        landOntheOtherSideNight();
        nearGroundNight();
    }

    house1(1190, 457, 1, currentScene.houseWallShadowed, currentScene.houseWallSide, currentScene.houseRoof, currentScene.houseWindows);

    house2(1045, 435, 1, currentScene.houseWallShadowed, currentScene.houseWallSide, currentScene.houseRoof, currentScene.houseWindows, currentScene.houseDoor);

    house2(395, 410, 1, currentScene.houseWallShadowed, currentScene.houseWallSide, currentScene.houseRoof, currentScene.houseWindows, currentScene.houseDoor);

    house1(670, 420, -1, currentScene.houseWallShadowed, currentScene.houseWallSide, currentScene.houseRoof, currentScene.houseWindows);
    windMill(280, 410, currentScene.houseWallSide, currentScene.houseRoof, currentScene.houseWindows, currentScene.houseDoor);

    tree(30, 475, 0.4, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(60, 495, 0.4, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(90, 480, 0.4, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(120, 500, 0.3, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(150, 490, 0.4, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(180, 470, 0.4, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(210, 482, 0.4, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(230, 493, 0.3, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(50, 450, 0.4, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(80, 460, 0.4, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(110, 475, 0.4, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(130, 475, 0.4, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(0, 475, 0.4, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(20, 430, 0.4, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(40, 415, 0.4, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(60, 440, 0.4, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(100, 430, 0.4, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(120, 410, 0.4, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);

    if(currentScene.scene!="snow")
        boat(boatX, 300, factor, currentScene.boatSails, currentScene.boatMast, currentScene.boatBody);


    tent(1220, 100);
    tent( 610,150, -1);


    tree(1775, 155, 0.9, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1700, 155, 0.9, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1730, 55, 1, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1790, 55, 0.9, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1840, 25, 1.1, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1660, 25, 1.1, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1600, 25, 1.1, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1480, 25, .8, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1525, 5, .8, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1725, 15, 1, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    if (currentScene.scene == "night") {
        banyanTree(125, 90, 1, {66, 58, 162});
    }else {
        banyanTree(125, 90, 1, {16, 94, 38});
    }
    river2();

    glutSwapBuffers();
}

void idle()
{
    float frameTime = 1000 / 60.0, currentTime = GetTickCount();
    if (currentTime - lastFrameTime >= frameTime)
    {
        lastFrameTime = currentTime;
        cloudX += 0.5;
        cloud2X += 0.8;
        cloud3X += 1.2;
        cloud4X += 0.7;
        if (cloudX > 1920)
        {
            cloudX = -60*3*0.5;
        }
        if(cloud2X>1920) cloud2X = -60*3*0.8;
        if(cloud3X>1920) cloud3X = -60*3*1.2;
        if(cloud4X>1920) cloud4X = -60*3*0.7;

        boatX += 3.5 * factor;
        if (boatX > 1920 + 60 * 4 * 1.5)
        {
            factor = -1;
        }
        if (boatX < -60 * 4 * 2)
        {
            factor = 1;
        }

        angle += 3;
    }

    glutPostRedisplay();
}

void keyboard(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_RIGHT:
        if(currentScene.scene == "day") {
            currentScene = night;
        }else {
            currentScene = day;
        }
        glutPostRedisplay();
        break;
    default:
        break;
    }
}

void init(void)
{
    glClearColor(0.0F, 0.0F, 0.0F, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1920, 0, 1080, -100, 100);
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_MULTISAMPLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1920, 1080);
    glutCreateWindow("Mountain View");
    glutSpecialFunc(keyboard);
    init();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
}
