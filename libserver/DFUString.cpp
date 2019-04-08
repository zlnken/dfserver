#include "DFUString.h"
#include <assert.h>
namespace DF{

	UString::_base_iterator::_base_iterator(void)
	{
		mString = 0;
	}
	void UString::_base_iterator::_seekFwd(size_type c)
	{
		mIter += c;
	}
	void UString::_base_iterator::_seekRev(size_type c)
	{
		mIter -= c;
	}
	void UString::_base_iterator::_become(const _base_iterator& i)
	{
		mIter = i.mIter;
		mString = i.mString;
	}
	bool UString::_base_iterator::_test_begin(void) const
	{
		return mIter == mString->mData.begin();
	}
	bool UString::_base_iterator::_test_end(void) const
	{
		return mIter == mString->mData.end();
	}
	UString::size_type UString::_base_iterator::_get_index(void)const
	{
		return mIter - mString->mData.begin();
	}
	void UString::_base_iterator::_jump_to(size_type index)
	{
		mIter = mString->mData.begin() + index;
	}
	UString::unicode_char UString::_base_iterator::_getCharacter(void)const
	{
		size_type current_index = _get_index();
		return mString->getChar(current_index);
	}
	int UString::_base_iterator::_setCharacter(unicode_char uc)
	{
		size_type current_index = _get_index();
		int change = mString->setChar( current_index, uc );
		_jump_to( current_index );
		return change;
	}
	void UString::_base_iterator::_moveNext(void)
	{
		_seekFwd( 1 );
		if ( _test_end() ) return; 
		if ( _utf16_surrogate_follow( mIter[0] ) )
		{
			code_point lead_half = 0;
			lead_half = mIter[-1];
			if ( _utf16_surrogate_lead( lead_half ) ) 
			{
				_seekFwd( 1 );
			}
		}
	}
	void UString::_base_iterator::_movePrev(void)
	{
		_seekRev( 1 ); 
		if ( _test_begin() ) return; 
		if ( _utf16_surrogate_follow( mIter[0] ) )
		{
			code_point lead_half = 0;
			lead_half = mIter[-1]; 
			if ( _utf16_surrogate_lead( lead_half ) )
			{
				_seekRev( 1 ); 
			}
		}
	}

	UString::_fwd_iterator::_fwd_iterator(void)
	{

	}
	UString::_fwd_iterator::_fwd_iterator(const _fwd_iterator& i)
	{
		_become( i );
	}
	UString::_fwd_iterator& UString::_fwd_iterator::operator++(void)
	{
		_seekFwd( 1 );
		return *this;
	}
	UString::_fwd_iterator UString::_fwd_iterator::operator++(int)
	{
		_fwd_iterator tmp( *this );
		_seekFwd( 1 );
		return tmp;
	}
	UString::_fwd_iterator& UString::_fwd_iterator::operator--(void)
	{
		_seekRev( 1 );
		return *this;
	}
	UString::_fwd_iterator UString::_fwd_iterator::operator--(int)
	{
		_fwd_iterator tmp( *this );
		_seekRev( 1 );
		return tmp;
	}
	UString::_fwd_iterator UString::_fwd_iterator::operator+(difference_type n)
	{
		_fwd_iterator tmp( *this );
		if ( n < 0 )
			tmp._seekRev( -n );
		else
			tmp._seekFwd( n );
		return tmp;
	}
	UString::_fwd_iterator UString::_fwd_iterator::operator-(difference_type n)
	{
		_fwd_iterator tmp( *this );
		if ( n < 0 )
			tmp._seekFwd( -n );
		else
			tmp._seekRev( n );
		return tmp;
	}
	UString::_fwd_iterator& UString::_fwd_iterator::operator+=(difference_type n)
	{
		if ( n < 0 )
			_seekRev( -n );
		else
			_seekFwd( n );
		return *this;
	}
	UString::_fwd_iterator& UString::_fwd_iterator::operator-=(difference_type n)
	{
		if ( n < 0 )
			_seekFwd( -n );
		else
			_seekRev( n );
		return *this;
	}
	UString::value_type& UString::_fwd_iterator::operator*(void) const
	{
		return *mIter;
	}
	UString::value_type& UString::_fwd_iterator::operator[](difference_type n) const
	{
		_fwd_iterator tmp( *this );
		tmp += n;
		return *tmp;
	}
	UString::_fwd_iterator& UString::_fwd_iterator::moveNext(void)
	{
		_moveNext();
		return *this;
	}
	UString::_fwd_iterator& UString::_fwd_iterator::movePrev(void)
	{
		_movePrev();
		return *this;
	}
	UString::unicode_char UString::_fwd_iterator::getCharacter(void) const
	{
		return _getCharacter();
	}
	int UString::_fwd_iterator::setCharacter(unicode_char uc)
	{
		return _setCharacter(uc);
	}

	UString::_const_fwd_iterator::_const_fwd_iterator(void)
	{
	}
	UString::_const_fwd_iterator::_const_fwd_iterator(const _const_fwd_iterator& i)
	{
		_become(i);
	}

	UString::_const_fwd_iterator::_const_fwd_iterator(const _fwd_iterator& i)
	{
		_become(i);
	}

