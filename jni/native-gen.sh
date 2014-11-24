#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

JAVAH=javah

OUT_DIR=${DIR}/src/headers/generated
CP=${DIR}/../src/main/java/

CLASSES="org.luwrain.os.speech.CarbonTts org.luwrain.os.Terminal"

#for class in $CLASSES ; do
echo Executing: $JAVAH -classpath $CP -d $OUT_DIR $class
$JAVAH -classpath $CP -d $OUT_DIR $CLASSES
#done
