﻿#ifndef SINGLETON_H
#define SINGLETON_H

#include <QDebug>
#include <iostream>
#include <memory>
#include <mutex>
using namespace std;
template <typename T>
class Singleton {
protected:
	Singleton() = default;
	Singleton(const Singleton<T> &) = delete;
	Singleton &operator=(const Singleton<T> &st) = delete;

	static std::shared_ptr<T> _instance;

public:
	static std::shared_ptr<T> GetInstance() {
		static std::once_flag s_flag;
		std::call_once(s_flag, [&]() {
			_instance = shared_ptr<T>(new T);
		});

		return _instance;
	}
	void PrintAddress() {
		// qDebug() << _instance.get() << endl;
	}
	~Singleton() {
		// qDebug() << "this is singleton destruct" ;
	}
};

template <typename T>
std::shared_ptr<T> Singleton<T>::_instance = nullptr;

#endif // !SINGLETON_H
