ARG R_VERSION
ARG OS_VERSION

FROM almalinux:${OS_VERSION}
ARG R_VERSION

# install required packages
RUN dnf -y update \
 && dnf -y upgrade \
 && dnf -y --allowerasing install \
        autoconf \
        automake \
        bash \
        bison \
        bzip2-devel \
        boost-devel \
        cairo \
        cairo-devel \
        cmake \
        curl \
        cyrus-sasl-devel \
        e2fsprogs \
        epel-release \
        file \
        g++ \
        gcc \
        gcc-gfortran \
        git \
        glibc-langpack-en \
        graphviz \
        icu \
        java-11-openjdk \
        java-11-openjdk-devel \
        lapack \
        libcurl-devel \
        libgomp \
        libICE-devel \
        libjpeg-devel \
        libsecret \
        libsecret-devel \
        libSM-devel \
        libtiff-devel \
        libtool \
        libxml2-devel \
        lz4-devel \
        make \
        mpfr-devel \
        openssl \
        openssl-devel \
        pango \
        pango-devel \
        perf \
        pcre-devel \
        pcre2-devel \
        procps \
        readline-devel \
        perl \
        subscription-manager \
        subversion \
        texlive \
        texlive-framed \
        texlive-latex-fonts \
        unixODBC \
        urw-fonts \
        wget \
        valgrind \
        unzip \
        which \
        poppler-cpp \
        qpdf-libs \
        snappy \
        xorg-x11-fonts-Type1 \
        xz-devel \
        unzip \
        zip \
  && dnf clean all

# install arrow, google profiler and other dependencies
RUN dnf -y groupinstall "Development Tools" \
    && dnf install -y epel-release || dnf install -y oracle-epel-release-el$(cut -d: -f5 /etc/system-release-cpe | cut -d. -f1) || dnf install -y https://dl.fedoraproject.org/pub/epel/epel-release-latest-$(cut -d: -f5 /etc/system-release-cpe | cut -d. -f1).noarch.rpm \
    && dnf install -y https://apache.jfrog.io/artifactory/arrow/almalinux/$(cut -d: -f5 /etc/system-release-cpe | cut -d. -f1)/apache-arrow-release-latest.rpm \
    && dnf config-manager --set-enabled epel \
    && dnf config-manager --set-enabled crb \
    && dnf install -y \
      arrow16-libs \
      arrow16-glib-libs \
      arrow-devel \
      arrow-glib-devel \
      arrow-dataset-devel \
      arrow-dataset-glib-devel \
      arrow-acero-devel \
      arrow-flight-devel \
      arrow-flight-glib-devel \
      arrow-flight-sql-devel \
      arrow-flight-sql-glib-devel \
      freetype-devel \
      fribidi-devel \
      gandiva-devel \
      gandiva-glib-devel \
      gperftools \
      gperftools-devel \
      htop \
      harfbuzz-devel \
      libgit2 \
      libgit2-devel \
      libjpeg-turbo-devel \
      libpng-devel \
      libsodium \
      libsodium-devel \
      libssh2 \
      libssh2-devel \
      libtiff-devel \
      parquet-devel \
      parquet-glib-devel \
      texinfo \
      texinfo-tex \
      # texlive-fonts-extra \
      texlive-latex-base-dev \
      texlive-latex-firstaid-dev \
      xclip

# install oneTBB library
RUN echo $'[oneAPI]\n\
name=Intel® oneAPI repository\n\
baseurl=https://yum.repos.intel.com/oneapi\n\
enabled=1\n\
gpgcheck=1\n\
gpgkey=https://yum.repos.intel.com/intel-gpg-keys/GPG-PUB-KEY-INTEL-SW-PRODUCTS.PUB\n\
repo_gpgcheck=1\n\n' > /etc/yum.repos.d/oneAPI.repo \
    && dnf -y update \
    && dnf -y upgrade --allowerasing --best \
    && dnf -y install \
        intel-oneapi-mkl \
        intel-oneapi-vtune \
        intel-oneapi-tbb-devel \
        intel-basekit \
    && dnf -y autoremove \
    && dnf clean all

# Set up local container variables useful for R
ENV PKG_CONFIG_PATH=/opt/intel/mkl/bin/pkgconfig:/usr/local/lib/pkgconfig:${PKG_CONFIG_PATH} \
    MKLROOT=/opt/intel/oneapi/mkl/latest \
    MKL_INTERFACE_LAYER=GNU,LP64 \
    MKL_THREADING_LAYER=GNU \
    MKL_DYNAMIC=FALSE \
    MKL_NUM_THREADS=8 \
    MKL_CBWR=AVX \
    OMP_NUM_THREADS=1 \
    OMP_DYNAMIC=FALSE \
    R_VERSION=${R_VERSION} \
    R_ENVIRON=/etc/R/Renviron.site \
    R_PROFILE=/etc/R/Rprofile.site \
    LC_ALL=en_US.UTF-8 \
    LANG=en_US.UTF-8 \
    TERM=xterm \
    TZ=UTC \
    R_INSTALL_TAR=/usr/bin/tar \
    R_BUILD_TAR=/usr/bin/tar \
    NOAWT=1 

RUN cd /tmp \
  && [[ ${R_VERSION} =~ ^([0-9]+)\.[0-9]+\.[0-9]+$ ]] \
  # && R_MAJOR_VERSION=${BASH_REMATCH[1]} \
  ## Download R source code
  && curl -O https://cran.rstudio.com/src/base/R-4/R-${R_VERSION}.tar.gz \
  && tar -xf R-${R_VERSION}.tar.gz
RUN cd /tmp/R-${R_VERSION} \
  # Configure link-time-optimization (LTO; see also --enable-lto option below)
  && printf "AR=gcc-ar\nRANLIB=gcc-ranlib\nNM=gcc-nm\n" >> config.site \
  && export MKL="-L${MKLROOT}/lib -lmkl_rt -Wl,--no-as-needed -lpthread -lm -ldl -flto=auto" \
  && ./configure \
      --enable-R-shlib \
      --enable-memory-profiling \
      --enable-lto \
      --with-blas="$MKL" \
      --with-lapack \
      --with-cairo \
      --with-x=no \
      --with-tcltk=no

RUN cd /tmp/R-${R_VERSION} \
  ## Build and install
  && make \
  && make install \
  && make clean \
  && R CMD javareconf \
  ## Clean-up R source directory
  && cd / \
  && rm -rf /tmp/R-${R_VERSION}* 

# configure and install R
COPY install_4.3.3.r install.r
RUN Rscript install.r

COPY install_arrow_4.3.3.r install_arrow.r
RUN Rscript install_arrow.r

CMD ["/bin/bash"]
WORKDIR /home/rmpuser
