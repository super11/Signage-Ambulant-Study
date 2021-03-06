%define __libtoolize :

Name: 	 ambulant
Summary: A SMIL library
Version: 2.6
Release: 1

License: 	LGPL
Group: System Environment/Libraries
Source: 	ambulant-%{version}.tar.gz
BuildRoot:	%{_tmppath}/%{name}-%{version}-root

%description
An SMIL library based on libart.


%package devel
Summary: Libraries and include files for developing with libambulant
Group: Development/Libraries
Requires:	%{name} = %{version}-%{release}

%description devel
This package provides the necessary development libraries and include
files to allow you to develop with libambulant.

%prep
%setup -q -n ambulant-%{version}
%configure --with-sdl=no --with-ffmpeg=no
make

%install
rm -rf $RPM_BUILD_ROOT
%makeinstall
rm -f $RPM_BUILD_ROOT%{_libdir}/*.la

%clean
rm -rf $RPM_BUILD_ROOT

%post
/sbin/ldconfig

%postun
/sbin/ldconfig

%files
%defattr(-, root, root)
%doc AUTHORS COPYING ChangeLog NEWS README
%{_bindir}/AmbulantPlayer
%{_libdir}/*.so.*
%{_mandir}/man1/*
%{_datadir}/ambulant
%{_datadir}/locale

%files devel
%defattr(-, root, root)
%{_libdir}/libambulant*.so
%{_libdir}/libambulant*.a
%{_libdir}/ambulant
%{_includedir}/ambulant
%{_libdir}/pkgconfig/libambulant.pc

%changelog
* Thu Aug 04 2005 Christian Schaller <uraeus@gnome.org>
- created this thing

