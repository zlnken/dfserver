/************************************************************************
* @File			:	DFUString.h
* @Author		:	Sword
* @DateTime		:	2013.12.9 
* @Description	:
*
*
*
*
************************************************************************/
#ifndef __DFUString_H__
#define __DFUString_H__


#include "DFPrerequisite.h"

namespace DF{

	class DFExport UString
	{
	public:
		static const unsigned char _lead1 = 0xC0;      //110xxxxx
		static const unsigned char _lead1_mask = 0x1F; //00011111
		static const unsigned char _lead2 = 0xE0;      //1110xxxx
		static const unsigned char _lead2_mask = 0x0F; //00001111
		static const unsigned char _lead3 = 0xF0;      //11110xxx
		static const unsigned char _lead3_mask = 0x07; //00000111
		static const unsigned char _lead4 = 0xF8;      //111110xx
		static const unsigned char _lead4_mask = 0x03; //00000011
		static const unsigned char _lead5 = 0xFC;      //1111110x
		static const unsigned char _lead5_mask = 0x01; //00000001
		static const unsigned char _cont = 0x80;       //10xxxxxx
		static const unsigned char _cont_mask = 0x3F;  //00111111

	public:
		typedef size_t size_type;
		static const size_type npos = static_cast<size_type>(~0);
		typedef unsigned int unicode_char;
		typedef unsigned short code_point;
		typedef code_point value_type;
		typedef std::basic_string<code_point> dstring; 
		typedef std::basic_string<unicode_char> utf32string;

		//class invalid_data: public std::runtime_error 
		//{ 
		//public:
		//	explicit invalid_data(const std::string& _Message): std::runtime_error( _Message ){}
		//};


	public:
		// --------------------------------------------------------------------------
		//	_base_iterator
		// --------------------------------------------------------------------------
		class DFExport _base_iterator : public std::iterator<std::random_access_iterator_tag, value_type>
		{
			friend class UString;
		public:
			_base_iterator(void);
			void _seekFwd(size_type c);
			void _seekRev(size_type c);
			void _become(const _base_iterator& i);
			bool _test_begin(void) const;
			bool _test_end(void) const;
			size_type _get_index(void) const;
			void _jump_to(size_type index);
			unicode_char _getCharacter(void) const;
			int _setCharacter(unicode_char uc);
			void _moveNext(void);
			void _movePrev(void);

			dstring::iterator mIter;
			UString* mString;
		};

		// --------------------------------------------------------------------------
		//	_fwd_iterator
		// --------------------------------------------------------------------------
		class _const_fwd_iterator;
		class DFExport _fwd_iterator: public _base_iterator 
		{
			friend class _const_fwd_iterator;
		public:
			_fwd_iterator(void);
			_fwd_iterator(const _fwd_iterator& i);
			_fwd_iterator& operator++(void);
			_fwd_iterator operator++(int);
			_fwd_iterator& operator--(void);
			_fwd_iterator operator--(int);
			_fwd_iterator operator+(difference_type n);
			_fwd_iterator operator-(difference_type n);
			_fwd_iterator& operator+=(difference_type n);
			_fwd_iterator& operator-=(difference_type n);
			value_type& operator*(void) const;
			value_type& operator[](difference_type n) const;
			_fwd_iterator& moveNext(void);
			_fwd_iterator& movePrev(void);
			unicode_char getCharacter(void) const;
			int setCharacter(unicode_char uc);

			DFExport friend size_type operator-(const _fwd_iterator& left, const _fwd_iterator& right){ return left.mIter - right.mIter; }
			DFExport friend bool operator==(const _fwd_iterator& left, const _fwd_iterator& right){ return left.mIter == right.mIter; }
			DFExport friend bool operator!=(const _fwd_iterator& left, const _fwd_iterator& right){ return left.mIter != right.mIter; }
			DFExport friend bool operator<(const _fwd_iterator& left, const _fwd_iterator& right){ return left.mIter < right.mIter; }
			DFExport friend bool operator<=(const _fwd_iterator& left, const _fwd_iterator& right){ return left.mIter <= right.mIter; }
			DFExport friend bool operator>(const _fwd_iterator& left, const _fwd_iterator& right){ return left.mIter > right.mIter; }
			DFExport friend bool operator>=(const _fwd_iterator& left, const _fwd_iterator& right){ return left.mIter >= right.mIter; }
		};

