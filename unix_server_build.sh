########################################################################
# DateTime: 2013-6-28
# Athor: sword
# Version: 1.0
# libz sh
########################################################################
#!/bin/sh
PROJ_DIR=$( cd $( dirname ${BASH_SOURCE[0]} ) && pwd )

dir_array=("libserver" "dfServer" "logicServer" "loginServer")
for name in ${dir_array[@]}
do
	cd ${PROJ_DIR}/${name}
	sh build_unix.sh
done

