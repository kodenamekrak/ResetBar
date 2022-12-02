#include "main.hpp"
#include "Hooks/LobbyGameStateController.hpp"
#include "GlobalNamespace/LobbySetupViewController.hpp"
#include "GlobalNamespace/MultiplayerModeSelectionViewController.hpp"

bool isMultiplayer;

MAKE_AUTO_HOOK_MATCH(LobbySetupViewController_DidActivate, &GlobalNamespace::LobbySetupViewController::DidActivate, void, GlobalNamespace::LobbySetupViewController *self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
{
    LobbySetupViewController_DidActivate(self, firstActivation, addedToHierarchy, screenSystemEnabling);
    isMultiplayer = true;
}

MAKE_AUTO_HOOK_MATCH(MultiplayerModeSelectionViewController_DidActivate, &GlobalNamespace::MultiplayerModeSelectionViewController::DidActivate, void, GlobalNamespace::MultiplayerModeSelectionViewController *self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
{
    MultiplayerModeSelectionViewController_DidActivate(self, firstActivation, addedToHierarchy, screenSystemEnabling);
    isMultiplayer = false;
}

bool IsInMultiplayer()
{
    return isMultiplayer;
}