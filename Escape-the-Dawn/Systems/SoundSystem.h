#ifndef SoundEmitter_h__
#define SoundEmitter_h__

#include "System.h"
#include "Components/Transform.h"
#include "Components/SoundEmitter.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <vector>
#include <glm/gtx/quaternion.hpp>

namespace Systems
{

class SoundSystem : public System
{
public:
	SoundSystem(World* world);

	void Update(double dt) override;
	void UpdateEntity(double dt, EntityID entity, EntityID parent) override;
	void OnComponentCreated(std::string type, std::shared_ptr<Component> component) override;
	void OnComponentRemoved(std::string type, Component* component) override;
	void PlaySound(std::shared_ptr<Components::SoundEmitter> emitter, std::string fileName);

private:
	ALuint LoadFile(std::string fileName);
	ALuint CreateSource();

	//File-info
	char type[4];
	unsigned long size, chunkSize;
	short formatType, channels;
	unsigned long sampleRate, avgBytesPerSec;
	short bytesPerSample, bitsPerSample;
	unsigned long dataSize;
	
	
	std::map<Component*, ALuint> m_Sources; 
	std::map<std::string, ALuint> m_BufferCache; // string = fileName
};

}
#endif // !SoundEmitter_h__

