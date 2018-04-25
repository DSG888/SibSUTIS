#!/usr/bin/env bash

#	9. Написать скрипт, копирующий, удаляющий или переименовывающий файлы в текущем
#	каталоге в соответствии с маской. Выбор операции осуществляется с использованием
#	опций. Маска вводится как параметр соответствующей опции.

while getopts r:cm OPTION ; do
	case $OPTION in
	r)
		if [ -n "${OPTARG}" ] ; then
			FILE=${OPTARG}
		fi
		
		if [ -e $FILE ] ; then
			rm $FILE
		fi
		;;
	c)
		if [ -n "${OPTARG}" ] ; then
			C1FILE=${OPTARG}
		fi
		
		echo "Enter the name of the copyed file: "
		read C2FILE
		cp $C1FILE $C2FILE
		;;
	m)
		if [ -n "${OPTARG}" ] ; then
			M1FILE=${OPTARG}
		fi
		
		echo "Enter the new name of the renamed file: "
		read M2FILE
		mv $M1FILE $M2FILE
		;;
	esac
done
