#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray {

private:
	unsigned int VAO;
public:
	VertexArray();
	~VertexArray();

	void vertex_Array_Bind() const;
	void vertex_Array_UnBind() const;

	void add_vertex_Buffer(const VertexBuffer& vb, const VertexBufferLayout& vbl);
	
	unsigned int getVAO() {
		return VAO;
	}
};






#endif // !VERTEX_ARRAY_H
