
#$1 is path to ur local repo

#git checkout https://github.com/qemu/qemu.git $1
#cd $1
#git checkout -b v2.2.1 v2.2.1 or checkout sbs_encryption_2.2.1 branch
#apply patches for sbs encryption
#git am 000*.patch
#git submodules sync
#git submodules update --init

set -x
mkdir ~/sbs_qemu_build
cd ~/sbs_qemu_build
apt-get source qemu -y
dpkg-source -x qemu_2.0.0+dfsg-*.dsc
cd qemu-2.0.0+dfsg
uupdate -v 2.2.1 $1
cd ../qemu-2.2.1
export DEB_BUILD_OPTIONS="parallel=8"
#echo "" >debian/patches/series
sed -i 's/seccomp="yes"/seccomp="no"/' configure
debian/rules build
fakeroot debian/rules binary
