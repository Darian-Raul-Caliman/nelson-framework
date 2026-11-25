#pragma once
#include <functional>
#include <map>
#include <string>


namespace Nelson {
	class KeyPressedEvent;

	namespace Mod {
		enum : int { None = 0, Ctrl = 1 << 0, Shift = 1 << 1, Alt = 1 << 2 };
	}


	struct Shortcut
	{
		int Key = 0;            
		int Mods = Mod::None;

		Shortcut() = default;
		Shortcut(int key, int mods = Mod::None) : Key(key), Mods(mods) {}

		bool IsEmpty() const { return Key == 0; }
		std::string ToString() const;   // "Ctrl+Shift+Z"
	};


	struct Action
	{
		std::string Id;
		std::string Label;
		Nelson::Shortcut Shortcut;
		std::function<void()> Callback;
		std::function<bool()> IsEnabled;
	};

	class ActionRegistry
	{
	public:
		static void Register(const std::string& id, const std::string& label, Shortcut shortcut,
			std::function<void()> callback, std::function<bool()> isEnabled = nullptr);
		static void Unregister(const std::string& id);
		static void Clear();

		static Action* Get(const std::string& id);
		static bool CanExecute(const std::string& id);
		static bool Execute(const std::string& id);
		static bool OnKeyPressed(KeyPressedEvent& e);
		static bool MenuItem(const std::string& id);
		static bool Button(const std::string& id);

		static const std::map<std::string, Action>& GetAll() { return s_Actions; }

	private:
		static std::map<std::string, Action> s_Actions;
	};
}