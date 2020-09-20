cmake_minimum_required(VERSION 3.16)
project(Tarea1_SistemasOperativos C)
set(CMAKE_C_STANDARD 99)
add_executable(Tarea1_SistemasOperativos main.c SocketManagement/clientsocket.h SocketManagement/clientsocket.c ImageProcessing/imagproc.h ImageProcessing/imagproc.c FileManagement/dirmag.h FileManagement/dirmag.c SocketManagement/clientinformation.h SocketManagement/clientinformation.c ConfigManagement/configproc.h ConfigManagement/configproc.c SocketManagement/messagemag.c SocketManagement/messagemag.h SocketManagement/hostsocket.c SocketManagement/hostsocket.h)

target_link_libraries(Tarea1_SistemasOperativos  png)
target_link_libraries(Tarea1_SistemasOperativos  jpeg)
target_link_libraries(Tarea1_SistemasOperativos  pthread)
