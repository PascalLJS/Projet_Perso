#pragma once

#include <map>
#include <string>

#include "Asset.hpp"
#include "Texture.hpp"
#include "Color.hpp"
#include "Font.hpp"

/// @class AssetManager
/// @brief Gère les assets du jeu, y compris les textures, couleurs, polices et uvmesh.
class AssetManager {
private:
	std::map<std::string, Asset*> assets; ///< Conteneur pour stocker les assets, mappés par leur nom.

public:
	/// @brief Destructeur de la classe AssetManager.
	/// @details Libère la mémoire allouée pour tous les assets lors de la destruction de l'objet.
	~AssetManager() {
		for (auto it : assets) {
			delete it.second;
		}
	}

	/// @brief Ajoute un asset au gestionnaire.
	/// @param nom Nom de l'asset à ajouter.
	/// @param asset Pointeur vers l'asset à ajouter.
	/// @throw std::logic_error si T n'est pas dérivé de Asset.
	void addAsset(const std::string &nom,Asset *asset){
		assets[nom] = asset;
	}

	/// @brief Récupère un asset générique du gestionnaire.
	/// @param nom Nom de l'asset à récupérer.
	/// @return Pointeur vers l'asset demandé.
	/// @throw std::runtime_error si l'asset n'est pas trouvé ou si le type est incorrect.
	template<typename T>
	T getAsset(const std::string &nom) {
		return dynamic_cast<T>(assets[nom]);
	}

	/// @brief Supprime un asset du gestionnaire.
	/// @param nom Nom de l'asset à supprimer.
	/// @throw std::runtime_error si l'asset n'est pas trouvé.
	void removeAsset(const std::string &nom) {
		std::map<std::string, Asset*>::iterator it = assets.find(nom);
		if (it != assets.end()) {
			delete it->second;
			assets.erase(it);
		} else {
			throw std::runtime_error("Asset non trouvé : " + nom);
		}
	}
};
