/*
build with
g++ chicken_game.cpp -Iraylib-5.0_linux_amd64/include/ raylib-5.0_linux_amd64/lib/libraylib.a
*/
#include "raylib.h"

#include <iostream>
#include <string>
using std::cout;

#define DEBUG_CHEATS 1
#define DEBUG_VISUAL_HELPERS 0

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
std::string speech{std::string("cheep!")};

const int PLAYER_CHICK = 1;
const int PLAYER_CHICKEN = 2;
const int PLAYER_ROOSTER = 3;
int PLAYER_MODEL = PLAYER_CHICK;

const float CHICK_SPEED = 300.0f;
const float CHICKEN_SPEED = 200.0f;
float MOVE_SPEED = 300.0f;

const float CHICK_SIZE = 22.0f;
const float CHICKEN_SIZE = 40.0f;
float character_size = CHICK_SIZE;

const Color CHICK_PRIMARY_COLOR{YELLOW};
const Color CHICK_SECONDARY_COLOR{GOLD};
const Color CHICKEN_PRIMARY_COLOR{WHITE};
const Color CHICKEN_SECONDARY_COLOR{220, 220, 220, 255};
Color player_primary_color{CHICK_PRIMARY_COLOR};
Color player_secondary_color{CHICK_SECONDARY_COLOR};

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
    // Set values for Chick
    case PLAYER_CHICK:
        character_size = CHICK_SIZE;
        MOVE_SPEED = CHICK_SPEED;
        speech = std::string("cheep!");
        player_primary_color = CHICK_PRIMARY_COLOR;
        player_secondary_color = CHICK_SECONDARY_COLOR;
        break;
    // Set values for Chicken
    case PLAYER_CHICKEN:
        character_size = CHICKEN_SIZE;
        MOVE_SPEED = CHICKEN_SPEED;
        speech = std::string("Cluck!");
        player_primary_color = CHICKEN_PRIMARY_COLOR;
        player_secondary_color = CHICKEN_SECONDARY_COLOR;
        break;
    default:
        break;
    }
    DrawCircleGradient(x, y, character_size, player_primary_color, player_secondary_color);

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
    Food()
    {
        r.x = static_cast<float>(GetScreenWidth())/2.0f - width;
        r.y = static_cast<float>(GetScreenHeight())/2.0f - height;
        r.width = width;
        r.height = height;
        c = BEIGE;
        c2 = BROWN;
    }
    void set_new_position(int lower_x, int lower_y, int upper_x, int upper_y)
    {
        // TODO: ensure upper_x and y will not be negative after math
        r.x = GetRandomValue(lower_x, upper_x - static_cast<int>(width));
        r.y = GetRandomValue(lower_y, upper_y - static_cast<int>(height));
    }

    void draw()
    {
        DrawRectangleGradientV(r.x, r.y, r.width, r.height, c, c2);
    }


    Rectangle r;
    CLITERAL(Color) c;//{BEIGE}; // primary color
    CLITERAL(Color) c2;//{BROWN}; // shading color for gradients
private:
    float width{40.0f};
    float height{40.0f};
};



void draw_food(Food& grain)
{
    //Image perlinNoise = GenImagePerlinNoise(screenWidth, screenHeight, 50, 50, 4.0f);
    //Texture2D texture = LoadTextureFromImage(perlinNoise);
    //UnloadImage(perlinNoise);
    //DrawTexture(textures[currentTexture], 0, 0, WHITE); // do this here
    //UnloadTexture(texture); // do this before CloseWindow()
}

void update_game_state(Food& grain)
{
    if(score == 6
    #if DEBUG_CHEATS
    || PLAYER_MODEL == PLAYER_CHICKEN
    #endif
    )
    {
        PLAYER_MODEL = PLAYER_CHICKEN;
    }
    // player boundry collision
    if((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) && x + (character_size*beak_len_factor) < GetScreenWidth()) x += MOVE_SPEED * GetFrameTime();
    if((IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) && x - (character_size*beak_len_factor) >= 0) x -= MOVE_SPEED * GetFrameTime();
    if((IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) && y + (character_size*beak_len_factor) < GetScreenHeight()) y += MOVE_SPEED * GetFrameTime();
    if((IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) && y - (character_size*beak_len_factor) >= 0) y -= MOVE_SPEED * GetFrameTime();

    // object collision calculations
    if(CheckCollisionRecs({x-character_size, y-character_size, character_size*2, character_size*2}, grain.r))
    // if(CheckCollisionRecs({x-(character_size*beak_len_factor),y-(character_size*beak_len_factor),x+character_size,y+character_size}, grain.r))
    {
        got_food = true;      
        speech_x = x-character_size;
        speech_y = y-character_size*2;
        score += 1;
        grain.set_new_position(0, 0, GetScreenWidth(), GetScreenHeight());
    }

    
}

void draw_game(Food& grain)
{
    BeginDrawing();
    ClearBackground(DARKGREEN);

    draw_character(PLAYER_MODEL);
    grain.draw();
    // TODO: fade out speech text
    static int i = 0;
    if(got_food && timeout-GetFrameTime() > 0)
    {
        // TODO: check if text will be within window bounds and not obstructing other elements
        DrawText(speech.c_str(), speech_x, speech_y, 20, {200,200,200,255-10*i});
        timeout -= 0.1f;
        ++i;
    }
    else
    {
        got_food = false;
        speech_x = 0;
        speech_y = 0;
        timeout = speech_lifetime;
    }
    DrawText(std::string("Score: " + std::to_string(score)).c_str(), 10, 10, 20, LIGHTGRAY);

    // show collision boundry
    #if DEBUG_VISUAL_HELPERS
    // show the collision boundry of the player
    DrawRectangleLines(x-character_size, y-character_size, character_size*2, character_size*2, WHITE);
    // show the collision boundry of the food
    DrawRectangleLines(grain.r.x, grain.r.y, grain.r.width, grain.r.height, WHITE);
    #endif


    EndDrawing();
}

int main(void)
{
    std::string window_title{"What the Cluck"};
    InitWindow(1000, 650, window_title.c_str());
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetWindowMinSize(5*CHICK_SIZE*2, 4*CHICK_SIZE*2);

    
    // initialize data
    Food grain{};
    
    SetTargetFPS(60);
    // main game loop
    while (!WindowShouldClose())
    {
        update_game_state(grain);
        
        // debug helpers
        #if DEBUG_CHEATS
        if(IsKeyPressed('1'))
            PLAYER_MODEL = PLAYER_CHICK;
        else if (IsKeyPressed('2'))
            PLAYER_MODEL = PLAYER_CHICKEN;
        #endif

        draw_game(grain);
    }

    CloseWindow();

    return 0;
}
