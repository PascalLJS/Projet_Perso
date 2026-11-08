#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

#include "AssetManager.hpp"

class Style {

private:

	AssetManager& assetManager;
	std::vector<std::string> loadedAssets; ///< Noms des assets chargés (utile pour reloadAssets).

	static std::string getExeDir() {
		char path[MAX_PATH];
		GetModuleFileNameA(NULL, path, MAX_PATH);
		std::string p(path);
		return p.substr(0, p.find_last_of("\\/"));
	}

	template <typename T>
	void registerAsset(const std::string& name, T* asset) {
		assetManager.addAsset(name, asset);
		loadedAssets.push_back(name);
	}

	void loadAssetsFromFile() {
		const std::string basePath = getExeDir() + "\\Ressources\\";
		std::ifstream file(basePath + "Style.txt");
		if (!file) {
			std::cerr << "Erreur : Impossible d'ouvrir " << basePath << "Style.txt\n";
			return;
		}

		std::string line;
		while (std::getline(file, line)) {
			if (line == "Color:") {
				while (std::getline(file, line) && !line.empty()) {
					std::istringstream ss(line);
					std::string name;
					int r, g, b, a;
					if (ss >> name >> r >> g >> b >> a)
						registerAsset(name, new Color(r, g, b, a));
				}
			} else if (line == "Texture:") {
				while (std::getline(file, line) && !line.empty()) {
					std::istringstream ss(line);
					std::string name, texturePath;
					if (ss >> name >> texturePath)
						registerAsset(name, new Texture(basePath + texturePath));
				}
			} else if (line == "Font:") {
				while (std::getline(file, line) && !line.empty()) {
					std::istringstream ss(line);
					std::string name, fontPath;
					int fontSize = 12;
					if (ss >> name >> fontPath >> fontSize)
						registerAsset(name, new Font(basePath + fontPath, fontSize));
				}
			}
		}
	}

public:

	explicit Style(AssetManager& assetManager) : assetManager(assetManager) {
		loadAssetsFromFile();
	}

	/// @brief Supprime les assets précédemment chargés puis relit Style.txt.
	void reloadAssets() {
		for (const auto& name : loadedAssets)
			assetManager.removeAsset(name);
		loadedAssets.clear();
		loadAssetsFromFile();
	}
};