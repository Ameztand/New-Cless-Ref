#pragma once

class SysCommand {
private:
	bool isExit = false;
public:
	const bool& getExit()const;
	void setExit(const bool p);

	void clear();
};