		// --------------------------------------------------------------------------
		//	_const_fwd_iterator
		// --------------------------------------------------------------------------
		class DFExport _const_fwd_iterator: public _base_iterator 
		{
		public:
			_const_fwd_iterator(void);
			_const_fwd_iterator(const _const_fwd_iterator& i);
			_const_fwd_iterator(const _fwd_iterator& i);
			_const_fwd_iterator& operator++(void);
			_const_fwd_iterator operator++(int);
			_const_fwd_iterator& operator--(void);
			_const_fwd_iterator operator--(int);
			_const_fwd_iterator operator+(difference_type n);
			_const_fwd_iterator operator-(difference_type n);
			_const_fwd_iterator& operator+=(difference_type n);
			_const_fwd_iterator& operator-=(difference_type n);
			value_type& operator*(void) const;
			value_type& operator[](difference_type n) const;
			_const_fwd_iterator& moveNext(void);
			_const_fwd_iterator& movePrev(void);
			unicode_char getCharacter(void) const;

			DFExport friend size_type operator-(const _const_fwd_iterator& left, const _const_fwd_iterator& right){ return left.mIter  - right.mIter ; }
			DFExport friend bool operator==(const _const_fwd_iterator& left, const _const_fwd_iterator& right){ return left.mIter == right.mIter; }
			DFExport friend bool operator!=(const _const_fwd_iterator& left, const _const_fwd_iterator& right){ return left.mIter != right.mIter ; }
			DFExport friend bool operator<(const _const_fwd_iterator& left, const _const_fwd_iterator& right){ return left.mIter < right.mIter ; }
			DFExport friend bool operator<=(const _const_fwd_iterator& left, const _const_fwd_iterator& right){ return left.mIter <= right.mIter ; }
			DFExport friend bool operator>(const _const_fwd_iterator& left, const _const_fwd_iterator& right){ return left.mIter > right.mIter ; }
			DFExport friend bool operator>=(const _const_fwd_iterator& left, const _const_fwd_iterator& right){ return left.mIter >= right.mIter ; }
		};

		// --------------------------------------------------------------------------
		//	_rev_iterator
		// --------------------------------------------------------------------------
		class _const_rev_iterator;
		class DFExport _rev_iterator: public _base_iterator 
		{
			friend class _const_rev_iterator;
		public:
			_rev_iterator(void);
			_rev_iterator(const _rev_iterator& i);
			_rev_iterator& operator++(void);
			_rev_iterator operator++(int);
			_rev_iterator& operator--(void);
			_rev_iterator operator--(int);
			_rev_iterator operator+(difference_type n);
			_rev_iterator operator-(difference_type n);
			_rev_iterator& operator+=(difference_type n);
			_rev_iterator& operator-=(difference_type n);
			value_type& operator*(void) const;
			value_type& operator[](difference_type n) const;
			unicode_char getCharacter(void) const;
		};

		// --------------------------------------------------------------------------
		//	_const_rev_iterator
		// --------------------------------------------------------------------------
		class DFExport _const_rev_iterator: public _base_iterator 
		{
		public:
			_const_rev_iterator(void);
			_const_rev_iterator(const _const_rev_iterator& i);
			_const_rev_iterator(const _rev_iterator& i);
			_const_rev_iterator& operator++(void);
			_const_rev_iterator operator++(int);
			_const_rev_iterator& operator--(void);
			_const_rev_iterator operator--(int);
			_const_rev_iterator operator+(difference_type n);
			_const_rev_iterator operator-(difference_type n);
			_const_rev_iterator& operator+=(difference_type n);
			_const_rev_iterator& operator-=(difference_type n);
			value_type& operator*(void) const;
			value_type& operator[](difference_type n) const;
			unicode_char getCharacter(void) const;

