#include <includs.h>

#define MAX_WALL_HP 2000
#define MAX_DEFENDER_LEVEL 3

const int wallHpUpgradeCost = 200;
const int defenderUpgradeCost = 500;

void DrawShopUI(void) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // Адаптивная кнопка "SHOP"
    int buttonPadding = 20;
    int buttonTextSize = 20;
    int textWidth = MeasureText("SHOP", buttonTextSize);
    int buttonWidth = textWidth + buttonPadding * 2;
    int buttonHeight = 50;

    Rectangle shopButton = { screenWidth - buttonWidth - 10, 10, buttonWidth, buttonHeight };

    // Проверка нажатия на кнопку "SHOP"
    if (CheckCollisionPointRec(GetMousePosition(), shopButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        shopOpen = !shopOpen;
    }

    if (shopOpen) {
        int shopPanelWidth = screenWidth * 0.23f;
        int shopPanelX = screenWidth - shopPanelWidth;
        int textOffsetX = 20;
        int textOffsetY = 20;
        int buttonHeight = 30;

        // Фон магазина
        DrawRectangle(shopPanelX, 0, shopPanelWidth, screenHeight, Fade(DARKGRAY, 0.85f));

        // Заголовок
        DrawText("SHOP", shopPanelX + textOffsetX, textOffsetY, 30, WHITE);
        DrawText(TextFormat("Money: %d", money), shopPanelX + textOffsetX, textOffsetY + 40, 20, GOLD);
        DrawText(TextFormat("Wall HP: %d / %d", wallHP, MAX_WALL_HP), shopPanelX + textOffsetX, textOffsetY + 80, 20, WHITE);

        // Кнопка улучшения стены
        Rectangle upgradeWallButton = { shopPanelX + textOffsetX, textOffsetY + 110, shopPanelWidth - 2 * textOffsetX, buttonHeight };
        Color wallTextColor = (money >= wallHpUpgradeCost) ? GREEN : RED;

        if (CheckCollisionPointRec(GetMousePosition(), upgradeWallButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && money >= wallHpUpgradeCost) {
            wallHP += 200;
            if (wallHP > MAX_WALL_HP) wallHP = MAX_WALL_HP;
            money -= wallHpUpgradeCost;
        }

        DrawText(TextFormat("Upgrade (+200 HP) - %d$", wallHpUpgradeCost), upgradeWallButton.x, upgradeWallButton.y, 20, wallTextColor);

        // Информация об уровне защитника
        DrawText(TextFormat("Defender Level: %d / %d", defenderLevel, MAX_DEFENDER_LEVEL), shopPanelX + textOffsetX, textOffsetY + 150, 20, WHITE);

        // Кнопка улучшения защитника
        Rectangle upgradeDefenderButton = { shopPanelX + textOffsetX, textOffsetY + 180, shopPanelWidth - 2 * textOffsetX, buttonHeight };
        Color defenderTextColor = (money >= defenderUpgradeCost) ? GREEN : RED;

        if (CheckCollisionPointRec(GetMousePosition(), upgradeDefenderButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && money >= defenderUpgradeCost) {
            defenderLevel++;
            money -= defenderUpgradeCost;
        }

        DrawText(TextFormat("Upgrade Defender - %d$", defenderUpgradeCost), upgradeDefenderButton.x, upgradeDefenderButton.y, 20, defenderTextColor);
    }

    // *** Кнопка "SHOP" остаётся сверху ***
    DrawRectangleRec(shopButton, DARKGRAY);
    DrawText("SHOP", shopButton.x + buttonPadding, shopButton.y + (buttonHeight / 2) - (buttonTextSize / 2), buttonTextSize, WHITE);
}

void ToggleShop(void) {
    if (IsKeyPressed(KEY_B)) shopOpen = !shopOpen;
}
