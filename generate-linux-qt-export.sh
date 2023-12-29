#!/bin/bash
QtPath="${1%\/}"
echo "path: $QtPath"
export QTDIR=$1
export LD_LIBRARY_PATH=$QTDIR/lib:$LD_LIBRARY_PATH
export PATH=$QTDIR/bin:$PATH
export INCLUDE=$QTDIR/include:$INCLUDE
export QT_PLUGIN_PATH=$QTDIR/plugins:$QT_PLUGIN_PATH
