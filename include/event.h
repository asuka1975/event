//
// Created by hungr on 2020/02/18.
//

#ifndef EVENT_EVENT_H
#define EVENT_EVENT_H

#include <algorithm>
#include <list>
#include <functional>
#include <mutex>
#include <stdexcept>

template <class TSender, class TEventArgs>
class event {
public:
    event() = default;
    void operator+=(std::function<void(TSender, TEventArgs)> callback);
    void operator-=(std::function<void(TSender, TEventArgs)> callback);
    void operator()(TSender sender, TEventArgs e);

    event(const event<TSender, TEventArgs>& obj) = delete;
    event(event<TSender, TEventArgs>&& obj) = delete;
    void operator=(const event<TSender, TEventArgs>& obj) = delete;
    void operator=(event<TSender, TEventArgs>&& obj) = delete;

private:
    using fp_type = void(*)(TSender, TEventArgs);
    std::mutex mtx;
    std::list<std::function<void(TSender, TEventArgs)>> callbacks;
};

template <class TSender, class TEventArgs>
inline void event<TSender, TEventArgs>::operator+=(std::function<void(TSender, TEventArgs)> callback) {
    std::lock_guard<std::mutex> lock(mtx);
    auto citer = std::find_if(callbacks.begin(), callbacks.end(), [&callback](auto c) {
        auto fp1 = callback.template target<fp_type>();
        auto fp2 = callback.template target<fp_type>();
        if(fp1 == nullptr || fp2 == nullptr) throw std::runtime_error("invalid function signature. type `void(*)(TSender, TEventArgs)` is required");
        return *(callback.template target<fp_type>()) == *(c.template target<fp_type>());
    });
    if(citer == callbacks.end()) callbacks.push_back(callback);
}

template<class TSender, class TEventArgs>
inline void event<TSender, TEventArgs>::operator-=(std::function<void(TSender, TEventArgs)> callback) {
    std::lock_guard<std::mutex> lock(mtx);
    auto citer = std::find_if(callbacks.begin(), callbacks.end(), [&callback](auto c) {
        auto fp1 = callback.template target<fp_type>();
        auto fp2 = callback.template target<fp_type>();
        if(fp1 == nullptr || fp2 == nullptr) throw std::runtime_error("invalid function signature. type `void(*)(TSender, TEventArgs)` is required");
        return *(callback.template target<fp_type>()) == *(c.template target<fp_type>());
    });
    if(citer != callbacks.end()) callbacks.erase(citer);

}

template<class TSender, class TEventArgs>
inline void event<TSender, TEventArgs>::operator()(TSender sender, TEventArgs e) {
    std::lock_guard<std::mutex> lock(mtx);
    for(auto callback : callbacks) callback(sender, e);
}

#endif //EVENT_EVENT_H
