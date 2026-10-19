#include <iostream>

#include <QCoreApplication>


int main(int argc, char *argv[])
{
  //QCoreApplication a(argc, argv);
  //return a.exec();
  size_t produse_cnt = 0, device_cnt = 0, buffer_cap = 0;
  if (!(std::cin >> produse_cnt >> device_cnt >> buffer_cap))
  {
      std::cerr << "Incorrect enter argument: enter produse count, device count and buffer capacity" << std::endl;
  }
}
