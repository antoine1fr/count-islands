#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>

static ptrdiff_t coords_to_offset(ptrdiff_t width, ptrdiff_t x, ptrdiff_t y)
{
  return (width * y) + x;
}

static void offset_to_coords(ptrdiff_t offset,
                             ptrdiff_t width,
                             ptrdiff_t* x,
                             ptrdiff_t* y)
{
  *x = offset % width;
  *y = offset / width;
}

static ptrdiff_t map_field(uint8_t* field,
                           ptrdiff_t* map,
                           ptrdiff_t width,
                           ptrdiff_t height)
{
  ptrdiff_t size = width * height;
  ptrdiff_t offset = 0;
  ptrdiff_t x;
  ptrdiff_t y;
  ptrdiff_t hoffset;
  ptrdiff_t voffset;
  ptrdiff_t count = 0;

  while (offset < size)
  {
    offset_to_coords(offset, width, &x, &y);
    hoffset = coords_to_offset(width, x - 1, y);
    voffset = coords_to_offset(width, x, y - 1);
    if (field[offset])
    {
      if (((x > 0) && map[hoffset])
          || ((y > 0) && map[voffset]))
        map[offset] = count;
      else
        map[offset] = ++count;
    }
    else
      map[offset] = 0;
    offset += 1;
  }
  return count;
}

static ptrdiff_t count_islands(uint8_t* field,
                               ptrdiff_t width,
                               ptrdiff_t height)
{
  ptrdiff_t count;
  ptrdiff_t* map;

  map = (ptrdiff_t*)malloc(sizeof(ptrdiff_t) * width * height);
  count = map_field(field, map, width, height);
  free(map);
  return count;
}

int main()
{
  uint8_t field1[3][4] =
    {
      {1, 1, 1, 0},
      {1, 1, 1, 0},
      {0, 0, 0, 1}
    };
  uint8_t field2[4][4] =
    {
      {1, 1, 1, 0},
      {1, 1, 1, 0},
      {0, 0, 0, 1},
      {0, 1, 0, 1}
    };
  uint8_t field3[4][4] =
    {
      {1, 1, 1, 0},
      {1, 1, 0, 0},
      {1, 1, 0, 0},
      {1, 0, 1, 1}
    };
  uint8_t field4[4][4] =
    {
      {1, 0, 0, 0},
      {0, 1, 0, 0},
      {0, 0, 1, 0},
      {0, 0, 0, 1}
    };
  uint8_t field5[4][4] =
    {
      {1, 1, 1, 0},
      {1, 1, 1, 1},
      {0, 0, 0, 1},
      {0, 1, 0, 1}
    };
  uint8_t field6[4][4] =
    {
      {0, 0, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}
    };
  uint8_t field7[4][4] =
    {
      {1, 1, 1, 1},
      {1, 1, 1, 1},
      {1, 1, 1, 1},
      {1, 1, 1, 1}
    };
  printf("Count: %ld.\n", count_islands(&field1[0][0], 4, 3));
  printf("Count: %ld.\n", count_islands(&field2[0][0], 4, 4));
  printf("Count: %ld.\n", count_islands(&field3[0][0], 4, 4));
  printf("Count: %ld.\n", count_islands(&field4[0][0], 4, 4));
  printf("Count: %ld.\n", count_islands(&field5[0][0], 4, 4));
  printf("Count: %ld.\n", count_islands(&field6[0][0], 4, 4));
  printf("Count: %ld.\n", count_islands(&field7[0][0], 4, 4));
  return 0;
}
