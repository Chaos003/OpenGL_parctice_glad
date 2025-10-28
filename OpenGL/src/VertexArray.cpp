#include "VertexArray.h"


VertexArray::VertexArray() {
	GLCall(glGenVertexArrays(1, &VAO));
	//GLCall(glBindVertexArray(VAO));
}
VertexArray::~VertexArray() {
	GLCall(glDeleteVertexArrays(1, &VAO));

}

void VertexArray::add_vertex_Buffer(const VertexBuffer& vb, const VertexBufferLayout& vb_layout) {

	vertex_Array_Bind();
	vb.Bind();
	const auto& elements = vb_layout.getElements();
	unsigned int offset = 0;


	for (unsigned int i = 0; i<elements.size(); i++) {
		std::cout << offset << std::endl;
		const auto& element = elements[i];
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized,
			vb_layout.getStride(), (void*)(offset * sizeof(element.type))));
		GLCall(glEnableVertexAttribArray(i));
		offset += element.count;
	}

}


void VertexArray::vertex_Array_Bind() const{
	GLCall(glBindVertexArray(VAO));
}

void VertexArray::vertex_Array_UnBind() const{
	GLCall(glBindVertexArray(0));
}