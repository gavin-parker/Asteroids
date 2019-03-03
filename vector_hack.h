
#include <tuple>

template<class ...Objs>
class VectorHack {
public:

    VectorHack() {
        (_Reserve<Objs>(1024), ...);
    }


    template<class Func>
    void ForAll(Func f);

    template<class Func>
    void RemoveIf(Func f);

    template<class Obj, class ...Args>
    uint64_t Create(Args ...args) {
        Obj& newObject = std::get<std::vector<Obj>>(mContents).emplace_back(args...);
        std::get<std::unordered_map<uint64_t, Obj*>>(mLookup).insert({newObject.GetId(), &newObject});
        return newObject.GetId();
    }

    template<class Object>
    Object& Get(uint64_t id)
    {
        return *std::get<std::unordered_map<uint64_t, Object*>>(mLookup)[id];
    }

private:

    std::tuple<std::vector<Objs>...> mContents;
    std::tuple<std::unordered_map<uint64_t, Objs*>...> mLookup;

    template<class Object>
    void _Reserve(size_t count)
    {
        std::get<std::vector<Object>>(mContents).reserve(count);
    }

    template<class Object, class Func>
    void _ForAll(Func f);
    template<class Object, class Func>
    void _RemoveIf(Func f);
};

template<class... Objs>
template<class Func>
void VectorHack<Objs...>::ForAll(Func f)
{
    (_ForAll<Objs>(f), ...);
}

template<class... Objs>
template<class Func>
void VectorHack<Objs...>::RemoveIf(Func f) {
    (_RemoveIf<Objs>(f), ...);
}

template<class... Objs>
template<class Obj, class Func>
void VectorHack<Objs...>::_ForAll(Func f) {
    auto &contents = std::get<std::vector<Obj>>(mContents);
    std::for_each(contents.begin(), contents.end(), f);
}

template<class... Objs>
template<class Obj, class Func>
void VectorHack<Objs...>::_RemoveIf(Func f) {
    auto &contents = std::get<std::vector<Obj>>(mContents);
    contents.erase(std::remove_if(contents.begin(), contents.end(), f), contents.end());
    auto &lookup = std::get<std::unordered_map<uint64_t, Obj*>>(mLookup);
    std::for_each(contents.begin(), contents.end(),
            [&](auto& c){
        lookup[c.GetId()] = &c;
    });

}
