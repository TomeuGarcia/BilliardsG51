#include "SFXSoundBuffer.h"

SFXSoundBuffer::SFXSoundBuffer(GameAudioManager* manager, const SoundResourceData& resourceData, const int& bufferCount)
	: m_sfxSounds(), m_nextSoundIndex(0)
{
	m_sfxSounds.reserve(bufferCount);
	for (size_t i = 0; i < bufferCount; ++i)
	{
		m_sfxSounds.emplace_back(manager->CreateSFXSound(resourceData));
	}
}

void SFXSoundBuffer::PlayNext()
{
	m_sfxSounds[m_nextSoundIndex]->Play();
	m_nextSoundIndex = (m_nextSoundIndex + 1) % m_sfxSounds.size();
}

void SFXSoundBuffer::PlayNextWithVolume(const float& volume01)
{
	m_sfxSounds[m_nextSoundIndex]->SetVolume(volume01);
	PlayNext();
}

void SFXSoundBuffer::SetVolumeToAll(const float& volume01)
{
	for (auto it = m_sfxSounds.begin(); it != m_sfxSounds.end(); ++it)
	{
		(*it)->SetVolume(volume01);
	}
}
