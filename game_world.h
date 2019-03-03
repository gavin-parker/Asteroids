#pragma once
#include "controller.h"
#include "utils.h"
#include "vector_hack.h"
#include "asteroid.h"
#include "ship.h"
#include "collidable.h"

class GameWorld {
public:
    explicit GameWorld(Controller& controller);

    void Update(FrameDelta frameDelta);
    void Draw();
    void AddCollider(Collidable* collidable);
    void RemoveCollider(Collidable* collidable);

    template<typename T, typename ...Args>
    uint64_t CreateGameObject(Args&&... args)
    {
        return SpawnObject<T>(args...);
    }

    void RegisterCallback(std::function<void()> f, std::chrono::microseconds time)
    {
        mCallbacks.emplace_back(f, std::chrono::steady_clock::now() + time);
    }

    uint64_t GetId()
    {
        return mIds++;
    }

    template<class Obj>
    Obj& GetObject(uint64_t id)
    {
        return mWorldContents.Get<Obj>(id);
    }
private:
    Controller& mController;
    std::vector<Collidable*> mColliders;
    using Callback = std::tuple<std::function<void()>, std::chrono::steady_clock::time_point>;

    VectorHack<Ship, Laser, Asteroid> mWorldContents;
    std::deque<Callback> mCallbacks;
    uint64_t mIds = 0;
    void SpawnAsteroid();
    void UpdateCollisions();
    bool Call(Callback &callback);

    template<typename T, typename ...Args>
    uint64_t SpawnObject(Args&&... args)
    {
        return mWorldContents.Create<T>(this, args...);
    }

};