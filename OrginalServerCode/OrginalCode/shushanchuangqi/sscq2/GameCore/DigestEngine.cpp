#include "Config.h"

#include "DigestEngine.h"


DigestEngine::DigestEngine()
{
}


DigestEngine::~DigestEngine()
{
}


std::string DigestEngine::digestToHex(const Digest& bytes)
{
	static const char digits[] = "0123456789abcdef";
	std::string result;
	result.reserve(bytes.size()*2);
	for (Digest::const_iterator it = bytes.begin(); it != bytes.end(); ++it)
	{
		unsigned char c = *it;
		result += digits[(c >> 4) & 0xF];
		result += digits[c & 0xF];
	}
	return result;
}

