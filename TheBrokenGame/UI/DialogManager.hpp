#pragma once

#include <list>
#include "../UI/LabelGrid.hpp"
#include "../UI/Image.hpp"

/// @brief 
class DialogManager {
private:
  std::list<LabelGrid*> dialogs;
  LabelGrid *currentDialog;
  Image* dialogBox;
  bool dialogActive = false;
  int dialogIndex = 0;
  int dialogCount;

public:
  DialogManager(int dialogCount, Image *dialogBox) { 
    this->dialogCount = dialogCount;
    this->dialogBox = dialogBox;
    currentDialog = nullptr;
  }

  ~DialogManager() {
    for(auto it = dialogs.begin(); it != dialogs.end(); ++it)
      delete &it;
    dialogs.clear();
  }

  void resetCounter(int newCounter) {
    dialogIndex = 0;
    dialogCount = newCounter;
  }

  LabelGrid getCurrentDialog() {
    if(currentDialog)
      this->currentDialog;
  }

  bool isDialogActive() {
    return this->dialogActive;
  }

  void activateDialog() {
    this->dialogActive = true;
    this->currentDialog->setVisible();
    this->dialogBox->setVisible();
  }

  void deactivateDailog() {
    this->dialogActive = false;
    this->currentDialog->setInvisible();
    this->dialogBox->setInvisible();
  }

  void setCurrentVisible() {
    this->currentDialog->setVisible();
  }

  void addDialog(LabelGrid *labelGrid) {
    if(dialogs.empty()) {
      this->currentDialog = labelGrid;
    }
    this->dialogs.push_back(labelGrid);
  }

  void removeDialog(LabelGrid *labelGrid) {
    this->dialogs.remove(labelGrid);
  }

  void changeDialog() {
    dialogIndex++;
    if(dialogIndex < dialogCount && dialogs.size() >= 2) {
      this->currentDialog->setInvisible();
      this->dialogs.pop_front();
      this->currentDialog = dialogs.front();
      setCurrentVisible();
    } else
      deactivateDailog();
  }
};