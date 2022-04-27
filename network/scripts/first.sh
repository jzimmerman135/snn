BUILD=../build/apps
DATA=../datasets
CONFIG=./configs
ANALYSIS=../analysis

TRAIN=$DATA/first_train.data
TEST=$DATA/first_test.data
OUTPUT_FILENAME=first_output.out
CONFIG_FILE=$CONFIG/first_config.snn

OUTPUT_FILEPATH=../analysis/output/$OUTPUT_FILENAME

make clean all
cat $CONFIG_FILE > config.snn

if test -f "$OUTPUT_FILE"
then
    $BUILD/snn $TRAIN $TEST $OUTPUT_FILENAME
else
    echo "Model and output file '$OUTPUT_FILENAME' already made."
fi

python3 $ANALYSIS/analyze.py $OUTPUT_FILEPATH
