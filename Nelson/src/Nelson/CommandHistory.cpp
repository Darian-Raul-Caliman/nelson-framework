#include "nspch.h"
#include "CommandHistory.h"

namespace Nelson {



	void GroupCommand::Undo()
	{

		for (auto cmd = m_Commands.rbegin(); cmd != m_Commands.rend(); ++cmd)
			(*cmd)->Undo();

	};

	void GroupCommand::Execute()
	{
		for (auto& cmd : m_Commands)
			cmd->Execute();
	}

	void CommandHistory::Execute(std::unique_ptr<Command> cmd)
	{
		cmd->Execute();                   

		if (m_Group)
			m_Group->Add(std::move(cmd)); 
		else
			Push(std::move(cmd));         
	}

	void CommandHistory::Push(std::unique_ptr<Command> cmd)
	{

		if (m_SavedIndex > (int)m_Undo.size())
			m_SavedIndex = -1;

		m_Redo.clear();
		m_Undo.push_back(std::move(cmd));

		if (m_Undo.size() > m_MaxSteps)
		{
			m_Undo.erase(m_Undo.begin());


			if (m_SavedIndex > 0)
				m_SavedIndex--;
			else
				m_SavedIndex = -1;  
		}
	}

	void CommandHistory::Undo()
	{
		if (!CanUndo()) return;

		std::unique_ptr<Command> cmd = std::move(m_Undo.back()); 
		m_Undo.pop_back();                                     
		cmd->Undo();                                             
		m_Redo.push_back(std::move(cmd));                     
	}

	void CommandHistory::Redo()
	{
		if (!CanRedo()) return;

		std::unique_ptr<Command> cmd = std::move(m_Redo.back());
		m_Redo.pop_back();
		cmd->Execute();
		m_Undo.push_back(std::move(cmd));
	}

	void CommandHistory::BeginGroup(const std::string& name)
	{
		if (m_Group) {
			return;
		}

		m_Group = std::make_unique<GroupCommand>(name);


	}

	void CommandHistory::EndGroup()
	{
		if (!m_Group)
			return;

		std::unique_ptr<GroupCommand> group = std::move(m_Group);

		if (!group->IsEmpty())
			Push(std::move(group));
	}

	void CommandHistory::MarkSaved()
	{
		m_SavedIndex = (int)m_Undo.size();
	}

	bool CommandHistory::IsDirty() const
	{
		return m_SavedIndex != (int)m_Undo.size();
	}

	void CommandHistory::Clear()
	{
		m_Undo.clear();
		m_Redo.clear();
		m_Group.reset();
		m_SavedIndex = 0;
	}

}


