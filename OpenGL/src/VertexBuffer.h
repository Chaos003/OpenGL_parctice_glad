#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H
#include "Renderer.h"


class VertexBuffer {
private:
	unsigned int VBO;

public:
	//data��ʾ����������׵�ַ��size��ʾ�����ֽ���
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();


	void Bind() const;
	void UnBind() const;
};


#endif // !VERTEX_BUFFER_H
