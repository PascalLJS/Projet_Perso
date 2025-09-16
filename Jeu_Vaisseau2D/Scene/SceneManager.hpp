#pragma once

#include <map>
#include <string>

#include "Scene.hpp"

/// @class SceneManager
/// @brief Le gestionnaire de scenes
class SceneManager {
	private:
		Scene *currentScene; ///< La scene actuelle
		std::map<std::string, Scene*> scenes; ///< Le dictionnaire contenant les scenes

	public:
		/// @brief  Le Constructeur
		SceneManager() { currentScene = nullptr; }

		/// @brief Obtention da la scene actuelle
		/// @return La scene actuelle
		Scene& getCurrentScene() {
			return *currentScene;
		}

		/// @brief Ajouter une scene
		/// @param sceneName Le nom de la scene
		/// @param scene La scene
		void addScene(std::string sceneName, Scene *scene) {
			scenes[sceneName] = scene;
		}

		/// @brief Supprime une scene
		/// @param sceneName Le nom de la scene
		void removeScene(std::string sceneName) {
			if(scenes[sceneName]) {
				delete scenes[sceneName];
				scenes.erase(sceneName);
			}
		}

		/// @brief Transition vers une autre scene
		/// @param sceneName Le nom de la scene
		void transitScene(std::string sceneName) {
			if(scenes[sceneName]) {
				if(currentScene)
					currentScene->unload();
				scenes[sceneName]->load();
				currentScene = scenes[sceneName];
			}
		}

		/// @brief Obtention d'une scene
		/// @param sceneName Le nom de la scene
		/// @return La scene
		Scene* getScene(std::string sceneName) {
			return scenes[sceneName];
		}
};