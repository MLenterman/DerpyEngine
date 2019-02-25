#include "Color.h"

namespace Derpy { namespace Graphics {

#define FOIL_PERCEIVED_BRIGHTNESS_HSP
#define FOIL_PERCEIVED_BRIGHTNESS_ACCURATE

#ifdef FOIL_PERCEIVED_BRIGHTNESS_HSP
	#ifdef FOIL_PERCEIVED_BRIGHTNESS_ACCURATE
		#define FOIL_PERCEIVED_BRIGHTNESS_RED 0.299
		#define FOIL_PERCEIVED_BRIGHTNESS_GREEN 0.587
		#define FOIL_PERCEIVED_BRIGHTNESS_BLUE 0.114
	#else
		#define FOIL_PERCEIVED_BRIGHTNESS_RED 0.375
		#define FOIL_PERCEIVED_BRIGHTNESS_GREEN 0.5
		#define FOIL_PERCEIVED_BRIGHTNESS_BLUE 0.125
	#endif
#endif




	Color::Color(){

	}

	Color::Color(unsigned int alpha, unsigned int red, unsigned int green, unsigned int  blue) 
		: color(((alpha & 0xff) << 24) | ((red & 0xff) << 16) | ((green & 0xff) << 8) | (blue & 0xff)){

	}

	Color::Color(unsigned int color)
		: color(color){

	}

	Color::~Color(){

	}

	unsigned int Color::getAlpha() const{
		return color >> 24;
	}

	unsigned int Color::getRed() const{
		return (color >> 16) & 0xff;
	}

	unsigned int Color::getGreen() const{
		return (color >> 8) & 0xff;
	}

	unsigned int Color::getBlue() const{
		return color & 0xff;
	}

	float Color::getLightness() const{
		return 0.5f * (Maths::max(Maths::max(getRed(), getGreen()), getBlue()) + 
					Maths::min(Maths::min(getRed(), getGreen()), getBlue()));
	}

	float Color::getLuminance() const{
		return FOIL_PERCEIVED_BRIGHTNESS_RED * getRed() +
			FOIL_PERCEIVED_BRIGHTNESS_GREEN * getGreen() +
			FOIL_PERCEIVED_BRIGHTNESS_BLUE * getBlue();
	}

	unsigned int Color::getAverage() const{
		return (getRed() + getGreen() + getBlue()) / 3;
	}

	void Color::setAlpha(unsigned int alpha){
		color = ((alpha & 0xff) << 24) | (color & 0x00ffffff);
	}

	void Color::setRed(unsigned int red){
		color = ((red & 0xff) << 16) | (color & 0xff00ffff);
	}

	void Color::setGreen(unsigned int green){
		color = ((green & 0xff) << 8) | (color & 0xffff00ff);
	}

	void Color::setBlue(unsigned int blue){
		color = (blue & 0xff) | (color & 0xffffff00);
	}

	unsigned short Color::toA1R5G5B5() const{
		return 0; //TODO
	}
	
	void Color::toOpenGLColor(unsigned char* dest) const{
		*dest = (unsigned char)getRed();
		*++dest = (unsigned char)getGreen();
		*++dest = (unsigned char)getBlue();
		*++dest = (unsigned char)getAlpha();
	}

	void Color::set(unsigned int alpha, unsigned int red, unsigned int green, unsigned int blue){
		color = (((alpha & 0xff) << 24) | ((red & 0xff) << 16) | ((green & 0xff) << 8) | (blue & 0xff));
	}

	void Color::set(unsigned int color){
		this->color = color;
	}

	bool Color::operator==(const Color& other) const{
		return color == other.color;
	}

	bool Color::operator!=(const Color& other) const{
		return color != other.color;
	}

	bool Color::operator<(const Color& other) const{
		return color < other.color;
	}

	Color Color::operator+(const Color& other) const{
		return Color(
			Maths::min(getAlpha() + other.getAlpha(), 255u),
			Maths::min(getRed() + other.getRed(), 255u),
			Maths::min(getGreen() + other.getGreen(), 255u),
			Maths::min(getBlue() + other.getBlue(), 255u));
	}

	Color Color::getInterpolated(const Color &other, float d) const{
		d = Maths::clamp(d, 0.0f, 1.0f);
		const float inv = 1.0f - d;
		
		return Color(
			(unsigned int)Maths::round32(other.getAlpha() * inv + getAlpha() * d),
			(unsigned int)Maths::round32(other.getRed() * inv + getRed() * d),
			(unsigned int)Maths::round32(other.getGreen() * inv + getGreen() * d),
			(unsigned int)Maths::round32(other.getBlue() * inv + getBlue() * d));
	}

} }