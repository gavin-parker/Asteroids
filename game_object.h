#pragma once

#include <vector>
#include <memory>
#include <functional>
#include <deque>
#include <chrono>
#include <algorithm>
#include <glm/vec2.hpp>

class GameObject {

public:
    GameObject(GameObject& parent, glm::vec2 position, float size) : mParent(parent), mPosition(position), mSize(size){};
    explicit GameObject() : mParent(*this), mPosition(0,0), mSize(0){};
    explicit GameObject(bool isRoot) : mRoot(isRoot), mParent(*this), mPosition(0,0), mSize(0){};
    virtual void Update(float frameDelta);
    virtual void Draw();

    bool IsRoot() { return mRoot;}
    GameObject& GetParent() { return mParent;}
protected:
    bool mRoot = false;
    GameObject& mParent;
    glm::vec2 mPosition;
    float mSize;
    //Use circular hitboxes for now


    void Create(const std::shared_ptr<GameObject> &object)
    {
        mChildren.push_back(object);
    }

    template<typename T, typename ...Args>
    std::shared_ptr<T> CreateGameObject(Args&&... args)
    {
        auto newObject = std::make_shared<T>(mParent, args...);
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


