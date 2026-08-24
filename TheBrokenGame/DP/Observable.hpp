#pragma once

#include <list>

#include "Observer.hpp"

using namespace std;

/// @brief Classe du patron observable
/// @class Observable
class Observable {
	private:
		list<Observer*> observers;

	public:
		/// @brief S'abonne à un observateur
		/// @param observer L'observateur à abonner
		void subscribe(Observer* observer) {
			observers.push_back(observer);
		}
		/// @brief Se désabonne d'un observateur
		/// @param observer L'observateur à désabonner
		void unsubscribe(Observer* observer) {
			observers.remove(observer);
		}
		/// @brief Notifie l'observateur
		void notify() {
			for (const auto it : observers)
				it->notification();
		}
};