	UString::_const_fwd_iterator& UString::_const_fwd_iterator::operator++(void)
	{
		_seekFwd( 1 );
		return *this;
	}
	UString::_const_fwd_iterator UString::_const_fwd_iterator::operator++(int)
	{
		_const_fwd_iterator tmp( *this );
		_seekFwd( 1 );
		return tmp;
	}
	UString::_const_fwd_iterator& UString::_const_fwd_iterator::operator--(void)
	{
		_seekRev( 1 );
		return *this;
	}
	UString::_const_fwd_iterator UString::_const_fwd_iterator::operator--(int)
	{
		_const_fwd_iterator tmp( *this );
		_seekRev( 1 );
		return tmp;
	}
	UString::_const_fwd_iterator UString::_const_fwd_iterator::operator+(difference_type n)
	{
		_const_fwd_iterator tmp( *this );
		if ( n < 0 )
			tmp._seekRev( -n );
		else
			tmp._seekFwd( n );
		return tmp;
	}
	UString::_const_fwd_iterator UString::_const_fwd_iterator::operator-(difference_type n)
	{
		_const_fwd_iterator tmp( *this );
		if ( n < 0 )
			tmp._seekFwd( -n );
		else
			tmp._seekRev( n );
		return tmp;
	}
	UString::_const_fwd_iterator& UString::_const_fwd_iterator::operator+=(difference_type n)
	{
		if ( n < 0 )
			_seekRev( -n );
		else
			_seekFwd( n );
		return *this;
	}
	UString::_const_fwd_iterator& UString::_const_fwd_iterator::operator-=(difference_type n)
	{
		if ( n < 0 )
			_seekFwd( -n );
		else
			_seekRev( n );
		return *this;
	}
	UString::value_type& UString::_const_fwd_iterator::operator*(void) const
	{
		return *mIter;
	}
	UString::value_type& UString::_const_fwd_iterator::operator[](difference_type n) const
	{
		_const_fwd_iterator tmp( *this );
		tmp += n;
		return *tmp;
	}
	UString::_const_fwd_iterator& UString::_const_fwd_iterator::moveNext(void)
	{
		_moveNext();
		return *this;
	}
	UString::_const_fwd_iterator& UString::_const_fwd_iterator::movePrev(void)
	{
		_movePrev();
		return *this;
	}
	UString::unicode_char UString::_const_fwd_iterator::getCharacter(void) const
	{
		return _getCharacter();
	}

	UString::_rev_iterator::_rev_iterator(void)
	{

	}
	UString::_rev_iterator::_rev_iterator(const _rev_iterator& i)
	{
		_become( i );
	}

	UString::_rev_iterator& UString::_rev_iterator::operator++(void)
	{
		_seekRev( 1 );
		return *this;
	}
	UString::_rev_iterator UString::_rev_iterator::operator++(int)
	{
		_rev_iterator tmp( *this );
		_seekRev( 1 );
		return tmp;
	}
	UString::_rev_iterator& UString::_rev_iterator::operator--(void)
	{
		_seekFwd( 1 );
		return *this;
	}
	UString::_rev_iterator UString::_rev_iterator::operator--(int)
	{
		_rev_iterator tmp( *this );
		_seekFwd( 1 );
		return tmp;
	}
	UString::_rev_iterator UString::_rev_iterator::operator+(difference_type n)
	{
		_rev_iterator tmp( *this );
		if ( n < 0 )
			tmp._seekFwd( -n );
		else
			tmp._seekRev( n );
		return tmp;
	}
	UString::_rev_iterator UString::_rev_iterator::operator-(difference_type n)
	{
		_rev_iterator tmp( *this );
		if ( n < 0 )
			tmp._seekRev( -n );
		else
			tmp._seekFwd( n );
		return tmp;
	}
	UString::_rev_iterator& UString::_rev_iterator::operator+=(difference_type n)
	{
		if ( n < 0 )
			_seekFwd( -n );
		else
			_seekRev( n );
		return *this;
	}
	UString::_rev_iterator& UString::_rev_iterator::operator-=(difference_type n)
	{
		if ( n < 0 )
			_seekRev( -n );
		else
			_seekFwd( n );
		return *this;
	}
	UString::value_type& UString::_rev_iterator::operator*(void) const
	{
		return mIter[-1];
	}
	UString::value_type& UString::_rev_iterator::operator[](difference_type n) const
	{
		_rev_iterator tmp( *this );
		tmp -= n;
		return *tmp;
	}
	UString::unicode_char UString::_rev_iterator::getCharacter(void) const
	{
		return _getCharacter();
	}

	UString::_const_rev_iterator::_const_rev_iterator(void)
	{

	}
	UString::_const_rev_iterator::_const_rev_iterator(const _const_rev_iterator& i)
	{
		_become( i );
	}
	UString::_const_rev_iterator::_const_rev_iterator(const _rev_iterator& i)
	{
		_become(i);
	}

	UString::_const_rev_iterator& UString::_const_rev_iterator::operator++(void)
	{
		_seekRev( 1 );
		return *this;
	}
	UString::_const_rev_iterator UString::_const_rev_iterator::operator++(int)
	{
		_const_rev_iterator tmp( *this );
		_seekRev( 1 );
		return tmp;
	}
	UString::_const_rev_iterator& UString::_const_rev_iterator::operator--(void)
	{
		_seekFwd( 1 );
		return *this;
	}
	UString::_const_rev_iterator UString::_const_rev_iterator::operator--(int)
	{
		_const_rev_iterator tmp( *this );
		_seekFwd( 1 );
		return tmp;
	}
	UString::_const_rev_iterator UString::_const_rev_iterator::operator+(difference_type n)
	{
		_const_rev_iterator tmp( *this );
		if ( n < 0 )
			tmp._seekFwd( -n );
		else
			tmp._seekRev( n );
		return tmp;
	}
	UString::_const_rev_iterator UString::_const_rev_iterator::operator-(difference_type n)
	{
		_const_rev_iterator tmp( *this );
		if ( n < 0 )
			tmp._seekRev( -n );
		else
			tmp._seekFwd( n );
		return tmp;
	}
	UString::_const_rev_iterator& UString::_const_rev_iterator::operator+=(difference_type n)
	{
		if ( n < 0 )
			_seekFwd( -n );
		else
			_seekRev( n );
		return *this;
	}
	UString::_const_rev_iterator& UString::_const_rev_iterator::operator-=(difference_type n)
	{
		if ( n < 0 )
			_seekRev( -n );
		else
			_seekFwd( n );
		return *this;
	}
	UString::value_type& UString::_const_rev_iterator::operator*(void) const
	{
		return mIter[-1];
	}
	UString::value_type& UString::_const_rev_iterator::operator[](difference_type n) const
	{
		_const_rev_iterator tmp( *this );
		tmp -= n;
		return *tmp;
	}
	UString::unicode_char UString::_const_rev_iterator::getCharacter(void) const
	{
		return _getCharacter();
	}


	UString::~UString( void )
	{
		_cleanBuffer();
	}

	UString::UString(void)
	{
		_init();
	}

	UString::UString(const UString& copy)
	{
		_init();
		mData = copy.mData;
	}

	UString::UString(unsigned int length, unsigned short ch)
	{
		_init();
		assign((size_t)length, (const code_point)ch);
	}

	UString::UString(const code_point* str)
	{
		_init();
		assign(str);
	}

