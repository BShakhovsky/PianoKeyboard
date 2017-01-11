#pragma once

class SoundError : public std::exception
{
public:
#pragma warning(push)
#pragma warning(disable:4514)	// unreferenced inline function has been removed
	SoundError() : std::exception() {}
	explicit SoundError(const char* _Message) : std::exception(_Message) {}
#pragma warning(pop)
	virtual ~SoundError() throw() override final = default;
	virtual const char* what() const override final
	{
		return std::exception::what();
	}
};