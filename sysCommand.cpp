#include "sysCommand.h"

const bool& SysCommand::getExit() const
{
    return isExit;
}

void SysCommand::setExit(const bool p)
{
    isExit = p;
}

void SysCommand::clear()
{
    isExit = false;
}
