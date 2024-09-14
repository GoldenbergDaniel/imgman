#include <stdio.h>

#include "base/base.hpp"
#include "base/base_arena.cpp"
#include "base/base_string.cpp"
#include "arguments.cpp"
#include "image.cpp"
#include "manipulator.cpp"

i32 main(i32 argc, char *argv[])
{
  Arena arena = Arena(MiB(16));

  Image image;
  image.read_from_path(str("res/car.tga"), &arena);
  image.add(10, Channel_R | Channel_B);
  image.print_stats();

  Slice<byte> bytes;
  bytes.from_ptr(image.raw_data(), 0, image.size());
  bytes = bytes.slice(0, bytes.len());
  printf("   PIXEL: %i %i %i\n", bytes[0], bytes[1], bytes[2]);

  arena.clear();

  if (argc > 1)
  {
    String str = string_from_argv(argv, argc, &arena);
    str.print();
  }
  
  return 0;
}
