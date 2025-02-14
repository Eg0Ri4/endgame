#include <includs.h>


#define MAX_WALL_HP 2000
#define MAX_DEFENDER_LEVEL 3

const int wallHpUpgradeCost = 200;
const int defenderUpgradeCost = 500;

void DrawShopUI(void) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // Адаптивная кнопка "SHOP" с улучшенным дизайном
    int buttonPadding = 20;
    int buttonTextSize = 26;
    int textWidth = MeasureText("SHOP", buttonTextSize);
    int buttonWidth = textWidth + buttonPadding * 3;
    int buttonHeight = 60;

    Rectangle shopButton = { screenWidth - buttonWidth - 15, 15, buttonWidth, buttonHeight };

    // Проверка нажатия на кнопку "SHOP"
    if (CheckCollisionPointRec(GetMousePosition(), shopButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        shopOpen = !shopOpen;
    }

    if (shopOpen) {
        int shopPanelWidth = screenWidth * 0.25f;
        int shopPanelX = screenWidth - shopPanelWidth;
        int textOffsetX = 20;
        int textOffsetY = 20;
        int buttonHeight = 40;

        // Фон магазина (чёрный с прозрачностью)
        DrawRectangle(shopPanelX, 0, shopPanelWidth, screenHeight, Fade(BLACK, 0.85f));

        // Заголовок
        DrawText("SHOP", shopPanelX + textOffsetX, textOffsetY, 34, WHITE);
        DrawText(TextFormat("Money: %d", money), shopPanelX + textOffsetX, textOffsetY + 50, 24, GOLD);
        DrawText(TextFormat("Wall HP: %d / %d", wallHP, MAX_WALL_HP), shopPanelX + textOffsetX, textOffsetY + 90, 24, WHITE);

        // Кнопка улучшения стены (шире, чтобы влез текст)
        Rectangle upgradeWallButton = { shopPanelX + textOffsetX, textOffsetY + 130, shopPanelWidth - 2 * textOffsetX, buttonHeight };
        Color wallTextColor = (money >= wallHpUpgradeCost) ? GREEN : RED;

        if (CheckCollisionPointRec(GetMousePosition(), upgradeWallButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && money >= wallHpUpgradeCost) {
            wallHP += 200;
            if (wallHP > MAX_WALL_HP) wallHP = MAX_WALL_HP;
            money -= wallHpUpgradeCost;
        }
        DrawRectangleRec(upgradeWallButton, DARKGRAY);
        DrawText(TextFormat("Upgrade Wall +200HP - %d$", wallHpUpgradeCost), upgradeWallButton.x + 5, upgradeWallButton.y + 5, 20, wallTextColor);

        // Информация об уровне защитника
        DrawText(TextFormat("Defender Level: %d / %d", defenderLevel, MAX_DEFENDER_LEVEL), shopPanelX + textOffsetX, textOffsetY + 180, 24, WHITE);

        // Кнопка улучшения защитника
        Rectangle upgradeDefenderButton = { shopPanelX + textOffsetX, textOffsetY + 220, shopPanelWidth - 2 * textOffsetX, buttonHeight };
        Color defenderTextColor = (money >= defenderUpgradeCost) ? GREEN : RED;

        if (CheckCollisionPointRec(GetMousePosition(), upgradeDefenderButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && money >= defenderUpgradeCost) {
            defenderLevel++;
            money -= defenderUpgradeCost;
        }
        DrawRectangleRec(upgradeDefenderButton, DARKGRAY);
        DrawText(TextFormat("Upgrade Defender - %d$", defenderUpgradeCost), upgradeDefenderButton.x + 5, upgradeDefenderButton.y + 5, 20, defenderTextColor);
    }

    // Улучшенная кнопка "SHOP"
    DrawRectangleRec(shopButton, Fade(DARKGRAY, 0.8f));
    DrawText("SHOP", shopButton.x + buttonPadding, shopButton.y + (buttonHeight / 2) - (buttonTextSize / 2), buttonTextSize, WHITE);
}

void ToggleShop(void) {
    if (IsKeyPressed(KEY_B)) shopOpen = !shopOpen;
}
