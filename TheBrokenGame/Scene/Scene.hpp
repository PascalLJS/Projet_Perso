#pragma once

/// @class Scene
/// @brief Classe abstraite qui modele les scenes
class Scene {

	public:
		///	@brief Charge une scene
		virtual void load() = 0;

		///	@brief Décharge une scene
		virtual void unload() = 0;

		/// @brief Gère le rendu de la scene
		virtual void handleRender() = 0;

		/// @brief Gère les events de la scene
		virtual void handleEvent() = 0;

		/// @brief Gère les changements de la scene
		/// @param deltaTime Delta temps, en seconde, entre chaque rafraîchissement
		virtual void handleUpdate(double deltaTime) = 0;
};