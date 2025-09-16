#pragma once

#include "Stopwatch.hpp"
#include <sstream>
#include <iomanip>
#include <string>

///@class TimeUtil
///@brief Classe statique utilitaire pour gérer le temps
class TimeUtil {
public:
        /// @brief Convertit un chronomètre en string pour l'affichage
        /// @param stopwatch Le chronomètre à convertir
        /// @return Une string de la durée du chronomètre (h:m:s)

    static std::string formatStopwatch(Stopwatch& stopwatch) {
        double elapsedSeconds = stopwatch.getElapsedSeconds();

        int hours = static_cast<int>(elapsedSeconds / 3600);
        int minutes = static_cast<int>((elapsedSeconds - hours * 3600) / 60);
        int seconds = static_cast<int>(elapsedSeconds) % 60;

        // Use stringstream to format with leading zeros
        std::ostringstream oss;
        oss << hours << ":" 
            << std::setw(2) << std::setfill('0') << minutes << ":" 
            << std::setw(2) << std::setfill('0') << seconds;

        return oss.str();
    }
};