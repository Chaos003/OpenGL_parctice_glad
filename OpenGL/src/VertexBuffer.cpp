#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
	GLCall(glGenBuffers(1, &VBO));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer(){
	GLCall(glDeleteBuffers(1, &VBO));

}


void VertexBuffer::Bind() const {
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
}


void VertexBuffer::UnBind() const {
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, NULL));
}