			DFExport friend size_type operator-(const _const_rev_iterator& left, const _const_rev_iterator& right){ return left.mIter  - right.mIter ; }
			DFExport friend bool operator==(const _const_rev_iterator& left, const _const_rev_iterator& right){ return left.mIter == right.mIter; }
			DFExport friend bool operator!=(const _const_rev_iterator& left, const _const_rev_iterator& right){ return left.mIter != right.mIter ; }
			DFExport friend bool operator<(const _const_rev_iterator& left, const _const_rev_iterator& right){ return left.mIter < right.mIter ; }
			DFExport friend bool operator<=(const _const_rev_iterator& left, const _const_rev_iterator& right){ return left.mIter <= right.mIter ; }
			DFExport friend bool operator>(const _const_rev_iterator& left, const _const_rev_iterator& right){ return left.mIter > right.mIter ; }
			DFExport friend bool operator>=(const _const_rev_iterator& left, const _const_rev_iterator& right){ return left.mIter >= right.mIter ; }
		};

		// --------------------------------------------------------------------------
		//	UString
		// --------------------------------------------------------------------------
	public:
		typedef _fwd_iterator iterator;                     //!< iterator
		typedef _rev_iterator reverse_iterator;             //!< reverse iterator
		typedef _const_fwd_iterator const_iterator;         //!< const iterator
		typedef _const_rev_iterator const_reverse_iterator; //!< const reverse iterator

		~UString(void);
		UString(void);
		UString(const UString& copy);
		UString(unsigned int length, unsigned short ch);
		UString(const code_point* str);
		UString(const code_point* str, size_type length);
		UString(const UString& str, size_type index, size_type length);
		UString(const wchar_t* w_str);
		UString(const wchar_t* w_str, size_type length);
		UString(const std::wstring& wstr);
		UString(const std::string& c_str);
		UString(const char* c_str, size_type length);
		UString(const char* str);

		size_type size(void)const;
		size_type length(void) const;
		size_type length_Characters(void)const;
		size_type max_size(void)const;
		void reserve(size_type size);
		void resize(size_type num, const code_point& val = 0);
		void swap(UString& from);
		bool empty(void)const;
		const code_point* c_str(void)const;
		const code_point* data(void) const;
		size_type capacity(void) const;
		void clear(void);
		UString substr(size_type index, size_type num = npos) const;
		code_point& at(size_type loc);
		const code_point& at(size_type loc)const;
		bool inString(unicode_char ch)const;
		const char* asUTF8(void)const;
		const utf32string& asUTF32(void)const;
		const unicode_char* asUTF32_c_str(void)const;
		const std::wstring& asWStr(void)const;
		const wchar_t* asWStr_c_str(void)const;
		unicode_char getChar(size_type loc)const;
		int setChar(size_type loc, unicode_char ch);

		iterator begin(void);
		const_iterator begin(void)const;
		iterator end(void);
		const_iterator end(void)const;
		reverse_iterator rbegin(void);
		const_reverse_iterator rbegin(void)const;
		reverse_iterator rend(void);
		const_reverse_iterator rend(void)const;


		void setBegin(void);
		unsigned int getNext(void)const;
		void next(void);
		bool hasNext(void)const;


		iterator erase(iterator loc);
		iterator erase(iterator start, iterator end);
		UString& erase(size_type index = 0, size_type num = npos);

		UString& assign(iterator start, iterator end);
		UString& assign(const UString& str);
		UString& assign(const code_point* str);
		UString& assign(const code_point* str, size_type num);
		UString& assign(const UString& str, size_type index, size_type len);
		UString& assign(size_type num, const code_point& ch);
		UString& assign(const std::wstring& wstr);
		UString& assign(const wchar_t* w_str);
		UString& assign(const wchar_t* w_str, size_type num);
		UString& assign(const std::string& str);
		UString& assign(const char* c_str);
		UString& assign(const char* c_str, size_type num);

		UString& append(const UString& str);
		UString& append(const code_point* str);
		UString& append(const UString& str, size_type index, size_type len);
		UString& append(const code_point* str, size_type num);
		UString& append(size_type num, code_point ch);
		UString& append(iterator start, iterator end);

		UString& append(const wchar_t* w_str, size_type num);
		UString& append(size_type num, wchar_t ch);
		UString& append(const char* c_str, size_type num);
		UString& append(size_type num, char ch);
		UString& append(size_type num, unicode_char ch);

		void push_back(unicode_char val);
		void push_back(wchar_t val);
		void push_back(code_point val);
		void push_back(char val);

