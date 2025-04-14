#include "MusicSound.h"

MusicSound::MusicSound(IMusicSoundManager* manager, const SoundResourceData& resourceData)
	: m_manager(manager),
	m_singleSound(manager->GetAudioSystem()->LoadSingleSound(resourceData.p_sourcePath)),
	m_volume01(1.0f), m_loops(-1)
{
	m_manager->AddActiveMusicSound(this);
}

MusicSound::~MusicSound()
{
	m_manager->RemoveActiveMusicSound(this);
	GetAudioSystem()->DeleteSingleSound(m_singleSound);
}



void MusicSound::Play()
{
	GetAudioSystem()->PlaySingleSound(m_singleSound, m_manager->ComputeMusicEndVolume01(m_volume01), m_loops);
}

void MusicSound::Stop()
{
	GetAudioSystem()->StopSingleSound(m_singleSound);
}

void MusicSound::Pause()
{
	GetAudioSystem()->PauseSingleSound(m_singleSound);
}

void MusicSound::Resume()
{
	GetAudioSystem()->ResumeSingleSound(m_singleSound);
}



void MusicSound::SetLoops(const int& loops)
{
	m_loops = Math::Max(loops, -1);
}

void MusicSound::SetVolume(const float& volume01)
{
	m_volume01 = Math::Clamp01(volume01);
	RefreshVolume();
}

void MusicSound::RefreshVolume()
{
	if (m_singleSound.IsPlaying())
	{
		GetAudioSystem()->SetSingleSoundVolume(m_singleSound, m_manager->ComputeMusicEndVolume01(m_volume01));
	}
}



inline AudioSystem* MusicSound::GetAudioSystem() const
{
	return m_manager->GetAudioSystem();
}
