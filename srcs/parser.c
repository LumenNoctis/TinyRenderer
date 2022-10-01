# include "renderer.h"

int CountNumbers(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (isdigit(str[i]))
		{
			i += strspn(str + i, "-0123456789");
			count++;
		}
		else
			i++;
	}
	return count;
}

void MapToMesh(Mesh_t *dest, char *filename)
{
	long filesize;
	size_t width;
	size_t height;
	char *data;
	int spaceLen;
	int i;
	int x;
	int y;


	data = OpenFile(filename, &filesize);
	data = strtok(data, "\n");
	height = (filesize / strlen(data)) - 1;
	width = CountNumbers(data);

	dest->edgesCount = (width - 1) * (height + 1) + (width * height);
	dest->vertexCount = width * (height + 1);
	dest->vertices = calloc(dest->vertexCount, sizeof(Vertex_t));
	dest->edges = calloc(dest->edgesCount, sizeof(Edge_t));

	y = 0;
	while(data != NULL)
	{
		i = 0;
		x = 0;
		while (x < width)
		{
			if (isdigit(data[i]))
			{
				dest->vertices[(width * y) + x].coordinates.z = atoi(data + i);
				dest->vertices[(width * y) + x].coordinates.x = (x - (width / 2)) ;
				dest->vertices[(width * y) + x].coordinates.y = y - ((height + 1) / 2);
				i += strspn(data + i, "-0123456789");
				x++;
			}
			else
				i++;
		}
		y++;
		data = strtok(NULL, "\n");
	}

	i = 0;
	x = 0;
	while (i < dest->vertexCount)
	{
		if (i + width < dest->vertexCount)
		{
			dest->edges[x].vertexA = &(dest->vertices[i]);
			dest->edges[x].vertexB = &(dest->vertices[i + width]);
			x++;
		}
		if ((i + 1) % width != 0)
		{
			dest->edges[x].vertexA = &(dest->vertices[i]);
			dest->edges[x].vertexB = &(dest->vertices[i + 1]);
			x++;
		}
		i++;
	}


	dest->_center = dest->vertices[(height * width)/2].coordinates;
	dest->center = &dest->vertices[(height * width)/2].coordinates;
}

void ObjToMesh(Mesh_t *dest, char *filename)
{
	long filesize;
	int	 lineCount;
	char *data;
	char *tmp;
	int i;
	int dataOffset;
	int firstVertexIndex;
	int secondVertexIndex;

	data = OpenFile(filename, &filesize);

	data = strtok(data, "\n");

	while(data && data[0] != 'o')
	{
		data = strtok(NULL, "\n");
	}
	data += strlen(data) + 1;
	lineCount = 0;
	dest->vertexCount = count(data, 'v');
	dest->edgesCount = count(data, 'l');
	dest->vertices = calloc(dest->vertexCount, sizeof(Vertex_t));
	dest->edges = calloc(dest->edgesCount, sizeof(Edge_t));

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
	dest->_center = dest->vertices[dest->vertexCount / 2].coordinates;
	dest->center = &dest->vertices[dest->vertexCount / 2].coordinates;
}
