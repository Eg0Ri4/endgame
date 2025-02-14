#include <includs.h>

#define MAX_WALL_HP 2000
#define MAX_DEFENDER_LEVEL 3

const int wallHpUpgradeCost = 200;
const int defenderUpgradeCost = 500;

void DrawShopUI(void) {
    if (!shopOpen) return;

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // Размеры и позиции UI элементов
    int shopPanelWidth = screenWidth * 0.23f; // Ширина панели магазина (23% от ширины экрана)
    int shopPanelX = screenWidth - shopPanelWidth; // Позиция панели магазина (справа)
    int textOffsetX = 20; // Отступ текста от края панели
    int textOffsetY = 20; // Отступ текста сверху
    int buttonHeight = 30; // Высота кнопки// Расстояние между элементами

    // Рисуем фон магазина
    DrawRectangle(shopPanelX, 0, shopPanelWidth, screenHeight, Fade(DARKGRAY, 0.8f));

    // Рисуем заголовок магазина
    DrawText("SHOP", shopPanelX + textOffsetX, textOffsetY, 30, WHITE);

    // Рисуем количество денег
    DrawText(TextFormat("Money: %d", money), shopPanelX + textOffsetX, textOffsetY + 40, 20, GOLD);

    // Рисуем информацию о здоровье стены
    DrawText(TextFormat("Wall HP: %d / %d", wallHP, MAX_WALL_HP), shopPanelX + textOffsetX, textOffsetY + 80, 20, WHITE);

    // Рисуем кнопку улучшения стены
    if (wallHP < MAX_WALL_HP && money >= wallHpUpgradeCost) {
        Rectangle upgradeWallButton = {
            shopPanelX + textOffsetX,
            textOffsetY + 110,
            shopPanelWidth - 2 * textOffsetX,
            buttonHeight
        };

        if (CheckCollisionPointRec(GetMousePosition(), upgradeWallButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            wallHP += 200;
            if (wallHP > MAX_WALL_HP) wallHP = MAX_WALL_HP;
            money -= wallHpUpgradeCost;
        }
        DrawText(TextFormat("Upgrade (+200 HP) - %d$", wallHpUpgradeCost), upgradeWallButton.x, upgradeWallButton.y, 20, (money >= wallHpUpgradeCost) ? GREEN : RED);
    }

    // Рисуем информацию об уровне защитника
    DrawText(TextFormat("Defender Level: %d / %d", defenderLevel, MAX_DEFENDER_LEVEL), shopPanelX + textOffsetX, textOffsetY + 150, 20, WHITE);

    // Рисуем кнопку улучшения защитника
    if (defenderLevel < MAX_DEFENDER_LEVEL && money >= defenderUpgradeCost) {
        Rectangle upgradeDefenderButton = {
            shopPanelX + textOffsetX,
            textOffsetY + 180,
            shopPanelWidth - 2 * textOffsetX,
            buttonHeight
        };

        if (CheckCollisionPointRec(GetMousePosition(), upgradeDefenderButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            defenderLevel++;
            money -= defenderUpgradeCost;
        }
        DrawText(TextFormat("Upgrade Defender - %d$", defenderUpgradeCost), upgradeDefenderButton.x, upgradeDefenderButton.y, 20, (money >= defenderUpgradeCost) ? GREEN : RED);
    }
}

void ToggleShop(void) {
    if (IsKeyPressed(KEY_B)) shopOpen = !shopOpen;
}
