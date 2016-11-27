#include <algorithm>
#include "bitSet.h"

BitSet::BitSet():m_size( 0 )
{
}

BitSet::BitSet( size_t size ) : m_size( size )
{
	size_t sizeByte = getByteSize( size );
	m_dataVec.reserve( sizeByte );
	m_dataVec.resize( sizeByte );
	memset( &m_dataVec[0],0,sizeByte );
}

BitSet::BitSet( const BitSet &ref )
{
	m_size = ref.m_size;
	size_t sizeByte = getByteSize( ref.m_size );
	m_dataVec.reserve( sizeByte );
	m_dataVec.resize( sizeByte );
	std::copy( ref.m_dataVec.begin(),ref.m_dataVec.end(),m_dataVec.begin() );
}

BitSet::~BitSet()
{
	clear();
}

BitSet& BitSet::operator= (const BitSet& ref )
{
	if( m_size != ref.m_size )
	{
		m_dataVec.resize( getByteSize( m_size ) );
	}
	m_size = ref.m_size;
	std;:copy( ref.m_dataVec.begin(),ref.m_dataVec.end(),m_dataVec.begin() );
	return *this;
}

void BitSet::set( size_t index )
{
	if( index >= m_size )
	{
		return;
	}
	m_dataVec[index >> 3] |= maskAt( index & 7 );
}

void BitSet::reSet( size_t index )
{
	if( index >= m_size )
	{
		return;
	}
	m_dataVec[index >> 3] &= ~maskAt( index & 7 );
}

bool BitSet::get( size_t index )
{
	
		

