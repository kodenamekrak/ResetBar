#include "GlobalNamespace/PracticeViewController.hpp"
#include "Hooks/PracticeViewController.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/QuestUI.hpp"
#include "HMUI/TimeSlider.hpp"
#include "HMUI/PercentSlider.hpp"

// Preview player includes
#include "GlobalNamespace/SongPreviewPlayer.hpp"
#include "UnityEngine/AudioClip.hpp"
#include "GlobalNamespace/IBeatmapLevel.hpp"
#include "GlobalNamespace/IBeatmapLevelData.hpp"
#include "GlobalNamespace/PerceivedLoudnessPerLevelModel.hpp"

using namespace GlobalNamespace;

HMUI::RangeValuesTextSlider *resetSlider;

float sliderValue;

float volume;
UnityEngine::AudioClip* audioClip;
SongPreviewPlayer* previewPlayer;

void PlaySongPreview()
{
    if(!previewPlayer) 
        previewPlayer = UnityEngine::Resources::FindObjectsOfTypeAll<SongPreviewPlayer*>().FirstOrDefault();
    previewPlayer->CrossfadeTo(audioClip, volume, ResetSlider::GetValue(), 5, nullptr);
}

MAKE_AUTO_HOOK_MATCH(PracticeViewController_DidActivate, &PracticeViewController::Init, void, PracticeViewController *self, GlobalNamespace::IBeatmapLevel* level, GlobalNamespace::BeatmapCharacteristicSO* beatmapCharacteristic, GlobalNamespace::BeatmapDifficulty beatmapDifficulty)
{
    PracticeViewController_DidActivate(self, level, beatmapCharacteristic, beatmapDifficulty);

    volume = self->perceivedLoudnessPerLevelModel->GetLoudnessCorrectionByLevelId(self->level->i_IPreviewBeatmapLevel()->get_levelID());
    audioClip = self->level->get_beatmapLevelData()->get_audioClip();
    previewPlayer = self->songPreviewPlayer;

    if(!resetSlider)
    {
        QuestUI::SliderSetting* slider = QuestUI::BeatSaberUI::CreateSliderSetting(self->get_transform(), "", 1, 5, 0, 10, 0.01f, [](float value)
        {
            sliderValue = value;
            PlaySongPreview();
        });
        slider->FormatString = std::move([](float value)
        {
            int m = value / 60;
            int s = value - m * 60;
            if(m) return std::to_string(m) + " m " + std::to_string(s) + " s";
            return std::to_string(s) + " s";
        });
        resetSlider = slider->slider;

        // auto speedTrans = self->speedSlider->GetComponent<UnityEngine::RectTransform*>();
        // speedTrans->set_anchoredPosition({speedTrans->get_anchoredPosition().x, -50});

        auto resetTrans = resetSlider->GetComponent<UnityEngine::RectTransform*>();
        resetTrans->set_sizeDelta({110, 3});
        resetTrans->set_anchoredPosition({-25, -57});

        auto rect = self->playButton->GetComponent<UnityEngine::RectTransform*>();
        rect->set_anchoredPosition({rect->get_anchoredPosition().x, -67});
    }
    
    resetSlider->set_value(0);
    resetSlider->set_maxValue(self->songStartSlider->get_maxValue());
    resetSlider->set_numberOfSteps(self->songStartSlider->get_numberOfSteps());
}

namespace ResetSlider
{
    float GetValue()
    {
        return resetSlider ? resetSlider->get_value() : 0.0f; 
    }

    void ResetValue()
    {
        if(resetSlider)
            resetSlider->set_value(0);
    }
}