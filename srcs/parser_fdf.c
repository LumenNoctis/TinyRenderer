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

void LoadFdFFile(Mesh_t *dest, char *filename)
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
