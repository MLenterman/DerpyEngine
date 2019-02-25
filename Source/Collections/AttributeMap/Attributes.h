#pragma once

#include <iostream>
#include <string>

namespace Derpy { namespace Collections {

	enum class EAttributeType{
		INT,
		FLOAT,
		BOOL,
		BINARY,
		STRING,
		USER_POINTER
	};


	class IAttribute{
	protected:
		std::string m_Name;

	public:
		IAttribute();
		virtual ~IAttribute();

		virtual int getInt() { return 0; }
		virtual float getFloat() { return 0; }
		virtual bool getBool() { return false; }
		virtual void getBinary(void* outdata, int maxLength) {};
		virtual std::string getString() { return ""; }
		virtual void* getUserPointer() { return 0; }

		virtual void setInt(int value) {};
		virtual void setFloat(float value) {};
		virtual void setBool(bool boolValue) {};
		virtual void setBinary(void* data, int maxLenght) {};
		virtual void setString(const char* value) {};
		virtual void setString(std::string value) { setString(value.c_str()); };
		virtual void setUserPointer(void* value) {};

		virtual EAttributeType getType() const = 0;
		virtual std::string getTypeString() const = 0;
		
	};

	class IntAttribute : public IAttribute{
	protected:
		int m_Value;

	public:
		IntAttribute(const char* name, int value){
			m_Name = name;
			m_Value = value;
		}

		virtual int getInt(){
			return m_Value;
		}

		virtual float getFloat(){
			return (float)m_Value;
		}

		virtual bool getBool(){
			return m_Value != 0;
		}

		virtual std::string getString(){
			return std::to_string(m_Value);
		}

		virtual void setInt(int value){
			m_Value = value;
		}

		virtual void setFloat(float value){
			m_Value = (int)value;
		};

		virtual void setString(const char* value){
			m_Value = atoi(value);
		}

		virtual EAttributeType getType() const override{
			return EAttributeType::INT;
		}

		virtual std::string getTypeString() const override{
			return "int";
		}
	};

	class FloatAttribute : public IAttribute{
	protected:
		float m_Value;

	public:
		FloatAttribute(const char* name, float value){
			m_Name = name;
			m_Value = value;
		}

		virtual int getInt(){
			return (int)m_Value;
		}

		virtual float getFloat(){
			return m_Value;
		}

		virtual bool getBool(){
			return m_Value != 0;
		}

		virtual std::string getString(){
			return std::to_string(m_Value);
		}

		virtual void setInt(int value){
			m_Value = (float)value;
		}

		virtual void setFloat(float value){
			m_Value = value;
		}

		virtual void setString(const char* value){
			m_Value = std::atof(value);
		}

		virtual EAttributeType getType() const{
			return EAttributeType::FLOAT;
		}

		virtual std::string getTypeString() const{
			return "float";
		}

	};

	class BoolAttribute : public IAttribute{
	protected:
		bool m_Value;

	public:
		BoolAttribute(const char* name, bool value){
			m_Name = name;
			m_Value = value;
		}

		virtual int getInt(){
			return m_Value ? 1 : 0;
		}

		virtual float getFloat(){
			return m_Value ? 1.0f : 0.0f;
		}

		virtual bool getBool(){
			return m_Value;
		}

		virtual std::string getString(){
			return m_Value ? "true" : "false";
		}

		virtual void setInt(int value){
			m_Value = (value != 0);
		}

		virtual void setFloat(float value){
			m_Value = (value != 0);
		}

		virtual void setBool(bool value){
			m_Value = value;
		}

		virtual void setString(const char* value){
			m_Value = strcmp(value, "true") == 0;
		}

		virtual EAttributeType getType() const{
			return EAttributeType::BOOL;
		}
	};

	class StringAttribute : public IAttribute{
	protected:
		std::string m_Value;

	public:

		StringAttribute(const char* name, const char* value){
			m_Name = name;
			m_Value = value;;
		}

		StringAttribute(const char* name, void* binaryData, int lenghtInBytes){

			m_Name = name;
			setBinary(binaryData, lenghtInBytes);
		}

		virtual int getInt(){
			return atoi(m_Value.c_str());
		}

		virtual float getFloat(){
			return atof(m_Value.c_str());
		}

		virtual bool getBool(){
			return (m_Value == "true");
		}

		virtual std::string getString(){
			return m_Value;
		}

		virtual void setInt(int value){
			m_Value = std::to_string(value);
		}

		virtual void setFloat(float value){
			m_Value = std::to_string(value);
		};

		virtual void setString(const char* value){
			m_Value = value;
		}

		virtual EAttributeType getType() const{
			return EAttributeType::STRING;
		}

		virtual std::string getTypeString() const{
			return "string";
		}

		virtual void getBinary(void* outdata, int maxLength){
			int dataSize = maxLength;
			char* data = (char*)outdata;
			int index = 0;
			const char* dataString = m_Value.c_str();

			for (int i = 0; i < dataSize; i++)
				data[i] = 0;

			while (dataString[index] && index < dataSize){
				int value = hexToByte(dataString[index * 2]) * 16;

				if (dataString[(index * 2) + 1])
					value += hexToByte(dataString[(index * 2) + 1]);

				data[index] = value;
				index++;
			}
		}

		virtual void setBinary(void* inData, int maxLength){
			int dataSize = maxLength;
			char* data = (char*)inData;
			char temp[3];
			temp[2] = 0;
			m_Value = "";

			for (int i = 0; i < dataSize; i++){
				byteToHex(data[i], temp);
				m_Value.append(temp);
			}
		}

	protected:
		inline int hexToByte(char hex){
			if (hex >= '0' && hex <= '9')
				return hex - '0';
			if (hex >= 'A' && hex <= 'F')
				return hex - 'A' + 10;
			if (hex >= 'a' && hex <= 'f')
				return hex - 'a' + 10;

			return 0;
		}

		inline void byteToHex(char byte, char* out){
			int b = (byte & 0xf0) >> 4;

			for (int i = 0; i < 2; i++){
				if (b >= 0 && b <= 9)
					out[i] = b + '0';
				if (b >= 10 && b <= 15)
					out[i] = (b - 10) + 'A';

				b = byte & 0x0f;
			}
		}
	};

	class BinaryAttribute : public StringAttribute{
	public:
		BinaryAttribute(const char* name, void* binaryData, int lenghtInBytes)
			: StringAttribute(name, binaryData, lenghtInBytes){

		}

		virtual EAttributeType getType() const{
			return EAttributeType::BINARY;
		}


		virtual std::string getTypeString() const{
			return "binary";
		}
	};

	class UserPointerAttribute : public IAttribute{
	protected:
		void* m_Value;

	public:

		UserPointerAttribute(const char* name, void* value){
			m_Name = name;
			m_Value = value;
		}

		virtual int getInt(){
			return *static_cast<int*>(m_Value);
		}

		virtual bool getBool(){
			return m_Value != 0;
		}

		virtual std::string getString(){
			char buff[32];
			sprintf(buff, "%p", m_Value);

			return buff;
		}

		virtual void setString(const char* value){
			unsigned int temp;
			sscanf(value, "0x%x", &temp);
			m_Value = (void*)temp;
		}

		virtual EAttributeType getType() const{
			return EAttributeType::USER_POINTER;
		}

		virtual void setUserPointer(void* value){
			m_Value = value;
		}

		virtual void* getUserPointer(){
			return m_Value;
		}

		virtual std::string getTypeString() const{
			return "userPointer";
		}
	};

} }