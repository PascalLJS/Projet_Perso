#pragma once

/// @brief Classe du patron observateur
/// @class Observer
class Observer {
	public:
		virtual void notification() = 0;
};