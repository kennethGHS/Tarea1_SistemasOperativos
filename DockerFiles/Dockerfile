FROM ubuntu:20.04
# LABEL about the custom image
LABEL maintainer="khken21@gmail.com"
LABEL version="0.1"
LABEL description="Operative Systems docker"
ARG DEBIAN_FRONTEND=noninteractive
EXPOSE 8080
RUN apt-get update && apt-get install -y \
	build-essential \
	cmake	\
	git \
	libgtk2.0-dev \
	pkg-config \
	libavcodec-dev \
	libavformat-dev \
	libswscale-dev\
	libtbb2 \
	libtbb-dev \
	libjpeg-dev \
	libpng-dev \
	libtiff-dev \
	libeigen3-dev \
	liblapack-dev \
	libatlas-base-dev \
	libgomp1 \
	gcc 
COPY /Tarea1-SistemasOperativos /app
WORKDIR /app
RUN 	mkdir build-dir && \
	cd build-dir && \
	cmake .. && \
	make &&\
	chmod +x Tarea1_SistemasOperativos 
WORKDIR /app/build-dir
CMD ["./Tarea1_SistemasOperativos"]

