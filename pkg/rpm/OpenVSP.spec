%global _duplicate_files_terminate_build 0
%global commit 5c366ec7530fdd6e64deea3f5669bba0c50f41ee
%global shortcommit %(c=%{commit}; echo ${c:0:7})
%global commitdate 20260515
%global min_version 3.50.3

Name:     OpenVSP
Version:  3.50.3
Release:  %autorelease
Summary:  A parametric aircraft geometry tool
License:  NASA-1.3
URL:      https://www.openvsp.org
Source:   https://github.com/OpenVSP/OpenVSP/archive/refs/tags/%{name}_%{version}.tar.gz
Source1:  openvsp.desktop
Patch0:   find_shared_libs.patch
Patch1:   relative_install_paths1.patch
Patch2:   relative_install_paths2.patch
Patch3:   relative_install_paths3.patch
Patch4:   relative_install_paths4.patch
Patch5:   relative_install_paths5.patch
Patch6:   update_stepcode_pointers.patch
Patch7:   code_eli_cmake_minimum.patch
BuildRequires: libxml2-devel >= 2.12.10, gcc-c++ >= 14.2.1-2, openjpeg-devel >= 2.5.4-1, glm-devel >= 1.0.1, cminpack-devel >= 1.3.8, glew-devel >= 2.2.0, swig >= 4.3.0, doxygen >= 1.14.0-5, graphviz >= 12, texlive-scheme-basic, python3-devel >= 3.13, conda >= 24
BuildRequires:  cmake >= 3.31, gcc, gcc-c++, rpm-build >= 4
BuildRequires: eigen3-devel
#fltk-fluid, fltk-devel,
BuildRequires: mesa-libGL-devel, mesa-libGLU-devel
BuildRequires: python3-numpy
BuildRequires: stepcode, stepcode-devel
BuildRequires: angelscript, angelscript-devel

# The following libraries are currently bundled:
# Angelscript : addons required in build, not available in system package
# FLTK : build fails when using system Libraries
# CPPTEST : build fails when using system Libraries
# Clipper2 : in the process of being packaged for fedora
# Code-Eli : OpenVSP is the only user of this library.  It is too obscure
# to package
# delabella : in the process of being packaged for fedora
# exprparse : not currently available
# libIGES : modified for OpenVSP
# OpenABF : in the process of being packaged for fedora
# Pinocchio : not currently available
# Triangle : modified for OpenVSP

#stepcode is only available on x86_64 architecture
ExclusiveArch: x86_64

%description
OpenVSP is a parametric aircraft geometry tool. OpenVSP allows the user to
create a 3D model of an aircraft defined by common engineering parameters.
This model can be processed into formats suitable for engineering analysis.

%prep
%autosetup -n OpenVSP-%{name}_%{version} -p1

%build
# build third-party libraries
pushd Libraries
%cmake \
    -DCMAKE_BUILD_TYPE=Release \
    -DVSP_USE_SYSTEM_LIBXML2=true \
    -DVSP_USE_SYSTEM_FLTK=false \
    -DVSP_USE_SYSTEM_GLM=true \
    -DVSP_USE_SYSTEM_GLEW=true \
    -DVSP_USE_SYSTEM_CMINPACK=true \
    -DVSP_USE_SYSTEM_EIGEN=true \
    -DVSP_USE_SYSTEM_STEPCODE=true \
    -DVSP_USE_SYSTEM_ANGELSCRIPT=false \
    -DVSP_USE_SYSTEM_CPPTEST=false
%cmake_build
popd

# build main
pushd src
%cmake \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_SHARED_LIBS=OFF \
    -DVSP_INSTALL_TO_SYSTEM=ON \
    -DVSP_LIBRARY_PATH=%{_builddir}/OpenVSP-%{name}_%{version}/Libraries/redhat-linux-build
%cmake_build

%install
pushd src
%cmake_install
install -Dm 644 %{_sourcedir}/openvsp.desktop %{buildroot}%{_datadir}/applications/openvsp.desktop
install -Dm 644 %{_builddir}/OpenVSP-%{name}_%{version}/vspIcon.png %{buildroot}%{_datadir}/icons/hicolor/scalable/apps/openvsp.png
# Remove git placeholder files
find %{buildroot} -name ".keep" -delete
chmod 755 %{buildroot}%{_prefix}/python/openvsp/conda-recipe/build.sh

%files
%{_bindir}/vsp
%{_bindir}/vspscript
%{_bindir}/vspaero
%{_bindir}/vspaero_opt
%{_bindir}/vspviewer
%{_bindir}/vsploads
%{_datadir}/openvsp/
%{_datadir}/applications/openvsp.desktop
%{_datadir}/icons/hicolor/scalable/apps/openvsp.png
%{_prefix}/help/
%{_prefix}/python/
%{_datadir}/doc/VSP/
%doc README.md
%license LICENSE

%changelog
%autochangelog
