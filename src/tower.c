#include "tower.h"
#include "utils.h"


tower* clickedOnTowerPosition(tower* head, int x, int y){
    tower* cur_tower = head;
    while (cur_tower != NULL){
        if (cur_tower->x <= x && x <= cur_tower->x + BLOCK_WIDTH &&
            cur_tower->y <= y && y <= cur_tower->y + BLOCK_HEIGHT){
            return cur_tower;
        }
        cur_tower = cur_tower->next;
    }
    return NULL;
}

void renderTowersAndShoot(tower* tow_head, enemy* enemy_head, SDL_Renderer* Renderer, int* Gold){
    SDL_Rect Rect;
    enemy* cur_enemy = enemy_head;
    enemy* enemy_for_shoot = NULL;
    SDL_RendererFlip Flip = SDL_FLIP_NONE;

    double towx, towy, enx, eny;
    double delta_x, delta_y, radius, highest_radius, righter;

    while (tow_head != NULL){
        if (tow_head->texture != NULL){
            tow_head->angle = 180;
            Rect.x = tow_head->x;
            Rect.y = tow_head->y;
            Rect.w = BLOCK_WIDTH;
            Rect.h = BLOCK_HEIGHT;

            towx = tow_head->x + BLOCK_WIDTH / 2;
            towy = tow_head->y + BLOCK_HEIGHT / 2;

            highest_radius = 0;
            righter = 0;

            while(cur_enemy != NULL){
                enx = cur_enemy->x + BLOCK_WIDTH / 2;
                eny = cur_enemy->y + BLOCK_HEIGHT / 2;

                delta_x = towx - enx;
                delta_y = towy - eny;
                radius = sqrt(pow(delta_x, 2) + pow(delta_y, 2));


                if (cur_enemy->isAlive == 1 && radius <= tow_head->radius && righter <= enx ){
                    highest_radius = radius;
                    righter = enx;
                    enemy_for_shoot = cur_enemy;

                    if (enx - towx == 0 & eny - towy > 0) tow_head->angle = 90;
                    else if (enx - towx == 0 & eny - towy < 0) tow_head->angle = -90;
                    else tow_head->angle = atan((eny - towy) / (enx - towx)) * 180 / PI;
                    if (enx - towx < 0) tow_head->angle += 180;
                }
                cur_enemy = cur_enemy->next;
            }
            cur_enemy = enemy_head;
            SDL_RenderCopyEx(Renderer, tow_head->texture, NULL, &Rect, tow_head->angle, NULL, Flip);
            if (enemy_for_shoot != NULL) renderShootingInEnemy(Renderer, enemy_for_shoot, tow_head, Gold);
        }
        tow_head = tow_head->next;
        enemy_for_shoot = NULL;
    }
}

void renderShootingInEnemy(SDL_Renderer* Renderer, enemy* cur_enemy, tower* cur_tower, int* Gold){
    int towx = cur_tower->x + BLOCK_WIDTH / 2;
    int towy = cur_tower->y + BLOCK_HEIGHT / 2;
    int enx = cur_enemy->x + BLOCK_WIDTH / 2;
    int eny = cur_enemy->y + BLOCK_HEIGHT / 2;

    SDL_SetRenderDrawColor(Renderer, 0xFF, 0x00, 0x00, 0xFF);

    SDL_RenderDrawLine(Renderer, towx, towy, enx, eny);
    cur_enemy->health -= cur_tower->damage;

    if (cur_enemy->health <= 0){
        cur_enemy->isAlive = 0;
        *Gold += cur_enemy->price;
    }
}

void clickedUpgradeMenu(tower* cur_tower, SDL_Texture* tow_textures[COUNT_SPRITES_TOWER], int x, int y, int* gold){
    if (cur_tower != NULL){
        if (cur_tower->level == 0){
            if (cur_tower->x <= x && x <= cur_tower->x + BLOCK_WIDTH &&
            cur_tower->y - BLOCK_HEIGHT - 5 <= y && y <= cur_tower->y - 5){
                if (cur_tower->cost <= *gold) upgradeTower(cur_tower, tow_textures, gold);
            }
        }
        else if (cur_tower->level == 7){
            if (cur_tower->x <= x && x <= cur_tower->x + BLOCK_WIDTH &&
            cur_tower->y - BLOCK_HEIGHT - 5 <= y && y <= cur_tower->y - 5){
                destroyTower(cur_tower, gold);
            }
        }
        else if (1 <= cur_tower->level & cur_tower->level <= 6){
            if (cur_tower->x - BLOCK_WIDTH / 2 <= x && x <= cur_tower->x + BLOCK_WIDTH / 2 &&
            cur_tower->y - BLOCK_HEIGHT - 5 <= y && y <= cur_tower->y - 5){
                if (cur_tower->cost <= *gold) upgradeTower(cur_tower, tow_textures, gold);
            }
            if (cur_tower->x + BLOCK_WIDTH / 2 <= x && x <= cur_tower->x + BLOCK_WIDTH * 3 / 2 &&
            cur_tower->y - BLOCK_HEIGHT - 5 <= y && y <= cur_tower->y - 5){
                destroyTower(cur_tower, gold);
            }
        }
    }
}

