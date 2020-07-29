#ifndef _ALGO_STRING_HPP_
#define _ALGO_STRING_HPP_
/*
String类
索引操作保证不会下标越界，因此你需要自己控制你的下标，
由于动态大小调整，当下标越界时会自动扩容空间，发生一次拷贝
当你的使用空间较小时，会适当地压缩空间，也会发生一次拷贝
默认会分配64个字符空间，没有设置扩容函数，如果你需要扩容，
只需要下标索引到你想要的空间大小即可，这样的好处是能够减少复制
同样你如果需要节省空间，提供了缩容函数,并且提供了设置自动缩小状态设置
整体功能：
动态大小管理
永远不会下标越界（如果分配空间顺利）
运算符重载支持
增删改查（append/+/*,remove/clear,replace/[],find/first/last,indexOf...）
拆分与合并 join/split
常见字符串操作(compare,substring,endwith,startwith,...)

采用模板，模板参数说明：
T:字符，比如char,无符号限制
E:索引，计数，比如：int，需要带有符号，不能是无符号型
*/

#include"AlgoContainer.hpp"
#define STRING_END_VALUE 0
template<typename T,typename E>
class AlgoString
{
public:
	AlgoString()
	{
		initString();
	}
	AlgoString(const T * str)
	{
		initString();
		fromString(str);
	}
	AlgoString(const AlgoString & str)
	{
		initString();
		fromString(str.m_data);
	}
	AlgoString & operator=(const AlgoString & str)
	{
		return fromString(str.m_data);
	}
	AlgoString & operator=(const T * str)
	{
		return fromString(str);
	}
	AlgoString & fromString(const T * str)
	{
		const T *  data = str;
		E i = 0;
		for (i = 0; *data != STRING_END_VALUE; i++, data++)
		{
			extendCapital(i);
			m_data[i] = *data;
		}
		notifyStringEnd(i);

		return *this;
	}
	operator T *() const
	{
		return this->m_data; 
	}
	AlgoString & operator+(const T * str)
	{
		return appendString(str);
	}
	AlgoString & operator+(const AlgoString & str)
	{
		return appendString(str.m_data);
	}
	AlgoString & operator+=(const AlgoString & str)
	{
		return appendString(str.m_data);
	}
	AlgoString & operator+=(const T * str)
	{
		return appendString(str);
	}
	AlgoString & append(const T * str)
	{
		return appendString(str);
	}
	AlgoString & append(const AlgoString & str)
	{
		return appendString(str.m_data);
	}
	AlgoString & appendString(const T * str)
	{
		E i = this->getLength();
		const T *  data = str;
		for (; *data != STRING_END_VALUE; i++, data++)
		{
			extendCapital(i);
			m_data[i] = *data;
		}
		notifyStringEnd(i);
		return *this;
	}
	AlgoString & operator*(E repeat)
	{
		return repeatString(repeat);
	}
	AlgoString & operator*=(E repeat)
	{
		return repeatString(repeat);
	}
	AlgoString& repeatString(E repeat)
	{
		if (repeat <= 0)
		{
			notifyStringEnd(0);
			return *this;
		}
		E len = this->getLength();
		E j = len;
		for (E i = 0; i < repeat - 1; i++)
		{
			T *  data = this->m_data;
			for (E k = 0; k<len; j++, k++)
			{
				extendCapital(j);
				data = this->m_data;
				m_data[j] = data[k];
			}
		}
		notifyStringEnd(j);
		return *this;
	}
	bool operator==(const T * str)const
	{
		return cmpString(this->m_data,str) == 0;
	}
	bool operator==(const AlgoString & str)const
	{
		return cmpString(this->m_data,str.m_data) == 0;
	}
	bool operator>(const T * str)const
	{
		return cmpString(this->m_data, str)>0;
	}
	bool operator>(const AlgoString & str)const
	{
		return cmpString(this->m_data, str.m_data)>0;
	}
	bool operator<(const T * str)const
	{
		return cmpString(this->m_data, str)<0;
	}
	bool operator<(const AlgoString & str)const
	{
		return cmpString(this->m_data, str.m_data)<0;
	}
	bool operator>=(const T * str)const
	{
		return cmpString(this->m_data, str) >= 0;
	}
	bool operator>=(const AlgoString & str)const
	{
		return cmpString(this->m_data, str.m_data) >= 0;
	}
	bool operator<=(const T * str)const
	{
		return cmpString(this->m_data, str) <= 0;
	}
	bool operator<= (const AlgoString & str)const
	{
		return cmpString(this->m_data, str.m_data) <= 0;
	}
	bool operator!=(const T * str)const
	{
		return cmpString(this->m_data, str) != 0;
	}
	bool operator!=(const AlgoString & str)const
	{
		return cmpString(this->m_data,str.m_data)!=0;
	}
	E compareIgnoreCase(const T * str)const
	{
		String tp2(str);
		String tp1(this->m_data);
		tp1.toLowerCase();
		tp2.toLowerCase();
		return cmpString(tp1, tp2);
	}
	E compareIgnoreCase(const AlgoString & str)const
	{
		AlgoString tp2(str);
		AlgoString tp1(this->m_data);
		tp1.toLowerCase();
		tp2.toLowerCase();
		return cmpString(tp1, tp2);
	}
	E compare(const T * str)const
	{
		return cmpString(this->m_data,str);
	}
	bool equals(const AlgoString & str)const
	{
		return this->compare(str)==0;
	}
	bool equalsIgnoreCase(const AlgoString & str)const
	{
		return this->compareIgnoreCase(str) == 0;
	}
	E compare(const AlgoString & str)const
	{
		return cmpString(this->m_data,str.m_data);
	}
	E cmpString(const T * str1, const T * str2)const
	{
		while (*str1 != STRING_END_VALUE && *str2 != STRING_END_VALUE)
		{
			if (*str1 > *str2)
			{
				return 1;
			}
			else if (*str1 < *str2)
			{
				return -1;
			}
			str1++;
			str2++;
		}
		if (*str1 == STRING_END_VALUE && *str2 == STRING_END_VALUE)
			return 0;
		if (*str1 == STRING_END_VALUE)
			return -1;
		if (*str2 == STRING_END_VALUE)
			return 1;
	}
	bool contains(const T * str)const
	{
		return containsString(this->m_data,str);
	}
	bool contains(const AlgoString & str)const
	{
		return containsString(this->m_data,str.m_data);
	}
	bool containsString(const T * str, const T * child)const
	{
		return findString(str,child)!=-1;
	}
	E lenCompare(const T * child)const
	{
		return ncmpString(this->m_data,child,lengthString(child));
	}
	E lenCompare(const T * str,E len)const
	{
		return ncmpString(this->m_data,str,len);
	}
	E lenCompare(const AlgoString & str, E len)const
	{
		return ncmpString(this->m_data,str.m_data,len);
	}
	E ncmpString(const T * str1, const T * str2, E len)const
	{
		for (E i = 0; i < len; i++,str1++,str2++)
		{
			if (*str1 == STRING_END_VALUE && *str2 == STRING_END_VALUE)
				return 0;
			if (*str1 == STRING_END_VALUE)
				return -1;
			if (*str2 == STRING_END_VALUE)
				return 1;
			if (*str1 > *str2)
				return 1;
			if (*str1 < *str2)
				return -1;
		}
		return 0;
	}
	E first(const T * str)const
	{
		return findString(this->m_data,str);
	}
	E first(const AlgoString & str)const
	{
		return findString(this->m_data,str.m_data);
	}
	E find(E beginIndex, const T * str)const
	{
		return findString(&(this->m_data[beginIndex]),str);
	}
	E find(E beginIndex, const AlgoString & str)const
	{
		return findString(&(this->m_data[beginIndex]),str.m_data);
	}
	E firstString(const T * str, const T * child)const
	{
		return findString(str, child);
	}
	E last(const T * str)const
	{
		return lastString(this->m_data,str);
	}
	E last(const AlgoString & str)const
	{
		return lastString(this->m_data,str.m_data);
	}
	E lastString(const T * str, const T * child)const
	{
		E clen = lengthString(child);
		if (clen == 0)
			return -1;
		E mlen = lengthString(str);
		if (clen > mlen)
			return -1;
		E i = mlen - 1;
		while ((i - clen) >= 0)
		{
			if (str[i] == child[0] && str[i + clen - 1] == child[clen - 1])
			{
				if (ncmpString(&str[i], child, clen) == 0)
				{
					return i;
				}

			}
			i--;
		}
		return -1;
	}
	E indexOf(const T * str)const
	{
		return findString(this->m_data,str);
	}
	E countOf(const T * str)const
	{
		E count = 0;
		E index = 0;
		E len = lengthString(str);
		E mlen = lengthString(m_data);
		while (index < mlen)
		{
			E pindex=findString(&m_data[index], str);
			if (pindex>0)
			{
				count++;
				index = index+pindex + len;
			}
			else
			{
				index++;
			}
			
		}

		return count;
	}
	E countOf(const AlgoString& str)const
	{
		return countOf(str.m_data);
	}
	E findString(const T * str, const T * child)const
	{
		E clen = lengthString(child);
		if (clen == 0)
			return -1;
		E i = 0;
		while (str[i] != STRING_END_VALUE)
		{
			if (str[i] == child[0] && str[i+clen-1]==child[clen-1])
			{
				if (ncmpString(&str[i], child, clen) == 0)
				{
					return i;
				}

			}
			i++;
			if (str[i + clen] == STRING_END_VALUE)
			{
				break;
			}
		}

		return -1;
	}
	bool startWith(const AlgoString & str)const
	{
		return startWithString(this->m_data,str.m_data)
	}
	bool startWith(const T * str)const
	{
		return startWithString(this->m_data,str);
	}
	bool startWithString(const T * str1, const T * str2)const
	{
		if (ncmpString(str1, str2, lengthString(str2)) == 0)
			return true;
		return false;
	}
	bool endWith(const AlgoString & str)const
	{
		return endWithString(this->m_data,str.m_data);
	}
	bool endWith(const T * str)const
	{
		return endWithString(this->m_data,str);
	}
	bool endWithString(const T * str1, const T * str2)const
	{
		E clen = lengthString(str2);
		E mlen = lengthString(str1);
		if (clen > mlen)
			return false;
		if (ncmpString(&str1[mlen  - clen], str2,clen) == 0)
			return true;
		return false;
	}
	AlgoString& toLowerCase()
	{
		toLowerCaseString(this->m_data);
		return *this;
	}
	AlgoString& toUpperCase()
	{
		toUpperCaseString(this->m_data);
		return *this;
	}
	void toLowerCaseString(T * str)
	{
		while (*str != STRING_END_VALUE)
		{
			if (isA2Z(*str))
			{
				(*str) |= 32;
			}
			*str++;
		}
	}
	void toUpperCaseString(T * str)
	{
		while (*str != STRING_END_VALUE)
		{
			if (isa2z(*str))
			{
				(*str) -= 32;
			}
			*str++;
		}
	}
	bool isAsciiChar(T ch)const
	{
		return ch >= 0 && ch < 128;
	}
	bool isA2Z(T ch)const
	{
		return ch >= 'A' && ch <= 'Z';
	}
	bool isa2z(T ch)const
	{
		return ch >= 'a' && ch <= 'z';
	}
	bool isControlChar(T ch)const
	{
		return ch > 0 && ch < 32;
	}
	AlgoString& replace(const AlgoString & srcStr, const AlgoString & drtStr, E maxReplaceCount)
	{
		return replace(srcStr.m_data,drtStr.m_data,maxReplaceCount);
	}
	AlgoString& replace(const T * srcStr, const T * drtStr, E maxRelapceCount)
	{
		if (maxRelapceCount == 0)
			return *this;
		T * orgData = m_data;
		initString();

		bool needReplace = true;
		E count = 0;
		E srcLen = lengthString(srcStr);
		E drtLen = lengthString(drtStr);
		E index = 0;
		E saveIndex = 0;
		while (orgData[index] != STRING_END_VALUE)
		{
			if (needReplace && ncmpString(&orgData[index], srcStr, srcLen) == 0)
			{
				count++;
				if (maxRelapceCount > 0)
				{
					if (count >= maxRelapceCount)
						needReplace = false;
				}

				E k = 0;
				while (drtStr[k] != STRING_END_VALUE)
				{
					extendCapital(saveIndex);
					m_data[saveIndex] = drtStr[k];
					saveIndex++;
					k++;
				}
				index += srcLen;
			}
			else
			{
				extendCapital(saveIndex);
				m_data[saveIndex] = orgData[index];
				saveIndex++;
				index++;
			}
			
		}
		delete[] orgData;
		notifyStringEnd(saveIndex);
		return *this;
	}
	AlgoString& join(const AlgoString & joinStr, AlgoArray<AlgoString<T, E>, E> & joinArray, bool headJoin = true)
	{
		for (E i = 0; i < joinArray.size(); i++)
		{
			if (headJoin && i == 0)
				this->appendString(joinStr.m_data);
			AlgoString str = joinArray[i];
			this->appendString(str.m_data);
			if (i != joinArray.size()-1)
				this->appendString(joinStr.m_data);
		}
		return *this;
	}
	//使用此方法时，参数2可能需要类型装换一下：(const char **)
	AlgoString & joinString(const T * joinStr, const T * joinArray[], E arrCount, bool headJoin = true)
	{
		for (E i = 0; i < arrCount; i++)
		{
			if (headJoin && i==0)
				this->appendString(joinStr);
			AlgoString str = joinArray[i];
			this->appendString(joinArray[i]);
			if (i != arrCount - 1)
				this->appendString(joinStr);
		}
		return *this;
	}
	AlgoArray<AlgoString<T, E>, E> & split(const AlgoString & splitStr, AlgoArray<AlgoString<T, E>, E> & saveArray, E maxSplitCount, bool removeEmpty = true)const
	{
		saveArray.setSize(0);
		E clen = lengthString(splitStr.m_data);
		E index = 0;
		E tpi = 0;
		AlgoString tp;
		E count = 0;
		bool isNeedDo = true;
		while ( m_data[index] != STRING_END_VALUE)
		{
			if (isNeedDo && ncmpString(&m_data[index], splitStr.m_data, clen) == 0)
			{
				count++;
				if (maxSplitCount > 0)
				{
					if (count >= maxSplitCount)
					{
						isNeedDo = false;
					}
				}
				if (removeEmpty)
				{
					if (tp.m_data[0] != STRING_END_VALUE)
						saveArray.push(tp);
				}
				else
				{
					saveArray.push(tp);
				}

				tp.clear();
				tpi = 0;
				index += clen;
			}
			else
			{
				tp.extendCapital(tpi);
				tp.m_data[tpi] = m_data[index];
				tp.notifyStringEnd(tpi + 1);
				index++;
				tpi++;
			}
		}
		if (tp.getLength() > 0)
			saveArray.push(tp);
		return saveArray;
	}
	//字符串拆分，当字符串在给定的字符串序列中时进行拆分，相邻的字符会被合并看待
	AlgoArray<AlgoString<T, E>, E> & splitWhen(const T * splitChars, AlgoArray<AlgoString<T, E>, E> & saveArray, E maxSplitCount, bool removeEmpty = true)const
	{
		saveArray.setSize(0);
		E index = 0;
		E tpi = 0;
		AlgoString tp;
		E tplen = 0;
		E count = 0;
		bool isNeedDo = true;
		while (m_data[index] != STRING_END_VALUE)
		{
			T pch = m_data[index];
			bool isInChar = false;
			if(isNeedDo)
			{
				E k = 0;
				while (splitChars[k] != STRING_END_VALUE)
				{
					if (pch == splitChars[k])
					{
						isInChar = true;
						break;
					}
					k++;
				}

			}
			
			if (isInChar)
			{
				if (tplen > 0)
				{
					count++;
					if (maxSplitCount > 0)
					{
						if (count >= maxSplitCount)
						{
							isNeedDo = false;
						}
					}
					if (removeEmpty)
					{
						if (tp.m_data[0] != STRING_END_VALUE)
							saveArray.push(tp);
					}
					else
					{
						saveArray.push(tp);
					}
					tp.clear();
					tpi = 0;
					tplen = 0;
				}
			}
			else
			{
				tp.extendCapital(tpi);
				tp.m_data[tpi] = m_data[index];
				tp.notifyStringEnd(tpi + 1);
				tplen = tpi + 1;
				tpi++;
			}
			index++;
		}
		if (tp.getLength() > 0)
			saveArray.push(tp);
		return saveArray;
	}
	AlgoString subString(E index, E length)const
	{
		AlgoString ret;
		if (length == 0)
			return ret;
		if (length > 0)
		{
			E i = 0;
			while (i < length)
			{
				ret.extendCapital(i);
				ret.m_data[i] = m_data[index + i];
				ret.notifyStringEnd(i + 1);
				if (m_data[index + i] == STRING_END_VALUE)
					break;
				i++;
			}
		}
		else
		{
			E i = 0;
			while (m_data[index + i] != STRING_END_VALUE)
			{
				ret.extendCapital(i);
				ret.m_data[i] = m_data[index + i];
				ret.notifyStringEnd(i + 1);
				i++;
			}
		}
		return ret;
	}
	AlgoString subStringIndex(E beginIndex, E endIndex)const
	{
		return subString(beginIndex,endIndex-beginIndex+1);
	}
	AlgoString& remove(const T * str, E maxRemoveCount)
	{
		if (maxRemoveCount == 0)
			return *this;
		T * orgData = m_data;
		initString();

		bool needRemove = true;
		E count = 0;
		E srcLen = lengthString(str);
		E index = 0;
		E saveIndex = 0;
		while (orgData[index] != STRING_END_VALUE)
		{
			if (needRemove && ncmpString(&orgData[index], str, srcLen) == 0)
			{
				count++;
				if (maxRemoveCount > 0)
				{
					if (count >= maxRemoveCount)
						needRemove = false;
				}
				index += srcLen;
			}
			else
			{
				extendCapital(saveIndex);
				m_data[saveIndex] = orgData[index];
				saveIndex++;
				index++;
			}

		}
		delete[] orgData;
		notifyStringEnd(saveIndex);
		return *this;
	}
	AlgoString& remove(const AlgoString & str, E maxRemoveCount)
	{
		return remove(str.m_data, maxRemoveCount);
	}
	bool isSpaceChar(T ch)const
	{
		return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' || ch == '\v';
	}
	AlgoString& trim()
	{
		E len = 0;
		while (isSpaceChar(m_data[len]))
			len++;
		E index = 0;
		while (m_data[index + len] != STRING_END_VALUE)
		{
			m_data[index] = m_data[index + len];
			index++;
		}
		index = index - 1;
		while (isSpaceChar(m_data[index]) && index >= 0)
			index--;
		notifyStringEnd(index + 1);
		return *this;
	}
	AlgoString& trimEnd()
	{
		E len = lengthString(this->m_data);
		E index = len-1;
		while (isSpaceChar(m_data[index]) && index>=0)
			index--;
		notifyStringEnd(index + 1);
		return *this;
	}
	AlgoString& trimBegin()
	{
		E len = 0;
		while (isSpaceChar(m_data[len]))
			len++;
		E index = 0;
		while (m_data[index + len] != STRING_END_VALUE)
		{
			m_data[index] = m_data[index + len];
			index++;
		}
		notifyStringEnd(index);
		return *this;
	}
	AlgoString& clear()
	{
		notifyStringEnd(0);
		return *this;
	}
	T& operator[](E index)
	{
		extendCapital(index);
		return m_data[index];
	}
	T * getData()const
	{
		return m_data;
	}
	E getCapital()const
	{
		return m_capital;
	}
	void shrinkCapital()
	{
		E len = lengthString(m_data);
		E newCapital = m_capital;
		E ml = 1;
		while ((newCapital >> ml) > len)
		{
			ml++;
		}
		newCapital = newCapital >> (ml-1);
		if (newCapital <= 1)
		{
			newCapital = 1;
		}
		T * buf = new T[newCapital];
		for (E i = 0; i < len; i++)
		{
			buf[i] = m_data[i];
		}
		delete[] m_data;
		m_data = buf;
		m_capital = newCapital;
		notifyStringEnd(len);
	}
	E lengthString(const T * str)const
	{
		E len = 0;
		while (str[len] != STRING_END_VALUE)
			len++;
		return len;
	}
	E getLength()const
	{
		return lengthString(this->m_data);
	}
	void zeroMemory()
	{
		memorySet(0,m_capital-1,STRING_END_VALUE);
	}
	void memorySet(E beginIndex, E endIndex, T value)
	{
		extendCapital(endIndex);
		for (; beginIndex <= endIndex; beginIndex++)
		{
			m_data[beginIndex] = value;
		}
	}
	T * prepareMemery(E size)
	{
		extendCapital(size - 1);
		return m_data;
	}
	void setAutoShinkState(bool open)
	{
		openAutoShrink = open;
	}
	virtual ~AlgoString()
	{
		if (m_data != NULL)
		{
			delete[] m_data;
			m_data = NULL;
		}
		m_capital = 0;
	}
protected:
	T * m_data;
	E  m_capital;
	bool openAutoShrink;

	void initString()
	{
		openAutoShrink = false;
		m_capital = 64;
		m_data = new T[m_capital];
		zeroMemory();
	}
	void notifyStringEnd(int index)
	{
		extendCapital(index);
		m_data[index] = STRING_END_VALUE;
		if (openAutoShrink && index>16 && index * 4 < m_capital && m_capital>=256)
		{
			shrinkCapital();
		}
	}
	void extendCapital(E index)
	{
		if (index >= m_capital)
		{
			E bufSize = m_capital << 1;
			if (bufSize <= index)
				bufSize = index + 1 + 16;
			T * buf = new T[bufSize];
			for (E i = 0; i <m_capital; i++)
			{
				buf[i] = m_data[i];
			}
			delete[] m_data;
			m_capital = bufSize;
			m_data = buf;

		}
	}
};

#endif // _ALGO_STRING_HPP_