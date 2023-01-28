FROM ubuntu:18.04
ENV DEBIAN_FRONTEND noninteractive
MAINTAINER Islam A. Ali <islam.a.mustafa@gmail.com>

# ------------------------------------------------------------------------------------------
# Definitions
ENV OPENCV_VERSION 4.1.0
ENV OPENCV_DOWNLOAD_URL https://github.com/opencv/opencv/archive/$OPENCV_VERSION.zip
ENV OpenCV_DIR opencv-$OPENCV_VERSION
ENV EIGEN_VERSION 3.3.2
ENV EIGEN_DOWNLOAD_URL http://bitbucket.org/eigen/eigen/get/$EIGEN_VERSION.tar.gz

# ------------------------------------------------------------------------------------------
# [1] General Dependencies
RUN echo "[Dockerfile Info] Installing GENERAL Dependencies ......"
RUN apt-get update && apt-get install -y \
	 	build-essential \
		cmake \
		pkg-config \
		htop \
		gedit \
		wget \
		git \
		unzip \
		curl \
		software-properties-common
		

# ------------------------------------------------------------------------------------------                                 
# [2] OpenCV

RUN echo "[Dockerfile Info] Installing OPENCV Dependencies ......"
RUN apt-get update && apt-get install -y \
	build-essential \
	libgtk2.0-dev\
	libavcodec-dev\
	libavformat-dev\ 
	libswscale-dev \
	python3.8-dev \
	python3-numpy \
	libtbb2 \
	libtbb-dev
	
RUN apt-add-repository "deb http://security.ubuntu.com/ubuntu xenial-security main"
RUN apt-get update && apt-get install -y \
	libjasper1\
	libjasper-dev \
	libjpeg-dev \
	libpng-dev \
	libtiff5-dev \
	libjasper-dev \
	libdc1394-22-dev \
	libeigen3-dev \
	libtheora-dev \
	libvorbis-dev \
	libxvidcore-dev \
	libx264-dev \
	sphinx-common \
	libtbb-dev \
	yasm \
	libfaac-dev \
	libopencore-amrnb-dev \
	libopencore-amrwb-dev \
	libopenexr-dev \
	libgstreamer-plugins-base1.0-dev \
	libavutil-dev \
	libavfilter-dev \
	libboost-thread-dev \
	libavresample-dev

RUN echo "[Dockerfile Info] Installing OPENCV ......"

RUN mkdir ~/opencv_build && cd ~/opencv_build
	
RUN wget https://github.com/opencv/opencv/archive/${OPENCV_VERSION}.zip && \
	unzip ${OPENCV_VERSION}.zip && \
	wget https://github.com/opencv/opencv_contrib/archive/${OPENCV_VERSION}.zip -O ${OPENCV_VERSION}-contrib.zip  && \
	unzip ${OPENCV_VERSION}-contrib.zip && \
	mkdir opencv-${OPENCV_VERSION}/build && cd opencv-${OPENCV_VERSION}/build  && \
 	cmake -D BUILD_TIFF=ON \
			  -D BUILD_opencv_java=OFF \
			  -D WITH_CUDA=OFF \
			  -D ENABLE_AVX=ON \
			  -D WITH_OPENGL=ON \
			  -D WITH_OPENCL=ON \
			  -D WITH_IPP=ON \
			  -D WITH_TBB=ON \
			  -D WITH_EIGEN=ON \
			  -D WITH_V4L=ON \
			  -D BUILD_TESTS=OFF \
			  -D BUILD_PERF_TESTS=OFF \
			  -D CMAKE_BUILD_TYPE=RELEASE \
			  -D CMAKE_INSTALL_PREFIX=$(python3.8 -c "import sys; print(sys.prefix)") \
			  -D OPENCV_EXTRA_MODULES_PATH=/opencv_contrib-${OPENCV_VERSION}/modules \
			  -D OPENCV_GENERATE_PKGCONFIG=YES \
			  -D BUILD_opencv_xfeatures2d=ON \
			  -D OPENCV_ENABLE_NONFREE=ON .. && \
			  make -j8 install
	RUN ldconfig
	RUN pkg-config --modversion opencv4
	RUN rm /${OPENCV_VERSION}.zip
	RUN rm /${OPENCV_VERSION}-contrib.zip

	
# ------------------------------------------------------------------------------------------
# [3] Pangolin
RUN echo "[Dockerfile Info] Installing PNGOLIN Dependencies ......"
RUN apt-get update && apt-get install -y \
		libgl1-mesa-dev \
		libglew-dev \
		libpython2.7-dev \
		ffmpeg libavcodec-dev libavutil-dev libavformat-dev libswscale-dev libavdevice-dev \
		libdc1394-22-dev libraw1394-dev \		
		libjpeg-dev libpng12-dev libtiff5-dev libopenexr-dev

RUN echo "[Dockerfile Info] Installing PNGOLIN ......"
RUN mkdir -p ~/pangolin && \
		cd ~/pangolin && \
		git clone https://github.com/stevenlovegrove/Pangolin.git && \
		cd Pangolin && \
		mkdir build && \
		cd build && \
		cmake .. && \
		cmake --build .	


# ------------------------------------------------------------------------------------------
# [4] Eigen3
RUN echo "[Dockerfile Info] Installing EIGEN3 Dependencies ......"
# none 
RUN echo "[Dockerfile Info] Installing EIGEN3 ......"
RUN mkdir -p ~/eigen3 && \
	cd ~/eigen3 && \
	git clone https://github.com/libigl/eigen.git && \
	cd eigen && \
	mkdir build_dir && \
	cd build_dir && \
  	cmake ../ && \
  	make install


# # ------------------------------------------------------------------------------------------
# [5] SLAM Datasets Characterization System

# RUN apt-get update && apt-get install -y \
# 	libpcap-dev \
# 	libssl-dev

WORKDIR ../../

RUN echo "[Dockerfile Info] Installing DSChar here ......"
RUN mkdir -p ds_char
RUN cd ds_char
COPY ./ ./ds_char/code
RUN	cd ds_char/code/script && \
		chmod +x build_sys.sh && \
		./build_sys.sh   
		
		
		
# # ------------------------------------------------------------------------------------------
# install editor
RUN apt-get install nano
RUN apt-get install ne -y

# # ############################################################################################
# # ############################################################################################
# # ############################################################################################
# # ============================================================================================
# # -----------------------------------------------------------------------------------------
# # The following part is adapted partially from : https://github.com/jupemara/x11vnc-docker
# # -----------------------------------------------------------------------------------------
# # ============================================================================================

# EXPOSE 5900
# ENV \
#   DEBIAN_FRONTEND="nonintractive" \
#   X11VNC_PASSWORD="password"
# RUN apt-get update -y
# RUN apt-get install -y xvfb x11vnc fluxbox
# ADD ./entrypoint.sh /opt/entrypoint.sh
# ENTRYPOINT /opt/entrypoint.sh
