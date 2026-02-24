#pragma once
#include <string>
#include <memory>
#include <iostream>

template<class T>
class Entry
{
public:
	std::string name;
	std::shared_ptr<T> Object;
	Entry(std::string name, std::shared_ptr<T> obj) {
		this->name = name;
		this->Object = obj;
	}
	~Entry();
};

template<class T>
inline Entry<T>::~Entry()
{
}
