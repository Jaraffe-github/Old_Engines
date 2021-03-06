#include "JFStringW.h"

JFFoundation::JFStringW::JFStringW()
	: data(nullptr)
{
}

JFFoundation::JFStringW::JFStringW(const wchar_t* c, size_t len)
	: JFStringW()
{
	Append(c, len);
}

JFFoundation::JFStringW::JFStringW(const JFStringW& str)
	: JFStringW()
{
	Append(str);
}

JFFoundation::JFStringW::JFStringW(JFStringW&& str) noexcept
	: JFStringW()
{
	data = str.data;
	str.data = nullptr;
}

JFFoundation::JFStringW::~JFStringW()
{
	Clear();
}

void JFFoundation::JFStringW::Clear()
{
	if (data)
		free(data);
	data = nullptr;
}

void JFFoundation::JFStringW::Reverse()
{
	size_t len = Length();

	for (size_t i = 0; i < len / 2; ++i)
	{
		wchar_t temp = data[i];
		data[i] = data[len - i - 1];
		data[len - i - 1] = temp;
	}
}

JFFoundation::JFStringW& JFFoundation::JFStringW::Append(const JFStringW& str)
{
	return Append(str.Str());
}

JFFoundation::JFStringW& JFFoundation::JFStringW::Append(const wchar_t* c, size_t len)
{
	if (c)
	{
		size_t sourceLen = Length();
		size_t targetLen = 0;
		while (c[targetLen] && targetLen < len)
			++targetLen;

		size_t totalSize = (sourceLen + targetLen + 1) * sizeof(wchar_t);
		if (totalSize < 2)
			return *this;

		wchar_t* appendChar = (wchar_t*)malloc(totalSize);
		assert(appendChar);
		memset(appendChar, 0, totalSize);

		wchar_t* cursor = appendChar;
		if (sourceLen > 0)
		{
			memcpy(cursor, data, sourceLen * sizeof(wchar_t));
			cursor += sourceLen;
		}

		if (targetLen > 0)
		{
			memcpy(cursor, c, targetLen * sizeof(wchar_t));
			cursor += targetLen;
		}

		*cursor = 0;

		if (data)
			free(data);

		data = appendChar;
	}

	return *this;
}

JFFoundation::JFStringW& JFFoundation::JFStringW::Erase(size_t pos, size_t len)
{
	// pos is the first character in str is denoted by a value of 0 (not 1).
	size_t maxPos = Length();
	if (pos < 0 || pos >= maxPos)
		return *this;

	size_t erasableCount = maxPos - pos;
	if (len != All)
		erasableCount = min(erasableCount, len);

	// +1 : \0
	size_t newSize = (maxPos - erasableCount + 1) * sizeof(wchar_t);
	wchar_t* erasedChar = (wchar_t*)malloc(newSize);
	assert(erasedChar);
	memset(erasedChar, 0, newSize);

	size_t copyByte = pos * sizeof(wchar_t);
	if (copyByte > 0)
	{
		memcpy(erasedChar, data, copyByte);
	}

	copyByte = (maxPos - pos - erasableCount) * sizeof(wchar_t);
	if (copyByte > 0)
	{
		memcpy(&erasedChar[pos], &data[erasableCount + 1], copyByte);
	}

	if (data)
		free(data);

	data = erasedChar;
	return *this;
}

size_t JFFoundation::JFStringW::Length() const
{
	if (!data)
		return 0;

	size_t len = 0;
	while (data[len])
		++len;
	return len;
}

const wchar_t* JFFoundation::JFStringW::Str() const
{
	return data;
}

JFFoundation::JFStringW& JFFoundation::JFStringW::operator=(const wchar_t* c)
{
	return Append(c);
}

JFFoundation::JFStringW& JFFoundation::JFStringW::operator=(const JFStringW& str)
{
	return Append(str);
}

JFFoundation::JFStringW& JFFoundation::JFStringW::operator=(JFStringW&& str)
{
	data = str.data;
	str.data = nullptr;
	return *this;
}
