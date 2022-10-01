#include "renderer.h"

int		count (char *str, char c)
{
	int count = 0;

	while (*str)
	{
		count += *str == c;
		str++;
	}
	return count;
}

char * OpenFile(char *filename, long *filesize)
{
	FILE	*file;
	char	*data;

	file = fopen(filename, "r");
	fseek(file, 0L , SEEK_END);

	*filesize = ftell(file);
	data = calloc(*filesize + 1, 1);

	rewind(file);
	fread(data, *filesize, 1, file);
	fclose(file);
	return data;
}


void printCoord2D(Vector2_t coord)
{
	SDL_Log("Coords (%d,%d)", coord.x, coord.y);
}

void printCoord3D(Vector3_t coord)
{
	SDL_Log("Coords (%d,%d,%d)", coord.x, coord.y, coord.z);

}
void printCoord3DF(Vector3F_t coord)
{
	SDL_Log("Coords (%f,%f,%f)", coord.x, coord.y, coord.z);
}
