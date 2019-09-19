Name:           mqm-elf-util
Version:        1.0
Release:        0%{?dist}
Summary:        mqm elf utilities

Group:          Applications/System
License:        DBAG
Url:            http://krpan

Source0:        mqm-elf-util.tar
#Patch:          mqm-elf-util.patch
BuildRoot:      %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

BuildArch:      x86_64

Provides: libmsggcat.so libsogen.so libmqutil.so
#BuildRequires:  perl
#Requires:       
AutoReqProv: no

%define install_home opt/dbag

%description
mqm elf utilities

%prep 

%setup -q

# ------------------------------------------------------------------------------
# PATCH
# ------------------------------------------------------------------------------
#%patch -p1 -b .buildroot

# ------------------------------------------------------------------------------
# BUILD
# ------------------------------------------------------------------------------
%build

mkdir -p %{buildroot}/%{install_home}/bin
mkdir -p %{buildroot}/%{install_home}/lib64
cp  bin/*   %{buildroot}/%{install_home}/bin
cp  lib64/* %{buildroot}/%{install_home}/lib64

#rm -f %{buildroot}/%{install_home}/bin/*.buildroot
#rm -f %{buildroot}/%{install_home}/lib64/*.buildroot

# ------------------------------------------------------------------------------
# INSTALL
# ------------------------------------------------------------------------------
%install

install -o root -g root -m 0755 -d /%{install_home}
install -o root -g root -m 2755 -d /%{install_home}/bin
install -o root -g root -m 2755 -d /%{install_home}/lib64
install -o mqm  -g mqm  -m 2755 -t /%{install_home}/lib64 lib64/libmqutil.so 
install -o mqm  -g mqm  -m 2755 -t /%{install_home}/lib64 lib64/libmsgcat.so
install -o mqm  -g mqm  -m 2755 -t /%{install_home}/lib64 lib64/libsogen.so
install -o mqm  -g mqm  -m 2755 -t /%{install_home}/bin   bin/catalogrc
install -o mqm  -g mqm  -m 2755 -t /%{install_home}/bin   bin/cleanq
install -o mqm  -g mqm  -m 2755 -t /%{install_home}/bin   bin/mqLogEv

#rm -f %{buildroot}/%{hobbit_home}/ext/*.buildroot
#rm -f %{buildroot}/%{hobbit_home}/etc/*.buildroot

%check


# ------------------------------------------------------------------------------
# CLEAN
# ------------------------------------------------------------------------------
%clean
rm -r %{buildroot}


%files
#%defattr(754,bbrother,mqm,-)
#/%{install_home}/bin
#/%{install_home}/lib64
/%{install_home}/bin/catalogrc
/%{install_home}/bin/cleanq
/%{install_home}/bin/mqLogEv
/%{install_home}/lib64/libmqutil.so
/%{install_home}/lib64/libmsgcat.so
/%{install_home}/lib64/libsogen.so

#%attr(644,bbrother,mqm) %{hobbit_home}/etc/*
%doc


%changelog
