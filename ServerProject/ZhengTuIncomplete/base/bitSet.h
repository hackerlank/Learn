#ifndef BIT_SET_H
#define BIT_SET_H

class BitSet
{
	public:
		typedef unsigned char ValueType;
		typedef const unsigned char ConstValueType;

		BitSet();
		explicit BitSet( size_t size );
		BitSet( const BitSet &ref );
		~BitSet();

		BitSet& operator= (const BitSet &ref );
		void set( size_t index );
		void reSet( size_t index );
		bool get( size_t index );

		bool operator[] (size_t index ) const;
		void reSize( size_t index );
		void reSet();
		void clear();

		size_t sizeSet() const;
		size_t size() const;

		int findFirstSet() const;
		int findFirstUnSet() const;

		static size_t getByteSize( size_t size );
		static ValueType maskAt( size_t index );
		static ValueType maskBefore( size_t index );
		static ValueType maskFrom( size_t index );

		const ValueType* data() const;
		size_t sizeByte() const;

	private:
		void flush( size_t size );
		int findFirstByte( bool set ) const;
		int findFirstBit( bool set ) const;
	private:
		size_t m_size;
		vector< ValueType > m_dataVec;
};

#endif
