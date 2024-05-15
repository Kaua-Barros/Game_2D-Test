#include "CollisionHandler.h"
#include "..\Global\GlobalProperties.h"

RigidBody *rigidBody = nullptr;

bool CollisionHeader::CheckCollision(Vector positionObject1, Vector sizeObject1, Vector positionObject2, Vector sizeObject2)
{
    sizeObject1.x = (sizeObject1.x * UNIT_TO_PIXELS);
    sizeObject1.y = (sizeObject1.y * UNIT_TO_PIXELS);
    sizeObject2.x = (sizeObject2.x * UNIT_TO_PIXELS);
    sizeObject2.y = (sizeObject2.y * UNIT_TO_PIXELS);
    positionObject2.x = (positionObject2.x * UNIT_TO_PIXELS);
    positionObject2.y = (positionObject2.y * UNIT_TO_PIXELS);

    bool collisionX = positionObject1.x < positionObject2.x + sizeObject2.x &&
                      positionObject1.x + sizeObject1.x > positionObject2.x;
    bool collisionY = positionObject1.y < positionObject2.y + sizeObject2.y &&
                      positionObject1.y + sizeObject1.y > positionObject2.y;

    return collisionX && collisionY;
}

void CollisionHeader::ApplyCollisionForce(Vector &positionObject1, Vector sizeObject1, RigidBody *rigidBody, Vector positionObject2, Vector sizeObject2)
{
    // Convertendo as dimensões para pixels
    sizeObject1.x *= UNIT_TO_PIXELS;
    sizeObject1.y *= UNIT_TO_PIXELS;
    sizeObject2.x *= UNIT_TO_PIXELS;
    sizeObject2.y *= UNIT_TO_PIXELS;
    positionObject2.x *= UNIT_TO_PIXELS;
    positionObject2.y *= UNIT_TO_PIXELS;

    // Verifica a colisão no eixo y
    if (positionObject1.y > positionObject2.y + (sizeObject2.y / 3) && positionObject1.y < positionObject2.y + sizeObject2.y)
    {
        std::cout << "baixo?" << '\n';
        rigidBody->ApplyForceY(15); // Aplica força para cima
    }
    else if (positionObject1.y + sizeObject1.y < positionObject2.y + (sizeObject2.y / 3) && positionObject1.y + sizeObject1.y > positionObject2.y)
    {
        std::cout << "cima?" << '\n';
        rigidBody->ApplyForceY((-(rigidBody->Acceleration().y) - 9.8));
    }

    // Verifica a colisão no eixo x
    else if (positionObject1.x > positionObject2.x + sizeObject2.x / 3 && positionObject1.x < positionObject2.x + sizeObject2.x)
    {
        rigidBody->ApplyForceX(5); // Aplica força para a direita
    }
    else if (positionObject1.x + sizeObject1.x < positionObject2.x + sizeObject2.x / 3 && positionObject1.x + sizeObject1.x > positionObject2.x)
    {
        rigidBody->ApplyForceX(-5);
    }
}
