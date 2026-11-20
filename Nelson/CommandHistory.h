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
	};


}