	UString::UString(const code_point* str, size_type length)
	{
		_init();
		assign(str, length);
	}

	UString::UString(const UString& str, size_type index, size_type length)
	{
		_init();
		assign(str, index, length);
	}

	UString::UString(const wchar_t* w_str)
	{
		_init();
		assign(w_str);
	}

	UString::UString(const wchar_t* w_str, size_type length)
	{
		_init();
		assign(w_str, length);
	}

	UString::UString(const std::wstring& wstr)
	{
		_init();
		assign(wstr);
	}

	UString::UString(const std::string& c_str)
	{
		_init();
		assign(c_str);
	}

	UString::UString(const char* c_str, size_type length)
	{
		_init();
		assign(c_str, length);
	}

	UString::UString(const char* str)
	{
		_init();
		assign(str);
	}

	void UString::_init(void)
	{
		m_bufferType = bt_none;
		m_bufferSize = 0;
		m_buffer.mVoidBuffer = 0;

	}

	void UString::_cleanBuffer(void)const
	{
		if ( m_buffer.mVoidBuffer != 0 ) {
			switch ( m_bufferType ) {
			case bt_string:
				delete m_buffer.mStrBuffer;
				break;
			case bt_wstring:
				delete m_buffer.mWStrBuffer;
				break;
			case bt_utf32string:
				delete m_buffer.mUTF32StrBuffer;
				break;
			case bt_none: 
			default:
				assert("This should never happen - mVoidBuffer should never contain something if we "
					"don't know the type");
				break;
			}
			m_buffer.mVoidBuffer = 0;
			m_bufferSize = 0;
			m_bufferType = bt_none;
		}
	}

	void UString::_getBufferStr(void)const
	{
		if ( m_bufferType != bt_string ) {
			_cleanBuffer();
			m_buffer.mStrBuffer = new std::string();
			m_bufferType = bt_string;
		}
		m_buffer.mStrBuffer->clear();
	}

	void UString::_getBufferWStr(void) const
	{
		if ( m_bufferType != bt_wstring ) {
			_cleanBuffer();
			m_buffer.mWStrBuffer = new std::wstring();
			m_bufferType = bt_wstring;
		}
		m_buffer.mWStrBuffer->clear();
	}

	void UString::_getBufferUTF32Str(void)const
	{
		if ( m_bufferType != bt_utf32string ) {
			_cleanBuffer();
			m_buffer.mUTF32StrBuffer = new utf32string();
			m_bufferType = bt_utf32string;
		}
		m_buffer.mUTF32StrBuffer->clear();
	}
	void UString::_load_buffer_UTF8(void)const
	{
		_getBufferStr();
		std::string& buffer = (*m_buffer.mStrBuffer);
		buffer.reserve(length());

		unsigned char utf8buf[6];
		char* charbuf = ( char* )utf8buf;
		unicode_char c;
		size_t len;

		const_iterator i, ie = end();
		for ( i = begin(); i != ie; i.moveNext() ) 
		{
			c = i.getCharacter();
			len = _utf32_to_utf8( c, utf8buf );
			size_t j = 0;
			while ( j < len )
				buffer.push_back( charbuf[j++] );
		}
	}

	void UString::_load_buffer_WStr(void)const
	{
		_getBufferWStr();
		std::wstring& buffer = ( *m_buffer.mWStrBuffer );
		buffer.reserve( length() ); // may over reserve, but should be close enough

		const_iterator i, ie = end();
		for ( i = begin(); i != ie; ++i )
		{
			buffer.push_back(( wchar_t )( *i ) );
		}
	}

	void UString::_load_buffer_UTF32(void)const
	{
		_getBufferUTF32Str();
		utf32string& buffer = ( *m_buffer.mUTF32StrBuffer );
		buffer.reserve( length() ); 

		unicode_char c;

		const_iterator i, ie = end();
		for ( i = begin(); i != ie; i.moveNext() )
		{
			c = i.getCharacter();
			buffer.push_back( c );
		}
	}

	UString::unicode_char UString::getChar(size_type loc)const
	{
		const code_point* ptr = c_str();
		unicode_char uc;
		size_t l = _utf16_char_length( ptr[loc] );
		code_point cp[2] = { 0, 0 };
		cp[0] = ptr[loc];
		if ( l == 2 && ( loc + 1 ) < mData.length() )
		{
			cp[1] = ptr[loc+1];
		}
		_utf16_to_utf32(cp, uc);
		return uc;
	}

	int UString::setChar( size_type loc, unicode_char ch )
	{
		code_point cp[2] = { 0, 0};
		size_t l = _utf32_to_utf16( ch, cp );
		unicode_char existingChar = getChar( loc );
		size_t existingSize = _utf16_char_length( existingChar );
		size_t newSize = _utf16_char_length( ch );

		if ( newSize > existingSize ) {
			at( loc ) = cp[0];
			insert( loc + 1, 1, cp[1] );
			return 1;
		}
		if ( newSize < existingSize ) 
		{
			erase( loc, 1 );
			at( loc ) = cp[0];
			return -1;
		}
		at( loc ) = cp[0];
		if ( l == 2 ) at( loc + 1 ) = cp[1];
		return 0;
	}

	UString::size_type UString::size(void)const
	{
		return mData.size();
	}

	UString::size_type UString::length(void)const
	{
		return mData.length();
	}

	UString::size_type UString::length_Characters(void)const
	{
		const_iterator itBegin = begin();
		const_iterator itEnd = end();
		UString::size_type lengthCount = 0;
		while(itBegin != itEnd)
		{
			unicode_char uc = itBegin.getCharacter();
			lengthCount += (uc > 256 ? 2 : 1);
			++itBegin;
		}
		return lengthCount;
	}

	UString::size_type UString::max_size(void)const
	{
		return mData.max_size();
	}

	void UString::reserve(size_type size)
	{
		mData.reserve(size);
	}

	void UString::resize(size_type num, const code_point& val)
	{
		mData.resize(num, val);
	}

	void UString::swap( UString& from )
	{
		mData.swap(from.mData);
	}

	bool UString::empty(void)const
	{
		return mData.empty();
	}

	const UString::code_point* UString::c_str(void)const
	{
		return mData.c_str();
	}

	const  UString::code_point* UString::data(void)const
	{
		return c_str();
	}

