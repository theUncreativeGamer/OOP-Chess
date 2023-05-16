#pragma once
#include"chessPiece.h"
bool Move(ChessPiece* chess, Vector2i destination, std::list<Vector2i>& validPos){
    for (Vector2i it : validPos) {
        if (it.x == destination.x && it.y == destination.y) {
            chess->setPosition(destination);
            return true; // 成功移動
        }
    }
    return false; // 移動失敗
}
