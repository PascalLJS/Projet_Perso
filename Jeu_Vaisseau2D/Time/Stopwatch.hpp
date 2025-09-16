#pragma once

#include <chrono>

///@class Stopwatch
///@brief Représente un chronomètre (gère le temps en nanosecondes)
class Stopwatch {
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> startTime; ///< Temps de départ

public:
	/// @brief Constructeur, démarre le chronomètre
	Stopwatch() {
		startTime = std::chrono::high_resolution_clock::now();
	}

	///@brief Redémarre le chronomètre
	void Restart() {
		startTime = std::chrono::high_resolution_clock::now();
	}

	/// @brief Donne le temps écoulé en secondes
	/// @return Retourne le temps écoulé en secondes et millisecondes dans un double (ex: 1.5s)
	double getElapsedSeconds() {
		std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(now - startTime);
		return elapsed.count();
	}
};