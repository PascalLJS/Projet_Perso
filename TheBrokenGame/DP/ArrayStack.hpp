#include <cstdlib>
#include <optional>

/// @class ArrayStack
/// @brief Pile statique
template <typename T>
class ArrayStack {
  private:
  T* array; ///< Tableau de données
  size_t topIndex; ///< Indice du dessus dans le tableau
  size_t length; ///< taille du tableau

  public :
  /// @brief Constructeur
  /// @param length Taille maximum 
  ArrayStack(size_t length) {
    this->length = length;
    array = new T[length];
    topIndex = 0;
  }

  /// @brief Destructeur
  ~ArrayStack() {
    delete[] array;
  }

  /// @brief Regarde si une valeur donnée existe déjà dans la pile
  /// @param value La valeur à vérifié
  /// @return Vrai si la valeur existe
  bool ifValueAlreadyExist(T value) {
    for (int i = 0; i < topIndex; i++) {
      if (array[i] == value)
        return true;
    }
    return false;
  }

  /// @brief Empile une donnée
  /// @param value donnée à empiler 
  void push(T value) {
    if(topIndex < length && !ifValueAlreadyExist(value))
      array[topIndex++] = value;
  }

  /// @brief Dépile les données à partir d'un index
  /// @param index Indice
  void popDownStackValues(int index) {
    if(index == topIndex)
      pop();
    else {
      for(int i = index; i < topIndex - 1; i++) {
        array[i] = array[i + 1];
      }
      topIndex--;
    }
  }

  /// @brief Dépiler une donnée
  void removeValue(T value) {
    if(topIndex) {
      for(int i = 0; i < topIndex; i++) {
        if(array[i] == value) {
          popDownStackValues(i);
        }
      }
    }
  }

  /// @brief Dépile à partir du dessus de la pile
  void pop() {
    if(topIndex)
      topIndex--;
  }

  /// @brief Optention du dessus de la pile
  /// @return donnée au dessus
  T top() {
    return array[topIndex-1];
  }

  /// @brief Regerde si la pile est vide
  /// @return Retourne vrai si la pile est vide
  bool isEmpty() {
    return !topIndex;
  }

  /// @brief Optention de la taille de la pile
  /// @return Nombre de données
  size_t size() {
    return topIndex;
  }
};