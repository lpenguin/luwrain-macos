#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

JAVAH=javah

OUT_DIR=${DIR}/src/headers/generated
CP=${DIR}/../src/main/java/

CLASSES="org.luwrain.macos.speech.CarbonTts org.luwrain.macos.term.Terminal"

#for class in $CLASSES ; do
echo Executing: $JAVAH -classpath $CP -d $OUT_DIR $class
$JAVAH -classpath $CP -d $OUT_DIR $CLASSES
#done
