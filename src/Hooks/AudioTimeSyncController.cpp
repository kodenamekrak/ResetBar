#include "Hooks/PracticeViewController.hpp"
#include "Hooks/SinglePlayerLevelSelectionFlowCoordinator.hpp"
#include "Hooks/LobbyGameStateController.hpp"
#include "GlobalNamespace/AudioTimeSyncController.hpp"
#include "GlobalNamespace/PauseController.hpp"
#include "GlobalNamespace/ILevelRestartController.hpp"

#include "UnityEngine/Resources.hpp"

using namespace GlobalNamespace;

PauseController* pauseController;

MAKE_AUTO_HOOK_MATCH(AudioTimeSyncController_Start, &AudioTimeSyncController::Start, void, AudioTimeSyncController* self)
{
    AudioTimeSyncController_Start(self);
    pauseController = UnityEngine::Resources::FindObjectsOfTypeAll<PauseController*>().FirstOrDefault();
}

MAKE_AUTO_HOOK_MATCH(AudioTimeSyncController_Update, &AudioTimeSyncController::Update, void, AudioTimeSyncController* self)
{
    AudioTimeSyncController_Update(self);
    if(!IsInPractice() || IsInMultiplayer()) return;

    float resetTime = ResetSlider::GetValue();
    float songTime = self->songTime;

    if(resetTime > 1 && resetTime < songTime)
    {
        pauseController->levelRestartController->RestartLevel();
    }
}