#pragma once

class SoundError : public std::exception
{
	SoundError() = delete;
public:
	explicit SoundError(const char* _Message)
		: msg_(_Message)
	{}
	virtual ~SoundError() throw() override final = default;
	virtual const char* what() const override final
	{
		return msg_.empty() ? "Unknown exception" : msg_.c_str();
	}
private:
	std::string msg_;
};