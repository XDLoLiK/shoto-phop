#ifndef MESSAGE_TOOL_HPP
#define MESSAGE_TOOL_HPP

#include <iostream>
#include <cstring>
#include <algorithm>
#include <filesystem>

#include "tools.hpp"

class MessageTool : public booba::Tool
{
public:
    MessageTool();
    virtual ~MessageTool();

    virtual void apply(booba::Image* image, const booba::Event* event) override;
    virtual const char* getTexture() override; 
    virtual void buildSetupWidget()  override;

    void putDot(booba::Image* image, int x, int y, int dotSize);

private:
    char* m_texture = nullptr;
    char* m_message = nullptr;

    size_t m_messageLen = 0;
    size_t m_curPos     = 0;
};

#endif // MESSAGE_TOOL_HPP
