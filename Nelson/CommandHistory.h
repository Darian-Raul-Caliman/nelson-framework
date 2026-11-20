#pragma once
#include "memory"
#include <string>
#include <vector>

namespace Nelson {


	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute() = 0;
		virtual void Undo() = 0;
		virtual std::string GetName() const = 0;

	private:
		std::string m_Name;
		std::vector<std::unique_ptr<Command>> m_Commands;
	};

	class CommandHistory
	{
	public:
		explicit CommandHistory(size_t maxSteps = 100) : m_MaxSteps(maxSteps);
		void Execute(std::unique_ptr<Command> cmd);

		template<typename T, typename... Args>
		void Execute(Args&&... args) { Execute(std::make_unique<T>(std::forward<Args>(args)...)); }

		void Undo();
		void Redo();
		bool CanUndo() const { return !m_Undo.empty() && !IsGrouping(); }
		bool CanRedo() const { return !m_Redo.empty() && !IsGrouping(); }

		std::string GetUndoName() const { return m_Undo.empty() ? "" : m_Undo.back()->GetName(); }
		std::string GetRedoName() const { return m_Redo.empty() ? "" : m_Redo.back()->GetName(); }

		void BeginGroup(const std::string& name);
		void EndGroup();
		bool IsGrouping() const { return m_Group != nullptr; }

		void MarkSaved();
		bool IsDirty() const;
		void Clear();

		const std::vector<std::unique_ptr<Command>>& GetUndoStack() const { return m_Undo; }

	private:
		void Push(std::unique_ptr<Command> cmd);
		std::vector<std::unique_ptr<Command>> m_Undo;
		std::vector<std::unique_ptr<Command>> m_Redo;
		std::unique_ptr<GroupCommand> m_Group;
		size_t m_MaxSteps;
		int m_SaveedIndex = 0;
	};

	class GroupCommand : public Command
	{
	public:
		explicit GroupCommand(std::string name) : m_Name(std::move(name)){}
		void Add(std::unique_ptr<Command> cmd) {m_Commands.push_back(std::move(cmd)) }
		bool IsEmpty() const { return m_Commands.empty(); }
		void Execute() override;
		void Undo() override;
		std::string GetName() const override { return m_Name; }

	private:
		std::string m_Name;
		std::vector<std::unique_ptr<Command>> m_Commands;
	};




}