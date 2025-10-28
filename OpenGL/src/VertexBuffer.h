#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H
#include "Renderer.h"


class VertexBuffer {
private:
	unsigned int VBO;

public:
	//data表示传入数组的首地址，size表示数组字节数
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();


	void Bind() const;
	void UnBind() const;
};


#endif // !VERTEX_BUFFER_H
