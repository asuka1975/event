//
// Created by hungr on 2020/02/21.
//

#ifndef EVENT_PROPERTY_H
#define EVENT_PROPERTY_H

#include <map>
#include <string>
#include <event.h>

template <class _Typ>
class property {
public:
    property() = default;
    property(const _Typ& v);
    property(_Typ&& v);
    property(const property<_Typ>& obj) = delete;
    property(property<_Typ>&& obj) = delete;
public:
    event<const property<_Typ>*, std::map<std::string, _Typ>> on_change;
    _Typ operator=(const _Typ& v);
    _Typ operator=(_Typ&& v);
    operator _Typ() const;
private:
    _Typ value;
};

template<class _Typ>
property<_Typ>::property(const _Typ &v) : value(v) { }

template<class _Typ>
property<_Typ>::property(_Typ &&v) : value(v) { }

template<class _Typ>
_Typ property<_Typ>::operator=(const _Typ &v) {
    _Typ old = value;
    value = v;
    on_change(this, std::map<std::string, _Typ>{ {"old", old}, {"new", value} });
    return value;
}

template<class _Typ>
_Typ property<_Typ>::operator=(_Typ &&v) {
    _Typ old = value;
    value = v;
    on_change(this, std::map<std::string, _Typ>{ {"old", old}, {"new", value} });
    return value;
}

template<class _Typ>
property<_Typ>::operator _Typ() const {
    return value;
}

#endif //EVENT_PROPERTY_H
