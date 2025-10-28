#ifndef VERTEX_BUFFER_LAYOUT_H
#define VERTEX_BUFFER_LAYOUT_H
#include "Renderer.h"
#include <glad/glad.h>
#include <vector>

struct VertexBufferElement {
   unsigned int count; // Corrected typo from 'cout' to 'count'
   unsigned int type;
   unsigned char normalized;

   static unsigned int GetSizeOfType(unsigned int type) {
	   switch (type) {
	   case GL_FLOAT:
		   return sizeof(GLfloat);
	   case GL_UNSIGNED_INT:
		   return sizeof(GLuint);
	   case GL_UNSIGNED_BYTE:
		   return sizeof(GLubyte);
		}
	   ASSERT(false);
	   return 0;
   }
};

class VertexBufferLayout {
private:
   //template<typename T>
   std::vector<VertexBufferElement> m_element;
   unsigned int m_stride = 0;
public:
	VertexBufferLayout() {};

   // 阻止不支持的类型调用模板类push
   template<typename T>
   void push(unsigned int count) {
       // 使用静态断言来判断类型是否支持
       static_assert(false, "Type not supported!");
   }

   template<>
   void push<float>(unsigned int count) {
       m_element.push_back({ count, GL_FLOAT, GL_FALSE });
	   m_stride += count * VertexBufferLayout::getElements().back().GetSizeOfType(GL_FLOAT);
   }

   template<>
   void push<unsigned int>(unsigned int count) {
	   m_element.push_back({ count, GL_UNSIGNED_INT, GL_FALSE });
	   m_stride += count * VertexBufferLayout::getElements().back().GetSizeOfType(GL_UNSIGNED_INT);
   }

   template<>
   void push<unsigned char>(unsigned int count) {
	   m_element.push_back({ count,GL_UNSIGNED_BYTE, GL_TRUE });
	   m_stride += count * VertexBufferLayout::getElements().back().GetSizeOfType(GL_UNSIGNED_BYTE);
   }

   inline const unsigned int getStride() const { return m_stride; }

  /* inline const unsigned int getStride() const {
	   unsigned int stride = 0;
	   for (const auto& element : m_element) {
		   stride += element.count * sizeof(element.type);
	   }
	   return stride;
   }*/


   // Adding const to make member function const-correct
   const std::vector<VertexBufferElement>& getElements() const {
       return m_element;
   }
};

#endif // ! VERTEX_BUFFER_LAYOUT_H
