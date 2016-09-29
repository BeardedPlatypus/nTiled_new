#pragma once

#include <string>

namespace nTiled {
namespace state {

struct Log {
  Log(bool is_logging_data,
      std::string path,
      unsigned int frame_start,
      unsigned int frame_end,
      bool exit_after_done,
      unsigned int exit_frame);
  Log(std::string path,
      unsigned int frame_start,
      unsigned int frame_end);
  Log();

  bool is_logging_data;
  std::string path;

  unsigned int frame_start;
  unsigned int frame_end;

  bool exit_after_done;
  unsigned int exit_frame;
};

}
}