#include "PlayerSystem.h"
#include "World.h"

Systems::PlayerSystem::PlayerSystem( World* world ) : System(world)
{
	m_PlayerSpeed = 20;
	m_PlayerOriginalBounds = glm::vec3(0);
}

void Systems::PlayerSystem::Update(double dt)
{
}

void Systems::PlayerSystem::UpdateEntity(double dt, EntityID entity, EntityID parent)
{
	auto transform = m_World->GetComponent<Components::Transform>(entity, "Transform");
	if (transform == nullptr)
		return;
	auto input = m_World->GetComponent<Components::Input>(entity, "Input");
	if (input == nullptr)
		return;

	auto name = m_World->GetProperty<std::string>(entity, "Name");
	if (name == "Camera") {
			glm::vec3 Camera_Right = glm::vec3(glm::vec4(1, 0, 0, 0) * transform->Orientation);
			glm::vec3 Camera_Forward = glm::vec3(glm::vec4(0, 0, 1, 0) * transform->Orientation);

			float speed = m_PlayerSpeed;
			if(input->KeyState[GLFW_KEY_LEFT_SHIFT]) {
				speed *= 4.0f;
			}
			if(input->KeyState[GLFW_KEY_LEFT_ALT]) {
				speed /= 4.0f;
			}
			if(input->KeyState[GLFW_KEY_A] || input->KeyState[GLFW_KEY_LEFT]) {
				transform->Position -= Camera_Right * (float)dt * speed;
			}
			else if(input->KeyState[GLFW_KEY_D] || input->KeyState[GLFW_KEY_RIGHT]) {
				transform->Position += Camera_Right * (float)dt * speed;
			}
			if(input->KeyState[GLFW_KEY_W]) {
				transform->Position -= Camera_Forward * (float)dt * speed;
			}
			if(input->KeyState[GLFW_KEY_S]) {
				transform->Position += Camera_Forward * (float)dt * speed;
			}
			if(input->KeyState[GLFW_KEY_SPACE]) {
				transform->Position += glm::vec3(0, 1, 0) * (float)dt * speed;
			}
			if(input->KeyState[GLFW_KEY_LEFT_CONTROL]) {
				transform->Position -= glm::vec3(0, 1, 0) * (float)dt * speed;
			}
		if (input->MouseState[GLFW_MOUSE_BUTTON_LEFT]) {
			// TOUCHING THIS CODE MIGHT COUSE THE UNIVERSE TO IMPLODE, ALSO DRAGONS
			//---------------------------------------------------------------------
			transform->Orientation = glm::angleAxis<float>(input->dY/300.f,glm::vec3(1,0,0)) * transform->Orientation;

			transform->Orientation = transform->Orientation * glm::angleAxis<float>(input->dX/300.f,glm::vec3(0,1,0));
			//---------------------------------------------------------------------
			// TOUCHING THIS CODE MIGHT COUSE THE UNIVERSE TO IMPLODE, ALSO DRAGONS
		}

		auto collision = m_World->GetComponent<Components::Collision>(entity, "Collision");
		if(collision->CollidingEntities.size() > 0) {
			// DO STUFF
		}
	}
	
	name = m_World->GetProperty<std::string>(entity, "Name");
	if (name == "PlayerShip") 
	{
		auto bounds = m_World->GetComponent<Components::Bounds>(entity, "Bounds");
		if (bounds && m_PlayerOriginalBounds == glm::vec3(0)) {
			m_PlayerOriginalBounds = bounds->VolumeVector;
		}

		glm::vec3 Ship_Right = glm::vec3(glm::vec4(1, 0, 0, 0));
		glm::vec3 Ship_Forward = glm::vec3(glm::vec4(0, 0, 1, 0));

		float TurnSpeed = 2.0f;
		glm::vec3 Euler = glm::eulerAngles(transform->Orientation);

		if(input->KeyState[GLFW_KEY_LEFT]) {
			transform->Position -= Ship_Right * (float)dt * m_PlayerSpeed;
			
			if(Euler.z < 10.f)
			{
				transform->Orientation = transform->Orientation * glm::angleAxis<float>((float)dt * TurnSpeed,glm::vec3(0,0,1));
			}
			else if(Euler.z < 20.f)
			{
				transform->Orientation = transform->Orientation * glm::angleAxis<float>((float)dt * TurnSpeed/2,glm::vec3(0,0,1));
			}
			else if (Euler.z < 25.f)
			{
				transform->Orientation = transform->Orientation * glm::angleAxis<float>((float)dt * TurnSpeed/4,glm::vec3(0,0,1));
			}
		}
		else if(input->KeyState[GLFW_KEY_RIGHT]) {
			transform->Position += Ship_Right * (float)dt * m_PlayerSpeed;

			if(Euler.z > -10.f)
			{
				transform->Orientation = transform->Orientation * glm::angleAxis<float>((float)dt * TurnSpeed,glm::vec3(0,0,-1));
			}
			else if(Euler.z > -20.f)
			{
				transform->Orientation = transform->Orientation * glm::angleAxis<float>((float)dt * TurnSpeed/2,glm::vec3(0,0,-1));
			}
			else if (Euler.z > -25.f)
			{
				transform->Orientation = transform->Orientation * glm::angleAxis<float>((float)dt * TurnSpeed/4,glm::vec3(0,0,-1));
			}
		}
		else
		{
			if(Euler.z < 1.5f && Euler.z > -1.5f)
				transform->Orientation = glm::angleAxis<float>(0,glm::vec3(0,0,1));
			else if(Euler.z < 0.f)
				transform->Orientation = transform->Orientation * glm::angleAxis<float>((float)dt,glm::vec3(0,0,1));
			else if(Euler.z > 0.f)
				transform->Orientation = transform->Orientation * glm::angleAxis<float>((float)dt,glm::vec3(0,0,-1));
		}

		// Update player bounds based on rotation
		if (bounds) {
			Euler = glm::eulerAngles(transform->Orientation);
			bounds->VolumeVector.x = m_PlayerOriginalBounds.x * glm::cos(glm::radians(Euler.z));
		}
	}
}

