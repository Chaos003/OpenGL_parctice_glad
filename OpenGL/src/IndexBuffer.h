#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H
#include "Renderer.h"


class IndexBuffer {
private:
	unsigned int EBO;
	unsigned int EBO_element;
public:
	//data表示传入数组的首地址，size表示数组字节数
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void UnBind() const;

	inline unsigned int getCount() const { return EBO_element; }


};
#endif // !VERTEX_BUFFER_H
