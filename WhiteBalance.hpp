#ifndef WhiteBalance_hpp
#define WhiteBalance_hpp

#include<string>

class WhiteBalancer
{
public:
	WhiteBalancer(int ill, int vp, int sq) :ill{ ill }, vp{ vp }, sq{ sq } {}

	void greyPatch(float data[5][5][4][3], bool removeSpecular, const std::string& filename);//data[ill][vp][sq][3]
	void greyWorld(float data[5][5][4][3], bool removeSpecular, const std::string& filename);//data[ill][vp][sq][3]
	void whiteWorld(float data[5][5][4][3], bool removeSpecular, const std::string& filename);//data[ill][vp][sq][3]

	void linearize(float data[5][5][4][3], float g);
	void normalize(float data[5][5][4][3]);

	void writeToFile(float data[5][5][4][3], const std::string& filename);

private:
	int ill;
	int vp;
	int sq;
};

#endif // !WhiteBalance_hpp

