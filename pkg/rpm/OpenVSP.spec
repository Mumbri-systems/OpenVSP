%global _duplicate_files_terminate_build 0
%global commit 5240ef210f41c5d6aeed0ba7687f6fab0ca0cafb
%global shortcommit %(c=%{commit}; echo ${c:0:7})
%global commitdate 20261012
%global min_version 3.55.0
%global py_static_pkgs degen_geom utilities openvsp_config vsp_airfoils
%global py_tools       CHARM AvlPy pyPMARC

Name:     OpenVSP
Version:  3.55.0
Release:  %autorelease
Summary:  A parametric aircraft geometry tool
License:  NASA-1.3
URL:      https://www.openvsp.org
Source:   https://github.com/OpenVSP/OpenVSP/archive/refs/tags/%{name}_%{version}.tar.gz
Source1:  openvsp.desktop
Patch1:   relative_install_paths1.patch
Patch2:   relative_install_paths2.patch
Patch3:   relative_install_paths3.patch
Patch4:   relative_install_paths4.patch
Patch5:   relative_install_paths5.patch
Patch6:   relative_install_paths6.patch
BuildRequires: libxml2-devel >= 2.12.10, gcc-c++ >= 14.2.1-2, openjpeg-devel >= 2.5.4-1, glm-devel >= 1.0.1, cminpack-devel >= 1.3.8, glew-devel >= 2.2.0, swig >= 4.3.0, doxygen >= 1.14.0-5, graphviz >= 12, texlive-scheme-basic
BuildRequires:  cmake >= 3.31, gcc, gcc-c++, rpm-build >= 4
BuildRequires: eigen3-devel
#fltk-fluid, fltk-devel,
BuildRequires: mesa-libGL-devel, mesa-libGLU-devel
#BuildRequires: pyproject-rpm-macros
#BuildRequires: python3-devel >= 3.13, conda >= 24
#BuildRequires: python3-numpy
#BuildRequires: python3-pytest
#BuildRequires: python3-matplotlib
BuildRequires: stepcode, stepcode-devel
BuildRequires: angelscript, angelscript-devel
BuildRequires: cpptest >= 2.0.0, cpptest-devel >= 2.0.0
BuildRequires: polyclipping2, polyclipping2-devel
BuildRequires: desktop-file-utils
BuildRequires: delabella, delabella-devel
BuildRequires: openabf-devel
Requires: hicolor-icon-theme

# The following libraries are currently bundled:
# Angelscript : addons required in build, not available in system package
# FLTK : build fails when using system Libraries
# Code-Eli : OpenVSP is the only user of this library.  It is too obscure
# to package
# exprparse : not currently available
# libIGES : modified for OpenVSP
# Pinocchio : not currently available
# Triangle : modified for OpenVSP
Provides: angelscript = 2.38
Provides: fltk = 1.4.5
Provides: Code-Eli = 0.3.6^20261005gitc64fbef
Provides: exprparse = 0.1.0^20250414git332e580
Provides: libiges = 0.3^20261012git886bf8b
Provides: Pinocchio = 1.0.0^20260718git86efdc0
Provides: Triangle = 1.6^20261005git8df5a02

#stepcode is only available on x86_64 architecture
ExclusiveArch: x86_64

%description
OpenVSP is a parametric aircraft geometry tool. OpenVSP allows the user to
create a 3D model of an aircraft defined by common engineering parameters.
This model can be processed into formats suitable for engineering analysis.

%package data
Summary: Data files for %{name}
BuildArch: noarch
Requires: %{name} = %{version}-%{release}

%description data
Data files for OpenVSP.

%prep
%autosetup -n OpenVSP-%{name}_%{version} -p1
pushd Libraries
rm libxml2-2*.tar.xz
rm glm-0.9*.zip
rm glew-2*.tgz
rm cminpack-1*.zip
rm eigen-5*.zip
rm stepcode*.zip
rm Clipper2*.zip
rm OpenABF*.zip
rm cpptest*.tar.gz
rm delabella*.zip


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
    -DVSP_USE_SYSTEM_CLIPPER2=true \
    -DVSP_USE_SYSTEM_CPPTEST=true \
    -DVSP_USE_SYSTEM_DELABELLA=true \
    -DVSP_USE_SYSTEM_OPENABF=true
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
desktop-file-install \
--dir=%{buildroot}%{_datadir}/applications \
%{SOURCE1}
install -Dm 644 %{_builddir}/OpenVSP-%{name}_%{version}/vspIcon.png %{buildroot}%{_datadir}/icons/hicolor/scalable/apps/openvsp.png
# Remove git placeholder files
find %{buildroot} -name ".keep" -delete
#chmod 755 %{buildroot}%{_prefix}/python/openvsp/conda-recipe/build.sh

%check
pushd src
%ctest --exclude-regex "PyTest|PySampleCodeTest|ScriptSampleCodeTest|AnalysisVSPAERO|PyDegenGeomTest"
#excluded tests seem to fail for non-relevant reasons

%files
%{_bindir}/vsp
%{_bindir}/vspscript
%{_bindir}/vspaero
%{_bindir}/vspaero_opt
%{_bindir}/vspviewer
%{_bindir}/vsploads
%{_bindir}/help/
%{_datadir}/doc/VSP/
%doc README.md
%license LICENSE

%files data
%{_datadir}/openvsp/
%{_datadir}/applications/openvsp.desktop
%{_datadir}/icons/hicolor/scalable/apps/openvsp.png

%changelog
%autochangelog