		iterator insert(iterator i, const code_point& ch);
		UString& insert(size_type index, const UString& str);
		UString& insert( size_type index, const code_point* str );
		UString& insert(size_type index1, const UString& str, size_type index2, size_type num);
		void insert(iterator i, iterator start, iterator end);
		UString& insert(size_type index, const code_point* str, size_type num);
		UString& insert(size_type index, const wchar_t* w_str, size_type num);
		UString& insert(size_type index, const char* c_str, size_type num);
		UString& insert(size_type index, size_type num, code_point ch);
		UString& insert(size_type index, size_type num, wchar_t ch);
		UString& insert(size_type index, size_type num, char ch);
		UString& insert(size_type index, size_type num, unicode_char ch);
		void insert(iterator i, size_type num, const code_point& ch);
		void insert(iterator i, size_type num, const wchar_t& ch);
		void insert(iterator i, size_type num, const char& ch);
		void insert(iterator i, size_type num, const unicode_char& ch);

		UString& replace(size_type index1, size_type num1, const UString& str);
		UString& replace(size_type index1, size_type num1, const UString& str, size_type num2 );
		UString& replace(size_type index1, size_type num1, const UString& str, size_type index2, size_type num2);
		UString& replace(iterator start, iterator end, const UString& str, size_type num = npos);
		UString& replace(size_type index, size_type num1, size_type num2, code_point ch);
		UString& replace(iterator start, iterator end, size_type num, code_point ch);

		int compare(const UString& str)const;
		int compare(const code_point* str)const;
		int compare(size_type index, size_type length, const UString& str) const;
		int compare(size_type index, size_type length, const UString& str, size_type index2, size_type length2)const;
		int compare(size_type index, size_type length, const code_point* str, size_type length2)const;
		int compare(size_type index, size_type length, const wchar_t* w_str, size_type length2)const;
		int compare(size_type index, size_type length, const char* c_str, size_type length2)const;

		size_type find(const UString& str, size_type index = 0)const;
		size_type find(const code_point* cp_str, size_type index, size_type length)const;
		size_type find(const char* c_str, size_type index, size_type length)const;
		size_type find(const wchar_t* w_str, size_type index, size_type length)const;
		size_type find(char ch, size_type index = 0)const;
		size_type find(code_point ch, size_type index = 0)const;
		size_type find(wchar_t ch, size_type index = 0)const;
		size_type find(unicode_char ch, size_type index = 0)const;

		size_type rfind(const UString& str, size_type index = 0)const;
		size_type rfind(const code_point* cp_str, size_type index, size_type num) const;
		size_type rfind(const char* c_str, size_type index, size_type num) const;
		size_type rfind(const wchar_t* w_str, size_type index, size_type num)const;
		size_type rfind(char ch, size_type index = 0)const;
		size_type rfind(code_point ch, size_type index)const;
		size_type rfind(wchar_t ch, size_type index = 0)const;
		size_type rfind(unicode_char ch, size_type index = 0) const;

		size_type find_first_of(const UString &str, size_type index = 0, size_type num = npos)const;
		size_type find_first_of(code_point ch, size_type index = 0)const;
		size_type find_first_of(char ch, size_type index = 0) const;
		size_type find_first_of(wchar_t ch, size_type index = 0) const;
		size_type find_first_of(unicode_char ch, size_type index = 0) const;

		size_type find_first_not_of(const UString& str, size_type index = 0, size_type num = npos) const;
		size_type find_first_not_of(code_point ch, size_type index = 0)const;
		size_type find_first_not_of(char ch, size_type index = 0)const;
		size_type find_first_not_of(wchar_t ch, size_type index = 0)const;
		size_type find_first_not_of(unicode_char ch, size_type index = 0)const;

		size_type find_last_of(const UString& str, size_type index = npos, size_type num = npos)const;
		size_type find_last_of(code_point ch, size_type index = npos)const;
		size_type find_last_of(char ch, size_type index = npos)const;
		size_type find_last_of(wchar_t ch, size_type index = npos) const;
		size_type find_last_of(unicode_char ch, size_type index = npos) const;

		size_type find_last_not_of(const UString& str, size_type index = npos, size_type num = npos)const;
		size_type find_last_not_of(code_point ch, size_type index = npos)const;
		size_type find_last_not_of(char ch, size_type index = npos)const;
		size_type find_last_not_of(wchar_t ch, size_type index = npos)const;
		size_type find_last_not_of(unicode_char ch, size_type index = npos)const;


