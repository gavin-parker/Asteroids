#pragma once

#include <vector>
#include <memory>
#include <functional>
#include <deque>
#include <chrono>
#include <algorithm>

class GameObject {

public:

    virtual void Update(float frameDelta);
    virtual void Draw();

    void Create(const std::shared_ptr<GameObject> &object)
    {
        mChildren.push_back(object);
    }

    template<typename T, typename ...Args>
    std::shared_ptr<T> CreateGameObject(Args&&... args)
    {
        auto newObject = std::make_shared<T>(args...);
        mChildren.push_back(newObject);
        return newObject;
    }

    void DestroyGameObject(std::shared_ptr<GameObject> ptr)
    {
        mChildren.erase(std::remove_if(mChildren.begin(), mChildren.end(), [ptr](auto c){return c == ptr;}),mChildren.end());
    }

    void RegisterCallback(std::function<void()> f, std::chrono::steady_clock::time_point time)
    {
        mCallbacks.emplace_back(f, time);
    }

private:
    using Callback = std::tuple<std::function<void()>, std::chrono::steady_clock::time_point>;

    std::vector<std::shared_ptr<GameObject>> mChildren;
    std::deque<Callback> mCallbacks;
    bool Call(Callback &callback);
};


