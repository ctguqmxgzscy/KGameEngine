#pragma once

#include "KEngine/Core.h"
#include "KEngine/Core/Timestep.h"
#include "KEngine/Events/Event.h"

namespace KEngine {

	class KENGINE_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep timestep) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName()const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}