void upgradeTower(tower* cur_tower, SDL_Texture* tow_textures[COUNT_SPRITES_TOWER], int* gold){
    *gold -= cur_tower->cost;
    cur_tower->texture = tow_textures[cur_tower->level];
    cur_tower->cost = cur_tower->cost * 5 / 4;
    cur_tower->damage = cur_tower->damage * 6 / 4;
    cur_tower->level++;
    cur_tower->radius += 5;
}

void destroyTower(tower* cur_tower, int* gold){
    *gold += cur_tower->cost / 2;
    makeStartStatesForTower(cur_tower);
}

void showTowerUpgradeMenu(tower* cur_tower, SDL_Renderer* Renderer, SDL_Texture* tow_textures[COUNT_SPRITES_TOWER], int gold){
    SDL_Rect towRect;
    SDL_Rect destRect;
    if (cur_tower != NULL){
        if (cur_tower->level == 0) towRect.x = cur_tower->x;
        else towRect.x = cur_tower->x - BLOCK_WIDTH / 2;
        towRect.y = cur_tower->y - BLOCK_HEIGHT - 5;
        towRect.w = BLOCK_WIDTH;
        towRect.h = BLOCK_HEIGHT;

        if (cur_tower->level == 7) destRect.x = cur_tower->x;
        else destRect.x = cur_tower->x + BLOCK_WIDTH / 2;
        destRect.y = cur_tower->y - BLOCK_HEIGHT - 5;
        destRect.w = BLOCK_WIDTH;
        destRect.h = BLOCK_HEIGHT;

        if (cur_tower->level == 0){
            SDL_RenderCopy(Renderer, tow_textures[0], NULL, &towRect);
        }
        if (cur_tower->level == 7){
            SDL_RenderCopy(Renderer, tow_textures[COUNT_SPRITES_TOWER - 1], NULL, &destRect);
        }
        if (1 <= cur_tower->level & cur_tower->level <= 6){
            SDL_RenderCopy(Renderer, tow_textures[cur_tower->level], NULL, &towRect);
            SDL_RenderCopy(Renderer, tow_textures[COUNT_SPRITES_TOWER - 1], NULL, &destRect);
        }

        SDL_SetRenderDrawColor(Renderer, 0x80, 0x80, 0x80, 0x90);
        SDL_SetRenderDrawBlendMode(Renderer, SDL_BLENDMODE_BLEND);
        if (cur_tower->cost > gold & cur_tower->level != 7) SDL_RenderFillRect(Renderer, &towRect);
    }
}

void createListTower(tower** head){
    tower* current_tower = NULL;
    int count = 0;

    for (count = 0; count < COUNT_TOWER; count++){
        addTower(head);
    }
    current_tower = *head;
    current_tower->x = BLOCK_WIDTH * 3;
    current_tower->y = BLOCK_HEIGHT * 1;
    current_tower = current_tower->next;

    current_tower->x = BLOCK_WIDTH * 6;
    current_tower->y = BLOCK_HEIGHT * 6;
    current_tower = current_tower->next;

    current_tower->x = BLOCK_WIDTH * 3;
    current_tower->y = BLOCK_HEIGHT * 10;
    current_tower = current_tower->next;

    current_tower->x = BLOCK_WIDTH * 10;
    current_tower->y = BLOCK_HEIGHT * 3;
    current_tower = current_tower->next;

    current_tower->x = BLOCK_WIDTH * 10;
    current_tower->y = BLOCK_HEIGHT * 9;
}

void addTower(tower** head){
    tower* new_tower = createTower();
    tower* current_tower = *head;
    if (current_tower != NULL){
        while (current_tower->next != NULL)
            current_tower = current_tower->next;
        current_tower->next = new_tower;
    }
    else *head = new_tower;
}

void makeStartStatesForTower(tower* cur_tower){
    cur_tower->radius = 5 * BLOCK_WIDTH / 2;
    cur_tower->damage = 2,5;
    cur_tower->level = 0;
    cur_tower->cost = 50;
    cur_tower->angle = 180;
    cur_tower->texture = NULL;
}

tower* createTower(void){
    tower* new_tower = malloc(sizeof(tower));
    new_tower->next = NULL;
    makeStartStatesForTower(new_tower);
    return new_tower;
}

void initTowerTextures(SDL_Texture* enemy_sprites[COUNT_SPRITES_TOWER], SDL_Renderer* Renderer){
    size_t i;
    char str_path[30];
    for (i = 0; i < COUNT_SPRITES_TOWER - 1; i++){
        sprintf(str_path, "BMPimages/Towers/%d.png", i + 1);
        enemy_sprites[i] = getTextureFromPath(str_path, Renderer);
    }
    enemy_sprites[COUNT_SPRITES_TOWER - 1] = getTextureFromPath("BMPimages/Towers/dest_tow.png", Renderer);
}
