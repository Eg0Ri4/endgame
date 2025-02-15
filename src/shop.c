#include "includs.h"

// Collision

bool CheckGoldCubeCollision(Ray ray, Vector3 cubePos, float cubeSize) {
    BoundingBox cubeBox = {
        (Vector3){ cubePos.x - cubeSize/2, cubePos.y - cubeSize/2, cubePos.z - cubeSize/2 },
        (Vector3){ cubePos.x + cubeSize/2, cubePos.y + cubeSize/2, cubePos.z + cubeSize/2 }
    };

    float tmin = (cubeBox.min.x - ray.position.x) / ray.direction.x;
    float tmax = (cubeBox.max.x - ray.position.x) / ray.direction.x;
    if (tmin > tmax) { float temp = tmin; tmin = tmax; tmax = temp; }

    float tymin = (cubeBox.min.y - ray.position.y) / ray.direction.y;
    float tymax = (cubeBox.max.y - ray.position.y) / ray.direction.y;
    if (tymin > tymax) { float temp = tymin; tymin = tymax; tymax = temp; }
    if ((tmin > tymax) || (tymin > tmax)) return false;
    if (tymin > tmin) tmin = tymin;
    if (tymax < tmax) tmax = tymax;

    float tzmin = (cubeBox.min.z - ray.position.z) / ray.direction.z;
    float tzmax = (cubeBox.max.z - ray.position.z) / ray.direction.z;
    if (tzmin > tzmax) { float temp = tzmin; tzmin = tzmax; tzmax = temp; }
    if ((tmin > tzmax) || (tzmin > tmax)) return false;

    return true;
}

void DrawGoldCube(Vector3 cubePos, float cubeSize) {
    (void)cubePos;
    (void)cubeSize;
}

