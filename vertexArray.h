#include <GL/glew.h>
#include <glm/ext.hpp>

#include <vector>
#include <memory>
#include <string>

struct vertexBuffer;

struct vertexArray
{
public:
	vertexArray();
	vertexArray(std::string _path);
	~vertexArray();
	void setBuffer(GLuint _index, std::shared_ptr<vertexBuffer> _buffer);
	GLuint getId();
	size_t getVertCount();
	void setVertCount(int _size);
private:
	std::vector<std::shared_ptr<vertexBuffer> > buffers;
	GLuint id;
	bool dirty;
	size_t vertCount;
};