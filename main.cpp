#include "raylib.h"

struct Animdata
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool isOnGround(Animdata data, int windowHeight)
{
    return data.pos.y >= windowHeight - data.rec.height;
}

Animdata updateAnimData(Animdata data, float deltaTime, int MaxFrame)
{
    // update running time
    data.runningTime += deltaTime;

    if (data.runningTime >= data.updateTime)
    {
        data.runningTime = 0.0;
        // update animation time
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if (data.frame > MaxFrame)
        {
            data.frame = 0;
        }
    }
    return data;
}

int main()
{ // Window dimensions
    const int windowWidth{518};
    const int windowHeight{380};

    // initialize the window
    InitWindow(windowWidth, windowHeight, "Dapper Dasher");

    const int gravity{1000};

    // nebula varables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    // AnimData for nebula
    const int sizeOfNebulae{6};
    Animdata nebulae[sizeOfNebulae]{};

    for (int i = 0; i < sizeOfNebulae; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width / 8;
        nebulae[i].rec.height = nebula.height / 8;
        nebulae[i].pos.y = windowHeight - nebula.height / 8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 1.0 / 16.0;
        nebulae[i].pos.x = windowWidth + i * 300;
    }

    float finshingLine{nebulae[sizeOfNebulae - 1].pos.x};
    // nebula x velocity(pixels/sec)
    int nebvel{-200};

    // scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Animdata scarfyData;
    scarfyData.rec.width = scarfy.width / 6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowHeight / 2 - scarfyData.rec.width / 2;
    scarfyData.pos.y = windowHeight - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0 / 12.0;
    scarfyData.runningTime = 0.0;

    int velocity{0};

    // is rectangle in air?
    bool isInAir{};

    // jump velocity
    const int jumpvel{-600};
    Texture2D background = LoadTexture("textures/far-buildings.png");
    float bgX{};
    Texture2D midground = LoadTexture("textures/back-buildings.png");
    float mgx{};
    Texture2D foreground = LoadTexture("textures/foreground.png");
    float fgx{};

    bool collision{};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // delta time(time since last frame)
        const float dt{GetFrameTime()};

        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // Scroll background
        bgX -= 20 * dt;

        if (bgX <= -background.width * 2)
        {
            bgX = 0;
        }

        // Scroll midground
        mgx -= 40 * dt;

        if (mgx <= -midground.width * 2)
        {
            mgx = 0.0;
        }

        // Scroll foreground
        fgx -= 80 * dt;

        if (fgx <= -foreground.width * 2)
        {
            fgx = 0.0;
        }

        // Draw the background image
        Vector2 bg1Pos{bgX, 0.0};
        DrawTextureEx(background, bg1Pos, 0.0, 2.0, WHITE);
        Vector2 bg2Pos{bgX + background.width * 2, 0.0};
        DrawTextureEx(background, bg2Pos, 0.0, 2.0, WHITE);

        // Draw the midground image
        Vector2 mg1Pos{mgx, 0.0};
        DrawTextureEx(midground, mg1Pos, 0.0, 2.0, WHITE);
        Vector2 mg2Pos{mgx + midground.width * 2, 0.0};
        DrawTextureEx(midground, mg2Pos, 0.0, 2.0, WHITE);

        // Draw the foreground
        Vector2 fg1Pos{fgx, 0.0};
        DrawTextureEx(foreground, fg1Pos, 0.0, 2.0, WHITE);
        Vector2 fg2Pos{fgx + foreground.width * 2, 0.0};
        DrawTextureEx(foreground, fg2Pos, 0.0, 2.0, WHITE);

        if (isOnGround(scarfyData, windowHeight))
        {
            // rectangle is on the ground
            velocity = 0;
            isInAir = false;
        }
        else
        {
            // rectangle is in air
            velocity += gravity * dt;
            isInAir = true;
        }

        if (IsKeyPressed(KEY_SPACE) == true && !isInAir)
        {
            velocity += jumpvel;
        }

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            // update nebula position
            nebulae[i].pos.x += nebvel * dt;
        }

        // update scarfy position
        scarfyData.pos.y += velocity * dt;

        if (!isInAir)
        {
            scarfyData = updateAnimData(scarfyData, dt, 5);
        }

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            nebulae[i] = updateAnimData(nebulae[i], dt, 7);
        }

        // update finish line
        finshingLine += nebvel * dt;

        for (Animdata nebula : nebulae)
        {
            float pad{50};
            Rectangle nebRec{
                nebula.pos.x + pad,
                nebula.pos.y + pad,
                nebula.rec.width - 2 * pad,
                nebula.rec.height - 2 * pad,
            };
            Rectangle scarfyrec{
                scarfyData.pos.x,
                scarfyData.pos.y,
                scarfyData.rec.width,
                scarfyData.rec.height};

            if (CheckCollisionRecs(nebRec, scarfyrec))
            {
                collision = true;
            }
        }

        if (collision)
        {
            // Lose the game
            DrawText("GameOver!", windowWidth / 4, windowHeight / 2, 40, BLUE);
        }
        else if (scarfyData.pos.x >= finshingLine)
        {
            DrawText("YouWin!", windowWidth / 4, windowHeight / 2, 40, BLUE);
        }
        else
        {

            for (int i = 0; i < sizeOfNebulae; i++)
            {
                // Draw nebula
                DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
            }

            // Draw scarfy
            DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
        }

        // end drawing
        EndDrawing();
    }
    UnloadTexture(nebula);
    UnloadTexture(scarfy);
    UnloadTexture(background);
    UnloadTexture(foreground);
    UnloadTexture(midground);

    CloseWindow();
}