	UString::size_type UString::capacity( void ) const
	{
		return mData.capacity();
	}

	void UString::clear(void)
	{
		mData.clear();
	}

	UString UString::substr(size_type index, size_type num)const
	{
		dstring data = mData.substr(index, num);
		UString tmp;
		tmp.mData.swap(data);
		return tmp;
	}
	UString::code_point& UString::at(size_type loc)
	{
		return mData.at(loc);
	}

	const UString::code_point& UString::at(size_type loc) const
	{
		return mData.at(loc);
	}

	bool UString::inString( unicode_char ch ) const
	{
		const_iterator i, ie = end();
		for ( i = begin(); i != ie; i.moveNext() ) {
			if ( i.getCharacter() == ch )
				return true;
		}
		return false;
	}

	const char* UString::asUTF8(void) const
	{
		_load_buffer_UTF8();
		return m_buffer.mStrBuffer->c_str();
	}

	const UString::utf32string& UString::asUTF32(void)const
	{
		_load_buffer_UTF32();
		return *m_buffer.mUTF32StrBuffer;
	}

	const UString::unicode_char* UString::asUTF32_c_str(void)const
	{
		_load_buffer_UTF32();
		return m_buffer.mUTF32StrBuffer->c_str();
	}

	const std::wstring& UString::asWStr(void)const
	{
		_load_buffer_WStr();
		return *m_buffer.mWStrBuffer;
	}

	const wchar_t* UString::asWStr_c_str(void)const
	{
		_load_buffer_WStr();
		return m_buffer.mWStrBuffer->c_str();
	}

	UString::iterator UString::begin( void )
	{
		iterator i;
		i.mIter = mData.begin();
		i.mString = this;
		return i;
	}

	void UString::setBegin(void)
	{
		m_It = this->begin();
	}
	unsigned int UString::getNext(void)const
	{
		return m_It.getCharacter();
	}
	
	void UString::next(void)
	{
		++m_It;
	}

	bool UString::hasNext(void)const
	{
		return m_It != this->end();
	}

	UString::const_iterator UString::begin(void)const
	{
		const_iterator i;
		i.mIter = const_cast<UString*>(this)->mData.begin();
		i.mString = const_cast<UString*>(this);
		return i;
	}
	UString::iterator UString::end(void)
	{
		iterator i;
		i.mIter = mData.end();
		i.mString = this;
		return i;
	}
	UString::const_iterator UString::end(void)const
	{
		const_iterator i;
		i.mIter = const_cast<UString*>(this)->mData.end();
		i.mString = const_cast<UString*>(this);
		return i;
	}
	UString::reverse_iterator UString::rbegin(void)
	{
		reverse_iterator i;
		i.mIter = mData.end();
		i.mString = this;
		return i;
	}
	UString::const_reverse_iterator UString::rbegin(void)const
	{
		const_reverse_iterator i;
		i.mIter = const_cast<UString*>(this)->mData.end();
		i.mString = const_cast<UString*>(this);
		return i;
	}
	UString::reverse_iterator UString::rend(void)
	{
		reverse_iterator i;
		i.mIter = mData.begin();
		i.mString = this;
		return i;
	}
	UString::const_reverse_iterator UString::rend(void)const
	{
		const_reverse_iterator i;
		i.mIter = const_cast<UString*>(this)->mData.begin();
		i.mString = const_cast<UString*>(this);
		return i;
	}

	UString::iterator UString::erase(iterator loc)
	{
		iterator ret;
		ret.mIter = mData.erase( loc.mIter );
		ret.mString = this;
		return ret;
	}
	UString::iterator UString::erase(iterator start, iterator end)
	{
		iterator ret;
		ret.mIter = mData.erase(start.mIter, end.mIter);
		ret.mString = this;
		return ret;
	}
	UString& UString::erase(size_type index, size_type num)
	{
		if ( num == npos )
			mData.erase( index );
		else
			mData.erase( index, num );
		return *this;
	}

	UString& UString::assign(iterator start, iterator end)
	{
		mData.assign(start.mIter, end.mIter);
		return *this;
	}

	UString& UString::assign( const UString& str )
	{
		mData.assign( str.mData );
		return *this;
	}
	UString& UString::assign(const code_point* str)
	{
		mData.assign( str );
		return *this;
	}
	UString& UString::assign(const code_point* str, size_type num)
	{
		mData.assign( str, num );
		return *this;
	}
	UString& UString::assign(const UString& str, size_type index, size_type len)
	{
		mData.assign( str.mData, index, len );
		return *this;
	}
	UString& UString::assign(size_type num, const code_point& ch)
	{
		mData.assign( num, ch );
		return *this;
	}
	UString& UString::assign( const std::wstring& wstr )
	{
		mData.clear();
		mData.reserve(wstr.length()); 
		code_point tmp;
		std::wstring::const_iterator i, ie = wstr.end();
		for ( i = wstr.begin(); i != ie; i++ ) 
		{
			tmp = static_cast<code_point>( *i );
			mData.push_back( tmp );
		}
		return *this;
	}
	UString& UString::assign(const wchar_t* w_str)
	{
		std::wstring tmp;
		tmp.assign( w_str );
		return assign( tmp );
	}
	UString& UString::assign(const wchar_t* w_str, size_type num)
	{
		std::wstring tmp;
		tmp.assign( w_str, num );
		return assign( tmp );
	}
	UString& UString::assign(const std::string& str)
	{
		size_type len = _verifyUTF8( str );
		clear(); 
		reserve( len ); 

		unicode_char uc;          
		unsigned char utf8buf[7]; 
		utf8buf[6] = 0;
		size_t utf8len;           
		code_point utf16buff[3];  
		utf16buff[2] = 0;
		size_t utf16len;          

		std::string::const_iterator i, ie = str.end();
		for ( i = str.begin(); i != ie; i++ ) 
		{
			utf8len = _utf8_char_length( static_cast<unsigned char>( *i ) ); 
			for ( size_t j = 0; j < utf8len; j++ )
			{ 
				utf8buf[j] = ( static_cast<unsigned char>( *( i + j ) ) );
			}
			utf8buf[utf8len] = 0;
			utf8len = _utf8_to_utf32( utf8buf, uc ); 
			i += utf8len - 1; 

			utf16len = _utf32_to_utf16( uc, utf16buff ); 
			append( utf16buff, utf16len ); 
		}
		return *this;
	}

