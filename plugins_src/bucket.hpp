#ifndef BUCKET_TOOL_HPP
#define BUCKET_TOOL_HPP

#include <queue>
#include <unordered_set>

#include "plugin.hpp"

class BucketTool : public booba::Tool
{
public:
	BucketTool();
	virtual ~BucketTool();

	virtual void apply(booba::Image* image, const booba::Event* event) override;
	virtual const char* getTexture() override; 
	virtual void buildSetupWidget()  override;

	void fill    (booba::Image* image, const std::pair<int, int>& point);
	void fastFill(booba::Image* image, const std::pair<int, int>& point);

private:
	uint32_t m_fillColor = 0x000000FF;
};

#endif // BUCKET_TOOL_HPP
