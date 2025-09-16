#pragma once

/// @class Singleton
/// @brief singleton
/// @tparam T 
template <typename T>
class Singleton {
	protected:
	Singleton() {}
	public:
	Singleton(Singleton& singleton) = delete;
	Singleton(const Singleton& singleton) = delete;
	Singleton& operator =(Singleton& singleton) = delete;
	Singleton& operator = (const Singleton& Singleton) = delete;

	static T& getInstance() {
		static T instance;
		return instance;
	}
};
