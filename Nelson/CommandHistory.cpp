#include "nspch.h"
#include "CommandHistory.h"

namespace Nelson {

	void GroupCommand::Execute()
	{
		
	}

	void GroupCommand::Undo()
	{
	
	};

	void CommandHistory::Execute(std::unique_ptr<Command> cmd)
	{
	}

	void CommandHistory::Push(std::unique_ptr<Command> cmd)
	{
	}

	void CommandHistory::Undo()
	{
	}

	void CommandHistory::Redo()
	{

	}

	void CommandHistory::BeginGroup(const std::string& name)
	{

	}

	void CommandHistory::EndGroup()
	{

	}

	void CommandHistory::MarkSaved()
	{

	}

	bool CommandHistory::IsDirty() const
	{
		
		return false;
	}

	void CommandHistory::Clear()
	{

	}

}