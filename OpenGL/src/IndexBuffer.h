#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H
#include "Renderer.h"


class IndexBuffer {
private:
	unsigned int EBO;
	unsigned int EBO_element;
public:
	//data��ʾ����������׵�ַ��size��ʾ�����ֽ���
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void UnBind() const;

	inline unsigned int getCount() const { return EBO_element; }


};
#endif // !VERTEX_BUFFER_H