	UString& UString::assign( const char* c_str )
	{
		std::string tmp( c_str );
		return assign( tmp );
	}
	UString& UString::assign( const char* c_str, size_type num )
	{
		std::string tmp;
		tmp.assign( c_str, num );
		return assign( tmp );
	}

	UString& UString::append(const UString& str)
	{
		mData.append( str.mData );
		return *this;
	}
	UString& UString::append(const code_point* str)
	{
		mData.append( str );
		return *this;
	}
	UString& UString::append(const UString& str, size_type index, size_type len)
	{
		mData.append( str.mData, index, len );
		return *this;
	}
	UString& UString::append(const code_point* str, size_type num)
	{
		mData.append( str, num );
		return *this;
	}
	UString& UString::append(size_type num, code_point ch)
	{
		mData.append( num, ch );
		return *this;
	}
	UString& UString::append(iterator start, iterator end)
	{
		mData.append( start.mIter, end.mIter );
		return *this;
	}
	UString& UString::append(const wchar_t* w_str, size_type num)
	{
		std::wstring tmp(w_str, num);
		return *this;
	}
	UString& UString::append(size_type num, wchar_t ch)
	{
		return append( num, static_cast<unicode_char>( ch ) );
	}
	UString& UString::append(const char* c_str, size_type num)
	{
		UString tmp( c_str, num );
		append( tmp );
		return *this;
	}
	UString& UString::append(size_type num, char ch)
	{
		append( num, static_cast<code_point>( ch ) );
		return *this;
	}

	UString& UString::append(size_type num, unicode_char ch)
	{
		code_point cp[2] = {0, 0};
		if ( _utf32_to_utf16( ch, cp ) == 2 )
		{
			for ( size_type i = 0; i < num; i++ )
			{
				append( 1, cp[0] );
				append( 1, cp[1] );
			}
		} 
		else 
		{
			for ( size_type i = 0; i < num; i++ )
			{
				append( 1, cp[0] );
			}
		}
		return *this;
	}

	void UString::push_back(unicode_char val)
	{
		code_point cp[2];
		size_t c = _utf32_to_utf16( val, cp );
		if ( c > 0 ) push_back( cp[0] );
		if ( c > 1 ) push_back( cp[1] );
	}

	void UString::push_back(wchar_t val)
	{
		mData.push_back(static_cast<code_point>(val));
	}

	void UString::push_back(code_point val)
	{
		mData.push_back(val);
	}

	void UString::push_back(char val)
	{
		mData.push_back(static_cast<code_point>(val));
	}

	UString::iterator UString::insert(iterator i, const code_point& ch)
	{
		iterator ret;
		ret.mIter = mData.insert( i.mIter, ch );
		ret.mString = this;
		return ret;
	}
	UString& UString::insert(size_type index, const UString& str)
	{
		mData.insert( index, str.mData );
		return *this;
	}
	UString& UString::insert( size_type index, const code_point* str)
	{
		mData.insert(index, str);
		return *this; 
	}
	UString& UString::insert(size_type index1, const UString& str, size_type index2, size_type num)
	{
		mData.insert( index1, str.mData, index2, num );
		return *this;
	}
	void UString::insert(iterator i, iterator start, iterator end)
	{
		mData.insert( i.mIter, start.mIter, end.mIter );
	}
	UString& UString::insert(size_type index, const code_point* str, size_type num)
	{
		mData.insert( index, str, num );
		return *this;
	}
	UString& UString::insert(size_type index, const wchar_t* w_str, size_type num)
	{
		UString tmp(w_str,num);
		insert( index, tmp );
		return *this;
	}
	UString& UString::insert(size_type index, const char* c_str, size_type num)
	{
		UString tmp( c_str, num );
		insert( index, tmp );
		return *this;
	}
	UString& UString::insert(size_type index, size_type num, code_point ch)
	{
		mData.insert( index, num, ch );
		return *this;
	}
	UString& UString::insert(size_type index, size_type num, wchar_t ch)
	{
		insert( index, num, static_cast<unicode_char>( ch ) );
		return *this;
	}
	UString& UString::insert(size_type index, size_type num, char ch)
	{
		insert( index, num, static_cast<code_point>( ch ) );
		return *this;
	}
	UString& UString::insert(size_type index, size_type num, unicode_char ch)
	{
		code_point cp[3] = {0, 0, 0};
		size_t l = _utf32_to_utf16( ch, cp );
		if ( l == 1 ) 
		{
			return insert( index, num, cp[0] );
		}
		for ( size_type c = 0; c < num; c++ )
		{
			insert( index, 1, cp[1] );
			insert( index, 1, cp[0] );
		}
		return *this;
	}
	void UString::insert(iterator i, size_type num, const code_point& ch)
	{
		mData.insert( i.mIter, num, ch );
	}
	void UString::insert(iterator i, size_type num, const wchar_t& ch)
	{
		insert( i, num, static_cast<unicode_char>( ch ) );
	}
	void UString::insert(iterator i, size_type num, const char& ch)
	{
		insert( i, num, static_cast<code_point>( ch ) );
	}
	void UString::insert(iterator i, size_type num, const unicode_char& ch)
	{
		code_point cp[3] = {0, 0, 0};
		size_t l = _utf32_to_utf16( ch, cp );
		if ( l == 1 ) 
		{
			insert( i, num, cp[0] );
		} else 
		{
			for ( size_type c = 0; c < num; c++ ) 
			{
				insert( i, 1, cp[1] );
				insert( i, 1, cp[0] );
			}
		}
	}
	UString& UString::replace(size_type index1, size_type num1, const UString& str)
	{
		mData.replace(index1, num1, str.mData, 0, npos);
		return *this;
	}
	UString& UString::replace(size_type index1, size_type num1, const UString& str, size_type num2)
	{
		mData.replace( index1, num1, str.mData, 0, num2 );
		return *this;
	}
	UString& UString::replace(size_type index1, size_type num1, const UString& str, size_type index2, size_type num2)
	{
		mData.replace( index1, num1, str.mData, index2, num2 );
		return *this;
	}
	UString& UString::replace(iterator start, iterator end, const UString& str, size_type num)
	{
		_const_fwd_iterator st(start); 
		size_type index1 = begin() - st;
		size_type num1 = end - st;
		return replace( index1, num1, str, 0, num );
	}
	UString& UString::replace(size_type index, size_type num1, size_type num2, code_point ch)
	{
		mData.replace(index, num1, num2, ch);
		return *this;
	}
	UString& UString::replace(iterator start, iterator end, size_type num, code_point ch)
	{
		_const_fwd_iterator st(start); 
		size_type index1 = begin() - st;
		size_type num1 = end - st;
		return replace(index1, num1, num, ch);
	}

