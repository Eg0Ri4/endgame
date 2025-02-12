#include "includs.h"

Vector2* delete_element(Vector2* array, int* size, int index) {
    if (*size == 0 || index >= *size) return array; 
    for (int i = index; i < *size - 1; i++) {
        array[i] = array[i + 1]; 
    }
    *size -= 1;
    array = realloc(array, *size * sizeof(Vector2));

    return array;
}

Texture2D load_texture(char *file_path){
    Image image = LoadImage(file_path);
    Texture2D results = LoadTextureFromImage(image);
    UnloadImage(image);
    return results;
}

