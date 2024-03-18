/*
build with
g++ chicken_game.cpp -Iraylib-5.0_linux_amd64/include/ raylib-5.0_linux_amd64/lib/libraylib.a
*/
#include "raylib.h"

#include <iostream>
#include <string>
using std::cout;

#define DEBUG_CHEATS 1

#if DEBUG_CHEATS
void printVector2(Vector2 v)
{
    cout << "x=" <<v.x << " y="<<v.y << "\n";
}
#endif

int score = 0;
    bool got_food = false;
    float timeout = 4.0f; //seconds
    int speech_x = 0;
    int speech_y = 0;
    float speech_lifetime = 4.0f;
std::string speech{"cheep!"};

const int PLAYER_CHICK = 1;
const int PLAYER_CHICKEN = 2;
const int PLAYER_ROOSTER = 3;
int PLAYER_MODEL = PLAYER_CHICK;

const float CHICK_SPEED = 300.0f;
const float CHICKEN_SPEED = 200.0f;
float MOVE_SPEED = 300.0f;

const float CHICK_SIZE = 22.0f;
float character_size = CHICK_SIZE;

float x = 100.0f;
float y = 100.0f;

float break_recess = 4.0f;
float beak_len_factor = 1.4f;
Vector2 beak1{x+character_size-break_recess, y+character_size/2.0f};
Vector2 beak2{x+character_size*beak_len_factor, y};
Vector2 beak3{x+character_size-break_recess, y-character_size/2.0f};

Vector2 eye{x + 8.0f, y - 12.0f};
Vector2 eye2{x + 8.0f, y + 12.0f};

void draw_character(int state)
{
    switch (state)
    {
    case PLAYER_CHICK:
        character_size = CHICK_SIZE;
        MOVE_SPEED = CHICK_SPEED;
        //DrawCircle(x, y, character_size, GOLD);
        DrawCircleGradient(x, y, character_size, YELLOW, GOLD);
        
        break;
    case PLAYER_CHICKEN:
        //character_size = 40.0f;
        MOVE_SPEED = CHICKEN_SPEED;
        //DrawCircle(x, y, 40.0f, CLITERAL(Color){ 235, 235, 235, 255 });
        DrawCircleGradient(x, y, 40.0f, WHITE, CLITERAL(Color){ 220, 220, 220, 255 });
        break;
    default:
        break;
    }

    if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) 
    {
        beak1.x = x-character_size+break_recess;
        beak1.y = y-character_size/2.0f;
        beak2.x = x-character_size*beak_len_factor;
        beak2.y = y;
        beak3.x = x-character_size+break_recess;
        beak3.y = y+character_size/2.0f;

        eye.x = x - 8.0f;
        eye.y = y - 12.0f;
        eye2.x = x - 8.0f;
        eye2.y = y + 12.0f;
    }
    else if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
    {
        beak1.x = x-character_size/2.0f;
        beak1.y = y+character_size-break_recess;
        beak2.x = x;
        beak2.y = y+character_size*beak_len_factor;
        beak3.x = x+character_size/2.0f;
        beak3.y = y+character_size-break_recess;

        eye.x = x - 12.0f;
        eye.y = y + 8.0f;
        eye2.x = x + 12.0f;
        eye2.y = y + 8.0f;
    }
    else if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
    {
        beak1.x = x+character_size-break_recess;
        beak1.y = y+character_size/2.0f;
        beak2.x = x+character_size*beak_len_factor;
        beak2.y = y;
        beak3.x = x+character_size-break_recess;
        beak3.y = y-character_size/2.0f;

        eye.x = x + 8.0f;
        eye.y = y - 12.0f;
        eye2.x = x + 8.0f;
        eye2.y = y + 12.0f;
    }
    else if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
    {
        beak1.x = x+character_size/2.0f;
        beak1.y = y-character_size+break_recess;
        beak2.x = x;
        beak2.y = y-character_size*beak_len_factor;
        beak3.x = x-character_size/2.0f;
        beak3.y = y-character_size+break_recess;

        eye.x = x - 12.0f;
        eye.y = y - 8.0f;
        eye2.x = x + 12.0f;
        eye2.y = y - 8.0f;
    }
    DrawTriangle(beak1, beak2, beak3, ORANGE);
    DrawCircleV(eye, 2.0f, BLACK);
    DrawCircleV(eye2, 2.0f, BLACK);
}

