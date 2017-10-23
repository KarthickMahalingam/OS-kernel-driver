root@karthick-VirtualBox:/home/karthick/Project/OSD# make
make -C /lib/modules/`uname -r`/build SUBDIRS=`pwd` modules
make[1]: Entering directory `/usr/src/linux-4.1.33'
  CC [M]  /home/karthick/Project/OSD/fuses.o
/home/karthick/Project/OSD/fuses.c:34:5: warning: initialization from incompatible pointer type [enabled by default]
/home/karthick/Project/OSD/fuses.c:34:5: warning: (near initialization for ‘fops.read’) [enabled by default]
/home/karthick/Project/OSD/fuses.c:36:5: warning: initialization from incompatible pointer type [enabled by default]
/home/karthick/Project/OSD/fuses.c:36:5: warning: (near initialization for ‘fops.write’) [enabled by default]
/home/karthick/Project/OSD/fuses.c: In function ‘init_module’:
/home/karthick/Project/OSD/fuses.c:48:5: warning: ISO C90 forbids mixed declarations and code [-Wdeclaration-after-statement]
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/karthick/Project/OSD/fuses.mod.o
  LD [M]  /home/karthick/Project/OSD/fuses.ko
make[1]: Leaving directory `/usr/src/linux-4.1.33'
root@karthick-VirtualBox:/home/karthick/Project/OSD# 
root@karthick-VirtualBox:/home/karthick/Project/OSD# mknod /dev/myDev c 89 1
root@karthick-VirtualBox:/home/karthick/Project/OSD# chmod a+r+w /dev/myDev
root@karthick-VirtualBox:/home/karthick/Project/OSD# insmod fuses.ko
root@karthick-VirtualBox:/home/karthick/Project/OSD# echo "Karthick"> /dev/myDev
root@karthick-VirtualBox:/home/karthick/Project/OSD# cat /dev/myDev

kcihtraKroot@karthick-VirtualBox:/home/karthick/Project/OSD# rmmod fuses
root@karthick-VirtualBox:/home/karthick/Project/OSD# dmesg | tail
[ 1600.895739] ISO 9660 Extensions: RRIP_1991A
[ 2191.805069] fuses: module license '@Karthick2016' taints kernel.
[ 2191.805074] Disabling lock debugging due to kernel taint
[ 2191.806043] device registered 
[ 2542.570411] device registered 
[ 2651.051442] device registered 
[ 2658.462603] device opened 1 times 
[ 2658.462620] device closed 
[ 2663.259536] device opened 2 times 
[ 2663.259553] device closed 
root@karthick-VirtualBox:/home/karthick/Project/OSD# rm /dev/myDev
