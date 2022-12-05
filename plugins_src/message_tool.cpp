#include "message_tool.hpp"

char messagePic[] =
"********  ********  ********  ********  ********  *     **\n"
"*      *  *      *  *         *      *  *         *    * *\n"
"*      *  *      *  *         *      *  *         *   *  *\n"
"*      *  *      *  *         *      *  *         *  *   *\n"
"*      *  *      *  *         *      *  *         * *    *\n"
"*      *  ********  ********  ********  ********  **     *\n";

char messageTexture[] = "./message.png";

MessageTool::MessageTool():
    m_texture(messageTexture),
    m_message(messagePic),
    m_messageLen(std::strlen(m_message)),
    m_curPos(0)
{
    FILE* messageFile = std::fopen("./message.txt", "r");
    if (!messageFile) {
        std::cout << "message.txt not found" << std::endl;
        return;
    }

    std::fseek(messageFile, 0, SEEK_END);
    size_t fileSize = ftell(messageFile);
    std::fseek(messageFile, 0, SEEK_SET);

    m_message = new char[fileSize]();
    std::fread(m_message, sizeof (char), fileSize, messageFile);

    m_messageLen = std::strlen(m_message);

    std::fclose(messageFile);
}

MessageTool::~MessageTool()
{

}

void MessageTool::apply(booba::Image* image, const booba::Event* event)
{
    const int dotSize = 8;

    static int pornCount = 0;

    static bool mpressed = false;

    static int startX = -1;
    static int startY = -1;

    static int curX = 0;
    static int curY = 0;

    if (image == nullptr) {
        return;
    }

    if (m_curPos >= m_messageLen) {
        m_curPos = 0;
        startX = -1;
        startY = -1;
        mpressed = false;
        pornCount++;
        std::filesystem::create_directory("Порно с красавчиками" + std::to_string(pornCount));
    }

    if (event->type == booba::EventType::MousePressed) {
        mpressed = true;

        if (startX < 0 || startY < 0) {
            startX = event->Oleg.mbedata.x;
            startY = event->Oleg.mbedata.y;

            curX = startX;
            curY = startY;
        }
    }
    else if (event->type == booba::EventType::MouseReleased) {
        mpressed = false;
    }

    if (event->type == booba::EventType::MouseMoved && mpressed) {
        if (m_message[m_curPos] == '\n') {
            m_curPos++;
            curX = startX;
            curY += dotSize;
        }
        else if (m_message[m_curPos] == '*') {
            this->putDot(image, curX, curY, dotSize);
            m_curPos++;
            curX += dotSize;
        }
        else {
            m_curPos++;
            curX += dotSize;
        }
    }
}

void MessageTool::putDot(booba::Image* image, int x, int y, int dotSize)
{ 
    for (int curX = std::max(0, x - dotSize); curX < std::min(static_cast<int>(image->getW()), x + dotSize); curX++) {
        for (int curY = std::max(0, y - dotSize); curY < std::min(static_cast<int>(image->getH()), y + dotSize); curY++) {
            image->putPixel(curX, curY, booba::APPCONTEXT->fgColor);
        }
    }
}

const char* MessageTool::getTexture()
{
    return m_texture;
}

void MessageTool::buildSetupWidget()
{

}

void booba::init_module() {
    MessageTool* messageTool = new MessageTool();
    booba::addTool(messageTool);
}