	int UString::compare(const UString& str)const
	{
		return mData.compare(str.mData);
	}
	int UString::compare(const code_point* str)const
	{
		return mData.compare(str);
	}
	int UString::compare(size_type index, size_type length, const UString& str) const
	{
		return mData.compare(index, length, str.mData);
	}
	int UString::compare(size_type index, size_type length, const UString& str, size_type index2, size_type length2)const
	{
		return mData.compare(index, length, str.mData, index2, length2);
	}
	int UString::compare(size_type index, size_type length, const code_point* str, size_type length2)const
	{
		return mData.compare(index, length, str, length2);
	}
	int UString::compare(size_type index, size_type length, const wchar_t* w_str, size_type length2)const
	{
		UString tmp( w_str, length2 );
		return compare(index, length, tmp);
	}
	int UString::compare(size_type index, size_type length, const char* c_str, size_type length2)const
	{
		UString tmp(c_str, length2);
		return compare(index, length, tmp);
	}

	UString::size_type UString::find(const UString& str, size_type index)const
	{
		return mData.find( str.c_str(), index );
	}

	UString::size_type UString::find(const code_point* cp_str, size_type index, size_type length)const
	{
		UString tmp( cp_str );
		return mData.find( tmp.c_str(), index, length );
	}

	UString::size_type UString::find(const char* c_str, size_type index, size_type length)const
	{
		UString tmp( c_str );
		return mData.find( tmp.c_str(), index, length );
	}

	UString::size_type UString::find(const wchar_t* w_str, size_type index, size_type length)const
	{
		UString tmp( w_str );
		return mData.find( tmp.c_str(), index, length );
	}

	UString::size_type UString::find(char ch, size_type index)const
	{
		return find( static_cast<code_point>( ch ), index );	
	}

	UString::size_type UString::find(code_point ch, size_type index)const
	{
		return mData.find( ch, index );
	}

	UString::size_type UString::find(wchar_t ch, size_type index)const
	{
		return find( static_cast<unicode_char>( ch ), index );
	}

	UString::size_type UString::find(unicode_char ch, size_type index)const
	{
		code_point cp[3] = {0, 0, 0};
		size_t l = _utf32_to_utf16( ch, cp );
		return find( UString( cp, l ), index );
	}

	UString::size_type UString::rfind(const UString& str, size_type index)const
	{
		return mData.rfind( str.c_str(), index );
	}
	UString::size_type UString::rfind(const code_point* cp_str, size_type index, size_type num) const
	{
		UString tmp( cp_str );
		return mData.rfind( tmp.c_str(), index, num );
	}
	UString::size_type UString::rfind(const char* c_str, size_type index, size_type num) const
	{
		UString tmp( c_str );
		return mData.rfind( tmp.c_str(), index, num );
	}
	UString::size_type UString::rfind(const wchar_t* w_str, size_type index, size_type num)const
	{
		UString tmp( w_str );
		return mData.rfind( tmp.c_str(), index, num );
	}
	UString::size_type UString::rfind(char ch, size_type index)const
	{
		return rfind( static_cast<code_point>( ch ), index );
	}
	UString::size_type UString::rfind(code_point ch, size_type index)const
	{
		return mData.rfind( ch, index );
	}
	UString::size_type UString::rfind(wchar_t ch, size_type index )const
	{
		return rfind( static_cast<unicode_char>( ch ), index );
	}
	UString::size_type UString::rfind(unicode_char ch, size_type index) const
	{
		code_point cp[3] = {0, 0, 0};
		size_t l = _utf32_to_utf16( ch, cp );
		return rfind( UString( cp, l ), index );
	}

	UString::size_type UString::find_first_of(const UString &str, size_type index, size_type num)const
	{
		size_type i = 0;
		const size_type len = length();
		while ( i < num && ( index + i ) < len ) 
		{
			unicode_char ch = getChar( index + i );
			if ( str.inString( ch ) )
				return index + i;
			i += _utf16_char_length( ch );
		}
		return npos;
	}
	UString::size_type UString::find_first_of(code_point ch, size_type index)const
	{
		UString tmp;
		tmp.assign( 1, ch );
		return find_first_of( tmp, index );
	}
	UString::size_type UString::find_first_of(char ch, size_type index) const
	{
		return find_first_of( static_cast<code_point>( ch ), index );
	}
	UString::size_type UString::find_first_of(wchar_t ch, size_type index) const
	{
		return find_first_of( static_cast<unicode_char>( ch ), index );
	}
	UString::size_type UString::find_first_of(unicode_char ch, size_type index) const
	{
		code_point cp[3] = {0, 0, 0};
		size_t l = _utf32_to_utf16( ch, cp );
		return find_first_of( UString( cp, l ), index );
	}
	UString::size_type UString::find_first_not_of(const UString& str, size_type index, size_type num)const
	{
		size_type i = 0;
		const size_type len = length();
		while ( i < num && ( index + i ) < len )
		{
			unicode_char ch = getChar( index + i );
			if ( !str.inString( ch ) )
				return index + i;
			i += _utf16_char_length( ch );
		}
		return npos;
	}
	UString::size_type UString::find_first_not_of(code_point ch, size_type index)const
	{
		UString tmp;
		tmp.assign( 1, ch );
		return find_first_not_of( tmp, index );
	}
	UString::size_type UString::find_first_not_of(char ch, size_type index)const
	{
		return find_first_not_of( static_cast<code_point>( ch ), index );
	}
	UString::size_type UString::find_first_not_of(wchar_t ch, size_type index)const
	{
		return find_first_not_of( static_cast<unicode_char>( ch ), index );
	}
	UString::size_type UString::find_first_not_of(unicode_char ch, size_type index)const
	{
		code_point cp[3] = {0, 0, 0};
		size_t l = _utf32_to_utf16( ch, cp );
		return find_first_not_of( UString( cp, l ), index );
	}

