#pragma once

#include <iostream>

#include "../../../Source/Graphics/Vertex/Vertex3D.h"
#include "Buffer.h"

namespace Derpy { namespace Graphics {

	enum class HardwareMapping{
		NEVER,
		STATIC,
		DYNAMIC,
		STREAM
	};


	template <class T>
	class MeshBuffer{
	public:
		unsigned int m_ChangedVertexId;
		unsigned int m_ChangedIndexId;

		HardwareMapping m_VertexMappingHint;
		HardwareMapping m_IndexMappingHint;

		Material m_Material;
		std::vector<T> m_Vertices;
		std::vector<unsigned short> m_Indices;
		//std::vector<float> m_BoundingBox;

	public:
		MeshBuffer() : m_ChangedVertexId(1), m_ChangedIndexId(1),
			m_VertexMappingHint(HardwareMapping::NEVER),
			m_IndexMappingHint(HardwareMapping::NEVER){ }

		~MeshBuffer(){ }

		virtual const Material& getMaterial() const{
			return m_Material;
		}

		virtual Material& getMaterial(){
			return m_Material;
		}

		virtual const void* getVertices() const{
			return m_Vertices.data();
		}

		virtual void* getVertices(){
			return m_Vertices.data();
		}

		virtual unsigned int getVertexCount() const{
			return m_Vertices.size();
		}

		virtual IndexType getIndexType() const{
			return IndexType::BITS16;
		}

		virtual const unsigned short* getIndices() const{
			return m_Indices.data();
		}

		virtual unsigned short* getIndices(){
			return m_Indices.data();
		}

		virtual unsigned int getIndexCount() const{
			return m_Indices.size();
		}

		//virtual const std::vector<float>& getBoundingBox() const;
		//virtual void setBoundingBox(const std::vector& box);
		//virtual void recalculateBoundingBox();

		virtual VertexType getVertexType() const{
			return T().getType();
		}

		virtual const Maths::Vec3f& getPosition(unsigned int index) const{
			return m_Vertices[index].position;
		}

		virtual Maths::Vec3f& getPosition(unsigned int index){
			return m_Vertices[index].position;
		}

		virtual const Maths::Vec3f& getNormal(unsigned int index) const{
			return m_Vertices[index].normal;
		}

		virtual Maths::Vec3f& getNormal(unsigned int index){
			return m_Vertices[index].normal;
		}

		virtual const Maths::Vec2f& getTextureCoords(unsigned int index) const{
			return m_Vertices[index].textureCoords;
		}

		virtual Maths::Vec2f& getTextureCoords(unsigned int index){
			return m_Vertices[index].textureCoords;
		}

		virtual void append(const void* const vertices, unsigned int numVertices, const unsigned short* const indices, unsigned int numIndices){
			if (vertices == getVertices())
				return;
			
			const unsigned int vertexCount = getVertexCount();
			
			m_Vertices.reserve(vertexCount + numVertices);
			for (unsigned int i = m_Vectices.size(); i < numVertices; ++i){
				m_Vertices.push_back(reinterpret_cast<const T*>(vertices)[i]);
				//m_BoundingBox.addInternalPoint(reinterpret_cast<const T*>(vertices)[i].Pos);
			}
			
			m_Indices.reserve(getIndexCount() + numIndices);
			for (unsigned int i = m_Indices.size(); i < numIndices; ++i)
				m_Indices.push_back(indices[i] + vertexCount);

		}

		virtual void append(const MeshBuffer* const other){
			//TODO
		}

		virtual HardwareMapping getVertexHardwareMappingHint() const{
			return m_VertexMappingHint;
		}

		virtual HardwareMapping getIndexHarwareMappingHint() const{
			return m_IndexMappingHint;
		}

		virtual void setHardwareMappingHint(HardwareMapping newMappingHint, BufferType buffer = BufferType::VERTEX_AND_INDEX){
			if (Buffer == BufferType::VERTEX_AND_INDEX || Buffer == BufferType::VERTEX)
				m_VertexMappingHint = newMappingHint;
			if (Buffer == BufferType::VERTEX_AND_INDEX || Buffer == BufferType::INDEX)
				m_IndexMappingHint = newMappingHint;
		}

		virtual void setDirty(BufferType buffer = BufferType::VERTEX_AND_INDEX){
			if (Buffer == BufferType::VERTEX_AND_INDEX || Buffer == BufferType::VERTEX)
				m_ChangedVertexId++;
			if (Buffer == BufferType::VERTEX_AND_INDEX || Buffer == BufferType::INDEX)
				m_ChangedIndexId++;
		}

		virtual unsigned int getChangedVertexId() const{
			return m_ChangedVertexId;
		}

		virtual unsigned int getChangedIndexId(){
			return m_ChangedIndexId;
		}

	};
	
	typedef MeshBuffer<Vertex3D> MeshBufferStandard;

} }