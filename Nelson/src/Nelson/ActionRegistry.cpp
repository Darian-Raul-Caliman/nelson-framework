#include "nspch.h"
#include "ActionRegistry.h"

#include "Nelson/Input.h"
#include "Nelson/KeyCodes.h"
#include "Nelson/Events/KeyEvent.h"
#include "imgui.h"

namespace Nelson {

	std::map<std::string, Action> ActionRegistry::s_Actions;



	static std::string KeyName(int key)
	{
		if ((key >= Key::A && key <= Key::Z) || (key >= Key::D0 && key <= Key::D9))
			return std::string(1, (char)key);

		if (key >= Key::F1 && key <= Key::F12)
			return "F" + std::to_string(key - Key::F1 + 1);

		switch (key)
		{
		case Key::Space:  return "Space";
		case Key::Enter:  return "Enter";
		case Key::Escape: return "Esc";
		case Key::Delete: return "Del";
		case Key::Tab:    return "Tab";
		case Key::Minus:  return "-";
		case Key::Equal:  return "=";
		}
		return "Key" + std::to_string(key);
	}

	std::string Shortcut::ToString() const
	{
		if (IsEmpty())
			return "";

		std::string text;
		if (Mods & Mod::Ctrl)  text += "Ctrl+";
		if (Mods & Mod::Shift) text += "Shift+";
		if (Mods & Mod::Alt)   text += "Alt+";
		return text + KeyName(Key);
	}

	void ActionRegistry::Register(const std::string& id, const std::string& label, Shortcut shortcut,
		std::function<void()> callback, std::function<bool()> isEnabled)
	{
		Action action;
		action.Id = id;
		action.Label = label;
		action.Shortcut = shortcut;
		action.Callback = std::move(callback);
		action.IsEnabled = std::move(isEnabled);

		s_Actions[id] = std::move(action);  
	}

	void ActionRegistry::Unregister(const std::string& id)
	{
		s_Actions.erase(id);
	}

	void ActionRegistry::Clear()
	{
		s_Actions.clear();
	}

	Action* ActionRegistry::Get(const std::string& id)
	{
		auto it = s_Actions.find(id);
		if (it == s_Actions.end())
			return nullptr;
		return &it->second;
	}



	bool ActionRegistry::CanExecute(const std::string& id)
	{
		Action* action = Get(id);
		if (!action || !action->Callback)
			return false;

		return !action->IsEnabled || action->IsEnabled();
	}

	bool ActionRegistry::Execute(const std::string& id)
	{
		if (!CanExecute(id))
			return false;

		Get(id)->Callback();
		return true;
	}


	static int CurrentMods()
	{
		int mods = Mod::None;
		if (Input::IsKeyPressed(Key::LeftControl) || Input::IsKeyPressed(Key::RightControl)) mods |= Mod::Ctrl;
		if (Input::IsKeyPressed(Key::LeftShift) || Input::IsKeyPressed(Key::RightShift))   mods |= Mod::Shift;
		if (Input::IsKeyPressed(Key::LeftAlt) || Input::IsKeyPressed(Key::RightAlt))     mods |= Mod::Alt;
		return mods;
	}

	bool ActionRegistry::OnKeyPressed(KeyPressedEvent& e)
	{

		if (e.GetRepeatCount() > 0)
			return false;

		if (ImGui::GetCurrentContext() && ImGui::GetIO().WantTextInput)
			return false;

		int key = e.GetKeyCode();
		int mods = CurrentMods();

		for (auto& [id, action] : s_Actions)
		{

			if (action.Shortcut.Key == key && action.Shortcut.Mods == mods)
				return Execute(id);   
		}
		return false;
	}


	bool ActionRegistry::MenuItem(const std::string& id)
	{
		Action* action = Get(id);
		if (!action)
			return false;

		std::string shortcut = action->Shortcut.ToString();
		if (ImGui::MenuItem(action->Label.c_str(), shortcut.empty() ? nullptr : shortcut.c_str(), false, CanExecute(id)))
			return Execute(id);
		return false;
	}

	bool ActionRegistry::Button(const std::string& id)
	{
		Action* action = Get(id);
		if (!action)
			return false;

		bool enabled = CanExecute(id);
		ImGui::BeginDisabled(!enabled);
		bool clicked = ImGui::Button(action->Label.c_str());
		ImGui::EndDisabled();

		if (!action->Shortcut.IsEmpty() && ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
			ImGui::SetTooltip("%s (%s)", action->Label.c_str(), action->Shortcut.ToString().c_str());

		return clicked && Execute(id);
	}
}