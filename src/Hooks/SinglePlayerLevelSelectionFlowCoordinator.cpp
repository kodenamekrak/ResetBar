#include "main.hpp"
#include "Hooks/SinglePlayerLevelSelectionFlowCoordinator.hpp"
#include "GlobalNamespace/SinglePlayerLevelSelectionFlowCoordinator.hpp"

bool isPractice;

MAKE_AUTO_HOOK_MATCH(SinglePlayerLevelSelectionFlowCoordinator_StartLevel, &GlobalNamespace::SinglePlayerLevelSelectionFlowCoordinator::StartLevel, void, GlobalNamespace::SinglePlayerLevelSelectionFlowCoordinator* self, System::Action* beforeSceneSwitchCallback, bool practice)
{
    SinglePlayerLevelSelectionFlowCoordinator_StartLevel(self, beforeSceneSwitchCallback, practice);
    isPractice = practice;
}

bool IsInPractice()
{
    return isPractice;
}