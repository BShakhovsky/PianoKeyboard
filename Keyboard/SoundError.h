#pragma once

class SoundError : public std::exception
{
	SoundError() = delete;
public:
#pragma warning(push)
#pragma warning(disable:4514)	// unreferenced inline function has been removed
	explicit SoundError(const char* _Message)
		: msg_(_Message)
	{}
#pragma warning(pop)
	virtual ~SoundError() throw() override final = default;
	virtual const char* what() const override final
	{
		return msg_.empty() ? "Unknown exception" : msg_.c_str();
	}
private:
	std::string msg_;
};