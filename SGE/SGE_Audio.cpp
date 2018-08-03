//====================================================================================================
// Filename:	SGE_Audio.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "SGE_Audio.h"

#include "Audio/Audio.h"
#include "Misc/Misc.h"
#include "Resource/Resource.h"

//====================================================================================================
// Namespace
//====================================================================================================

namespace SGE
{

//====================================================================================================
// Class Definitions
//====================================================================================================

SGE_Sound::SGE_Sound(void)
	: mpSound(nullptr)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

SGE_Sound::~SGE_Sound(void)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

void SGE_Sound::Load(const char* pSoundName)
{
	// Unload everything first
	Unload();

	// Construct the full name
	std::string fullname;
	fullname += CIniFile::Get()->GetString("SoundPath", "../Data/Sounds/");
	fullname += pSoundName;

	// Load the sound
	mpSound = CResourceManager::Get()->Create<CSound>(fullname.c_str());
}

//----------------------------------------------------------------------------------------------------

void SGE_Sound::Unload(void)
{
	// Unload sound
	if (nullptr != mpSound)
	{
		CResourceManager::Get()->Destroy(mpSound);
		mpSound = nullptr;
	}
}

//----------------------------------------------------------------------------------------------------

void SGE_Sound::Play(bool bLoop)
{
	if (nullptr != mpSound)
	{
		mpSound->Play(bLoop);
	}
}

//----------------------------------------------------------------------------------------------------

void SGE_Sound::Stop(void)
{
	if (nullptr != mpSound)
	{
		mpSound->Stop();
	}
}

} // namespace SGE