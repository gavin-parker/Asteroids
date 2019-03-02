#pragma once

#include "controller.h"

class GameObject;
class Collidable;

class GameWorld {
public:
    explicit GameWorld(Controller& controller);
    void Update(float frameDelta);
    void Draw();

    void AddCollider(Collidable* collidable);
    void RemoveCollider(Collidable* collidable);

    template<typename T, typename ...Args>
    std::shared_ptr<T> CreateGameObject(Args&&... args)
    {
        auto newObject = std::make_shared<T>(*this, args...);
        RegisterCallback([this, newObject](){
            mChildren.push_back(newObject);
            }, std::chrono::microseconds::zero());
        return newObject;
    }

    void DestroyGameObject(std::shared_ptr<GameObject> ptr)
    {
        mChildren.erase(std::remove_if(mChildren.begin(), mChildren.end(), [ptr](auto c){return c == ptr;}),mChildren.end());
    }

    void RegisterCallback(std::function<void()> f, std::chrono::microseconds time)
    {
        mCallbacks.emplace_back(f, std::chrono::steady_clock::now() + time);
    }


private:
    Controller& mController;
    std::vector<Collidable*> mColliders;
    using Callback = std::tuple<std::function<void()>, std::chrono::steady_clock::time_point>;

    std::vector<std::shared_ptr<GameObject>> mChildren;
    std::deque<Callback> mCallbacks;
    void SpawnAsteroid();
    void UpdateCollisions();
    bool Call(Callback &callback);

    template<typename T, typename ...Args>
    std::shared_ptr<T> SpawnObject(Args&&... args)
    {
        auto newObject = std::make_shared<T>(*this, args...);
        mChildren.push_back(newObject);
        return newObject;
    }

};