		void trim(const char* delims = " \t\n\x07\x08\x09\x0a\x0d");
		void split(std::vector<UString>& out, const char* delims = " \t\n", unsigned int uCount = 0xFFFFFFFF);
		
		bool operator<(const UString& right)const{ return compare(right) < 0; }
		bool operator<=(const UString& right)const{ return compare(right) <= 0; }
		bool operator>(const UString& right)const{ return compare(right) > 0; }
		bool operator>=(const UString& right)const{ return compare(right) >= 0; }
		bool operator==(const UString& right)const{ return compare(right) == 0; }
		bool operator!=(const UString& right)const{ return compare(right) != 0; }

		UString& operator=(const UString& s){ return assign(s); }
		UString& operator=(code_point ch){ clear(); return append(1, ch); }
		UString& operator=(char ch){ clear(); return append(1, ch); }
		UString& operator=(wchar_t ch){ clear(); return append(1, ch); }
		UString& operator=(unicode_char ch){ clear(); return append(1, ch);}

		code_point& operator[](int index){ return at((size_type)index); }
		const code_point& operator[](int index)const{ return at((size_type)index); }

		operator std::string()const{ return std::string(asUTF8()); }
		operator std::wstring()const{ return std::wstring(asWStr());}

		UString operator+(const UString& s2)const{ return UString(*this).append(s2); }
		UString operator+(code_point ch)const{ return UString(*this).append(1, ch); }
		UString operator+(unicode_char ch)const{ return UString(*this).append(1, ch); }
		UString operator+(wchar_t ch)const{ return UString(*this).append(1, ch); }
		UString operator+(char ch)const{ return UString(*this).append(1, ch); }

		DFExport friend UString operator+(code_point ch, const UString& s1){return UString().append(1,ch).append(s1); }
		DFExport friend UString operator+(unicode_char ch, const UString& s1){return UString().append(1,ch).append(s1); }
		DFExport friend UString operator+(wchar_t ch, const UString& s1){return UString().append(1,ch).append(s1); }
		DFExport friend UString operator+(char ch, const UString& s1){return UString().append(1,ch).append(s1); }

		DFExport friend std::ostream& operator<<(std::ostream& os, const UString& s){ return os<<s.asUTF8(); }
		DFExport friend std::wostream& operator<<(std::wostream& os, const UString& s){ return os<<s.asWStr(); }

		static bool _utf16_independent_char(code_point cp);
		static bool _utf16_surrogate_lead(code_point cp);
		static bool _utf16_surrogate_follow(code_point cp);
		static size_t _utf16_char_length(code_point cp);
		static size_t _utf16_char_length(unicode_char uc);
		static size_t _utf16_to_utf32(const code_point in_cp[2], unicode_char& out_uc);
		static size_t _utf32_to_utf16(const unicode_char& in_uc, code_point out_cp[2]);
		static bool _utf8_start_char(unsigned char cp);
		static size_t _utf8_char_length(unsigned char cp);
		static size_t _utf8_char_length(unicode_char uc);
		static size_t _utf8_to_utf32(const unsigned char in_cp[6], unicode_char& out_uc);
		static size_t _utf32_to_utf8(const unicode_char& in_uc, unsigned char out_cp[6]);
		static size_type _verifyUTF8(const std::string& str);
		static size_type _verifyUTF8(const unsigned char* c_str);

	private:

		void _init(void);
		void _cleanBuffer(void)const;
		void _getBufferStr(void)const;
		void _getBufferWStr(void)const;
		void _getBufferUTF32Str(void) const;
		void _load_buffer_UTF8(void)const;
		void _load_buffer_WStr(void)const;
		void _load_buffer_UTF32(void)const;


	private:
		enum BufferType 
		{
			bt_none,
			bt_string,
			bt_wstring,
			bt_utf32string
		};

		union UTFBuffer
		{
			mutable void* mVoidBuffer;
			mutable std::string* mStrBuffer;
			mutable std::wstring* mWStrBuffer;
			mutable utf32string* mUTF32StrBuffer;
		};

		dstring mData;
		mutable BufferType m_bufferType; 
		mutable size_t m_bufferSize; 
		UTFBuffer m_buffer;
		const_iterator m_It;
	};


}

#endif


