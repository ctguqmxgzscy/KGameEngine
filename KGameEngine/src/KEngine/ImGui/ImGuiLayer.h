#pragma once

#include "KEngine/Layer.h"

#include "KEngine/Events/KeyEvent.h"
#include "KEngine/Events/MouseEvent.h"
#include "KEngine/Events/ApplicationEvent.h"


namespace KEngine {

	class KENGINE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}