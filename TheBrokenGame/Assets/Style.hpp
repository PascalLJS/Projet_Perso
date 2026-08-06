#pragma once

#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>

#include "AssetManager.hpp"

/// @class Style
/// @brief Classe permettant de charger et de gérer les assets de style via un fichier de configuration.
class Style {
	
private:

	AssetManager& assetManager; ///< Référence vers le gestionnaire d'assets.

	/// @brief Initialise les assets en les chargeant depuis le fichier de configuration.
	void initializeAssets() {
		loadAssetsFromFile();
	}

	/// @brief Supprime les assets chargés.
	void removeAssets() {
		removeAssetsFromFile();
	}

	/// @brief Charge les assets depuis le fichier "Style.txt" en fonction de leurs types (couleur, texture, police ou uvmesh).
	void loadAssetsFromFile() {
		std::ifstream file("Style.txt");
		if (!file) {
			std::cerr << "Erreur : Impossible d'ouvrir le fichier Style.txt\n";
			return;
		}

		std::string line;
		while (std::getline(file, line)) {
			if (line == "Color:") {
				while (std::getline(file, line) && !line.empty()) {
					std::istringstream ss(line);
					std::string name;
					int r, g, b, a;
					if (ss >> name >> r >> g >> b >> a) {
						assetManager.addAsset(name, new Color(r, g, b, a));
					}
				}
			} else if (line == "Texture:") {
				while (std::getline(file, line) && !line.empty()) {
					std::istringstream ss(line);
					std::string name, texturePath;
					if (ss >> name >> texturePath) {
						assetManager.addAsset(name, new Texture(texturePath));
					}
				}
			} else if (line == "Font:") {
				while (std::getline(file, line) && !line.empty()) {
					std::istringstream ss(line);
					std::string name, fontPath;
					int fontSize = 12;
					if (ss >> name >> fontPath >> fontSize) {
						assetManager.addAsset(name, new Font(fontPath, fontSize));
					}
				}
			}
		}
		file.close();
	}

	/// @brief Supprime les assets listés dans le fichier "Style.txt".
	void removeAssetsFromFile() {
		std::ifstream file("Style.txt");
		if (!file) {
			std::cerr << "Erreur : Impossible d'ouvrir le fichier Style.txt\n";
			return;
		}

		std::string line;
		while (std::getline(file, line)) {
			if (line == "Color:") {
				while (std::getline(file, line) && !line.empty()) {
					std::istringstream ss(line);
					std::string name;
					if (ss >> name) {
						assetManager.removeAsset(name);
					}
				}
			} else if (line == "Texture:") {
				while (std::getline(file, line) && !line.empty()) {
					std::istringstream ss(line);
					std::string name;
					if (ss >> name) {
						assetManager.removeAsset(name);
					}
				}
			} else if (line == "Font:") {
				while (std::getline(file, line) && !line.empty()) {
					std::istringstream ss(line);
					std::string name;
					if (ss >> name) {
						assetManager.removeAsset(name);
					}
				}
			}
		}
		file.close();
	}

public:

	/// @brief Constructeur de la classe Style, initialisant les assets à partir du gestionnaire d'assets.
	/// @param assetManager Référence vers l'AssetManager pour la gestion des assets.
	Style(AssetManager& assetManager) : assetManager(assetManager) {
		initializeAssets();
	}

	/// @brief Destructeur de la classe Style.
	~Style() {
		removeAssets();
	}

	/// @brief Recharge les assets en les supprimant puis en les réinitialisant.
	void reloadAssets() {
		removeAssets();
		initializeAssets();
	}
};