	UString::size_type UString::find_last_of(const UString& str, size_type index, size_type num)const
	{
		size_type i = 0;
		const size_type len = length();
		if (index > len) index = len - 1;

		while (i<num && (index-i) != npos) 
		{
			size_type j = index - i;
			if(j!=0 && _utf16_surrogate_follow(at(j)) && _utf16_surrogate_lead(at(j-1))) 
			{
				j = index - ++i;
			}
			unicode_char ch = getChar( j );
			if ( str.inString( ch ) )
				return j;
			i++;
		}
		return npos;
	}

	UString::size_type UString::find_last_of(code_point ch, size_type index)const
	{
		UString tmp;
		tmp.assign(1, ch);
		return find_last_of(tmp, index);
	}

	UString::size_type UString::find_last_of(char ch, size_type index)const
	{
		return find_last_of(static_cast<code_point>(ch), index);
	}

	UString::size_type UString::find_last_of(wchar_t ch, size_type index)const
	{
		return find_last_of(static_cast<code_point>(ch), index);
	}

	UString::size_type UString::find_last_of(unicode_char ch, size_type index)const
	{
		code_point cp[3] = {0, 0, 0};
		size_t l = _utf32_to_utf16(ch, cp);
		return find_last_of(UString(cp, l), index);
	}

	UString::size_type UString::find_last_not_of(const UString& str, size_type index, size_type num)const
	{
		size_type i = 0;
		const size_type len = length();
		if(index > len) index = len - 1;

		while(i < num && (index-i) != npos) 
		{
			size_type j = index - i;
			if(j != 0 && _utf16_surrogate_follow(at(j)) && _utf16_surrogate_lead(at(j-1)))
			{
				j = index - ++i;
			}
			unicode_char ch = getChar(j);
			if (!str.inString(ch))
				return j;
			i++;
		}
		return npos;
	}

	UString::size_type UString::find_last_not_of(code_point ch, size_type index)const
	{
		UString tmp;
		tmp.assign(1, ch);
		return find_last_not_of(tmp, index);
	}

	UString::size_type UString::find_last_not_of(char ch, size_type index)const
	{
		return find_last_not_of(static_cast<code_point>(ch), index);
	}

	UString::size_type UString::find_last_not_of(wchar_t ch, size_type index)const
	{
		return find_last_not_of(static_cast<code_point>(ch), index);
	}

	UString::size_type UString::find_last_not_of(unicode_char ch, size_type index)const
	{
		code_point cp[3] = {0, 0, 0};
		size_t l = _utf32_to_utf16( ch, cp );
		return find_last_not_of(UString(cp, l), index );
	}
	bool UString::_utf16_independent_char(code_point cp)
	{
		if ( 0xD800 <= cp && cp <= 0xDFFF ) 
			return false; 
		return true;
	}
	
	bool UString::_utf16_surrogate_lead(code_point cp)
	{
		if ( 0xD800 <= cp && cp <= 0xDBFF )
			return true;
		return false;
	}

	bool UString::_utf16_surrogate_follow(code_point cp)
	{
		if ( 0xDC00 <= cp && cp <= 0xDFFF ) 
			return true;
		return false;
	}

	size_t UString::_utf16_char_length(code_point cp)
	{
		if(0xD800 <= cp && cp <= 0xDFFF)
			return 2;
		return 1;
	}

	size_t UString::_utf16_char_length(unicode_char uc)
	{
		if(uc > 0xFFFF)
			return 2;
		return 1;
	}

	size_t UString::_utf16_to_utf32(const code_point in_cp[2], unicode_char& out_uc)
	{
		const code_point& cp1 = in_cp[0];
		const code_point& cp2 = in_cp[1];
		bool wordPair = false;

		if ( 0xD800 <= cp1 && cp1 <= 0xDBFF ) {
			if ( 0xDC00 <= cp2 && cp2 <= 0xDFFF )
				wordPair = true; 
		}

		if(!wordPair)
		{
			out_uc = cp1;
			return 1;
		}

		unsigned short cU = cp1, cL = cp2;
		cU -= 0xD800;
		cL -= 0xDC00;

		out_uc = ( cU & 0x03FF ) << 10;
		out_uc |= ( cL & 0x03FF );
		out_uc += 0x10000;
		return 2;
	}

	size_t UString::_utf32_to_utf16(const unicode_char& in_uc, code_point out_cp[2])
	{
		if(in_uc <= 0xFFFF)
		{
			out_cp[0] = static_cast<code_point>(in_uc);
			return 1;
		}
		unicode_char uc = in_uc;
		unsigned short tmp;
		uc -= 0x10000;
		tmp = static_cast<unsigned short>(( uc >> 10 ) & 0x03FF);
		tmp += 0xD800;
		out_cp[0] = tmp;

		tmp = static_cast<unsigned short>(uc & 0x03FF);
		tmp += 0xDC00;
		out_cp[1] = tmp;

		return 2;
	}

	bool UString::_utf8_start_char(unsigned char cp)
	{
		return (cp & ~_cont_mask) != _cont;
	}

	size_t UString::_utf8_char_length( unsigned char cp )
	{
		if ( !( cp & 0x80 ) ) return 1;
		if (( cp & ~_lead1_mask ) == _lead1 ) return 2;
		if (( cp & ~_lead2_mask ) == _lead2 ) return 3;
		if (( cp & ~_lead3_mask ) == _lead3 ) return 4;
		if (( cp & ~_lead4_mask ) == _lead4 ) return 5;
		if (( cp & ~_lead5_mask ) == _lead5 ) return 6;
		//throw invalid_data("invalid UTF-8 sequence header value");
		return 0;
	}

