#include <vector>
#include <limits>
#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

void drawSomething(int width, int height, int margin, const std::string &windowName)
{

  cv::Mat image = cv::Mat(height, width, CV_8UC3, cv::Scalar(255, 255, 255));

  // draw the x and y axis
  cv::line(image, cv::Point(margin, margin), cv::Point(margin, height - margin), cv::Scalar(0, 0, 0), 2);                  // y axis
  cv::line(image, cv::Point(margin, height - margin), cv::Point(width - margin, height - margin), cv::Scalar(0, 0, 0), 2); // x axis

  // show the image
  cv::imshow(windowName, image);
  cv::waitKey(0);
  cv::destroyAllWindows();
}

int main()
{

  drawSomething(1300, 480, 10, "p, q, r (radiant)");
  return 0;
}