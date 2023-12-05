#pragma once

class CToolbar;

class ICommand {
public:
    virtual void Execute() const = 0;
    virtual ~ICommand() = default;
};
