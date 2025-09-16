#pragma once

#include <string>

/// @class Asset
/// @brief Classe abstraite représentant un asset du jeu, utilisée comme base pour
///        les classes dérivées comme Texture, Color et Font.
class Asset {
public:
	/// @brief Récupère le type de l'asset.
	/// @return Chaîne de caractères représentant le type de l'asset (ex. 'Texture',
	///         'Color', 'Font', etc.).
	/// @details Cette méthode est purement virtuelle et doit être implémentée 
	///          par les classes dérivées pour retourner le type spécifique de l'asset.
	virtual std::string getType() = 0;
};