	size_t UString::_utf8_char_length(unicode_char uc)
	{
		/*
		7 bit:  U-00000000 - U-0000007F: 0xxxxxxx
		11 bit: U-00000080 - U-000007FF: 110xxxxx 10xxxxxx
		16 bit: U-00000800 - U-0000FFFF: 1110xxxx 10xxxxxx 10xxxxxx
		21 bit: U-00010000 - U-001FFFFF: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
		26 bit: U-00200000 - U-03FFFFFF: 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
		31 bit: U-04000000 - U-7FFFFFFF: 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
		*/

		if ( !( uc & ~0x0000007F ) ) return 1;
		if ( !( uc & ~0x000007FF ) ) return 2;
		if ( !( uc & ~0x0000FFFF ) ) return 3;
		if ( !( uc & ~0x001FFFFF ) ) return 4;
		if ( !( uc & ~0x03FFFFFF ) ) return 5;
		if ( !( uc & ~0x7FFFFFFF ) ) return 6;
		//throw invalid_data( "invalid UTF-32 value" );
		return 0;
	}

	size_t UString::_utf8_to_utf32(const unsigned char in_cp[6], unicode_char& out_uc)
	{
		size_t len = _utf8_char_length(in_cp[0]);
		if ( len == 1 ) 
		{
			out_uc = in_cp[0];
			return 1;
		}

		unicode_char c = 0;
		size_t i = 0;
		switch (len) 
		{
		case 6:
			c = in_cp[i] & _lead5_mask;
			break;
		case 5:
			c = in_cp[i] & _lead4_mask;
			break;
		case 4:
			c = in_cp[i] & _lead3_mask;
			break;
		case 3:
			c = in_cp[i] & _lead2_mask;
			break;
		case 2:
			c = in_cp[i] & _lead1_mask;
			break;
		}

		for(++i; i<len; i++) 
		{
			if ((in_cp[i] & ~_cont_mask) != _cont)
				assert(true && "bad UTF-8 continuation unsigned char");
				//throw invalid_data( "bad UTF-8 continuation unsigned char" );
			c <<= 6;
			c |= ( in_cp[i] & _cont_mask );
		}

		out_uc = c;
		return len;
	}

	size_t UString::_utf32_to_utf8(const unicode_char& in_uc, unsigned char out_cp[6])
	{
		size_t len = _utf8_char_length(in_uc);
		unicode_char c = in_uc;
		for ( size_t i = len - 1; i > 0; i-- ) 
		{
			out_cp[i] = static_cast<unsigned char>((( c ) & _cont_mask ) | _cont);
			c >>= 6;
		}

		switch (len) {
		case 6:
			out_cp[0] = static_cast<unsigned char>((( c ) & _lead5_mask ) | _lead5);
			break;
		case 5:
			out_cp[0] = static_cast<unsigned char>((( c ) & _lead4_mask ) | _lead4);
			break;
		case 4:
			out_cp[0] = static_cast<unsigned char>((( c ) & _lead3_mask ) | _lead3);
			break;
		case 3:
			out_cp[0] = static_cast<unsigned char>((( c ) & _lead2_mask ) | _lead2);
			break;
		case 2:
			out_cp[0] = static_cast<unsigned char>((( c ) & _lead1_mask ) | _lead1);
			break;
		case 1:
		default:
			out_cp[0] = static_cast<unsigned char>(( c ) & 0x7F);
			break;
		}
		return len;
	}


	UString::size_type UString::_verifyUTF8(const std::string& str)
	{
		std::string::const_iterator i, ie = str.end();
		i = str.begin();
		size_type length = 0;

		while ( i != ie )
		{
			if(( *i ) & 0x80 ) 
			{
				unsigned char c = ( *i );
				size_t contBytes = 0;

				if(( c & ~_lead1_mask ) == _lead1 )
				{ 
					if (c == _lead1)
						assert(true && "overlong UTF-8 sequence");
						//throw invalid_data( "overlong UTF-8 sequence" );;
					contBytes = 1;

				}
				else if(( c & ~_lead2_mask ) == _lead2 ) 
				{ 
					contBytes = 2;
					if( c == _lead2 )
					{ 
						c = ( *( i + 1 ) ); 
						if(( c & _lead2 ) == _cont )
							assert(true && "overlong UTF-8 sequence");
							//throw invalid_data( "overlong UTF-8 sequence" );;
					}

				} 
				else if(( c & ~_lead3_mask ) == _lead3 )
				{ 
					contBytes = 3;
					if( c == _lead3 ) { 
						c = ( *( i + 1 ) ); 
						if(( c & _lead3 ) == _cont )  
							assert(true && "overlong UTF-8 sequence");
							//throw invalid_data( "overlong UTF-8 sequence" );;
					}

				}
				else if(( c & ~_lead4_mask ) == _lead4 ) 
				{ 
					contBytes = 4;
					if ( c == _lead4 ) { 
						c = ( *( i + 1 ) ); 
						if(( c & _lead4 ) == _cont ) 
							assert(true && "overlong UTF-8 sequence");
							//throw invalid_data( "overlong UTF-8 sequence" );;
					}

				} 
				else if(( c & ~_lead5_mask ) == _lead5 ) 
				{ 
					contBytes = 5;
					if( c == _lead5 )
					{ 
						c = ( *( i + 1 ) ); 
						if (( c & _lead5 ) == _cont )  
							assert(true && "overlong UTF-8 sequence");
							//throw invalid_data( "overlong UTF-8 sequence" );;
					}
				}

				while( contBytes-- ) 
				{
					c = ( *( ++i ) ); 
					if(( c & ~_cont_mask ) != _cont )
						assert(true && "overlong UTF-8 sequence");
						//throw invalid_data( "bad UTF-8 continuation unsigned char" );;
				}
			}
			length++;
			i++;
		}
		return length;
	}

	UString::size_type UString::_verifyUTF8( const unsigned char* c_str )
	{
		std::string tmp( reinterpret_cast<const char*>(c_str));
		return _verifyUTF8(tmp);
	}

	void UString::trim(const char* delims)
	{
		erase(0, find_first_not_of(delims));
		erase(find_last_not_of(delims) + 1);
	}

	void UString::split(std::vector<UString>& out, const char* delims, unsigned int uCount)
	{
		UString sStr = "";
		UString::size_type nStartPos = 0;
		UString::size_type nCurrentPos = 0;

		for (unsigned int i = 0; i < uCount; i++)
		{
			if (nCurrentPos == UString::npos)
				break;
			nCurrentPos = find_first_of(delims, nStartPos);
			sStr = substr(nStartPos, nCurrentPos - nStartPos);
			sStr.trim();
			if (sStr != "")
				out.push_back(sStr);
			nStartPos = nCurrentPos + 1;
		}
	}
}
