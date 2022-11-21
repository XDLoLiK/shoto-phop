#ifndef BUCKET_HPP
#define BUCKET_HPP

#include <queue>
#include <unordered_set>

#include "instrument.hpp"
#include "color.hpp"

class Bucket : public Instrument
{
public:
	Bucket(const std::string& icon = "", int x = 0, int y = 0);
	~Bucket();

	virtual bool apply(Surface* surface, booba::Event* event) override;

	void fill    (Surface* surface, std::pair<int, int> point);
	void fastFill(Surface* surface, std::pair<int, int> point);

private:
	Color m_fillColor = black;
};

#endif // BUCKET_HPP