void RenderShopSidebar(Font interFont, int screenWidth, int screenHeight, 
                       int* money, int* wallHP, int maxWallHP, 
                       int* defenderLevel, int maxDefenderLevel,
                       Tower **towers, int *towerCount)
{
    int sidebarWidth    = 320;
    int sidebarHeight   = 420;
    int headerHeight    = 50;
    int buttonHeight    = 60;   
    int buttonWidth     = 300;
    float fontSize      = 24.0f;
    float letterSpacing = 3.0f; 
    float labelPriceGap = 120.0f; 

    // sidebar
    int sidebarX = screenWidth - sidebarWidth;
    int sidebarY = (screenHeight - sidebarHeight) / 2;

    Color sideBarColor    = (Color){  20,  20,  20, 220 };
    Color sideBarHeaderBg = (Color){  40,  40,  40, 255 };
    Color textWhite       = RAYWHITE;
    Color goldColor       = (Color){ 255, 215,   0, 255 };
    Color buttonBgColor   = DARKGRAY;  
    Color textGreen       = GREEN;
    Color textRed         = RED;

    DrawRectangle(sidebarX, sidebarY, sidebarWidth, sidebarHeight, sideBarColor);
    DrawRectangle(sidebarX, sidebarY, sidebarWidth, headerHeight, sideBarHeaderBg);
    DrawTextEx(
        interFont,
        "SHOP",
        (Vector2){ (float)(sidebarX + 20), (float)(sidebarY + 10) },
        28,  
        letterSpacing,
        textWhite
    );

    DrawTextEx(
        interFont,
        TextFormat("Money: %d", *money),
        (Vector2){ (float)(sidebarX + 20), (float)(sidebarY + 70) },
        fontSize,
        letterSpacing,
        goldColor
    );

    {
        Rectangle upgradeWallRect = {
            (float)(sidebarX + 10),
            (float)(sidebarY + 120),
            (float)buttonWidth,
            (float)buttonHeight
        };
        DrawRectangleRec(upgradeWallRect, buttonBgColor);

        const char* upgradeWallLabel = "Add Defender";
        const char* upgradeWallPrice = " -300$";

        Vector2 labelPos = {
            upgradeWallRect.x + 10,
            upgradeWallRect.y + (buttonHeight - fontSize) / 2
        };
        DrawTextEx(interFont, upgradeWallLabel, labelPos, fontSize, letterSpacing, textGreen);

        Vector2 labelSize = MeasureTextEx(interFont, upgradeWallLabel, fontSize, letterSpacing);
        Vector2 pricePos = {
            labelPos.x + 47.0f + labelSize.x + labelPriceGap,
            labelPos.y
        };
        DrawTextEx(interFont, upgradeWallPrice, pricePos, fontSize, letterSpacing, textRed);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Vector2 mPos = GetMousePosition();
            if (CheckCollisionPointRec(mPos, upgradeWallRect))
            {
                if (*money >= 300)
                {
                    *money -= 300;
                    *wallHP += 2000;
                    AddTower(towers, towerCount, (Vector3){*towerCount*2-34 + ((*towerCount*2-34 >= -15)? 16: 0),  6.5f, 16.0f });
                    
                    if (*wallHP > maxWallHP) *wallHP = maxWallHP;
                }
            }
        }
    }

    DrawTextEx(
        interFont,
        TextFormat("Defender Level: %d", *defenderLevel),
        (Vector2){ (float)(sidebarX + 20), (float)(sidebarY + 200) },
        fontSize,
        letterSpacing,
        textWhite
    );

    {
        Rectangle upgradeDefRect = {
            (float)(sidebarX + 10),
            (float)(sidebarY + 240),
            (float)buttonWidth,
            (float)buttonHeight
        };
        DrawRectangleRec(upgradeDefRect, buttonBgColor);

        const char* upgradeDefLabel = "Upgrade";
        const char* upgradeDefPrice = " -2000$";

        Vector2 labelPos = {
            upgradeDefRect.x + 10,
            upgradeDefRect.y + (buttonHeight - fontSize) / 2
        };
        DrawTextEx(interFont, upgradeDefLabel, labelPos, fontSize, letterSpacing, textGreen);

        Vector2 labelSize = MeasureTextEx(interFont, upgradeDefLabel, fontSize, letterSpacing);
        Vector2 pricePos = {
            labelPos.x + 55.0f + labelSize.x + labelPriceGap,
            labelPos.y
        };
        DrawTextEx(interFont, upgradeDefPrice, pricePos, fontSize, letterSpacing, textRed);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Vector2 mPos = GetMousePosition();
            if (CheckCollisionPointRec(mPos, upgradeDefRect))
            {
                if ((*money >= 2000 && *defenderLevel < MAX_SHOOTERS) || *defenderLevel <= maxDefenderLevel)
                {
                    *money -= 2000;
                    (*defenderLevel)++;
                
            }
        }
    }

    // --- FIX WALL BUTTON (New) ---
    {
        Rectangle fixWallRect = {
            (float)(sidebarX + 10),
            (float)(sidebarY + 320),  // Below the "Add Defender" button
            (float)buttonWidth,
            (float)buttonHeight
        };
        DrawRectangleRec(fixWallRect, buttonBgColor);

        const char* fixWallLabel = "Fix Wall";
        const char* fixWallPrice = " -100$";

        Vector2 labelPos = {
            fixWallRect.x + 10,
            fixWallRect.y + (buttonHeight - fontSize) / 2
        };
        DrawTextEx(interFont, fixWallLabel, labelPos, fontSize, letterSpacing, textGreen);

        Vector2 labelSize = MeasureTextEx(interFont, fixWallLabel, fontSize, letterSpacing);
        Vector2 pricePos = {
            labelPos.x  -18.0f + labelSize.x + labelPriceGap,
            labelPos.y
        };
        DrawTextEx(interFont, fixWallPrice, pricePos, fontSize, letterSpacing, textRed);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Vector2 mPos = GetMousePosition();
            if (CheckCollisionPointRec(mPos, fixWallRect))
            {
                if (*money >= 100)
                {
                    *money -= 100;
                    wall.health += 500;
                    wallDestroyed = 1;
                    if (wall.health > maxWallHP) wall.health = maxWallHP;
                }
            }
        }
    }
}
}
