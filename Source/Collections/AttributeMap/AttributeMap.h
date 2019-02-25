#pragma once

#include <iostream>
#include <unordered_map>

#include "Attributes.h"

namespace Derpy { namespace Collections {

	class AttributeMap{
	protected:
		std::unordered_map<std::string, IAttribute*> m_Map;

	public:
		virtual unsigned int getAttributeCount() const;
		virtual const char* getAttributeName(int index);
		virtual EAttributeType getAttributeType(const char* attributeName);
		virtual EAttributeType getAttributeType(int index);
		virtual const wchar_t* getAttributeTypeString(const char* attributeName);
		virtual const wchar_t* getAttributeTypeString(int index);
		virtual bool existsAttribute(const char* attributeName);
		virtual int findAttribute(const char* attributeName) const;
		virtual void clear();
	};


} }