class Food
{
public:
    Rectangle r;
    CLITERAL(Color) c; // primary color
    CLITERAL(Color) c2; // shading color for gradients
};

Food grain;


void draw_food()
{
    //DrawRectangleRec(grain.r, grain.c);
    DrawRectangleGradientV(grain.r.x, grain.r.y, grain.r.width, grain.r.height, grain.c, grain.c2);

    //Image perlinNoise = GenImagePerlinNoise(screenWidth, screenHeight, 50, 50, 4.0f);
    //Texture2D texture = LoadTextureFromImage(perlinNoise);
    //UnloadImage(perlinNoise);
    //DrawTexture(textures[currentTexture], 0, 0, WHITE); // do this here
    //UnloadTexture(texture); // do this before CloseWindow()
}

void update_game_state()
{
    if(score == 6)
    {
        PLAYER_MODEL = PLAYER_CHICKEN;
        character_size = 40.0f;
        speech = std::string("Cluck!");
    }
    // player boundry collision
    if((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) && x + (character_size*beak_len_factor) < GetScreenWidth()) x += MOVE_SPEED * GetFrameTime();
    if((IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) && x - (character_size*beak_len_factor) >= 0) x -= MOVE_SPEED * GetFrameTime();
    if((IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) && y + (character_size*beak_len_factor) < GetScreenHeight()) y += MOVE_SPEED * GetFrameTime();
    if((IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) && y - (character_size*beak_len_factor) >= 0) y -= MOVE_SPEED * GetFrameTime();

    // object collision calculations
    if(CheckCollisionRecs({x, y, character_size, character_size}, grain.r))
    // if(CheckCollisionRecs({x-(character_size*beak_len_factor),y-(character_size*beak_len_factor),x+character_size,y+character_size}, grain.r))
    {
        got_food = true;      
        speech_x = x-character_size;
        speech_y = y-character_size*2;
        score += 1;
        //(Vector2){ GetRandomValue(0, (screenWidth/SQUARE_SIZE) - 1)*SQUARE_SIZE + offset.x/2, GetRandomValue(0, (screenHeight/SQUARE_SIZE) - 1)*SQUARE_SIZE + offset.y/2 };
        grain.r.x = GetRandomValue(0, GetScreenWidth() - grain.r.width);
        grain.r.y = GetRandomValue(0, GetScreenHeight() - grain.r.height);
    }

    
}

void draw_game()
{
    BeginDrawing();
    ClearBackground(DARKGREEN);

    draw_character(PLAYER_MODEL);
    draw_food();
    // TODO: fade out speech text
    if(got_food && timeout-GetFrameTime() > 0)
    {
        // TODO: check if text will be within window bounds and not obstructing other elements
        DrawText(speech.c_str(), speech_x, speech_y, 20, LIGHTGRAY);
    }
    else
    {
        got_food = false;
        speech_x = 0;
        speech_y = 0;
    }
    DrawText(std::string("Score: " + std::to_string(score)).c_str(), 10, 10, 20, LIGHTGRAY);
    EndDrawing();
}

int main(void)
{
    std::string window_title{"What the Cluck"};
    InitWindow(1000, 650, window_title.c_str());
    //SetWindowState(FLAG_WINDOW_RESIZABLE);

    
    // initialize data
    grain.r.x = (float)GetScreenWidth()/2.0f;
    grain.r.y = (float)GetScreenHeight()/2.0f;
    grain.r.width = 40.0f;
    grain.r.height = 40.0f;
    grain.c = BEIGE;
    grain.c2 = BROWN;

    
    
    SetTargetFPS(60);
    // main game loop
    while (!WindowShouldClose())
    {
        // update game state
        update_game_state();
        
        // debug helpers
        #if DEBUG_CHEATS
        if(IsKeyPressed('1'))
            PLAYER_MODEL = PLAYER_CHICK;
        else if (IsKeyPressed('2'))
            PLAYER_MODEL = PLAYER_CHICKEN;
        #endif

        // draw the game
        draw_game();
    }

    CloseWindow();

    return 0;
}
