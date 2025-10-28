#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) : EBO_element(count){
	GLCall(glGenBuffers(1, &EBO));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
	GLCall(glDeleteBuffers(1, &EBO));

}


void IndexBuffer::Bind() const {
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
}


void IndexBuffer::UnBind() const {
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL));
}
