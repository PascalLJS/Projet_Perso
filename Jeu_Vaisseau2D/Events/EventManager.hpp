/// @file Events/EventManager.hpp
/// @brief Fichier contenant la classe EventManager
/// @author Dylan Allaire-Drolet

#pragma once
#include <SDL2/SDL.h>
#include "../DP/Observable.hpp"
#include <map>

/// @class EventManager
/// @brief Classe qui contient toutes les événements de l'application
class EventManager {
private:
	std::map<unsigned int, Observable> events; ///< Dictionnaire des événements
public:

	/// @brief Abonne un observateur à un événement
	/// @param eventType Type de l'événement
	/// @param observer Observateur à abonner
	void subscribe(unsigned int eventType, Observer* observer) {
		events[eventType].subscribe(observer);
	}

	/// @brief Désabonne un observateur à un événement
	/// @param eventType Type de l'événement
	/// @param observer Observateur à désabonner
	void unsubscribe(unsigned int eventType, Observer* observer) {
		events[eventType].unsubscribe(observer);
	}

	/// @brief Notifie tous les observateurs d'un événement
	/// @param eventType Type de l'événement
	void notify(unsigned int eventType) {
		events[eventType].notify();
	}
};