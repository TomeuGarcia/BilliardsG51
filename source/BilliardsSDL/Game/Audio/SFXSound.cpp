#include "SFXSound.h"

SFXSound::SFXSound(ISFXSoundManager* manager, const SoundResourceData& resourceData)
	: m_manager(manager), 
	m_sound(manager->GetAudioSystem()->LoadWAVSound(resourceData.p_sourcePath)),
	m_volume01(1.0f)
{
	m_manager->AddActiveSFXSound(this);
}

SFXSound::~SFXSound()
{
	m_manager->RemoveActiveSFXSound(this);
	GetAudioSystem()->DeleteSound(m_sound);
}



void SFXSound::Play()
{
	GetAudioSystem()->PlaySound(m_sound, m_manager->ComputeSFXEndVolume01(m_volume01));
}

void SFXSound::Stop()
{
	GetAudioSystem()->StopSound(m_sound);
}

void SFXSound::Pause()
{
	GetAudioSystem()->PauseSound(m_sound);
}

void SFXSound::Resume()
{
	GetAudioSystem()->ResumeSound(m_sound);
}



void SFXSound::SetVolume(const float& volume01)
{
	m_volume01 = Math::Clamp01(volume01);
	RefreshVolume();	
}

void SFXSound::RefreshVolume()
{
	if (m_sound.IsPlayingInChannel())
	{
		GetAudioSystem()->SetSoundVolume(m_sound, m_manager->ComputeSFXEndVolume01(m_volume01));
	}
}



inline AudioSystem* SFXSound::GetAudioSystem() const
{
	return m_manager->GetAudioSystem();
}
