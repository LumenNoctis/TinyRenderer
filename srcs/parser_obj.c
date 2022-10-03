# include "renderer.h"

char *parseVertices(Mesh_t *dest, char *data)
{
	int i;
	int dataOffset;

	i = 0;
	data = strtok(data, "\n");
	while (data && data[0] == 'v')
	{
		dataOffset = 2;
		dest->vertices[i].coordinates.x = atof(data + dataOffset);
		dataOffset += strcspn(data + dataOffset, " ") + 1;
		dest->vertices[i].coordinates.y = atof(data + dataOffset);
		dataOffset += strspn(data + dataOffset, "-0123456789.") + 1;
		dest->vertices[i].coordinates.z = atof(data + dataOffset);
		i++;
		data = strtok(NULL, "\n");
	}
	dest->_center = dest->vertices[dest->vertexCount / 2].coordinates;
	dest->center = &dest->vertices[dest->vertexCount / 2].coordinates;

	return data;
}

char *parseEdges(Mesh_t *dest, char *data)
{
	int i;
	int dataOffset;
	int firstVertexIndex;
	int secondVertexIndex;

	i = 0;
	while (data && data[0] == 'l')
	{
		dataOffset = 2;
		firstVertexIndex = atoi(data + dataOffset);
		dataOffset += strcspn(data + dataOffset, " ") + 1;
		secondVertexIndex = atoi(data + dataOffset);

		dest->edges[i].vertexA = &(dest->vertices[firstVertexIndex - 1]);
		dest->edges[i].vertexB = &(dest->vertices[secondVertexIndex - 1]);
		i++;
		data = strtok(NULL, "\n");
	}

	return data;
}

void parseFace()
{

}

char *SkipHeader(char *data)
{
	data = strtok(data, "\n");

	while(data && data[0] != 'o')
	{
		data = strtok(NULL, "\n");
	}
	data += strlen(data) + 1;

	return data;
}


void InitParams(Mesh_t *dest, char *data)
{
	dest->vertexCount = count(data, 'v');
	dest->edgesCount = count(data, 'l');
	dest->vertices = calloc(dest->vertexCount, sizeof(Vertex_t));
	dest->edges = calloc(dest->edgesCount, sizeof(Edge_t));
}

void LoadObjFile(Mesh_t *dest, char *filename)
{
	long filesize;
	char *head;
	char *data;

	head = OpenFile(filename, &filesize);
	data = SkipHeader(head);

	InitParams(dest, data);
	data = parseVertices(dest, data);
	data = parseEdges(dest, data);

	dest->scale = 50;

}
