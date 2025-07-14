#include "PeggleGameObject.hpp"

PeggleGameObject::PeggleGameObject(std::list<std::shared_ptr<GameObject>>& gameObjects, float initialX, float initialY, float radius, const std::string& assetName, double rotation)
: GameObject(initialX, initialY, radius, assetName, rotation), gameObjectsInScene(gameObjects) {}

void PeggleGameObject::update(float deltaTime) {
    if (!isAlive) return;

    for (auto& gameObject : gameObjectsInScene) {
        BallGameObject* ball = dynamic_cast<BallGameObject*>(gameObject.get());

        if (ball && ball->getState() != AIMING) {
            if (collisionDetectionDelegate && collisionDetectionDelegate(this->collider, ball->collider)) {
                setIsAlive(false);

                // Notifica todos os componentes sobre a colisão
                for (const auto& component : onHitComponents) {
                    component->onHit(this);
                }

                ball->rebound(this->collider);
                break;
            }
        }
    }
}

void PeggleGameObject::addOnHitComponent(std::shared_ptr<OnHitComponent> component) {
    onHitComponents.push_back(component);
}

void PeggleGameObject::setCollisionDelegate(OnCollisionDetectionDelegate handler) {
    if (collisionDetectionDelegate != nullptr) return;
    collisionDetectionDelegate = handler;
}
