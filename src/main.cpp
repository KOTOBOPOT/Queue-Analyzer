#include <iostream>
#include <vector>
#include <thread>

#include "cam_video.h"
#include "const.h"
#include "file_video.h"
#include "sqlite_handler.h"
#include "video_processors.h"

int main(int argc, char* argv[]) {
  SQLiteHandler db_handler(DOC_ROOT + "/db/db.db");
  int pause = 10;
  while (true) {
    auto vid_processor = getVideoProcessor(DOC_ROOT + "/static/model");

    auto fv1 = std::make_shared<FileVideo>(
        DOC_ROOT + "/static/video_examples/ex1.mp4", 1);
    auto fv2 = std::make_shared<FileVideo>(
        DOC_ROOT + "/static/video_examples/sample.mp4", 1);

    vid_processor->pushBackVideoSource(fv1);
    vid_processor->pushBackVideoSource(fv2, cv::Rect(10, 50, 500, 500));
    
    if (argc > 1) {
      if (std::string(argv[1]) != "-v") {
        int visualizeIndex = std::stoi(argv[1]);
        vid_processor->setVisualizeVidSourceIndex(visualizeIndex);
        pause = 0;
      } else {
        auto fv3 = std::make_shared<CamVideo>(0);
        vid_processor->pushBackVideoSource(fv3);
        if (argc > 2) {
          int visualizeIndex = std::stoi(argv[2]);
          vid_processor->setVisualizeVidSourceIndex(visualizeIndex);
          pause = 0;
        }
      }
    }

    std::cout << "Reopen video..." << std::endl;
    std::vector<int> people_amounts = vid_processor->getQueuePeopleAmount();
    while (((people_amounts[0]) != -1) && (people_amounts[1] != -1)) {
      std::cout << "Current people amounts: ";
      for (int i = 0; i < people_amounts.size(); ++i) {
        std::cout << i << ": " << people_amounts[i] << ", ";
      };
      std::cout << std::endl;

      auto time_now = std::chrono::system_clock::now();

      for (int vid_index = 0; vid_index < people_amounts.size(); ++vid_index) {
        db_handler.insertEntry(people_amounts[vid_index], time_now, vid_index);
      }

      people_amounts = vid_processor->getQueuePeopleAmount();
      std::this_thread::sleep_for(std::chrono::seconds(pause));
    }
  }

  return 0;
}