#ifndef Foundation_SHA1Engine_INCLUDED
#define Foundation_SHA1Engine_INCLUDED


#include "Platform.h"
#include "DigestEngine.h"


class SHA1Engine: public DigestEngine
	/// This class implementes the SHA-1 message digest algorithm.
	/// (FIPS 180-1, see http://www.itl.nist.gov/fipspubs/fip180-1.htm)
{
public:
	enum
	{
		BLOCK_SIZE  = 64,
		DIGEST_SIZE = 20
	};

	SHA1Engine();
	~SHA1Engine();

	unsigned digestLength() const;
	void reset();
	const DigestEngine::Digest& digest();

protected:
	void updateImpl(const void* data, unsigned length);

private:
	void transform();
	static void byteReverse(UINT32* buffer, int byteCount);

	typedef UINT8 BYTE;

	struct Context
	{
		UINT32 digest[5]; // Message digest
		UINT32 countLo;   // 64-bit bit count
		UINT32 countHi;
		UINT32 data[16];  // SHA data buffer
		UINT32 slop;      // # of bytes saved in data[]
	};

	Context _context;
	DigestEngine::Digest _digest;

	SHA1Engine(const SHA1Engine&);
	SHA1Engine& operator = (const SHA1Engine&);
};



#endif // Foundation_SHA1Engine_INCLUDED
