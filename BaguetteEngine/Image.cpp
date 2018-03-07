#include "Image.h"
#include "ofMain.h"

Image::Image()
{
	isLoaded = false;
}

Image::Image(std::string filename)
{
	if (theImg.load("Image/" + filename) == 0)
		throw std::invalid_argument("Wrong Path.");
	else
		isLoaded = true;
}


Image::~Image()
{
}

void Image::Load(std::string filename)
{
	if (theImg.load("Image/" + filename) == 0)
		throw std::invalid_argument("Wrong Path.");
	else
		isLoaded = true;
}

void Image::Export(std::string filename)
{
	theImg.grabScreen(0,0,ofGetWidth(), ofGetHeight());
	theImg.save("Image/"+filename + ".jpg");
}

void Image::Draw(float x, float y)
{
	theImg.draw(x, y);

}
void Image::Draw(float x, float y, int width, int heigh)
{
	theImg.draw(x, y,width, heigh);
}

void Image::DrawPartOfImage(float posx, float posy, float toxpx, float toypx, float fromxpx, float fromypx)
{
	theImg.drawSubsection(posx, posy, toxpx, toypx, fromxpx, fromypx);
}